<?php
require "constants.php";

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
	private $ControlID = 1;
	private $ContactID = 1;
	private $Type = 0;
	private $Code = "";
	private $Name = "";
	private $Payments = 0.00;
	private $Receipts = 0.00;
	private $Increase = 0.00;
	private $Decrease = 0.00;
	private $Turnover = 0.00;
	private $Balance = 0.00;
	private $Opened = NULL;
	private $Closed = NULL;
	private $Created = NULL;
	private $Updated = NULL;
	private $field = NULL;
	private $table = NULL;
	private $query = NULL;
	private static $debug = MESSAGE_NONE;
	private static $trace = MESSAGE_NONE;
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
		return (Account::$debug);
	}
	public function SetDebug ($Debug) 
	{
		if (!is_integer($Debug)) 
		{
			printf ("Account: Can't set Debug to '$Debug': Property is integer.\n");
			return ($this);
		}
		Account::$debug = $Debug;
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
		return (Account::$debug);
	}
	public function SetTrace ($Trace) 
	{
		if (!is_integer($Trace)) 
		{
			printf ("Account: Can't set Trace to '$Trace': Property is integer.\n");
			return ($this);
		}
		Account::$trace = $Trace;
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
#                       Account::Error (__METHOD__, __LINE__,"Can't set ID to ($ID)", "Property is integer");
#                       return (false);
#               }
#
#               $this->ID = $ID;
#               return (true);
#       }


# ====================================================================
#
# Account ControlID Property;
#
#
#
# --------------------------------------------------------------------

	public function GetControlID () 
	{
		return ($this->ControlID);
	}
	public function SetControlID ($AccountID) 
	{
		if (!is_integer($AccountID)) 
		{
			Account::Error (__METHOD__, __LINE__, "Can't set ControlID to ($AccountID)", "Property is integer");
			return (false);
		}
		$this->ControlID = $AccountID;
		return (true);
	}

# ====================================================================
#
# Account SetControl Method;
#
#
# --------------------------------------------------------------------

	public function SetControl ($Account) 
	{
		if (!$AccountID = ID ($Account, "Account", Account::$db)) 
		{
			Account::Error (__METHOD__, __LINE__, "Can't set Control to '$Account'", "No such Account");
			return (false);
		}
		$this->ControlID = $AccountID;
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
			Account::Error (__METHOD__, __LINE__, "Can't set ContactID to ($ContactID)", "Property is integer");
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
		if (!$ContactID = ID ($Contact, "Contact", Account::$db)) 
		{
			Account::Error (__METHOD__, __LINE__, "Can't set Contact to '$Contact'", "No such Contact");
			return (false);
		}
		$this->ContactID = $ContactID;
		$this->Code = $Contact;
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
			Account::Error (__METHOD__, __LINE__, "Can't set Type to ($Type)", "Property is integer");
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
# Account Payments Property;
#
#
#
# --------------------------------------------------------------------

	public function GetPayments () 
	{
		return ($this->Payments);
	}

#	public function SetPayments ($Payments) 
#	{
#		if (!is_float($Payments)) 
#		{
#			Account::Error (__METHOD__, __LINE__,"Can't set Payments to ($Payments)", "Property is float");
#			return (false);
#		}
#		$this->Payments = $Payments;
#		return (true);
#	}


# ====================================================================
#
# Account Receipts Property;
#
#
#
# --------------------------------------------------------------------

	public function GetReceipts () 
	{
		return ($this->Receipts);
	}

#	public function SetReceipts ($Receipts) 
#	{
#		if (!is_float($Receipts)) 
#		{
#			Account::Error (__METHOD__, __LINE__,"Can't set Receipts to ($Receipts)", "Property is float");
#			return (false);
#		}
#		$this->Receipts = $Receipts;
#		return (true);
#	}


# ====================================================================
#
# Account Increase Property;
#
#
#
# --------------------------------------------------------------------

	public function GetIncrease () 
	{
		return (max(($this->Receipts)-($this->Payments), 0));
	}

#	public function SetIncrease ($Increase) 
#	{
#		if (!is_float($Increase)) 
#		{
#			Account::Error (__METHOD__, __LINE__,"Can't set Increase to ($Increase)", "Property is float");
#			return (false);
#		}
#		$this->Increase = $Increase;
#		return (true);
#	}


# ====================================================================
#
# Account Decrease Property;
#
#
#
# --------------------------------------------------------------------

	public function GetDecrease () 
	{
		return (max(($this->Payments)-($this->Receipts), 0));
	}

#	public function SetDecrease ($Decrease) 
#	{
#		if (!is_float($Decrease)) 
#		{
#			Account::Error (__METHOD__, __LINE__,"Can't set Decrease to ($Decrease)", "Property is float");
#			return (false);
#		}
#		$this->Decrease = $Decrease;
#		return (true);
#	}


# ====================================================================
#
# Account Turnover Property;
#
#
#
# --------------------------------------------------------------------

	public function GetTurnover () 
	{
		return ($this->Turnover);
	}

#	public function SetTurnover ($Turnover) 
#	{
#		if (!is_float($Turnover)) 
#		{
#			Account::Error (__METHOD__, __LINE__,"Can't set Turnover to ($Turnover)", "Property is float");
#			return (false);
#		}
#		$this->Turnover = $Turnover;
#		return (true);
#	}


# ====================================================================
#
# Account Balance Property;
#
#
#
# --------------------------------------------------------------------

	public function GetBalance () 
	{
		return ($this->Balance);
	}

#	public function SetBalance ($Balance) 
#	{
#		if (!is_float($Balance)) 
#		{
#			Account::Error (__METHOD__, __LINE__,"Can't set Balance to ($Balance)", "Property is float");
#			return (false);
#		}
#		$this->Balance = $Balance;
#		return (true);
#	}


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
		$this->ID = (int)(0);
		$this->ControlID = (int)(1);
		$this->ContactID = (int)(1);
		$this->Type = (int)(0);
		$this->Code = "";
		$this->Name = "";
		$this->Payments = (float)(0);
		$this->Receipts = (float)(0);
		$this->Increase = (float)(0);
		$this->Decrease = (float)(0);
		$this->Turnover = (float)(0);
		$this->Balance = (float)(0);
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
		if (is_integer($Account)) 
		{
			$query = "SELECT * FROM Account WHERE ID=($Account)";
		}
		else if (is_numeric($Account)) 
		{
			$query = "SELECT * FROM Account WHERE ID=($Account)";
		}
		else 
		{
			$query = "SELECT * FROM Account WHERE Code='$Account'";
		}
		Account::Event (__METHOD__, __LINE__, $query);
		if (!$table=mysql_query($query, Account::$db)) 
		{
			Account::Error (__METHOD__, __LINE__, "Can't fetch Account $Account", mysql_error(Account::$db));
			return (false);
		}
		if (!$field=mysql_fetch_object($table)) 
		{
			Account::Error (__METHOD__, __LINE__, "Can't fetch Account $Account", "No such Account");
			return (false);
		}
		$this->ID = $field->ID;
		$this->ControlID = $field->ControlID;
		$this->ContactID = $field->ContactID;
		$this->Type = $field->Type;
		$this->Code = $field->Code;
		$this->Name = $field->Name;
		$this->Payments = $field->Payments;
		$this->Receipts = $field->Receipts;
		$this->Increase = $field->Increase;
		$this->Decrease = $field->Decrease;
		$this->Turnover = $field->Turnover;
		$this->Balance = $field->Balance;
		$this->Opened = $field->Opened;
		$this->Closed = $field->Closed;
		$this->Created = $field->Created;
		$this->Updated = $field->Updated;
		return (true);
	}

# ====================================================================
#
# Account Store Method
#
#
#
# --------------------------------------------------------------------

	public function Store () 
	{
		if ($this->ID) 
		{
			$query = "UPDATE Account SET ControlID=($this->ControlID),ContactID=($this->ContactID),Type=($this->Type),Code='$this->Code',Name='$this->Name',Receipts=($this->Receipts),Payments=($this->Payments),Increase=($this->Increase),Decrease=($this->Decrease),Turnover=($this->Turnover),Balance=($this->Balance),Opened='$this->Opened',Closed='$this->Closed',Created='$this->Created',Updated=NOW() WHERE ID=($this->ID)";
		}
		else 
		{
			$query = "INSERT INTO Account (ControlID,ContactID,Type,Code,Name,Receipts,Payments,Turnover,Balance,Opened,Closed,Created,Updated) VALUES (($this->ControlID),($this->ContactID),($this->Type),'$this->Code','$this->Name',($this->Receipts),($this->Payments),($this->Turnover),($this->Balance),'$this->Opened','$this->Closed','$this->Created','$this->Updated')";
		}
		$query = "INSERT INTO Account (ID,ControlID,ContactID,Type,Code,Name,Receipts,Payments,Turnover,Balance,Opened,Closed,Created,Updated) VALUES (($this->ID),($this->ControlID),($this->ContactID),($this->Type),'$this->Code','$this->Name',($this->Receipts),($this->Payments),($this->Turnover),($this->Balance),'$this->Opened','$this->Closed','$this->Created','$this->Updated')";
		Account::Event (__METHOD__, __LINE__, $query);
		if (!$accounts = mysql_query($query, Account::$db)) 
		{
			Account::Error (__METHOD__, __LINE__, "Can't store $this->Code", mysql_error(Account::$db));
			return (false);
		}
		$query = "UPDATE Contact JOIN Account ON Contact.ID=Account.ContactID SET Contact.AccountID=Account.ID WHERE Contact.ID=($this->ContactID)";
		if (!$accounts = mysql_query($query, Account::$db)) 
		{
			Account::Error (__METHOD__, __LINE__, "Can't update Contact with AccountID", mysql_error(Account::$db));
			return (false);
		}
		$query = "UPDATE Account JOIN Contact ON Account.ID=Contact.AccountID SET Account.Code=Contact.Code";
		if (!$accounts = mysql_query($query, Account::$db)) 
		{
			Account::Error (__METHOD__, __LINE__, "Can't update Account with Code from Contact $this->ContactID", mysql_error(Account::$db));
			return (false);
		}
		return (true);
	}

# ====================================================================
#
# Account SelectContact;
#
#
#
# --------------------------------------------------------------------

	public function SelectContact()
	{
		$contacts = mysql_query("SELECT ID, Code, Name FROM Contact", Account::$db); 
		while ($contact = mysql_fetch_object ($contacts)) 
		{ 
			echo "<option value='$contact->ID'>$contact->Code - $contact->Name</option>"; 
		}
		return;
	}

# ====================================================================
#
# Account SelectControl;
#
#
#
# --------------------------------------------------------------------

	public function SelectControl()
	{
		$accounts = mysql_query("SELECT ID, Code, Name FROM Account WHERE NOT ID=($this->ID)", Account::$db); 
		while ($account = mysql_fetch_object ($accounts)) 
		{ 
			echo "<option value='$account->ID'>$account->Code - $account->Name</option>"; 
		}
		return;
	}

# ====================================================================
#
# Account SelectType;
#
#
#
# --------------------------------------------------------------------

	public function SelectType()
	{
		echo "<option value='0'>NONE</option>";
		echo "<option value='1'>SOME</option>";
		echo "<option value='2'>MORE</option>";
		return;
	}

# ====================================================================
#
# Account State Method;
#
#
#
# --------------------------------------------------------------------

	public function State() 
	{
		echo __METHOD__;
		echo " ID = ($this->ID)";
		echo " ControlID = ($this->ControlID)";
		echo " ContactID = ($this->ContactID)";
		echo " Type = ($this->Type)";
		echo " Code = [$this->Code]";
		echo " Name = [$this->Name]";
		echo " Receipts = ($this->Receipts)";
		echo " Payments = ($this->Payments)";
		echo " Turnover = ($this->Turnover)";
		echo " Balance = ($this->Balance)";
		echo "<br/>";
		return($this);
	}

# ====================================================================
#
# Account Event Method;
#
#
#
# --------------------------------------------------------------------

	public function Event ($Method, $Line, $Event) 
	{
		Error ($Method, $Line, $Event, Account::$trace);
		return ($this);
	}

# ====================================================================
#
# Account Error Method;
#
#
#
# --------------------------------------------------------------------

	public function Error ($Method, $Line, $Error, $Cause) 
	{
		Error ($Method, $Line, $Error.": ".$Cause, Account::$debug);
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
		Account::$db = $db;
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
