<?php

# ====================================================================
# Custom Include Files; 
# --------------------------------------------------------------------

require "constants.php";

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
	private $ControlID = 1;
	private $AccountID = 1;
	private $Type = 0;
	private $Code = "";
	private $Name = "";
	private $Username = "";
	private $Password = "";
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
	private $Region = "";
	private $Country = "";
	private $Postcode = "";
	private $Vox = "";
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
	private static $debug = MESSAGE_NONE;
	private static $trace = MESSAGE_NONE;
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
		return (Contact::$debug);
	}
	public function SetDebug ($Debug) 
	{
		if (!is_integer($Debug)) 
		{
			printf ("Contact: Can't set Debug to '${Debug}': Property is integer.\n");
			return ($this);
		}
		Contact::$debug = $Debug;
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
		return (Contact::$trace);
	}
	public function SetTrace ($Trace) 
	{
		if (!is_integer($Trace)) 
		{
			printf ("Contact: Can't set Trace to '${Trace}': Property is integer.\n");
			return ($this);
		}
		Contact::$trace = $Trace;
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
#                       Contact::Error (__METHOD__, __LINE__,"Can't set ID to '${ID}'", "Property is integer");
#                       return (false);
#               }
#
#               $this->ID = $ID;
#               return (true);
#       }


# ====================================================================
#
# Contact ControlID Property;
#
#
#
# --------------------------------------------------------------------

	public function GetControlID () 
	{
		return ($this->ControlID);
	}
	public function SetControlID ($ControlID) 
	{
		if (!is_integer($ControlID)) 
		{
			Contact::Error (__METHOD__, __LINE__, "Can't set ControlID to '${ControlID}'", "Property is integer");
			return (false);
		}
		$this->ControlID = $ControlID;
		return (true);
	}

# ====================================================================
#
# Contact SetControl Method;
#
#
#
# --------------------------------------------------------------------

	public function SetControl ($Control) 
	{
		if (!$ControlID = ID ($Control, "Control", Contact::$db)) 
		{
			Contact::Error (__METHOD__, __LINE__, "Can't set ControlID to ${Control}", "No such Contact");
			return (false);
		}
		$this->ControlID = $ControlID;
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
			Contact::Error (__METHOD__, __LINE__, "Can't set Type to '${Type}'", "Property is integer");
			return (false);
		}
		$this->Type = $Type;
		return (true);
	}

# ====================================================================
# 
# Contact Code Property;
# 
# get and set the code property; the code property must be unique;
# by default, it is the users initials plus any decoration needed
# to make them unique; however, it can be any unique string;
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
# get and set the name property; the name property is not unique; 
# by default, it is constructed by concatenating title, firstname,
# middlename and lastname; however, it can be any unique string;
# 
# --------------------------------------------------------------------

	public function GetName () 
	{
		if (empty($this->Name)) 
		{
			$this->Name = $this->Title;
			$this->Name = combine($this->Name, " ", $this->FirstName);
			$this->Name = combine($this->Name, " ", $this->MiddleName);
			$this->Name = combine($this->Name, " ", $this->LastName);
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
# Contact Username Property;
# 
#  
# 
# --------------------------------------------------------------------

	public function GetUsername () 
	{
		return ($this->Username);
	}
	public function SetUsername ($Username) 
	{
		$this->Username = $Username;
		return (true);
	}

# ====================================================================
# 
# Contact Password Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetPassword () 
	{
		return ($this->Password);
	}
	public function SetPassword ($Password) 
	{
		$this->Password = md5($Password);
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
# Contact Region Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetRegion () 
	{
		return ($this->Region);
	}
	public function SetRegion ($Region) 
	{
		$this->Region = $Region;
		return (true);
	}

# ====================================================================
# 
# Contact Country Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetCountry () 
	{
		return ($this->Country);
	}
	public function SetCountry ($Country) 
	{
		$this->Country = $Country;
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
# Contact Vox Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetVox () 
	{
		return ($this->Vox);
	}
	public function SetVox ($Vox) 
	{
		$this->Vox = $Vox;
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
		$this->ID = (int)(0);
		$this->ControlID = (int)(1);
		$this->AccountID = (int)(1);
		$this->Type =(int)(0);
		$this->Code = "";
		$this->Name = "";
		$this->Username = "";
		$this->Password = "";
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
		$this->Region = "";
		$this->Postcode = "";
		$this->Vox = "";
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
		Contact::Event (__METHOD__, __LINE__, $query);
		if (!$table=mysql_query($query, Contact::$db)) 
		{
			Contact::Error (__METHOD__, __LINE__, "Can't fetch Contact '${Contact}'", mysql_error(Contact::$db));
			return (false);
		}
		if (!$field=mysql_fetch_object($table)) 
		{
			Contact::Error (__METHOD__, __LINE__, "Can't fetch Contact '${Contact}'", "No such Contact");
			return (false);
		}
		$this->ID = $field->ID;
		$this->ControlID = $field->ControlID;
		$this->Type = $field->Type;
		$this->Code = $field->Code;
		$this->Name = $field->Name;
		$this->Username = $field->Username;
		$this->Password = $field->Password;
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
		$this->Region = $field->Region;
		$this->Postcode = $field->Postcode;
		$this->Vox = $field->Vox;
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
			Contact::Error (__METHOD__, __LINE__, "Can't store Contact", "Code is empty");
			return (false);
		}
		if (empty($this->Name)) 
		{
			Contact::Error (__METHOD__, __LINE__, "Can't store Contact", "Name is empty");
			return (false);
		}
		if ($this->ID) 
		{
			$query = "UPDATE Contact SET ControlID=($this->ControlID),Type=($this->Type),Code='$this->Code',Name='$this->Name',Username='$this->Username',Password='$this->Password',Title='$this->Title',FirstName='$this->FirstName',MiddleName='$this->MiddleName',LastName='$this->LastName',Honors='$this->Honors',Organization='$this->Organization',Division='$this->Division',Building='$this->Building',Street='$this->Street',City='$this->City',Region='$this->Region',Postcode='$this->Postcode',Vox='$this->Vox',Fax='$this->Fax',EMail='$this->EMail',SSN='$this->SSN',Opened='$this->Opened',Closed='$this->Closed',Created='$this->Created',Updated=NOW() WHERE ID=($this->ID)";
		}
		else 
		{
			$query = "INSERT INTO Contact (ControlID,Type,Code,Name,Username,Password,Title,FirstName,MiddleName,LastName,Honors,Organization,Division,Building,Street,City,Region,Postcode,Vox,Fax,EMail,SSN,Opened,Closed,Created,Updated) VALUES (($this->ControlID),($this->Type),'$this->Code','$this->Name','$this->Username','$this->Password','$this->Title','$this->FirstName','$this->MiddleName','$this->LastName','$this->Honors','$this->Organization','$this->Division','$this->Building','$this->Street','$this->City','$this->Region','$this->Postcode','$this->Vox','$this->Fax','$this->EMail','$this->SSN','$this->Opened','$this->Closed',NOW(),NOW())";
		}
		Contact::Event (__METHOD__, __LINE__, $query);
		if (!mysql_query($query, Contact::$db)) 
		{
			Contact::Error (__METHOD__, __LINE__, "Can't store Contact $this->Code", mysql_error(Contact::$db));
			return (false);
		}

#               if (!$this->ID)
#               {
#                       $this->ID = mysql_insert_id(Contact::$db);
#               }

		return (true);
	}

# ====================================================================
#
# Contact Components Method;
#
# Return an associative array of component contact codes indexed by 
# contact number; 
#
# --------------------------------------------------------------------

	public function Components ($ContactID) 
	{
		$components = array ();
		if (!is_integer($ContactID)) 
		{
			Contact::Error (__METHOD__, __LINE__, "Can't fetch components of Contact ($ContactID)", "Key must be integer");
			return (false);
		}
		$query = "SELECT ID, ControlID, Code FROM Contact WHERE ControlID=($ContactID)";
		Contact::Event (__METHOD__, __LINE__, $query);
		if (!$contacts = mysql_query($query, Contact::$db)) 
		{
			Contact::Error (__METHOD__, __LINE__, "Can't fetch components of Contact ($ContactID)", mysql_error(Contact::$db));
			return ($components);
		}
		while ($contact = mysql_fetch_object($contacts)) 
		{
			$components[$contact->ID]= $contact->Code;
			$components += Contact::Components ((int)($contact->ID));
		}
		return ($components);
	}

# ====================================================================
#
# Contact State Method;
#
#
#
# --------------------------------------------------------------------

	public function State () 
	{
		echo __METHOD__;
		echo " ID=($this->ID)";
		echo " ControlID=($this->ControlID)";
		echo " AccountID=($this->AccountID)";
		echo " Type=($this->Type)";
		echo " Code=[$this->Code]";
		echo " Name=[$this->Name]";
		echo " Username=[$this->Username]";
		echo " Password=[$this->Password]";
		echo " Title=[$this->Title]";
		echo " FirstName=[$this->FirstName]";
		echo " MiddleName=[$this->MiddleName]";
		echo " LastName=[$this->LastName]";
		echo " Honors=[$this->Honors]";
		echo " Organization=[$this->Organization]";
		echo " Division=[$this->Division]";
		echo " Building=[$this->Building]";
		echo " Street=[$this->Street]";
		echo " City=[$this->City]";
		echo " Region=[$this->Region]";
		echo " Country=[$this->Country]";
		echo " Postcode=[$this->Postcode]";
		echo " Vox=[$this->Vox]";
		echo " Fax=[$this->Fax]";
		echo " EMail=[$this->EMail]";
		echo " SSN=[$this->SSN]";
		echo "<br/>";
		return($this);
	}

# ====================================================================
#
# Contact SelectControl;
#
#
#
# --------------------------------------------------------------------

	public function SelectControl()
	{
		$contacts = mysql_query("SELECT ID, Code, Name FROM Contact", Contact::$db); 
		while ($contact = mysql_fetch_object ($contacts)) 
		{ 
			echo "<option value='$contact->ID'>$contact->Code - $contact->Name</option>"; 
		}
		return;
	}

# ====================================================================
#
# Contact SelectAccount;
#
#
#
# --------------------------------------------------------------------

	public function SelectAccount()
	{
		$accounts = mysql_query("SELECT ID, Code, Name FROM Account", Contact::$db); 
		while ($account = mysql_fetch_object ($accounts)) 
		{ 
			echo "<option value='$account->ID'>$account->Code - $account->Name</option>\n"; 
		}
		return;
	}

# ====================================================================
#
# Contact SelectType;
#
#
#
# --------------------------------------------------------------------

	public function SelectType()
	{
		echo "<option value='0'>Entity</option>\n";
		echo "<option value='1'>Person</option>\n";
		return;
	}

# ====================================================================
#
# Contact SelecTitle;
#
#
#
# --------------------------------------------------------------------

	public function SelectTitle()
	{
		$titles = mysql_query("SELECT ID, Code, Name FROM Title ORDER BY Name", Contact::$db); 
		while ($title = mysql_fetch_object ($titles)) 
		{ 
			echo "<option value='$title->Code'>$title->Name</option>\n"; 
		} 
		return;
	}

# ====================================================================
#
# Contact SelecCountry;
#
#
#
# --------------------------------------------------------------------

	public function SelectCountry()
	{
		$countries = mysql_query("SELECT Code, Name FROM Country ORDER BY Name", Contact::$db); 
		while ($country = mysql_fetch_object ($countries)) 
		{ 
			echo "<option value='$country->Code'>$country->Name</option>\n"; 
		} 
		return;
	}

# ====================================================================
#
# Contact Event Method;
#
#
#
# --------------------------------------------------------------------

	public function Event ($Method, $Line, $Event) 
	{
		Error ($Method, $Line, $Event, Contact::$trace);
		return ($this);
	}

# ====================================================================
#
# Contact Error Method;
#
#
#
# --------------------------------------------------------------------

	public function Error ($Method, $Line, $Error, $Cause) 
	{
		Error ($Method, $Line, $Error.": ".$Cause, Contact::$debug);
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
		Contact::$db = $db;
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
