<?php

# ====================================================================
# 
# Balance Class Definition;
# 
# 
# Published 2005 by Charles Maier Associates Limited for internal use;
# 
# --------------------------------------------------------------------

class Balance 
{

# ====================================================================
# Public Variables;
# --------------------------------------------------------------------


# ====================================================================
# Private Variables;
# --------------------------------------------------------------------

	private $prev;
	private $next;
	private $index;
	private $count;
	private static $stamp = "H:i:s D d M Y T";
	private static $style = "table { table-layout: fixed; border: solid 1pt silver; border-collapse: separate; border-spacing: 0px; padding: 5px; background: transparent; font: normal 8pt verdana; } th { padding: 0px 5px 0px 5px; font: normal 8pt verdana; } td { padding: 0px 5px 0px 5px; font: normal 8pt verdana; } th.tree, td.tree { width: 200px; text-align: left; font: normal 8pt verdana; } th.id, td.id { width: 055px; text-align: left; } th.date, td.date { width: 080px; text-align: left; } th.type, td.type { width: 050px; text-align: left; } th.code, td.code { width: 100px; text-align: left; } th.name, td.name { text-align: left; } th.count, td.count { width: 050px; text-align: right; } th.units, td.units { width: 075px; text-align: left; } th.price, td.price { width: 075px; text-align: right; } th.value, td.value { width: 075px; text-align: right; } th.tax, td.tax { width: 075px; text-align: right; } th.total, td.total { width: 100px; text-align: right; } th.receipt, td.receipt { width: 100px; text-align: right; } th.payment, td.payment { width: 100px; text-align: right; color: maroon; } th.turnover, td.turnover { width: 100px; text-align: right; } th.balance, td.balance { width: 100px; text-align: right; } th.summary, td.summary { text-align: right; } span.event { font: normal; color: navy; } span.error { font: normal; color: maroon; }";
	private static $debug = MESSAGE_NONE;
	private static $trace = MESSAGE_NONE;
	private static $db = NULL;

# ====================================================================
#
# Balance Debug Property;
#
# Enable or disable Debug messages; Debug messages appear prior to
# every error return;
#
# --------------------------------------------------------------------

	public function GetDebug () 
	{
		return (Balance::$debug);
	}
	public function SetDebug ($Debug) 
	{
		if (!is_integer($Debug)) 
		{
			printf ("Account: Can't set Debug to '$Debug': Property is integer.\n");
			return ($this);
		}
		Balance::$debug = $Debug;
		return ($this);
	}

# ====================================================================
#
# Balance Trace Property;
#
# Enable or disable Trace messages; Trace messages appear prior to
# every database query; 
#
# --------------------------------------------------------------------

	public function GetTrace () 
	{
		return (Balance::$debug);
	}
	public function SetTrace ($Trace) 
	{
		if (!is_integer($Trace)) 
		{
			printf ("Account: Can't set Trace to '$Trace': Property is integer.\n");
			return ($this);
		}
		Balance::$trace = $Trace;
		return ($this);
	}

# ====================================================================
#
# Balance Components Method;
#
# Return an associative array of component Account codes ordered by 
# Account number; 
#
# --------------------------------------------------------------------

	public function Components ($AccountID) 
	{
		$components = array ();
		if (!is_integer($AccountID)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't fetch components of Account ($AccountID)", "Key must be integer");
			return (false);
		}
		$query = "SELECT ID, ControlID, Code FROM Account WHERE ControlID=($AccountID)";
		Balance::Event (__METHOD__, __LINE__, $query);
		if (!$accounts = mysql_query($query, Balance::$db)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't fetch components of Account ($AccountID)", mysql_error(Balance::$db));
			return ($components);
		}
		while ($account = mysql_fetch_object($accounts)) 
		{
			$components[$account->ID]= $account->Code;
			$components += Balance::Components ((int)($account->ID));
		}
		return ($components);
	}

# ====================================================================
# 
# Balance Transactions Method;
# 
# Return Transactions for one Account ordered by date, ommitting
# rarely used fields;
# 
# --------------------------------------------------------------------

	public function Transactions ($AccountID) 
	{
		if (!is_integer($AccountID)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't fetch Transactions for Account ($AccountID)", "Key must be integer");
			return (false);
		}
		$query = "DROP TABLE IF EXISTS A${AccountID}";
		Balance::Event (__METHOD__, __LINE__, $query);
		if (!mysql_query($query, Balance::$db)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't collect Payments for Account ($AccountID)", mysql_error(Balance::$db));
			return (false);
		}
		$query = "CREATE TEMPORARY TABLE A${AccountID} SELECT Transaction.ID AS ID, Account.ID AS AccountID, Account.Code AS AccountCode, Transaction.Date, Transaction.Note, Transaction.Count, Transaction.Units, Transaction.Price, Transaction.Value, Transaction.TaxRate, Transaction.Tax, Transaction.Total, Transaction.Payment, Transaction.Receipt, Transaction.Balance, Transaction.Total AS Payments, (0.00) AS Receipts FROM Account JOIN Transaction ON Account.ID=ReceiptID WHERE PaymentID=($AccountID)";
		Balance::Event (__METHOD__, __LINE__, $query);
		if (!mysql_query($query, Balance::$db)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't collect Payments for Account '($AccountID)", mysql_error(Balance::$db));
			return (false);
		}
		$query = "INSERT INTO A${AccountID} SELECT Transaction.ID AS ID, Account.ID AS AccountID, Account.Code AS AccountCode, Transaction.Date, Transaction.Note, Transaction.Count, Transaction.Units, Transaction.Price, Transaction.Value, Transaction.TaxRate, Transaction.Tax, Transaction.Total, Transaction.Payment, Transaction.Receipt, Transaction.Balance, (0.00) AS Payments, Transaction.Total AS Receipts FROM Account JOIN Transaction ON Account.ID=PaymentID WHERE ReceiptID=($AccountID)";
		Balance::Event (__METHOD__, __LINE__, $query);
		if (!mysql_query($query, Balance::$db)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't collect Receipts for Account ($AccountID)", mysql_error(Balance::$db));
			return (false);
		}
		$query = "SELECT * FROM A${AccountID} ORDER BY Date";
		Balance::Event (__METHOD__, __LINE__, $query);
		if (!$table = mysql_query($query, Balance::$db)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't fetch Transactions for Account ($AccountID)'", mysql_error(Balance::$db));
			return (false);
		}
		return ($table);
	}

# ====================================================================
#
# Balance Collect Method;
#
# Recursively zero component Account balances using contra entries;
#
# --------------------------------------------------------------------

	public function Collect ($AccountID) 
	{
		if (!is_integer($AccountID)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't collect Transactions for Account ($AccountID)", "Key must be integer");
			return (false);
		}
		$query = "SELECT ID, ControlID, Code, Name FROM Account WHERE ControlID=($AccountID)";
		Balance::Event (__METHOD__, __LINE__, $query);
		if (!$accounts = mysql_query($query, Balance::$db)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't collect Transactions for Account ($AccountID)", mysql_error(Balance::$db));
			return (false);
		}
		while ($account = mysql_fetch_object($accounts)) 
		{
			$receipts = Balance::Receipts((int)($account->ID));
			$payments = Balance::Payments((int)($account->ID));
			Balance::Collect((int)($account->ID));

#
#			$query = "UPDATE Transaction SET ReceiptID=($account->ControlID) WHERE ReceiptID=($account->ID)";
#			Balance::Event (__METHOD__, __LINE__,$query);
#			if (!mysql_query($query, Balance::$db)) 
#			{
#				Balance::Error (__METHOD__, __LINE__,"Can't collect Receipts for Account '$account->ID'", mysql_error(Balance::$db));
#				return (false);
#			}
#			$query = "UPDATE Transaction SET PaymentID=($account->ControlID) WHERE PaymentID=($account->ID)";
#			Balance::Event (__METHOD__, __LINE__,$query);
#			if (!mysql_query($query, Balance::$db)) 
#			{
#				Balance::Error (__METHOD__, __LINE__,"Can't collect Payments for Account '$account->ID'", mysql_error(Balance::$db));
#				return (false);
#			}
#

			if ($receipts > $payments) 
			{
				$balance = $receipts - $payments;
				$query = "INSERT INTO Transaction (ContactID,ProjectID,PaymentID,ReceiptID,Type,InternalCode,ExternalCode,Note,Count,Units,Price,Local,Value,TaxRate,Tax,Total,Payment,Receipt,Balance,Date,Paid,Due,Created,Updated) VALUES ((1),(1),($account->ID),($account->ControlID),'NT','$account->Code','AUTO','$account->Name',(1),'Transfer',($balance),(1.000),($balance),(0.000),(0.00),($balance),(0.00),(0.00),(0.00),NOW(),NOW(),NULL,NOW(),NOW())";
				Balance::Event (__METHOD__, __LINE__, $query);
				if (!mysql_query($query, Balance::$db)) 
				{
					Balance::Error (__METHOD__, __LINE__, "Can't counter Receipts for Account '$account->ID'", mysql_error(Balance::$db));
					return (false);
				}
			}
			if ($receipts < $payments) 
			{
				$balance = $payments - $receipts;
				$query = "INSERT INTO Transaction (ContactID,ProjectID,PaymentID,ReceiptID,Type,InternalCode,ExternalCode,Note,Count,Units,Price,Local,Value,TaxRate,Tax,Total,Payment,Receipt,Balance,Date,Paid,Due,Created,Updated) VALUES ((1),(1),($account->ControlID),($account->ID),'NT','$account->Code','AUTO','$account->Name',(1),'Transfer',($balance),(1.000),($balance),(0.000),(0.00),($balance),(0.00),(0.00),(0.00),NOW(),NOW(),NULL,NOW(),NOW())";
				Balance::Event (__METHOD__, __LINE__, $query);
				if (!mysql_query($query, Balance::$db)) 
				{
					Balance::Error (__METHOD__, __LINE__, "Can't counter Payments for Account '$account->ID'", mysql_error(Balance::$db));
					return (false);
				}
			}
		}
		return (true);
	}

# ====================================================================
#
# Balance Receipts Method;
#
# Compute and return total Receipts for one Account;
#
# --------------------------------------------------------------------

	public function Receipts ($AccountID, $Field) 
	{
		if (!is_integer($AccountID)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't compute Receipts for Account ($AccountID)", "Key must be integer.");
			return (false);
		}
		$query = "SELECT SUM($Field) AS Receipts FROM Transaction WHERE ReceiptID=($AccountID)";
		Balance::Event (__METHOD__, __LINE__, $query);
		if (!$table = mysql_query($query, Balance::$db)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't compute Receipts for Account ($AccountID)", mysql_error(Balance::$db));
			return (false);
		}
		if (!$field = mysql_fetch_object($table)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't compute Receipts for Account ($AccountID)", "None exist.");
			return (false);
		}
		return ((float)($field->Receipts));
	}

# ====================================================================
#
# Balance Payments Method;
#
# Compute and return total Payments for one Account;
#
# --------------------------------------------------------------------

	public function Payments ($AccountID, $Field) 
	{
		if (!is_integer($AccountID)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't compute Payments for Account ($AccountID)", "Key must be integer.");
			return (false);
		}
		$query = "SELECT SUM($Field) AS Payments FROM Transaction WHERE PaymentID=($AccountID)";
		Balance::Event (__METHOD__, __LINE__, $query);
		if (!$table = mysql_query($query, Balance::$db)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't compute Payments for Account ($AccountID)", mysql_error(Balance::$db));
			return (false);
		}
		if (!$field = mysql_fetch_object($table)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't compute Payments for Account ($AccountID)", "None exist.");
			return (false);
		}
		return ((float)($field->Payments));
	}

# ====================================================================
#
# Balance Balance Method;
#
# Compute Receipts, Payments, Turnover and Balance for one Account
# and update the Account record; return true on success and false on
# failure;
#
# --------------------------------------------------------------------

	public function Balance ($AccountID) 
	{
		if (!is_integer($AccountID)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't update Balance for Account ($AccountID)", "Key must be integer.");
			return (false);
		}
		$Receipts = Balance::Receipts($AccountID, "Total");
		$Payments = Balance::Payments($AccountID, "Total");
		$Increase = ($Receipts > $Payments)? (($Receipts)-($Payments)): ((float)(0));
		$Decrease = ($Payments > $Receipts)? (($Payments)-($Receipts)): ((float)(0));
		$query = "UPDATE Account SET Receipts=($Receipts),Payments=($Payments),Increase=($Increase),Decrease=($Decrease),Turnover=(($Receipts)+($Payments)),Balance=(($Receipts)-($Payments)) WHERE ID=($AccountID)";
		Balance::Event (__METHOD__, __LINE__, $query);
		if (!mysql_query($query, Balance::$db)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't update Balance for Account ($AccountID)", mysql_error(Balance::$db));
			return (false);
		}
		return (true);
	}

# ====================================================================
#
# Balance Compile Method;
#
# Compute Receipts, Payments, Turnover and Balance for all accounts
# and update the Account table; return true on success and false on
# failure;
#
# --------------------------------------------------------------------

	public function Compile () 
	{
		$query = "DROP TABLE IF EXISTS Balance";
		Balance::Event (__METHOD__, __LINE__, $query);
		if (!mysql_query($query, Balance::$db)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't compute Account Receipts", mysql_error(Balance::$db));
			return (false);
		}
		Balance::Event (__METHOD__, __LINE__, $query);
		$query = "CREATE TEMPORARY TABLE Balance SELECT ReceiptID, SUM(Total) As Receipts FROM Transaction GROUP BY ReceiptID ORDER BY ReceiptID";
		Balance::Event (__METHOD__, __LINE__, $query);
		if (!mysql_query($query, Balance::$db)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't compute Account Receipts", mysql_error(Balance::$db));
			return (false);
		}
		$query = "UPDATE Account LEFT JOIN Balance ON Account.ID=Balance.ReceiptID SET Account.Receipts=Balance.Receipts";
		Balance::Event (__METHOD__, __LINE__, $query);
		if (!mysql_query($query, Balance::$db)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't update Account Receipts", mysql_error(Balance::$db));
			return (false);
		}
		$query = "DROP TABLE IF EXISTS Balance";
		Balance::Event (__METHOD__, __LINE__, $query);
		if (!mysql_query($query, Balance::$db)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't compute Account Payments", mysql_error(Balance::$db));
			return (false);
		}
		$query = "CREATE TEMPORARY TABLE Balance SELECT PaymentID, SUM(Total) As Payments FROM Transaction GROUP BY PaymentID ORDER BY PaymentID";
		Balance::Event (__METHOD__, __LINE__, $query);
		if (!mysql_query($query, Balance::$db)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't compute Account Payments", mysql_error(Balance::$db));
			return (false);
		}
		$query = "UPDATE Account LEFT JOIN Balance ON Account.ID=Balance.PaymentID SET Account.Payments=Balance.Payments";
		Balance::Event (__METHOD__, __LINE__, $query);
		if (!mysql_query($query, Balance::$db)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't compute Account Payments", mysql_error(Balance::$db));
			return (false);
		}
		$query = "UPDATE Account SET Turnover=((Receipts)+(Payments)),Balance=((Receipts)-(Payments))";
		Balance::Event (__METHOD__, __LINE__, $query);
		if (!mysql_query($query, Balance::$db)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't update Account balances", mysql_error(Balance::$db));
			return (false);
		}
		return (true);
	}

# ====================================================================
#
# Balance Structure Method;
#
# Write Account Structure page with hyperlinks to related pages; 
#
# --------------------------------------------------------------------

	public function Structure ($AccountID, $Margin = "&nbsp;", $Offset = ".&nbsp;&nbsp;") 
	{
		static $level = 0;
		static $shade = true;
		static $ofp = NULL;
		if (!is_integer($AccountID)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't write Accounts page ($AccountID)", "Key must be integer");
			return (false);
		}
		$query = "SELECT * FROM Account WHERE ControlID=($AccountID)";
		Balance::Event (__METHOD__, __LINE__, $query);
		if (!$accounts = mysql_query($query, Balance::$db)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't write Accounts page for '$AccountID'", mysql_error(Balance::$db));
			return (false);
		}
		if ($level == 0) 
		{
			if (!$ofp = fopen(BASEPATH."/accounts/000000.html", "w")) 
			{
				Balance::Error (__METHOD__, __LINE__, "Can't open 000000.html for output");
				return (false);
			}
		}
		if ($level++ == 0) 
		{
			fprintf ($ofp, "<html><head><title>Account Structure</title><link href='../".STYLESHEET."' rel='stylesheet' type='text/css'/><style type='text/css'>".Balance::$style."</style></head><body>");
			fprintf($ofp, "<div class='headerlinks' align='center'>[<a href='999999.html' title='balance'>MAIN</a>] [<a href='000005.html'>PREV</a>] [<a href='999999.html'>HOME</a>] [<a href='000001.html'>NEXT</a>]</div>");
			fprintf ($ofp, "<h2 id='accounts'>Account Structure</h2><table><tr><th class='tree'>Structure</th><th class='name'>Name</th><th class='balance'>Balance</th><th class='balance'>Turnover</th><th class='receipt'>Receipts</th><th class='payment'>Payments</th></tr>");
		}
		while ($account = mysql_fetch_object($accounts)) 
		{
			$color = ($shade)? "silver": "white";
			fprintf ($ofp, "<tr><td class='tree' id='$account->ID'>".((float)($account->Turnover)?"<a href='$account->ID.html' title='Transaction History'>$account->ID</a>":"$account->ID")."$Margin<a href='$account->ID.html' title='Transaction History'>$account->Code</a></td><td style='background:$color;' class='name'>$account->Name</td><td style='background:$color;' class='balance'>$account->Balance</td><td style='background:$color;' class='balance'>$account->Turnover</td><td style='background:$color;' class='receipt'>$account->Receipts</td><td style='background:$color;' class='payment'>$account->Payments</td></tr>");
			$shade = ! $shade;
			Balance::Structure ((int)($account->ID), $Margin.$Offset, $Offset);
		}
		if (--$level == 0) 
		{
			fprintf($ofp, "</table>");
			fprintf($ofp, "<div class='footerlinks' align='center'>[<a href='999999.html' title='balance'>MAIN</a>] [<a href='000005.html'>PREV</a>] [<a href='999999.html'>HOME</a>] [<a href='000001.html'>NEXT</a>]</div>");
			fprintf($ofp, "<div class='footer' align='center'>Posted ".date(Balance::$stamp)."</div>");
			fprintf($ofp, "</body></html>");
		}
		if ($level == 0) 
		{
			fclose ($ofp);
		}
		return (true);
	}

# ====================================================================
#
# Balance Summary Method;
#
# Write Account Symmary page with hyperlinks to related pages;
#
# --------------------------------------------------------------------

	public function Summary () 
	{
		$query = "SELECT * FROM Account";
		Balance::Event (__METHOD__, __LINE__, $query);
		if (!$accounts = mysql_query($query, Balance::$db)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't read Account table", mysql_error(Balance::$db));
			return (false);
		}
		if (!$ofp = fopen(BASEPATH."/accounts/999999.html", "w")) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't open balances.html for output");
			return (false);
		}
		fprintf ($ofp, "<html><head><title>Account Balances</title><link href='../".STYLESHEET."' rel='stylesheet' type='text/css'/><style type='text/css'>".Balance::$style."</style></head><body>");
		fprintf($ofp, "<div class='headerlinks' align='center'>[<a href='000000.html' title='balance'>MAIN</a>] [<a href='000005.html'>PREV</a>] [<a href='000000.html'>HOME</a>] [<a href='000001.html'>NEXT</a>]</div>");
		fprintf ($ofp, "<h2 id='balances'>Account Balances</h2><table><tr><th class='id'>Number</th><th class='code'>Code</th><th class='name'>Name</th><th class='balance'>Balance</th><th class='balance'>Turnover</th><th class='receipt'>Receipts</th><th class='payment'>Payments</th></tr>");
		for ($shade = true; $account = mysql_fetch_object($accounts); $shade = ! $shade) 
		{
			$color = ($shade)? "silver": "white";
			fprintf ($ofp, "<tr><td style='background:$color;' class='id' id='$account->ID' title='Transaction History'>".((float)($account->Turnover)?("<a href='$account->ID.html'>$account->ID</a>"):("$account->ID"))."</td><td style='background:$color;' class='code'><a href='$account->ID.html' title='Transaction History'>$account->Code</a></td><td style='background:$color;' class='note'>".$account->Name."</td><td style='background:$color;' class='balance'>".$account->Balance."</td><td style='background:$color;' class='turnover'>".$account->Turnover."</td><td style='background:$color;' class='receipt'>".$account->Receipts."</td><td style='background:$color;' class='payment'>".$account->Payments."</td></tr>");
		}
		fprintf ($ofp, "</table>");
		fprintf($ofp, "<div class='footerlinks' align='center'>[<a href='000000.html' title='balance'>MAIN</a>] [<a href='000005.html'>PREV</a>] [<a href='000000.html'>HOME</a>] [<a href='000001.html'>NEXT</a>]</div>");
		fprintf($ofp, "<div class='footer' align='center'>Posted ".date(Balance::$stamp)."</div>");
		fprintf ($ofp, "</body></html>");
		return (true);
	}

# ====================================================================
#
# Balance History Method;
#
# Write Account History pages with hyperlinks to related pages; 
#
# --------------------------------------------------------------------

	public function History () 
	{
		$query = "SELECT * FROM Account";
		Balance::Event (__METHOD__, __LINE__, $query);
		if (!$accounts = mysql_query($query, Balance::$db)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't read Account Table", mysql_error(Balance::$db));
			return (false);
		}
		while ($account = mysql_fetch_object($accounts)) 
		{
			if (!$transactions = Balance::Transactions((int)($account->ID))) 
			{
				Balance::Event (__METHOD__, __LINE__, "Skipping History Page for ($Account->ID)", "No Transactions");
				continue;
			}
			if (!$ofp = fopen(BASEPATH."/accounts/".$account->ID.".html", "w")) 
			{
				Balance::Error (__METHOD__, __LINE__, "Can't open $account-ID.html for output");
				continue;
			}
			fprintf ($ofp, "<html><head><title>Transaction History for $account->Name</title><link href='../".STYLESHEET."' rel='stylesheet' type='text/css'/><style type='text/css'>".Balance::$style."</style></head><body>");
			fprintf($ofp, "<div class='headerlinks' align='center'>[<a href='000000.html' title='balance'>MAIN</a>] [<a href='%06d.html'>PREV</a>] [<a href='%06d.html'>HOME</a>] [<a href='%06d.html'>NEXT</a>]</div>", $account->ID, $account->ControlID, $account->ID);
			fprintf ($ofp, "<h2 id='$account->ID'>(<a href='000000.html#$account->ID' title='Account Structure'>$account->ID</a>) [<a href='999999.html#$account->ID' title='Account Balance'>$account->Code</a>] &quot;$account->Name&quot;</h2>");
			fprintf ($ofp, "<table class='box'><tr class='box'><th class='id'>TID</th><th class='date'>Date</th><!-- th class='type'>Type</th --><th class='code'>Account</th><th class='name'>Note</th><th class='count'>Count</th><th class='units'>Units</th><th class='price'>Price</th><th class='receipt'>Receipts</th><th class='payment'>Payments</th></tr>");
			for ($shade = true; $transaction = mysql_fetch_object($transactions); $shade = ! $shade) 
			{
				$color = ($shade)? "silver": "white";
				fprintf ($ofp, "<tr><td style='background:$color;' class='id' ID='$transaction->ID'><a href='$transaction->AccountID.html#$transaction->ID' title='Corresponding Transaction'>$transaction->ID</a></td><td style='background:$color;' class='date'>$transaction->Date</td><!-- td style='background:$color;' class='type'>$transaction->Type</td --><td style='background:$color;' class='code'><a href='$transaction->AccountID.html#$transaction->ID' title='Transaction History'>$transaction->AccountCode</a></td><td style='background:$color;' class='note'>$transaction->Note</td><td style='background:$color;' class='count'>$transaction->Count</td><td style='background:$color;' class='units'>$transaction->Units</td><td style='background:$color;' class='price'>$transaction->Price</td><td style='background:$color;' class='receipt'>$transaction->Receipts</td><td style='background:$color;' class='payment'>$transaction->Payments</td></tr>");
			}
			$color = ($shade)? "silver": "white";
			fprintf ($ofp, "<tr><td colspan='7' class='summary'>Subtotal</td><td style='background:$color;' class='receipt'>".$account->Receipts."</td><td style='background:$color;' class='payment'>".$account->Payments."</td></tr>");
			$color = (!$shade)? "silver": "white";
			fprintf ($ofp, "<tr><td colspan='7' class='summary'>Balance</td><td style='background:$color;' class='receipt'>".Balance::Nett($account->Receipts, $account->Payments)."</td><td style='background:$color;' class='payment'>".Balance::Nett($account->Payments, $account->Receipts)."</td></tr>");
			fprintf ($ofp, "</table>");
			fprintf($ofp, "<div class='footerlinks' align='center'>[<a href='000000.html' title='balance'>MAIN</a>] [<a href='%06d.html'>PREV</a>] [<a href='%06d.html'>HOME</a>] [<a href='%06d.html'>NEXT</a>]</div>", $account->ID, $account->ControlID, $account->ID);
			fprintf($ofp, "<div class='footer' align='center'>Posted ".date(Balance::$stamp)."</div>");
			fprintf ($ofp, "</body></html>");
			fclose ($ofp);
		}
		return (true);
	}

# ====================================================================
#
# Balance EchoStylesheet Method;
#
# Echo the Account stylesheet; return the object address;
#
# --------------------------------------------------------------------

	public function EchoStylesheet () 
	{
		echo "<style type='text/css'>".Balance::$style."</style>";
		return ($this);
	}

# ====================================================================
#
# Balance EchoAccount Method;
#
# Echo a Transaction table for one Account; return true on success
# and false on failure; 
#
# Receipts and payments are reversed on membership account display
# because members see thing differently;
#
# --------------------------------------------------------------------

	public function EchoAccount ($AccountID) 
	{
		if (!is_integer($AccountID)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't show Transaction table ($AccountID)", "Key must be integer");
			return (false);
		}
		$query = "SELECT * FROM Account WHERE ID=($AccountID)";
		Balance::Event (__METHOD__, __LINE__, $query);
		if (!$accounts = mysql_query($query, Balance::$db)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't show Account tables", mysql_error(Balance::$db));
			return (false);
		}
		if (!$account = mysql_fetch_object($accounts)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't show Account tables", "No such Account");
			return (false);
		}
		if (!$transactions = Balance::Transactions($AccountID)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't show Transaction table ($AccountID)", "No Transactions");
			return (false);
		}
		echo "<table class='box'><tr class='box'><th class='id'>TID</th><th class='date'>Date</th><!-- th class='type'>Type</th --><th class='code'>Account</th><th class='name'>Note</th><th class='count'>Count</th><th class='units'>Units</th><th class='price'>Price</th><!-- th class='value'>Value</th --><!-- th class='tax'>Tax</th --><!-- th class='total'>Total</th --><!-- th>Receipt</th --><!-- th>Payment</th --><!-- th>Balance</th --><th class='receipt'>Receipts</th><th class='payment'>Payments</th></tr>";
		for ($shade = true; $transaction = mysql_fetch_object($transactions); $shade = ! $shade) 
		{
			$color = ($shade)? "silver": "white";
			echo "<tr><td style='background:$color;' class='id'>$transaction->ID</td><td style='background:$color;' class='date'>$transaction->Date</td><!-- td style='background:$color;' class='type'>$transaction->Type</td --><td style='background:$color;' class='code'>$transaction->AccountCode</td><td style='background:$color;' class='note'>$transaction->Note</td><td style='background:$color;' class='count'>$transaction->Count</td><td style='background:$color;' class='units'>$transaction->Units</td><td style='background:$color;' class='price'>$transaction->Price</td><!-- td style='background:$color;' class='value'>$transaction->Value</td --><!-- td style='background:$color;' class='tax'>$transaction->Tax</td --><!-- td style='background:$color;' class='total'>$transaction->Total</td --><!-- td style='background:$color;' class='total'>$transaction->Total</td --><!-- td style='background:$color;' class='receipt'>$transaction->Receipt</td --><!-- td style='background:$color;' class='receipt'>$transaction->Payment</td -

-><!-- td style='background:$color;' class='receipt'>$transaction->Balance</td --><td style='background:$color;' class='receipt'>$transaction->Payments</td><td style='background:$color;' class='payment'>$transaction->Receipts</td></tr>";
		}
		$color = ($shade)? "silver": "white";
		echo ("<tr><td colspan='7' class='summary'>Subtotal</td><td style='background:$color;' class='receipt'>".$account->Payments."</td><td style='background:$color;' class='payment'>".$account->Receipts."</td></tr>");
		$color = (!$shade)? "silver": "white";
		echo ("<tr><td colspan='7' class='summary'>Balance</td><td style='background:$color;' class='receipt'>".Balance::Nett($account->Payments, $account->Receipts)."</td><td style='background:$color;' class='payment'>".Balance::Nett($account->Receipts, $account->Payments)."</td></tr>");
		echo "</table>";
		return (true);
	}

# ====================================================================
#
# Balance EchoStatement Method;
#
# Echo a Transaction table for one Account; return true on success
# and false on failure; 
#
# For this display, payments are funds send and receipts are funds
# cleared;
#
# --------------------------------------------------------------------

	public function EchoStatement ($AccountID) 
	{
		if (!is_integer($AccountID)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't show Transaction table ($AccountID)", "Key must be integer");
			return (false);
		}
		$query = "SELECT * FROM Account WHERE ID=($AccountID)";
		Balance::Event (__METHOD__, __LINE__, $query);
		if (!$accounts = mysql_query($query, Balance::$db)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't show Account tables", mysql_error(Balance::$db));
			return (false);
		}
		if (!$account = mysql_fetch_object($accounts)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't show Account tables", "No such Account");
			return (false);
		}
		if (!$transactions = Balance::Transactions($AccountID)) 
		{
			Balance::Error (__METHOD__, __LINE__, "Can't show Transaction table ($AccountID)", "No Transactions");
			return (false);
		}
		echo "<table class='box'><tr class='box'><th class='id'>TID</th><th class='date'>Date</th><!-- th class='type'>Type</th --><th class='code'>Account</th><th class='name'>Note</th><th class='count'>Count</th><th class='units'>Units</th><th class='price'>Price</th><!-- th class='value'>Value</th --><!-- th class='tax'>Tax</th --><!-- th class='total'>Total</th --><th class='receipt'>Receipts</th> <th class='payment'>Payments</th><!-- th class='balance'>Balance</th --></tr>";
		for ($shade = true; $transaction = mysql_fetch_object($transactions); $shade = ! $shade) 
		{
			$color = ($shade)? 'silver': 'white';
			echo "<tr><td style='background:$color;' class='id'>$transaction->ID</td><td style='background:$color;' class='date'>$transaction->Date</td><!-- td style='background:$color;' class='type'>$transaction->Type</td --><td style='background:$color;' class='code'>$transaction->AccountCode</td><td style='background:$color;' class='note'>$transaction->Note</td><td style='background:$color;' class='count'>$transaction->Count</td><td style='background:$color;' class='units'>$transaction->Units</td><td style='background:$color;' class='price'>$transaction->Price</td><!-- td style='background:$color;' class='value'>$transaction->Value</td --><!-- td style='background:$color' class='tax'>$transaction->Tax</td --><!-- td style='background:$color' class='total'>$transaction->Total</td --><td style='background:$color;' class='receipt'>$transaction->Receipt</td><td style='background:$color;' class='payment'>$transaction->Payment</td><!-- td style='background:$color;' class='balance'>$transaction->Balance</td --></tr>";
		}
		$color = ($shade)? "silver": "white";

#		echo ("<tr><td colspan='7' class='summary'>Subtotal</td><td style='background:$color;' class='receipt'>".$account->Receipts."</td><td style='background:$color;' class='payment'>".$account->Payments."</td></tr>"); 

		$color = (!$shade)? "silver": "white";

#		echo ("<tr><td colspan='7' class='summary'>Balance</td><td style='background:$color;' class='receipt'>".Balance::Nett($account->Receipts, $account->Payments)."</td><td style='background:$color;' class='payment'>".Balance::Nett($account->Payments, $account->Receipts)."</td></tr>"); 

		echo "</table>";
		return (true);
	}

# ====================================================================
#
# Balance Nett Method;
#
# return the positive difference between two floating point values 
# as currency; 
#
# --------------------------------------------------------------------

	public function Nett($Value, $Other) 
	{
		$Value = (float)($Value);
		$Other = (float)($Other);
		if ($Value > $Other) 
		{
			return(Balance::Currency(($Value)- ($Other)));
		}
		return(Balance::Currency(0));
	}

# ====================================================================
#
# Balance Currency Method;
#
# convert a value to the currency string representation if its
# floating point value;
#
# --------------------------------------------------------------------

	public function Currency($Amount) 
	{
		return(sprintf("%8.2f", (float)($Amount)));
	}

# ====================================================================
#
# Balance Number Method;
#
#
#
# --------------------------------------------------------------------

	public function Index ($Number) 
	{
		return(sprintf("%06d", (int)($Number)));
	}

# ====================================================================
#
# Balance Event Method;
#
#
#
# --------------------------------------------------------------------

	public function Event ($Method, $Lineno, $Event) 
	{
		Error ($Method, $Lineno, $Event, Balance::$trace);
		return ($this);
	}

# ====================================================================
#
# Balance Error Method;
#
#
#
# --------------------------------------------------------------------

	public function Error ($Method, $Lineno, $Error, $Cause) 
	{
		Error ($Method, $Line, $Error.": ".$Cause, Balance::$debug);
		return ($this);
	}

# ====================================================================
#
# Balance Constructor;
#
#
#
# --------------------------------------------------------------------

	public function __construct ($db) 
	{
		Balance::$db = $db;
		return;
	}

# ====================================================================
#
# Balance Destructor;
#
#
#
# --------------------------------------------------------------------

	public function __destruct () 
	{
		return;
	}

# ====================================================================
# End Class Definition;
# --------------------------------------------------------------------

}
 ?>
