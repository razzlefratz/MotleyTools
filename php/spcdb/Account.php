<?php

# ====================================================================
# 
# Account Class Definition;
# 
# 
# Published 2005 by Charles Maier Associates Limited for internal use;
# 
# --------------------------------------------------------------------

class Account 
{

# ====================================================================
# Public Variables;
# --------------------------------------------------------------------


# ====================================================================
# Private Variables;
# --------------------------------------------------------------------

	private $ID = 0;
	private $AccountID = 0;
	private $ContactID = 0;
	private $Type = 0;
	private $Code = "";
	private $Name = "";
	private $Payments = 0.00;
	private $Receipts = 0.00;
	private $Balance = 0.00;
	private $Opened = NULL;
	private $Closed = NULL;
	private $Created = NULL;
	private $Updated = NULL;
	private $field = NULL;
	private $table = NULL;
	private $query = NULL;
	private static $debug = 0;
	private static $trace = 0;
	private static $db = NULL;

# ====================================================================
#
# Account Debug Property;
#
# Enable or disable Debug messages; Debug messages appear prior to
# every error return;
#
# --------------------------------------------------------------------

	public function GetDebug () 
	{
		return (self::$debug);
	}
	public function SetDebug ($Debug) 
	{
		if (!is_integer($Debug)) 
		{
			printf ("Account: Can't set Debug to '${Debug}': Property is integer.\n");
			return ($this);
		}
		self::$debug = $Debug;
		return ($this);
	}

# ====================================================================
#
# Account Trace Property;
#
# Enable or disable Trace messages; Trace messages appear prior to
# every database query; 
#
# --------------------------------------------------------------------

	public function GetTrace () 
	{
		return (self::$debug);
	}
	public function SetTrace ($Trace) 
	{
		if (!is_integer($Trace)) 
		{
			printf ("Account: Can't set Trace to '${Trace}': Property is integer.\n");
			return ($this);
		}
		self::$trace = $Trace;
		return ($this);
	}

# ====================================================================
#
# Account ID Property;
#
#
#
# --------------------------------------------------------------------

	public function GetID () 
	{
		return ($this->ID);
	}

#       public function SetID ($ID)
#
#       {
#               if (!is_integer($ID))
#               {
#                       Account::Error ("Can't set ID to '${ID}'", "Property is integer");
#                       return (false);
#               }
#
#               $this->ID = $ID;
#               return (true);
#       }


# ====================================================================
#
# Account AccountID Property;
#
#
#
# --------------------------------------------------------------------

	public function GetAccountID () 
	{
		return ($this->AccountID);
	}
	public function SetAccountID ($AccountID) 
	{
		if (!is_integer($AccountID)) 
		{
			Account::Error ("Can't set AccountID to '${AccountID}'", "Property is integer");
			return (false);
		}
		$this->AccountID = $AccountID;
		return (true);
	}

# ====================================================================
#
# Account SetAccount Method;
#
#
#
# --------------------------------------------------------------------

	public function SetAccount ($Account) 
	{
		if (!$AccountID = Database::GetID($Account, "Account", self::$db)) 
		{
			Account::Error ("Can't set Account to ${Account}", "No such Account");
			return (false);
		}
		$this->AccountID = $AccountID;
		return (true);
	}

# ====================================================================
#
# Account ContactID Property;
#
#
#
# --------------------------------------------------------------------

	public function GetContactID () 
	{
		return ($this->ContactID);
	}
	public function SetContactID ($ContactID) 
	{
		if (!is_integer($ContactID)) 
		{
			Account::Error ("Can't set ContactID to '${ContactID}'", "Property is integer");
			return (false);
		}
		$this->ContactID = $ContactID;
		return (true);
	}

# ====================================================================
#
# Account SetContact Method;
#
#
#
# --------------------------------------------------------------------

	public function SetContact ($Contact) 
	{
		if (!$ContactID = Database::GetID($Contact, "Contact", self::$db)) 
		{
			Account::Error ("Can't set Contact to ${Contact}", "No such Contact");
			return (false);
		}
		$this->ContactID = $ContactID;
		return (true);
	}

# ====================================================================
#
# Account Type Property;
#
#
#
# --------------------------------------------------------------------

	public function GetType () 
	{
		return ($this->Type);
	}
	public function SetType ($Type) 
	{
		if (!is_integer($Type)) 
		{
			Account::Error ("Can't set Type to '${Type}'", "Property is integer");
			return (false);
		}
		$this->Type = $Type;
		return (true);
	}

# ====================================================================
#
# Account Code Property;
#
#
#
# --------------------------------------------------------------------

	public function GetCode () 
	{
		return ($this->Code);
	}
	public function SetCode ($Code) 
	{
		$this->Code = $Code;
		return (true);
	}

# ====================================================================
#
# Account Name Property;
#
#
#
# --------------------------------------------------------------------

	public function GetName () 
	{
		return ($this->Name);
	}
	public function SetName ($Name) 
	{
		$this->Name = $Name;
		return (true);
	}

# ====================================================================
#
# Account Opened Property;
#
#
#
# --------------------------------------------------------------------

	public function GetOpened () 
	{
		return ($this->Opened);
	}
	public function SetOpened ($Opened) 
	{
		$this->Opened = $Opened;
		return (true);
	}

# ====================================================================
#
# Account Closed Property;
#
#
#
# --------------------------------------------------------------------

	public function GetClosed () 
	{
		return ($this->Closed);
	}
	public function SetClosed ($Closed) 
	{
		$this->Closed = $Closed;
		return (true);
	}

# ====================================================================
#
# Account Created Property;
#
#
#
# --------------------------------------------------------------------

	public function GetCreated () 
	{
		return ($this->Created);
	}

#       public function SetCreated ($Created)
#
#       {
#               $this->Created = $Created;
#               return (true);
#       }


# ====================================================================
#
# Account Updated Property;
#
#
#
# --------------------------------------------------------------------

	public function GetUpdated () 
	{
		return ($this->Updated);
	}

#       public function SetUpdated ($Updated)
#
#       {
#               $this->Updated = $Updated;
#               return (true);
#       }


# ====================================================================
#
# Account Clear Method;
#
#
#
# --------------------------------------------------------------------

	public function Clear () 
	{
		Account::Event ("Clearing Object Properties", "");
		$this->ID = 0;
		$this->AccountID = 0;
		$this->ContactID = 0;
		$this->Type = 0;
		$this->Code = "";
		$this->Name = "";
		$this->Payments = '0.00';
		$this->Receipts = '0.00';
		$this->Balance = '0.00';
		$this->Opened = NULL;
		$this->Closed = NULL;
		$this->Created = NULL;
		$this->Updated = NULL;
		return;
	}

# ====================================================================
#
# Account Fetch Method;
#
#
#
# --------------------------------------------------------------------

	public function Fetch ($Account) 
	{
		if (is_numeric($Account)) 
		{
			$query = "SELECT * FROM Account WHERE ID=(${Account})";
		}
		else 
		{
			$query = "SELECT * FROM Account WHERE Code='${Account}'";
		}
		Account::Event ($query, "");
		if (!$table=mysql_query($query, self::$db)) 
		{
			Account::Error ("Can't fetch Account ${Account}", mysql_error(self::$db));
			return (false);
		}
		if (!$field=mysql_fetch_object($table)) 
		{
			Account::Error ("Can't fetch Account ${Account}", "No such Account");
			return (false);
		}
		$this->ID = $field->ID;
		$this->AccountID = $field->AccountID;
		$this->ContactID = $field->ContactID;
		$this->Type = $field->Type;
		$this->Code = $field->Code;
		$this->Name = $field->Name;
		$this->Payments = $field->Payments;
		$this->Receipts = $field->Receipts;
		$this->Balance = $field->Balance;
		$this->Opened = $field->Opened;
		$this->Closed = $field->Closed;
		$this->Created = $field->Created;
		$this->Updated = $field->Updated;
		return (true);
	}

# ====================================================================
#
# Account Store Method;
#
#
#
# --------------------------------------------------------------------

	public function Store () 
	{
		if ($this->ID) 
		{
			$query = "UPDATE Account SET ContactID=($this->ContactID),AccountID=($this->AccountID),Type=($this->Type),Code='$this->Code',Name='$this->Name',Receipts=($this->Receipts),Payments=($this->Payments),Balance=($this->Balance),Opened='$this->Opened',Closed='$this->Closed',Created='$this->Created',Updated=NOW() WHERE ID=($this->ID)";
		}
		else 
		{
			$query = "INSERT INTO Account (ContactID,AccountID,Type,Code,Name,Receipts,Payments,Balance,Opened,Closed,Created,Updated) VALUES (($this->ContactID),($this->AccountID),($this->Type),'$this->Code','$this->Name',($this->Receipts),($this->Payments),($this->Balance),'$this->Opened','$this->Closed',NOW(),NOW())";
		}
		Account::Event ($query, "");
		if (!$accounts=mysql_query($query, self::$db)) 
		{
			Account::Error ("Can't store $this->Code", mysql_error(self::$db));
			return (false);
		}

#               if (!$this->ID)
#               {
#                       $this->ID = mysql_insert_id(self::$db);
#               }

		return (true);
	}

# ====================================================================
#
# Account Component_Array Method;
#
# Return an associative array of component account codes indexed by 
# account number; 
#
# --------------------------------------------------------------------

	public function Component_Array ($AccountID) 
	{
                $array = array ();
		$query = "SELECT ID, AccountID, Code FROM Account WHERE AccountID=(${AccountID})";
		Account::Event($query, "");
		if (!$accounts = mysql_query($query, self::$db)) 
		{
			Account::Error("Can't show structure of Account '${AccountID}'", mysql_error(self::$db));
			return ($array);
		}
		while ($account = mysql_fetch_object($accounts)) 
		{
			$array[$account->ID] = $account->Code;
			$array += Account::Component_Array ($account->ID);
		}
		return ($array);
	}

# ====================================================================
#
# Account Structure Method;
#
#
#
# --------------------------------------------------------------------

	public function Structure($AccountID, $Margin = " ", $Indent = "|  ") 
	{
		$query = "SELECT ID, AccountID, Code FROM Account WHERE AccountID=(${AccountID})";
		Account::Event($query, "");
		if (!$accounts = mysql_query($query, self::$db)) 
		{
			Account::Error("Can't show structure of Account '${AccountID}'", mysql_error(self::$db));
			return (false);
		}
		while ($account = mysql_fetch_object($accounts)) 
		{
			printf ("%s%s%s\n", $account->ID, $Margin, $account->Code);
			Account::Structure ($account->ID, $Margin.$Indent, $Indent);
		}
		return (true);
	}

# ====================================================================
# 
# Account Transactions Method;
# 
# Return a table transactions (ordered by date) for the named account;
# these transactions contain most fields found in a normal Transaction
# record with some exceptions; 
# 
# --------------------------------------------------------------------

	public function Transactions ($Account) 
	{
		if (!$AccountID = Database::GetID($Account, "Account", self::$db)) 
		{
			Account::Error ("Can't fetch Transactions for Account ${Account}", "No such Account");
			return (false);
		}
		$query = "DROP TABLE IF EXISTS A${AccountID}";
		Account::Event($query, "");
		if (!mysql_query($query, self::$db)) 
		{
			Account::Error ("Can't remove temporary table", mysql_error(self::$db));
			return (false);
		}
		$query = "CREATE TEMPORARY TABLE A${AccountID} SELECT Transaction.ID AS ID, Date, Account.Code AS Code, Transaction.Note, Transaction.Count, Transaction.Units, Transaction.Price, Transaction.Value, Transaction.TaxRate, Transaction.Total, Transaction.Tax, Transaction.Total AS Payment, (0.00) AS Receipt, Transaction.Balance AS Balance FROM Account JOIN Transaction ON Account.ID=ReceiptID WHERE PaymentID=(${AccountID})";
		Account::Event($query, "");
		if (!mysql_query($query, self::$db)) 
		{
			Account::Error ("Can't collect Payments for Account '${Account}'", mysql_error(self::$db));
			return (false);
		}
		$query = "INSERT INTO A${AccountID} SELECT Transaction.ID AS ID, Date, Account.Code AS Code, Transaction.Note, Transaction.Count, Transaction.Units, Transaction.Price, Transaction.Value, Transaction.TaxRate, Transaction.Tax, Transaction.Total, (0.00) AS Payment, Transaction.Total AS Receipt, Transaction.Balance AS Balance FROM Account JOIN Transaction ON Account.ID=PaymentID WHERE ReceiptID=(${AccountID})";
		Account::Event($query, "");
		if (!mysql_query($query, self::$db)) 
		{
			Account::Error ("Can't collect Receipts for Account '${Account}'", mysql_error(self::$db));
			return (false);
		}
		$query = "SELECT * FROM A${AccountID} ORDER BY Date";
		Account::Event($query, "");
		if (!$table = mysql_query($query, self::$db)) 
		{
			Account::Error("Can't fetch Transactions for Account '${Account}'", mysql_error(self::$db));
			return (false);
		}
		return ($table);
	}

# ====================================================================
#
# Balance ComputeReceipts Method;
#
# Compute the total Receipts for the numbered Account;            
#
# --------------------------------------------------------------------

   public function ComputeReceipts ($AccountID) 
   {
      if (!is_integer($AccountID)) 
      {
         Account::Error ("Can't compute Receipts for Account '${AccountID}'", "Key must be integer.");
         return (false);
      }
      $query = "SELECT SUM(Total) AS Receipts FROM Transaction WHERE ReceiptID=(${AccountID})";
      Account::Event ($query, "");
      if (!$table = mysql_query($query, self::$db)) 
      {
         Account::Error ("Can't compute Receipts for Account '${AccountID}'", mysql_error(self::$db));
         return (false);
      }
      if (!$field = mysql_fetch_object($table)) 
      {
         Account::Error ("Can't compute Receipts for Account '${AccountID}'", "None exist.");
         return (false);
      }
      return (floatval($field->Receipts));
   }

# ====================================================================
#
# Account ComputePayments Method;
#
# Compute the total Payments for the numbered account; 
#
# --------------------------------------------------------------------

   public function ComputePayments ($AccountID) 
   {
      if (!is_integer($AccountID)) 
      {
         Account::Error ("Can't compute Payments for Account '${AccountID}'", "Key must be integer.");
         return (false);
      }
      $query = "SELECT SUM(Total) AS Payments FROM Transaction WHERE PaymentID=(${AccountID})";
      Account::Event ($query, "");
      if (!$table = mysql_query($query, self::$db)) 
      {
         Account::Error ("Can't compute Payments for Account '${AccountID}'", mysql_error($this->$db));
         return (false);
      }
      if (!$field = mysql_fetch_object($table)) 
      {
         Account::Error ("Can't compute Payments for Account ${AccountID}", "None exist.");
         return (false);
      }
      return (floatval($field->Payments));
   }

# ====================================================================
#
# Balance UpdateBalance Method;
#
# Compute and return the current Account Balance;
#
# --------------------------------------------------------------------

   public function UpdateBalance ($AccountID) 
   {
      Account::Event ("Updating Balance for Account ${AccountID}.", "");
      if (!is_integer($AccountID)) 
      {
         Account::Error ("Can't update Balance for Account '${AccountID}'", "Key must be integer.");
         return (false);
      }
      $Receipts = Account::Receipts($AccountID);
      $Payments = Account::Payments($AccountID);
      $query = "UPDATE Account SET Receipts=(${Receipts}), Payments=(${Payments}), Balance=((${Receipts})-(${Payments})) WHERE ID=(${AccountID})";
      Account::Event ($query, "");
      if (!mysql_query($query, self::$db)) 
      {
         Account::Error ("Can't update Balance for Account '${AccountID}'");
         return (false);
      }
      return (true);
   }

# ====================================================================
#
# Balance UpdateBalances Method;
#
# Update Account table Receipts, Payments and Balances using query;
# create Balance table having an AccountID, Receipts and Payments 
# column; join Account and Balance tables with update; remove the 
# Balance table;
#
# This should be faster than looping because the Myquery engine does 
# all the work;
#
# --------------------------------------------------------------------

   public function UpdateBalances () 
   {
      $query = "DROP TABLE IF EXISTS Balance";
      Account::Event ($query, "");
      if (!mysql_query($query, self::$db)) 
      {
         Account::Error ("Can't remove old Balance table", mysql_error(self::$db));
         return (false);
      }
#      $query = "UPDATE Account SET Receipts=(0.00), Payments=(0.00), Balance=(0.00)";
#      Account::Event ($query, "");
#      if (!mysql_query($query, self::$db)) 
#      {
#         Account::Error ("Can't clear Account balances", mysql_error(self::$db));
#         return (false);
#      }
      $query = "CREATE TEMPORARY TABLE Balance SELECT ReceiptID, SUM(Total) As Receipts FROM Transaction GROUP BY ReceiptID ORDER BY ReceiptID";
      Account::Event ($query, "");
      if (!mysql_query($query, self::$db)) 
      {
         Account::Error ("Can't compute temporary Receipts", mysql_error(self::$db));
         return (false);
      }
      $query = "UPDATE Account LEFT JOIN Balance ON Account.ID=Balance.ReceiptID SET Account.Receipts=Balance.Receipts";
      Account::Event ($query, "");
      if (!mysql_query($query, self::$db)) 
      {
         Account::Error ("Can't update Account Receipts", mysql_error(self::$db));
         return (false);
      }
      $query = "DROP TABLE Balance";
      Account::Event ($query, "");
      if (!mysql_query($query, self::$db)) 
      {
         Account::Error ("Can't remove new Balance table", mysql_error(self::$db));
         return (false);
      }
      $query = "CREATE TEMPORARY TABLE Balance SELECT PaymentID, SUM(Total) As Payments FROM Transaction GROUP BY PaymentID ORDER BY PaymentID";
      Account::Event ($query, "");
      if (!mysql_query($query, self::$db)) 
      {
         Account::Error ("Can't compute temporary Payments", mysql_error(self::$db));
         return (false);
      }
      $query = "UPDATE Account LEFT JOIN Balance ON Account.ID=Balance.PaymentID SET Account.Payments=Balance.Payments";
      Account::Event ($query, "");
      if (!mysql_query($query, self::$db)) 
      {
         Account::Error ("Can't update Account Payments", mysql_error(self::$db));
         return (false);
      }
      $query = "DROP TABLE Balance";
      Account::Event ($query, "");
      if (!mysql_query($query, self::$db)) 
      {
         Account::Error ("Can't remove new Balance table", mysql_error(self::$db));
         return (false);
      }
      $query = "UPDATE Account SET Balance=((Account.Receipts)-(Account.Payments))";
      Account::Event ($query, "");
      if (!mysql_query($query, self::$db)) 
      {
         Account::Error ("Can't clear Account balances", mysql_error(self::$db));
         return (false);
      }
      return (true);
   }

# ====================================================================
#
# Account Event Method;
#
#
#
# --------------------------------------------------------------------

	public function Event ($Event, $Label) 
	{
		If (self::$trace == 1) 
		{
			printf ("<br><span class='event'>Account: %s;</span></br>", cmassoc::combine($Event, ": ", $Label));
		}
		if (self::$trace == 2) 
		{
			printf ("Account: %s;\n", cmassoc::combine($Event, ": ", $Label));
		}
		return ($this);
	}

# ====================================================================
#
# Account Error Method;
#
#
#
# --------------------------------------------------------------------

	public function Error ($Error, $Cause) 
	{
		if (self::$debug == 1) 
		{
			printf ("<br><span class='errror'>Account: %s;</span><br>\n", cmassoc::combine($Error, ": ", $Cause));
		}
		if (self::$debug == 2) 
		{
			printf ("Account: %s;\n", cmassoc::combine($Error, ": ", $Cause));
		}
		return ($this);
	}

# ====================================================================
#
# Account Constructor;
#
#
#
# --------------------------------------------------------------------

	public function __construct ($db) 
	{
		self::$db = $db;
		return;
	}

# ====================================================================
#
# Account Destructor;
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

