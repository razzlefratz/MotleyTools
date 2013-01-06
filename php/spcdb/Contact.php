<?php

# ====================================================================
# 
# Begin Contact Class Definition;
# 
# 
# Published 2005 by Charles Maier Associates Limited for internal use;
# Generated 02:38:24 Mon 29 Aug 2005 EDT by MySQL.php;
# 
# --------------------------------------------------------------------

class Contact 
{

# ====================================================================
# Public Variables;
# --------------------------------------------------------------------

# ====================================================================
# Private Variables;
# --------------------------------------------------------------------

	private $ID = 0;
	private $ContactID = 0;
	private $Type = 0;
	private $Code = "";
	private $Name = "";
	private $Title = "";
	private $FirstName = "";
	private $MiddleName = "";
	private $LastName = "";
	private $Honors = "";
	private $Organization = "";
	private $Division = "";
	private $Building = "";
	private $Street = "";
	private $City = "";
	private $State = "";
	private $Postcode = "";
	private $Phone = "";
	private $Fax = "";
	private $EMail = "";
	private $SSN = "0000-00-0000";
	private $Opened = NULL;
	private $Closed = NULL;
	private $Created = NULL;
	private $Updated = NULL;
	private $table = NULL;
	private $field = NULL;
	private $query = NULL;

	private static $debug = 0;
	private static $trace = 0;
	private static $db = NULL;

# ====================================================================
#
# Contact Debug Property;
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
			printf ("Contact: Can't set Debug to '${Debug}': Property is integer.\n");
			return ($this);
		}
		self::$debug = $Debug;
		return ($this);
	}

# ====================================================================
#
# Contact Trace Property;
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
			printf ("Contact: Can't set Trace to '${Trace}': Property is integer.\n");
			return ($this);
		}
		self::$trace = $Trace;
		return ($this);
	}

# ====================================================================
# 
# Contact ID Property;
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
#                       Contact::Error ("Can't set ID to '${ID}'", "Property is integer");
#                       return (false);
#               }
#
#               $this->ID = $ID;
#               return (true);
#       }


# ====================================================================
#
# Public Property ContactID;
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
		if (!$ContactID=spcdb::GetID($Contact, "Contact", self::$db)) 
		{
			Account::Error ("Can't set ContactID to ${Contact}", "No such Contact");
			return (false);
		}
		$this->ContactID = $ContactID;
		return (true);
	}

# ====================================================================
# 
# Contact Type Property;
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
			Contact::Error ("Can't set Type to '${Type}'", "Property is integer");
			return (false);
		}
		$this->Type = $Type;
		return (true);
	}

# ====================================================================
# 
# Contact Code Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetCode () 
	{
		if (empty($this->Code)) 
		{
			$this->Code = $this->FirstName[0].$this->MiddleName[0].$this->LastName[0];
		}
		return ($this->Code);
	}
	public function SetCode ($Code) 
	{
		$this->Code = $Code;
		return (true);
	}

# ====================================================================
# 
# Contact Name Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetName () 
	{
		if (empty($this->Name)) 
		{
			$this->Name = $this->Title;
			$this->Name = cmassoc::combine($this->Name, " ", $this->FirstName);
			$this->Name = cmassoc::combine($this->Name, " ", $this->MiddleName);
			$this->Name = cmassoc::combine($this->Name, " ", $this->LastName);
		}
		return ($this->Name);
	}
	public function SetName ($Name) 
	{
		$this->Name = $Name;
		return (true);
	}

# ====================================================================
# 
# Contact Title Property;
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
# Contact FirstName Property;
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
# Contact MiddleName Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetMiddleName () 
	{
		return ($this->MiddleName);
	}
	public function SetMiddleName ($MiddleName) 
	{
		$this->MiddleName = $MiddleName;
		return (true);
	}

# ====================================================================
# 
# Contact LastName Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetLastName () 
	{
		return ($this->LastName);
	}
	public function SetLastName ($LastName) 
	{
		$this->LastName = $LastName;
		return (true);
	}

# ====================================================================
# 
# Contact Honors Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetHonors () 
	{
		return ($this->Honors);
	}
	public function SetHonors ($Honors) 
	{
		$this->Honors = $Honors;
		return (true);
	}

# ====================================================================
# 
# Contact Organization Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetOrganization () 
	{
		return ($this->Organization);
	}
	public function SetOrganization ($Organization) 
	{
		$this->Organization = $Organization;
		return (true);
	}

# ====================================================================
# 
# Contact Division Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetDivision () 
	{
		return ($this->Division);
	}
	public function SetDivision ($Division) 
	{
		$this->Division = $Division;
		return (true);
	}

# ====================================================================
# 
# Contact Building Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetBuilding () 
	{
		return ($this->Building);
	}
	public function SetBuilding ($Building) 
	{
		$this->Building = $Building;
		return (true);
	}

# ====================================================================
# 
# Contact Street Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetStreet () 
	{
		return ($this->Street);
	}
	public function SetStreet ($Street) 
	{
		$this->Street = $Street;
		return (true);
	}

# ====================================================================
# 
# Contact City Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetCity () 
	{
		return ($this->City);
	}
	public function SetCity ($City) 
	{
		$this->City = $City;
		return (true);
	}

# ====================================================================
# 
# Contact State Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetState () 
	{
		return ($this->State);
	}
	public function SetState ($State) 
	{
		$this->State = $State;
		return (true);
	}

# ====================================================================
# 
# Contact Postcode Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetPostcode () 
	{
		return ($this->Postcode);
	}
	public function SetPostcode ($Postcode) 
	{
		$this->Postcode = $Postcode;
		return (true);
	}

# ====================================================================
# 
# Contact Phone Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetPhone () 
	{
		return ($this->Phone);
	}
	public function SetPhone ($Phone) 
	{
		$this->Phone = $Phone;
		return (true);
	}

# ====================================================================
# 
# Contact Fax Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetFax () 
	{
		return ($this->Fax);
	}
	public function SetFax ($Fax) 
	{
		$this->Fax = $Fax;
		return (true);
	}

# ====================================================================
# 
# Contact EMail Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetEMail () 
	{
		return ($this->EMail);
	}
	public function SetEMail ($EMail) 
	{
		$this->EMail = $EMail;
		return (true);
	}

# ====================================================================
# 
# Contact SSN Property; 
# 
# 
# 
# --------------------------------------------------------------------

	public function GetSSN () 
	{
		return ($this->SSN);
	}
	public function SetSSN ($SSN) 
	{
		$this->SSN = $SSN;
		return (true);
	}

# ====================================================================
# 
# Contact Opened Property;
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
# Contact Closed Property;
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
# Contact Created Property;
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
# Contact Updated Property;
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
#  Contact Clear Method;
# 
# 
# 
# --------------------------------------------------------------------

	public function Clear () 
	{
		Contact::Event ("Clearing Object Properties", "");
		$this->ID = 0;
		$this->ContactID = 0;
		$this->Type = 0;
		$this->Code = "";
		$this->Name = "";
		$this->Title = "";
		$this->FirstName = "";
		$this->MiddleName = "";
		$this->LastName = "";
		$this->Honors = "";
		$this->Organization = "";
		$this->Division = "";
		$this->Building = "";
		$this->Street = "";
		$this->City = "";
		$this->State = "";
		$this->Postcode = "";
		$this->Phone = "";
		$this->Fax = "";
		$this->EMail = "";
		$this->SSN = "0000-00-0000";
		$this->Opened = NULL;
		$this->Closed = NULL;
		$this->Created = NULL;
		$this->Updated = NULL;
		return (true);
	}

# ====================================================================
# 
# Contact Fetch Method;
# 
# 
# 
# --------------------------------------------------------------------

	public function Fetch ($Contact) 
	{
		if (is_numeric($Contact)) 
		{
			$query = "SELECT * FROM Contact WHERE ID=(${Contact})";
		}
		else 
		{
			$query = "SELECT * FROM Contact WHERE Code='${Contact}'";
		}
		Contact::Event ($query, "");
		if (!$table=mysql_query($query, self::$db)) 
		{
			Contact::Error ("Can't fetch Contact '${Contact}'", mysql_error(self::$db));
			return (false);
		}
		if (!$field=mysql_fetch_object($table)) 
		{
			Contact::Error ("Can't fetch Contact '${Contact}'", "No such Contact");
			return (false);
		}
		$this->ID = $field->ID;
		$this->ContactID = $field->ContactID;
		$this->Type = $field->Type;
		$this->Code = $field->Code;
		$this->Name = $field->Name;
		$this->Title = $field->Title;
		$this->FirstName = $field->FirstName;
		$this->MiddleName = $field->MiddleName;
		$this->LastName = $field->LastName;
		$this->Honors = $field->Honors;
		$this->Organization = $field->Organization;
		$this->Division = $field->Division;
		$this->Building = $field->Building;
		$this->Street = $field->Street;
		$this->City = $field->City;
		$this->State = $field->State;
		$this->Postcode = $field->Postcode;
		$this->Phone = $field->Phone;
		$this->Fax = $field->Fax;
		$this->EMail = $field->EMail;
		$this->SSN = $field->SSN;
		$this->Opened = $field->Opened;
		$this->Closed = $field->Closed;
		$this->Created = $field->Created;
		$this->Updated = $field->Updated;
		return (true);
	}

# ====================================================================
# 
# Contact Store Method;
# 
# 
# 
# --------------------------------------------------------------------

	public function Store () 
	{
		Contact::GetCode();
		Contact::GetName();

		if (empty($this->Code)) 
		{
			Contact::Error ("Can't store Contact", "Code is empty");
			return (false);
		}
		if (empty($this->Name)) 
		{
			Contact::Error ("Can't store Contact", "Name is empty");
			return (false);
		}
		if ($this->ID) 
		{
			$query = "UPDATE Contact SET ContactID=($this->ContactID),Type=($this->Type),Code='$this->Code',Name='$this->Name',Title='$this->Title',FirstName='$this->FirstName',MiddleName='$this->MiddleName',LastName='$this->LastName',Honors='$this->Honors',Organization='$this->Organization',Division='$this->Division',Building='$this->Building',Street='$this->Street',City='$this->City',State='$this->State',Postcode='$this->Postcode',Phone='$this->Phone',Fax='$this->Fax',EMail='$this->EMail',SSN='$this->SSN',Opened='$this->Opened',Closed='$this->Closed',Created='$this->Created',Updated=NOW() WHERE ID=($this->ID)";
		}
		else 
		{
			$query = "INSERT INTO Contact (ContactID,Type,Code,Name,Title,FirstName,MiddleName,LastName,Honors,Organization,Division,Building,Street,City,State,Postcode,Phone,Fax,EMail,SSN,Opened,Closed,Created,Updated) VALUES (('$this->ContactID'),('$this->Type'),'$this->Code','$this->Name','$this->Title','$this->FirstName','$this->MiddleName','$this->LastName','$this->Honors','$this->Organization','$this->Division','$this->Building','$this->Street','$this->City','$this->State','$this->Postcode','$this->Phone','$this->Fax','$this->EMail','$this->SSN','$this->Opened','$this->Closed',NOW(),NOW())";
		}
		Contact::Event ($query, "");
		if (!mysql_query($query, self::$db)) 
		{
			Contact::Error ("Can't store Contact $this->Code", mysql_error(self::$db));
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
# Contact Error Method;
#
#
#
# --------------------------------------------------------------------

	public function Error ($error, $cause) 
	{
		if (self::$debug == 1) 
		{
			printf ("<br><span class='error'>Contact: %s;</span><br>", cmassoc::combine($error, ": ", $cause));
		}
		if (self::$debug == 2) 
		{
			printf ("Contact: %s;\n", cmassoc::combine($error, ": ", $cause));
		}
		return ($this);
	}

# ====================================================================
#
# Contact Event Method;
#
#
#
# --------------------------------------------------------------------

	public function Event ($event, $label) 
	{
		if (self::$trace == 1) 
		{
			printf ("<br><span class='error'>Contact: %s;</span><br>", cmassoc::combine($event, ": ", $label));
		}
		if (self::$trace == 2) 
		{
			printf ("Contact: %s;\n", cmassoc::combine($event, ": ", $label));
		}
		return ($this);
	}

# ====================================================================
# 
# Contact Constructor;
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
# Contact Destructor;
# 
# 
# 
# --------------------------------------------------------------------

	public function __destruct () 
	{
		return;
	}

# ====================================================================
# End Contact Class Definition;
# --------------------------------------------------------------------

}
 ?>
