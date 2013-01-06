<?php

# ====================================================================
# Custom Include Files; 
# --------------------------------------------------------------------

require "constants.php";

# ====================================================================
# 
# Transaction Class Definition;
# 
# 
# Published 2005 by Charles Maier Associates Limited for internal use;
# 
# --------------------------------------------------------------------

class Transaction 
{

# ====================================================================
# Public Variables;
# --------------------------------------------------------------------


# ====================================================================
# Private Variables;
# --------------------------------------------------------------------

	private $ID = 0;
	private $ContactID = 1;
	private $ProjectID = 1;
	private $PaymentID = 1;
	private $ReceiptID = 1;
	private $Type = 0;
	private $InternalCode = "";
	private $ExternalCode = "";
	private $Note ="";
	private $Count = 1;
	private $Units = "Each";
	private $Price = 0.00;
	private $Local = 1.00;
	private $Value = 0.00;
	private $TaxRate = 0.00;
	private $Tax = 0.00;
	private $Total = 0.00;
	private $Payment = 0.00;
	private $Receipt = 0.00;
	private $Balance = 0.00;
	private $Date = NULL;
	private $Paid = NULL;
	private $Due = NULL;
	private $Created = NULL;
	private $Updated = NULL;
	private static $debug = MESSAGE_NONE;
	private static $trace = MESSAGE_NONE;
	private static $db = NULL;

# ====================================================================
#
# Transaction Debug Property;
#
# Enable or disable Debug messages; Debug messages appear prior to
# every error return;
#
# --------------------------------------------------------------------

	public function GetDebug () 
	{
		return (Transaction::$debug);
	}
	public function SetDebug ($Debug) 
	{
		if (!is_integer($Debug)) 
		{
			printf ("Transaction: Can't set Debug to '${Debug}': Property is integer.\n");
			return ($this);
		}
		Transaction::$debug = $Debug;
		return ($this);
	}

# ====================================================================
#
# Transaction Trace Property;
#
# Enable or disable Trace messages; Trace messages appear prior to
# every database query; 
#
# --------------------------------------------------------------------

	public function GetTrace () 
	{
		return (Transaction::$trace);
	}
	public function SetTrace ($Trace) 
	{
		if (!is_integer($Trace)) 
		{
			printf ("Transaction: Can't set Trace to '${Trace}': Property is integer.\n");
			return ($this);
		}
		Transaction::$trace = $Trace;
		return ($this);
	}

# ====================================================================
#
# Transaction ID Property;
#
# The ID property is auto-increment and readonly;
#
# --------------------------------------------------------------------

	public static function GetID () 
	{
		return ($this->ID);
	}

#       public function SetID ($ID)
#
#       {
#               if (!is_integer($ID))
#               {
#                       Transaction::Error (__METHOD__, __LINE__, "Can't set ID to '${ID}'", "Property is integer");
#                       return (false);
#               }
#
#               $this->ID = $ID;
#               return (true);
#       }


# ====================================================================
#
# Transaction ContactID Property;
#
# The integer index of some Contact; By convention, this 
# identifies the person recording the transaction but that need not
# be the case;
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
			Transaction::Error (__METHOD__, __LINE__, "Can't set ContactID to '${ContactID}'", "Property is integer");
			return (false);
		}
		$this->ContactID = $ContactID;
		return (true);
	}

# ====================================================================
#
# Transaction SetContact Method;
#
#
#
# --------------------------------------------------------------------

	public function SetContact ($Contact) 
	{
		if (!$ContactID = ID ($Contact, "Contact", Transaction::$db)) 
		{
			Transaction::Error (__METHOD__, __LINE__, "Can't set ContactID to ${Contact}", "No such Contact");
			return (false);
		}
		$this->ContactID = $ContactID;
		return (true);
	}

# ====================================================================
#
# Transaction ProjectID Property;
#
# The integer index of some Project; The corresponding 
# Project could represent a department, division, contract or other
# activity of interest; This permits parallel bookeeping where one
# or more activities share accounts but require separate analysis;;
#
# --------------------------------------------------------------------

	public function GetProjectID () 
	{
		return ($this->ProjectID);
	}
	public function SetProjectID ($ProjectID) 
	{
		if (!is_integer($ProjectID)) 
		{
			Transaction::Error (__METHOD__, __LINE__, "Can't set ProjectID to '${ProjectID}'", "Property is integer");
			return (false);
		}
		$this->ProjectID = $ProjectID;
		return (true);
	}

# ====================================================================
#
# Transaction PaymentID Property;
#
# The integer index of some Account; The corresponding 
# Transaction is the source of funds for this transaction which causes
# that account balance to decrease by the transaction amount; 
#
# --------------------------------------------------------------------

	public function GetPaymentID () 
	{
		return ($this->PaymentID);
	}
	public function SetPaymentID ($AccountID) 
	{
		if (!is_integer($AccountID)) 
		{
			Transaction::Error (__METHOD__, __LINE__, "Can't set PaymentID to '${AccountID}'", "Property is integer");
			return (false);
		}
		$this->PaymentID = $AccountID;
		return (true);
	}

# ====================================================================
#
# Transaction SetPaymentAccount Method;
#
#
#
# --------------------------------------------------------------------

	public function SetPaymentAccount ($Account) 
	{
		if (!$PaymentID = ID ($Account, "Account", Transaction::$db)) 
		{
			Transaction::Error (__METHOD__, __LINE__, "Can't set PaymentID to ${Account}", "No such Account");
			return (false);
		}
		$this->PaymentID = $PaymentID;
		return (true);
	}

# ====================================================================
#
# Transaction ReceiptID Property;
#
# The integer index of some Account; The corresponding 
# Transaction is the target of funds for this transaction which causes
# that account balance to increase by the transaction amount;
#
# --------------------------------------------------------------------

	public function GetReceiptID () 
	{
		return ($this->ReceiptID);
	}
	public function SetReceiptID ($AccountID) 
	{
		if (!is_integer($AccountID)) 
		{
			Transaction::Error (__METHOD__, __LINE__, "Can't set ReceiptID to '${AccountID}'", "Property is integer");
			return (false);
		}
		$this->ReceiptID = $AccountID;
		return (true);
	}

# ====================================================================
#
# Transaction SetReceiptAccount Method;
#
#
#
# --------------------------------------------------------------------

	public function SetReceiptAccount ($Account) 
	{
		if (!$ReceiptID = ID ($Account, "Account", Transaction::$db)) 
		{
			Transaction::Error (__METHOD__, __LINE__, "Can't set ReceiptID to ${Account}", "No such Account");
			return (false);
		}
		$this->ReceiptID = $ReceiptID;
		return (true);
	}

# ====================================================================
#
# Transaction Type Property; 
#
# A two-letter code indicating the transaction type; 
#
# --------------------------------------------------------------------

	public function GetType () 
	{
		return ($this->Type);
	}
	public function SetType ($Type) 
	{
		$this->Type = $Type;
		return (true);
	}

# ====================================================================
#
# Transaction InternalCode Property;
#
# An internal filing system identifier; By conventions, this might 
# be an invoice, receipt or check number or any other useful means
# of distinguishing this transaction from the others; 
#
# --------------------------------------------------------------------

	public function GetInternalCode () 
	{
		return ($this->InternalCode);
	}
	public function SetInternalCode ($Code) 
	{
		$this->InternalCode = $Code;
		return (true);
	}

# ====================================================================
#
# Transaction ExternalCode Property;
#
# An internal filing system identifier; By conventions, this might 
# be an invoice, receipt or check number or any other useful means
# of distinguishing this transaction from the others; 
#
# --------------------------------------------------------------------

	public function GetExternalCode () 
	{
		return ($this->ExternalCode);
	}
	public function SetExternalCode ($Code) 
	{
		$this->ExternalCode = $Code;
		return (true);
	}

# ====================================================================
#
# Transaction Note Property;
#
# A brief description of the transaction nature or purposes; 
#
# --------------------------------------------------------------------

	public function GetNote () 
	{
		return ($this->Note);
	}
	public function SetNote ($Note) 
	{
		$this->Note = $Note;
		return (true);
	}

# ====================================================================
#
# Transaction Count Property;
#
# Indicates the number of units involved in the transaction; In most
# cases the values is 1; Transaction value is computed by multiplying
# the price by this number;
#
# --------------------------------------------------------------------

	public function GetCount () 
	{
		return ($this->Count);
	}
	public function SetCount ($Count) 
	{
		if (!is_integer($Count)) 
		{
			Transaction::Error (__METHOD__, __LINE__, "Can't set Count to '${Count}'", "Property is integer");
			return (false);
		}
		$this->Count = $Count;
		$this->GetTotal();
		return (true);
	}

# ====================================================================
#
# Transaction Units Property;
#
# Inicate the type of units involved in the transaction;
#
# --------------------------------------------------------------------

	public function GetUnits () 
	{
		return ($this->Units);
	}
	public function SetUnits ($Units) 
	{
		$this->Units = $Units;
		return (true);
	}

# ====================================================================
#
# Transaction Price Property;
#
# The unit price; The transaction value will be some multiple of the
# unit price; Changing the unit price will cause the value, tax and
# total to change;
# 
# --------------------------------------------------------------------

	public function GetPrice () 
	{
		return ($this->Price);
	}
	public function SetPrice ($Price) 
	{
		if (!is_float($Price)) 
		{
			Transaction::Error (__METHOD__, __LINE__, "Can't set Price to '${Price}'", "Property is float");
			return (false);
		}
		$this->Price = $Price;
		$this->GetTotal();
		return (true);
	}

# ====================================================================
#
# Transaction Local Property;
#
# The local exchange rate; Normally, this value is 1; Changes in this
# will cause the value, tax and total to change; 
#
# --------------------------------------------------------------------

	public function GetLocal () 
	{
		return ($this->Local);
	}
	public function SetLocal ($Local) 
	{
		if (!is_float($Local)) 
		{
			Transaction::Error (__METHOD__, __LINE__, "Can't set Local to '${Local}'", "Property is float");
			return (false);
		}
		$this->Local = $Local;
		$this->GetTotal();
		return (true);
	}

# ====================================================================
#
# Transaction Value Property;
#
# The transaction value before tax; Normally, the value is computed 
# from the count and the price; however, setting the value directly
# will change the price based on the current value of count;
#
# --------------------------------------------------------------------

	public function GetValue () 
	{
		$this->Value = $this->Local * $this->Price * $this->Count;
		return ($this->Value);
	}
	public function SetValue ($Value) 
	{
		if (!is_float($Value)) 
		{
			Transaction::Error (__METHOD__, __LINE__, "Can't set Value to '${Value}'", "Property is float");
			return (false);
		}
		$this->Price = $Value / $this->Count;
		$this->GetTotal();
		return (true);
	}

# ====================================================================
#
# Transaction TaxRate Property;
#
# The transaction tax rate; This will be zero for non-taxable and
# non-zero for taxable transactions; For example, the value would 
# be 0.06 for a 6% sales tax; 
#
# --------------------------------------------------------------------

	public function GetTaxRate () 
	{
		return ($this->TaxRate);
	}
	public function SetTaxRate ($TaxRate) 
	{
		if (!is_float($TaxRate)) 
		{
			Transaction::Error (__METHOD__, __LINE__, "Can't set TaxRate to '${TaxRate}'", "Property is float");
			return (false);
		}
		$this->TaxRate = $TaxRate;
		$this->GetTotal();
		return (true);
	}

# ====================================================================
#
# Transaction Tax Property;
#
# The transaction tax amount; This should be zero for non-taxable
# transactions;
#
# --------------------------------------------------------------------

	public function GetTax () 
	{
		$this->Tax = $this->GetValue()* $this->GetTaxRate();
		return ($this->Tax);
	}
	public function SetTax ($Tax) 
	{
		if (!is_float($Tax)) 
		{
			Transaction::Error (__METHOD__, __LINE__, "Can't set Tax to '${Tax}'", "Property is float");
			return (false);
		}
		$this->TaxRate = $this->Value / $Tax;
		$this->GetTotal();
		return (true);
	}

# ====================================================================
#
# Transaction Total Property;
#
# The total transaction amount; This is the value plus any tax due;
#
# --------------------------------------------------------------------


# The public properties SetCount(), SetPrice(), SetLocal(), GetValue(),
# SetValue(), SetTaxRate(), GetTax(), SetTax() and GetTotal() interact
# to maintain a valid set of Count, Price, Local, Value, TaxRate, Tax,
# Total, Payament and Balance values; 

	public function GetTotal () 
	{
		$this->Total = $this->GetValue()+ $this->GetTax();
		$this->Payment = $this->Total;
		$this->Receipt = 0.00;
		$this->Balance = $this->Payment - $this->Receipt;
		return ($this->Total);
	}

#       public function SetTotal ($Total)
# 
#       {
#               if (!is_float($Total))
#               {
#                       Transaction::Error (__METHOD__, __LINE__,"Can't set Total to '${Total}'", "Property is float");
#                       return (false);
#               }
#
#               $this->Total = $Total;
#               return (true);
#       }


# ====================================================================
#
# Transaction Payment Property;
#
#
#
# --------------------------------------------------------------------

	public function GetPayment () 
	{
		return ($this->Payment);
	}
	public function SetPayment ($Payment) 
	{
		if (!is_float($Payment)) 
		{
			Transaction::Error (__METHOD__, __LINE__, "Can't set Payment to '${Payment}'", "Property is float");
			return (false);
		}
		$this->Payment = $Payment;
		return (true);
	}

# ====================================================================
#
# Transaction Receipt Property;
#
#
#
# --------------------------------------------------------------------

	public function GetReceipt () 
	{
		return ($this->Receipt);
	}
	public function SetReceipt ($Receipt) 
	{
		if (!is_float($Receipt)) 
		{
			Transaction::Error (__METHOD__, __LINE__, "Can't set Receipt to '${Receipt}'", "Property is float");
			return (false);
		}
		$this->Receipt = $Receipt;
		return (true);
	}

# ====================================================================
#
# Transaction Balance Property;
#
#
#
# --------------------------------------------------------------------

	public function GetBalance () 
	{
		return ($this->Balance);
	}
	public function SetBalance ($Balance) 
	{
		if (!is_float($Balance)) 
		{
			Transaction::Error (__METHOD__, __LINE__, "Can't set Balance to '${Balance}'", "Property is float");
			return (false);
		}
		$this->Balance = $Balance;
		return (true);
	}

# ====================================================================
#
# Transaction Date Property;
#
#
#
# --------------------------------------------------------------------

	public function GetDate () 
	{
		return ($this->Date);
	}
	public function SetDate ($Date) 
	{
		$this->Date = $Date;
		return (true);
	}

# ====================================================================
#
# Transaction Paid Property;
#
#
#
# --------------------------------------------------------------------

	public function GetPaid () 
	{
		return ($this->Paid);
	}
	public function SetPaid (date$Paid) 
	{
		$this->Paid = $Paid;
		return (true);
	}

# ====================================================================
#
# Transaction Due Property;
#
#
#
# --------------------------------------------------------------------

	public function GetDue () 
	{
		return ($this->Due);
	}
	public function SetDue ($value) 
	{
		$this->Due = $value;
		return (true);
	}

# ====================================================================
#
# Transaction Created Property;
#
#
#
# --------------------------------------------------------------------

	public function GetCreated () 
	{
		return ($this->Created);
	}

#       public function SetCreated (date $Created)
#
#       {
#               $this->Created = $Created;
#               return (true);
#       }


# ====================================================================
#
# Transaction Updated Property;
#
#
#
# --------------------------------------------------------------------

	public function GetUpdated () 
	{
		return ($this->Updated);
	}

#       public function SetUpdated (date $Updated)
#
#       {
#               $this->Updated = $Updated;
#               return (true);
#       }


# ====================================================================
#
# Transaction Clear Method;
#
#
#
# --------------------------------------------------------------------

	public function Clear () 
	{
		$this->ID = 0;
		$this->ContactID = 1;
		$this->ProjectID = 1;
		$this->PaymentID = 1;
		$this->ReceiptID = 1;
		$this->Type = 0;
		$this->InternalCode = "";
		$this->ExternalCode = "";
		$this->Note = "";
		$this->Count = 1;
		$this->Units = "Each";
		$this->Price = 0.00;
		$this->Local = 1.00;
		$this->Value = 0.00;
		$this->TaxRate = 0.00;
		$this->Tax = 0.00;
		$this->Total = 0.00;
		$this->Payment = 0.00;
		$this->Receipt = 0.00;
		$this->Balance = 0.00;
		$this->Date = NULL;
		$this->Paid = NULL;
		$this->Due = NULL;
		$this->Created = NULL;
		$this->Updated = NULL;
		return (true);
	}

# ====================================================================
#
# Transaction Fetch Method;
#
#
#
# --------------------------------------------------------------------

	public function Fetch ($ID) 
	{
		$query = "SELECT * FROM Transaction WHERE ID=(${ID})";
		Transaction::Event (__METHOD__, __LINE__, $query);
		if (!$table=mysql_query($query, Transaction::$db)) 
		{
			Transaction::Error (__METHOD__, __LINE__, "Can't fetch Transaction ${ID}", mysql_error(Transaction::$db));
			return (false);
		}
		if (!$field=mysql_fetch_object($table)) 
		{
			Transaction::Error (__METHOD__, __LINE__, "Can't fetch Transaction ${ID}", "No such Transaction");
			return (false);
		}
		$this->ID = $field->ID;
		$this->ContactID = $field->ContactID;
		$this->ProjectID = $field->ProjectID;
		$this->PaymentID = $field->PaymentID;
		$this->ReceiptID = $field->ReceiptID;
		$this->Type = $field->Type;
		$this->InternalCode = $field->InternalCode;
		$this->ExternalCode = $field->ExternalCode;
		$this->Note = $field->Name;
		$this->Count = $field->Count;
		$this->Units = $field->Units;
		$this->Price = $field->Price;
		$this->Local = $field->Local;
		$this->Value = $field->Value;
		$this->TaxRate = $field->TaxRate;
		$this->Tax = $field->Tax;
		$this->Total = $field->Total;
		$this->Payment = $field->Payment;
		$this->Receipt = $field->Receipt;
		$this->Balance = $field->Balance;
		$this->Date = $field->Date;
		$this->Paid = $field->Paid;
		$this->Due = $field->Due;
		$this->Created = $field->Created;
		$this->Updated = $field->Updated;
		return (true);
	}

# ====================================================================
#
# Transaction Store Method;
#
#
#
# --------------------------------------------------------------------

	public function Store () 
	{
		if (empty($this->Date)) 
		{
			$this->Date = date("Y-m-d");
		}
		if ($this->ID) 
		{
			$query = "UPDATE Transaction SET ContactID=($this->ContactID),ProjectID=($this->ProjectID),PaymentID=($this->PaymentID),ReceiptID=($this->ReceiptID),Type='$this->Type',InternalCode='$this->InternalCode',ExternalCode='$this->ExternalCode',Note='$this->Note',Count=($this->Count),Units='$this->Units',Price=($this->Price),Local=($this->Local),Value=($this->Value),TaxRate=($this->TaxRate),Tax=($this->Tax),Total=($this->Total),Payment=($this->Payment),Receipt=($this->Receipt),Balance=($this->Balance),Date='$this->Date',Paid='$this->Paid',Due='$this->Due',Created='$this->Created',Updated=NOW() WHERE ID=$this->ID";
		}
		else 
		{
			$query = "INSERT INTO Transaction (ContactID,ProjectID,PaymentID,ReceiptID,Type,InternalCode,ExternalCode,Note,Count,Units,Price,Local,Value,TaxRate,Tax,Total,Payment,Receipt,Balance,Date,Paid,Due,Created,Updated) VALUES (($this->ContactID),($this->ProjectID),($this->PaymentID),($this->ReceiptID),'$this->Type','$this->InternalCode','$this->ExternalCode','$this->Note',($this->Count),'$this->Units',($this->Price),($this->Local),($this->Value),($this->TaxRate),($this->Tax),($this->Total),($this->Payment),($this->Receipt),($this->Balance),'$this->Date','$this->Paid','$this->Due',NOW(),NOW())";
		}
		Transaction::Event (__METHOD__, __LINE__, $query);
		if (!$transactions=mysql_query($query, Transaction::$db)) 
		{
			Transaction::Error (__METHOD__, __LINE__, "Can't store Transaction $this->Note", mysql_error(Transaction::$db));
			return (false);
		}

#               if (!$this->ID)
#               {
#                       $this->ID = mysql_insert_id(Transaction::$db);
#               }

		return (true);
	}

# ====================================================================
#
# Transaction State Method;
#
#
#
# --------------------------------------------------------------------

	public function State() 
	{
		echo __METHOD__;
		echo " ContactID=($this->ContactID)";
		echo " ProjectID=($this->ProjectID)";
		echo " PaymentID=($this->PaymentID)";
		echo " ReceiptID=($this->ReceiptID)";
		echo " Type=($this->Type)";
		echo " InternalCode=[$this->InternalCode]";
		echo " ExternalCode=[$this->ExternalCode]";
		echo " Name=[$this->Name]";
		echo " Count=($this->Count)";
		echo " Units='$this->Units'";
		echo " Price=($this->Price)";
		echo " Local=($this->Local)";
		echo " Value=($this->Value)";
		echo " TaxRate=($this->TaxRate)";
		echo " Tax=($this->Tax)";
		echo " Total=($this->Total)";
		echo " Payment=($this->Payment)";
		echo " Receipt=($this->Receipt)";
		echo " Balance=($this->Balance)";
		echo "<br/>";
		return (true);
	}

# ====================================================================
#
# Transaction SelectContact;
#
#
#
# --------------------------------------------------------------------

	public function SelectContact()
	{
		$contacts = mysql_query("SELECT ID, Code, Name FROM Contact WHERE Type=(1)", Transaction::$db); 
		while ($contact = mysql_fetch_object ($contacts)) 
		{ 
			echo "<option value='$contact->ID'>$contact->Code - $contact->Name</option>\n"; 
		}
		return;
	}

# ====================================================================
#
# Transaction SelectProject;
#
#
#
# --------------------------------------------------------------------

	public function SelectProject()
	{
		$projects = mysql_query("SELECT ID, Code, Name FROM Project", Transaction::$db); 
		while ($project = mysql_fetch_object ($projects)) 
		{ 
			echo "<option value='$project->ID'>$project->Code - $project->Name</option>\n"; 
		}
		return;
	}

# ====================================================================
#
# Transaction SelectAccount;
#
#
#
# --------------------------------------------------------------------

	public function SelectAccount($ControlID)
	{
		if (!is_integer($ControlID)) 
		{
			Transaction::Error (__METHOD__, __LINE__, "Can't select Accounts under '${ControlID}'", "Property is integer");
			return;
		}
		$accounts = mysql_query("SELECT ID, Code, Name FROM Account WHERE ControlID=($ControlID) ORDER BY Code", Transaction::$db); 
		while ($account = mysql_fetch_object ($accounts)) 
		{ 
			echo "<option value='$account->ID'>$account->Code - $account->Name</option>\n"; 
		}
		return;
	}

# ====================================================================
#
# Transaction SelectAccountGroup Method;
#
# Return an associative array of component Account codes ordered by 
# Account number; 
#
# --------------------------------------------------------------------

	public function SelectAccountGroup ($AccountID) 
	{
		if (!is_integer($AccountID)) 
		{
			Transaction::Error (__METHOD__, __LINE__, "Can't select Accounts under ($AccountID)", "Key must be integer");
			return;
		}
		$query = "SELECT ID, ControlID, Code, Name FROM Account WHERE ControlID=($AccountID)";
		$accounts = mysql_query($query, Transaction::$db);
		while ($account = mysql_fetch_object($accounts)) 
		{
			echo "<option value='$account->ID'>$account->Code - $account->Name</option>\n"; 
			Transaction::SelectAccountGroup ((int)($account->ID));
		}
		return;
	}

# ====================================================================
#
# Transaction SelectPayment;
#
#
#
# --------------------------------------------------------------------

	public function SelectPayment()
	{
		$accounts = mysql_query("SELECT ID, Code, Name FROM Account", Transaction::$db); 
		while ($account = mysql_fetch_object ($accounts)) 
		{ 
			echo "<option value='$account->ID'>$account->Code - $account->Name</option>\n"; 
		}
		return;
	}

# ====================================================================
#
# Transaction SelectReceipt;
#
#
#
# --------------------------------------------------------------------

	public function SelectReceipt()
	{
		$accounts = mysql_query("SELECT ID, Code, Name FROM Account", Transaction::$db); 
		while ($account = mysql_fetch_object ($accounts)) 
		{ 
			echo "<option value='$account->ID'>$account->Code - $account->Name</option>\n"; 
		}
		return;
	}

# ====================================================================
#
# Transaction SelectType;
#
#
#
# --------------------------------------------------------------------

	public function SelectType()
	{
		$types = mysql_query("SELECT Code, Name FROM Transfer ORDER BY ID", Transaction::$db); 
		while ($type = mysql_fetch_object ($types)) 
		{ 
			echo "<option value='$type->Code'>$type->Name</option>\n"; 
		}
		return;
	}

# ====================================================================
#
# Transaction Event Method;
#
#
#
# --------------------------------------------------------------------

	public function Event ($Method, $Line, $Event) 
	{
		Error ($Method, $Line, $Event, $Label, Transaction::$trace);
		return ($this);
	}

# ====================================================================
#
# Transaction Error Method;
#
#
#
# --------------------------------------------------------------------

	public function Error ($Method, $Line, $Error, $Cause) 
	{
		Error ($Method, $Line, $Error.": ".$Cause, Transaction::$debug);
		return ($this);
	}

# ====================================================================
# Transaction Constructor;
# --------------------------------------------------------------------

	public function __construct ($db) 
	{
		Transaction::$db = $db;
		return;
	}

# ====================================================================
# Transaction Destructor;
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
