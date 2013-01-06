<?php

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
	private $ContactID = 0;
	private $ProjectID = 0;
	private $PaymentID = 0;
	private $ReceiptID = 0;
	private $Type = "NT";
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
	private static $debug = 0;
	private static $trace = 0;
	private $db = NULL;

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
		return (self::$debug);
	}
	public function SetDebug ($Debug) 
	{
		if (!is_integer($Debug)) 
		{
			printf ("Transaction: Can't set Debug to '${Debug}': Property is integer.\n");
			return ($this);
		}
		self::$debug = $Debug;
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
		return (self::$trace);
	}
	public function SetTrace ($Trace) 
	{
		if (!is_integer($Trace)) 
		{
			printf ("Transaction: Can't set Trace to '${Trace}': Property is integer.\n");
			return ($this);
		}
		self::$trace = $Trace;
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
#                       Transaction::Error ("Can't set ID to '${ID}'", "Property is integer");
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
			Transaction::Error ("Can't set ContactID to '${ContactID}'", "Property is integer");
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
		if (!$ContactID=spcdb::GetID($Contact, "Contact", $this->db)) 
		{
			Transaction::Error ("Can't set ContactID to ${Contact}", "No such Contact");
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
			Transaction::Error ("Can't set ProjectID to '${ProjectID}'", "Property is integer");
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
# Account is the source of funds for this transaction which causes
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
			Transaction::Error ("Can't set PaymentID to '${AccountID}'", "Property is integer");
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
		if (!$PaymentID=Database::GetID($Account, "Account", $this->db)) 
		{
			Transaction::Error ("Can't set PaymentID to ${Account}", "No such Account");
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
# Account is the target of funds for this transaction which causes
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
			Transaction::Error ("Can't set ReceiptID to '${AccountID}'", "Property is integer");
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
		if (!$ReceiptID=Database::GetID($Account, "Account", $this->db)) 
		{
			Transaction::Error ("Can't set ReceiptID to ${Account}", "No such Account");
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
			Transaction::Error ("Can't set Count to '${Count}'", "Property is integer");
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
			Transaction::Error ("Can't set Price to '${Price}'", "Property is float");
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
			Transaction::Error ("Can't set Local to '${Local}'", "Property is float");
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
			Transaction::Error ("Can't set Value to '${Value}'", "Property is float");
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
			Transaction::Error ("Can't set TaxRate to '${TaxRate}'", "Property is float");
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
		$this->Tax = $this->GetValue() * $this->GetTaxRate();
		return ($this->Tax);
	}
	public function SetTax ($Tax) 
	{
		if (!is_float($Tax)) 
		{
			Transaction::Error ("Can't set Tax to '${Tax}'", "Property is float");
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
		$this->Total = $this->GetValue() + $this->GetTax();
		$this->Balance = $this->Total;
		$this->Payment = 0.00;

#               $this->Receipt = 0.00;

		return ($this->Total);
	}

#       public function SetTotal ($Total)
# 
#       {
#               if (!is_float($Total))
#               {
#                       Transaction::Error ("Can't set Total to '${Total}'", "Property is float");
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
			Transaction::Error ("Can't set Payment to '${Payment}'", "Property is float");
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
			Transaction::Error ("Can't set Receipt to '${Receipt}'", "Property is float");
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
			Transaction::Error ("Can't set Balance to '${Balance}'", "Property is float");
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
		Transaction::Event ("Clearing Object Properties", "");
		$this->ID = 0;
		$this->ContactID = 0;
		$this->ProjectID = 0;
		$this->PaymentID = 0;
		$this->ReceiptID = 0;
		$this->Type = "NT";
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
# Transaction Peek Method;
#
#
#
# --------------------------------------------------------------------

	public function peek() 
	{
		printf ("Count=($this->Count)\n");
		printf ("Units=[$this->Units]\n");
		printf ("Price=($this->Price)\n");
		printf ("Local=($this->Local)\n");
		printf ("Value=($this->Value)\n");
		printf ("TaxRate=($this->TaxRate)\n");
		printf ("Tax=($this->Tax)\n");
		printf ("Total=($this->Total)\n");
		printf ("Payment=($this->Payment)\n");
		printf ("Receipt=($this->Receipt)\n");
		printf ("Balance=($this->Balance)\n");
		printf ("\n");
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
		Transaction::Event ($query, "");
		if (!$table=mysql_query($query, $this->db)) 
		{
			Transaction::Error ("Can't fetch Transaction ${ID}", mysql_error($this->db));
			return (false);
		}
		if (!$field=mysql_fetch_object($table)) 
		{
			Transaction::Error ("Can't fetch Transaction ${ID}", "No such Transaction");
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
			$query = "UPDATE Transaction SET ContactID=($this->ContactID),ProjectID=($this->ProjectID),PaymentID=($this->PaymentID),ReceiptID=($this->ReceiptID),Type='$this->Type',InternalCode='$this->InternalCode',ExternalCode='$this->ExternalCode',Note='$this->Note',Count=($this->Count),Units='$this->Units',Price=($this->Price),Local=($this->Local),Value=($this->Value),TaxRate=($this->TaxRate),Tax=($this->Tax),Total=($this->Total),Payment=($this->Payment),Balance=($this->Balance),Date='$this->Date',Paid='$this->Paid',Due='$this->Due',Created='$this->Created',Updated=NOW() WHERE ID=$this->ID";
		}
		else 
		{
			$query = "INSERT INTO Transaction (ContactID,ProjectID,PaymentID,ReceiptID,Type,InternalCode,ExternalCode,Note,Count,Units,Price,Local,Value,TaxRate,Tax,Total,Payment,Balance,Date,Paid,Due,Created,Updated) VALUES (($this->ContactID),($this->ProjectID),($this->PaymentID),($this->ReceiptID),'$this->Type','$this->InternalCode','$this->ExternalCode','$this->Note',($this->Count),'$this->Units',($this->Price),($this->Local),($this->Value),($this->TaxRate),($this->Tax),($this->Total),($this->Payment),($this->Balance),'$this->Date','$this->Paid','$this->Due',NOW(),NOW())";
		}
		Transaction::Event ($query, "");
		if (!$transactions=mysql_query($query, $this->db)) 
		{
			Transaction::Error ("Can't store Transaction $this->Note", mysql_error($this->db));
			return (false);
		}

#               if (!$this->ID)
#               {
#                       $this->ID = mysql_insert_id($this->db);
#               }

		return (true);
	}

# ====================================================================
#
# Transaction Event Method;
#
#
#
# --------------------------------------------------------------------

	public function Event ($event, $label) 
	{
		if (self::$trace == 1) 
		{
			printf ("<br><span class='event'>Transaction: %s;</span><br>", cmassoc::combine($event, ": ", $label));
		}
		if (self::$trace == 2) 
		{
			printf ("Transaction: %s;\n", cmassoc::combine($event, ": ", $label));
		}
		return ($this);
	}

# ====================================================================
#
# Transaction Error Method;
#
#
#
# --------------------------------------------------------------------

	public function Error ($error, $cause) 
	{
		if (self::$debug == 1) 
		{
			printf ("<br><span class='error'>Transaction: %s;</span><br>", cmassoc::combine($error, ": ", $cause));
		}
		if (self::$debug == 2) 
		{
			printf ("Transaction: %s;\n", cmassoc::combine($error, ": ", $cause));
		}
		return ($this);
	}

# ====================================================================
# Transaction Constructor;
# --------------------------------------------------------------------

	public function __construct ($db) 
	{
		$this->db = $db;
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
