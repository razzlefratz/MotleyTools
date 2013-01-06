<?php

# ====================================================================
# 
# Begin Member Class Definition;
# 
# 
# Published 2005 by Charles Maier Associates Limited for internal use;
# Generated 02:38:24 Mon 29 Aug 2005 EDT by MySQL.php;
# 
# --------------------------------------------------------------------

class Member 
{

# ====================================================================
# Public Variables;
# --------------------------------------------------------------------


# ====================================================================
# Private Variables;
# --------------------------------------------------------------------

	private $Contact = NULL;
	private $Account = NULL;

	private $query = NULL;
	private $table = NULL;
	private $field = NULL;

	private static $debug = 0;
	private static $trace = 0;
	private static $db = NULL;

# ====================================================================
#
# xxxx Debug Property;
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
		$this->Contact->Debug = $Debug;
		$this->Account->Debug = $Debug;
		$this->$Debug = $Debug;
		return ($this);
	}

# ====================================================================
#
# xxxx Trace Property;
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
		$this->Contact->Trace = $Trace;
		$this->Account->Trace = $Trace;
		self::$trace = $Trace;
		return ($this);
	}

# ====================================================================
# 
# Public Property ID;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetID () 
	{
		return (Contact::GetID());
	}

#       public function SetID ($ID)
#
#       {
#               Contact::SetID($ID);
#               return (true);
#       }


# ====================================================================
# 
# Public Property Code;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetCode () 
	{
		return (Contact::GetCode());
	}
	public function SetCode ($Code) 
	{
		Contact::SetCode($Code);
		return (true);
	}

# ====================================================================
# 
# Public Property Name;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetName () 
	{
		return (Contact::GetName());
	}
	public function SetName ($Name) 
	{
		Contact::SetName($Name);
		return (true);
	}

# ====================================================================
# 
# Public Property Title;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetTitle () 
	{
		return ($this->Title);
	}
	public function SetTitle ($Title) 
	{
		$this->Title = $Title;
		return (true);
	}

# ====================================================================
# 
# Public Property FirstName;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetFirstName () 
	{
		return ($this->FirstName);
	}
	public function SetFirstName ($FirstName) 
	{
		$this->FirstName = $FirstName;
		return (true);
	}

# ====================================================================
# 
# Public Property MiddleName;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetMiddleName () 
	{
		return (Contact::GetMiddleName());
	}
	public function SetMiddleName ($MiddleName) 
	{
		Contact::SetMiddleName($MiddleName);
		return (true);
	}

# ====================================================================
# 
# Public Property LastName;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetLastName () 
	{
		return (Contact::GetLastName());
	}
	public function SetLastName ($LastName) 
	{
		Contact::SetLastName($LastName);
		return (true);
	}

# ====================================================================
# 
# Public Property Honors;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetHonors () 
	{
		return (Contact::GetHonors());
	}
	public function SetHonors ($Honors) 
	{
		Contact::SetHonors($Honors);
		return (true);
	}

# ====================================================================
# 
# Public Property Building;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetBuilding () 
	{
		return (Contact::GetBuilding());
	}
	public function SetBuilding ($Building) 
	{
		Contact::SetBuilding($Building);
		return (true);
	}

# ====================================================================
# 
# Public Property Street;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetStreet () 
	{
		return (Contact::GetStreet());
	}
	public function SetStreet ($Street) 
	{
		Contact::SetStreet($Street);
		return (true);
	}

# ====================================================================
# 
# Public Property City;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetCity () 
	{
		return (Contact::GetCity());
	}
	public function SetCity ($City) 
	{
		Contact::SetCity($City);
		return (true);
	}

# ====================================================================
# 
# Public Property State;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetState () 
	{
		return (Contact::GetState());
	}
	public function SetState ($State) 
	{
		Contact::SetState($State);
		return (true);
	}

# ====================================================================
# 
# Public Property Postcode;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetPostcode () 
	{
		return (Contact::GetPostCode());
	}
	public function SetPostcode ($Postcode) 
	{
		Contact::SetPostcode($Postcode);
		return (true);
	}

# ====================================================================
# 
# Public Property Phone;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetPhone () 
	{
		return (Contact::GetPhone());
	}
	public function SetPhone ($Phone) 
	{
		Contact::SetPhone($Phone);
		return (true);
	}

# ====================================================================
# 
# Public Property Fax;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetFax () 
	{
		return (Contact::GetFax());
	}
	public function SetFax ($Fax) 
	{
		Contact::SetFax($Fax);
		return (true);
	}

# ====================================================================
# 
# Public Property Email;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetEmail () 
	{
		return (Contact::GetEmail());
	}
	public function SetEmail ($Email) 
	{
		Contact::SetEmail($Email);
		return (true);
	}

# ====================================================================
# 
# Public Property SSN;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetSSN () 
	{
		return (Contact::GetSSN());
	}
	public function SetSSN ($SSN) 
	{
		Contact::SetSSN($SNN);
		return (true);
	}

# ====================================================================
# 
# Public Property Opened;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetOpened () 
	{
		return (Contact::GetOpened());
	}
	public function SetOpened ($Opened) 
	{
		Contact::SetOpened($Opened);
		return (true);
	}

# ====================================================================
# 
# Public Property Closed;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetClosed () 
	{
		return (Contact::GetClosed());
	}
	public function SetClosed ($Closed) 
	{
		Contact::SetClosed($Closed);
		return (true);
	}

# ====================================================================
# 
# Public Property Created;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetCreated () 
	{
		return (Contact::GetCreated());
	}

#       public function SetCreated ($Created)
#
#       {
#               Contact::SetCreated($Created);
#               return (true);
#       }


# ====================================================================
# 
# Public Property Updated;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetUpdated () 
	{
		return (Contact::GetUpdated());
	}

#       public function SetUpdated ($Updated)
#
#       {
#               Contact::SetUpdated($Updated);
#               return (true);
#       }


# ====================================================================
# 
#  Clear Method;
# 
# 
# 
# --------------------------------------------------------------------

	public function Clear () 
	{
		Contact::Clear();
		Account::Clear();
		return (true);
	}

# ====================================================================
# 
# Member Fetch Method;
# 
# 
# 
# --------------------------------------------------------------------

	public function Fetch ($Contact) 
	{
		Contact::Fetch($Contact);
		return (true);
	}

# ====================================================================
# 
# Member Store Method;
# 
# 
# 
# --------------------------------------------------------------------

	public function Store () 
	{
Contact::SetDebug(2);
Contact::SetTrace(2);
#		Contact::Event ("Creating Contact", Contact::GetCode());
		Contact::Store();
#		Account::Event ("Creating Account", Contact::GetCode());
		Account::SetAccount("MEMBERS");
		Account::SetContact(Contact::GetCode());
		Account::SetCode(Contact::GetCode());
		Account::SetName(Contact::GetName());
		Account::Store();
		return (true);
	}

# ====================================================================
#
# Member Error Method;
#
#
#
# --------------------------------------------------------------------

	public function Error ($error, $cause) 
	{
		if (self::$debug == 1) 
		{
			printf ("<br><span class='error'>Member: %s;</span><br>", cmassoc::combine($error, ": ", $cause));
		}
		if (self::$debug == 2) 
		{
			printf ("Member: %s;\n", cmassoc::combine($error, ": ", $cause));
		}
		return ($this);
	}

# ====================================================================
#
# Member Event Method;
#
#
#
# --------------------------------------------------------------------

	public function Event ($event, $label) 
	{
		if (self::$trace == 1) 
		{
			printf ("<br><span class='error'>Member: %s;</span><br>", cmassoc::combine($event, ": ", $label));
		}
		if (self::$trace == 2) 
		{
			printf ("Member: %s;\n", cmassoc::combine($event, ": ", $label));
		}
		return ($this);
	}

# ====================================================================
# 
# Member Constructor;
# 
# 
# 
# --------------------------------------------------------------------

	public function __construct ($db) 
	{
		$this->Contact = new Contact ($db);
		$this->Account = new Account ($db);
		self::$db = $db;
		return;
	}

# ====================================================================
# 
# Member Destructor;
# 
# 
# 
# --------------------------------------------------------------------

	public function __destruct () 
	{
		return;
	}

# ====================================================================
# End Member Class Definition;
# --------------------------------------------------------------------

}
 ?>
