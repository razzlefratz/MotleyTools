<?php

# ====================================================================
#  
# --------------------------------------------------------------------

require "constants.php";

# ====================================================================
# 
# Begin Project Class Definition;
# 
# 
# Published 2005 by Charles Maier Associates Limited for internal use;
# Generated 11:53:47 Sun 11 Sep 2005 EDT by MySQL.php;
# 
# --------------------------------------------------------------------

class Project 
{

# ====================================================================
# Public Project Variables;
# --------------------------------------------------------------------


# ====================================================================
# Private Project Variables;
# --------------------------------------------------------------------

	private $ID = 0;
	private $ControlID = 1;
	private $ContactID = 1;
	private $Type = 0;
	private $Code = "";
	private $Name = "";
	private $Value = 0.00;
	private $Start = NULL;
	private $End = NULL;
	private static $debug = MESSAGE_NONE;
	private static $trace = MESSAGE_NONE;
	private static $db = NULL;

# ====================================================================
# 
# Project Debug Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetDebug () 
	{
		return (Project::$debug);
	}
	public function SetDebug ($Debug) 
	{
		if(!is_integer($Debug)) 
		{
			printf("Project: Can't set Debug to '${Debug}': Property is integer");
			return ($this);
		}
		Project::$debug = $Debug;
		return ($this);
	}

# ====================================================================
# 
# Project Trace Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetTrace () 
	{
		return (Project::$trace);
	}
	public function SetTrace ($Trace) 
	{
		if(!is_integer($Trace)) 
		{
			printf("Project: Can't set Trace to '${Trace}': Property is integer");
			return ($this);
		}
		Project::$trace = $Trace;
		return ($this);
	}

# ====================================================================
# 
# Project ID Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetID () 
	{
		return ($ID);
	}
	public function SetID ($ID) 
	{
		if(!is_integer($ID)) 
		{
			Project::Error (__METHOD__, __LINE__, "Can't set ID to '${ID}'", "Property is integer");
			return (false);
		}
		$this->ID = $ID;
		return (true);
	}

# ====================================================================
# 
# Project ControlID Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetControlID () 
	{
		return ($ControlID);
	}
	public function SetControlID ($ControlID) 
	{
		if(!is_integer($ControlID)) 
		{
			Project::Error (__METHOD__, __LINE__, "Can't set ControlID to '${ControlID}'", "Property is integer");
			return (false);
		}
		$this->ControlID = $ControlID;
		return (true);
	}

# ====================================================================
# 
# Project ContactID Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetContactID () 
	{
		return ($ContactID);
	}
	public function SetContactID ($ContactID) 
	{
		if(!is_integer($ContactID)) 
		{
			Project::Error (__METHOD__, __LINE__, "Can't set ContactID to '${ContactID}'", "Property is integer");
			return (false);
		}
		$this->ContactID = $ContactID;
		return (true);
	}

# ====================================================================
#
# Project Type Property;
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
			Projectt::Error (__METHOD__, __LINE__, "Can't set Type to ($Type)", "Property is integer");
			return (false);
		}
		$this->Type = $Type;
		return (true);
	}

# ====================================================================
# 
# Project Code Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetCode () 
	{
		return ($Code);
	}
	public function SetCode ($Code) 
	{
		if(is_numeric($Code)) 
		{
			Project::Error (__METHOD__, __LINE__, "Won't set Code to '${Code}'", "Property is alphanumeric");
			return (false);
		}
		$this->Code = $Code;
		return (true);
	}

# ====================================================================
# 
# Project Name Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetName () 
	{
		return ($Name);
	}
	public function SetName ($Name) 
	{
		$this->Name = $Name;
		return (true);
	}

# ====================================================================
# 
# Project Value Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetValue () 
	{
		return ($Value);
	}
	public function SetValue ($Value) 
	{
		if(!is_float($Value)) 
		{
			Project::Error (__METHOD__, __LINE__, "Can't set Value to '${Value}'", "Property is float");
			return (false);
		}
		$this->Value = $Value;
		return (true);
	}

# ====================================================================
# 
# Project Start Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetStart () 
	{
		return ($Start);
	}
	public function SetStart ($Start) 
	{
		if(!is_date($Start)) 
		{
			Project::Error (__METHOD__, __LINE__, "Can't set Start to '${Start}'", "Property is date");
			return (false);
		}
		$this->Start = $Start;
		return (true);
	}

# ====================================================================
# 
# Project End Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetEnd () 
	{
		return ($End);
	}
	public function SetEnd ($End) 
	{
		if(!is_date($End)) 
		{
			Project::Error (__METHOD__, __LINE__, "Can't set End to '${End}'", "Property is date");
			return (false);
		}
		$this->End = $End;
		return (true);
	}

# ====================================================================
# 
# Project Clear Method;
# 
# Reset property values;
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
		$this->Value = (float)(0.00);
		$this->Start = NULL;
		$this->End = NULL;
		return ($this);
	}

# ====================================================================
# 
# Project Fetch Method;
# 
# Fetch record by either numeric key or alphanumeric code;
# 
# --------------------------------------------------------------------

	public function Fetch ($Project) 
	{
		if (is_numeric($Project)) 
		{
			$query = "SELECT * FROM Project WHERE ID=(${Project})";
		}
		else 
		{
			$query = "SELECT * FROM Project WHERE Code='${Project}'";
		}
		Project::Event (__METHOD__, __LINE__, $query);
		if (!$this->table = mysql_query($query, Project::$db)) 
		{
			Project::Error (__METHOD__, __LINE__, "Can't fetch Project '${Project}'", mysql_error(Project::$db));
			return (false);
		}
		if (!$this->field = mysql_fetch_object ($this->table)) 
		{
			Project::Error (__METHOD__, __LINE__, "Can't fetch Project '${Project}'", "No such Project.");
			return (false);
		}
		$this->ID = $this->field->ID;
		$this->ControlID = $this->field->ControlID;
		$this->ContactID = $this->field->ContactID;
		$this->Code = $this->field->Code;
		$this->Name = $this->field->Name;
		$this->Value = $this->field->Value;
		$this->Start = $this->field->Start;
		$this->End = $this->field->End;
		return (true);
	}

# ====================================================================
# 
# Project Store Method;
# 
# Insert a new record or update the old record;
# 
# --------------------------------------------------------------------

	public function Store () 
	{

#		if (empty($this->Code))
#		{
#			Project::Error (__METHOD__, __LINE__, "Won't store Project record", "Code property is empty");
#			return (false);
#		}


#		if (empty($this->Name))
#		{
#			Project::Error (__METHOD__, __LINE__,"Won't store Project record", "Name property is empty");
#			return (false);
#		}

		if ($this->ID) 
		{
			$query = "UPDATE Project SET ControlID=($this->ControlID),ContactID=($this->ContactID),Code='$this->Code',Name='$this->Name',Value=($this->Value),Start='$this->Start',End='$this->End' WHERE ID=($this->ID)";
		}
		else 
		{
			$query = "INSERT INTO Project (ControlID,ContactID,Code,Name,Value,Start,End) VALUES (($this->ControlID),($this->ContactID),'$this->Code','$this->Name',($this->Value),'$this->Start','$this->End')";
		}
		Project::Event (__METHOD__, __LINE__, $query);
		if (!mysql_query($query, Project::$db)) 
		{
			Project::Error (__METHOD__, __LINE__, "Can't store Project $this->Code", mysql_error(Project::$db));
			return (false);
		}

#		if (!$this->ID)
#		{
#			$this->ID = mysql_insert_id(Project::$db);
#		}

		return (true);
	}

# ====================================================================
#
# Project SetControl Method;
#
#
#
# --------------------------------------------------------------------

	public function SetControl ($Contact) 
	{
		if (!$ControlID = ID ($Control, "Control", Project::$db)) 
		{
			Project::Error (__METHOD__, __LINE__, "Can't set ControlID to ${Control}", "No such Project");
			return (false);
		}
		$this->ControlID = $ControlID;
		return (true);
	}

# ====================================================================
#
# Project SetContact Method;
#
#
#
# --------------------------------------------------------------------

	public function SetContact ($Contact) 
	{
		if (!$ContactID = ID ($Contact, "Contact", Project::$db)) 
		{
			Project::Error (__METHOD__, __LINE__, "Can't set ContactID to ${Contact}", "No such Contact");
			return (false);
		}
		$this->ContactID = $ContactID;
		return (true);
	}

# ====================================================================
#
# Project Components Method;
#
# Return an associative array of component project codes indexed by 
# project number; 
#
# --------------------------------------------------------------------

	public function Components ($ProjectID) 
	{
		$components = array ();
		if (!is_integer($ProjectID)) 
		{
			Project::Error (__METHOD__, __LINE__, "Can't fetch components of Project ($ProjectID)", "Key must be integer");
			return (false);
		}
		$query = "SELECT ID, ControlID, Code FROM Project WHERE ControlID=($ProjectID)";
		Project::Event (__METHOD__, __LINE__, $query);
		if (!$projects = mysql_query($query, Project::$db)) 
		{
			Project::Error (__METHOD__, __LINE__, "Can't fetch components of Project ($ProjectID)", mysql_error(Project::$db));
			return ($components);
		}
		while ($project = mysql_fetch_object($projects)) 
		{
			$components[$project->ID]= $project->Code;
			$components += Project::Components ((int)($project->ID));
		}
		return ($components);
	}

# ====================================================================
# 
# Project Peek Method;
# 
# Reset property values;
# 
# --------------------------------------------------------------------

	public function Peek () 
	{
		echo __METHOD__;
		echo " ID = ($this->ID)";
		echo " ControlID = ($this->ControlID)";
		echo " ContactID = ($this->ContactID)";
		echo " Type = ($this->Type)";
		echo " Code = [$this->Code]";
		echo " Name = [$this->Name]";
		echo " Value = ($this->Value)";
		echo " Start = [$this->Start]";
		echo " End = [$this->End]";
		echo "<br/>";
		return ($this);
	}

# ====================================================================
#
# Project SelectContact;
#
#
#
# --------------------------------------------------------------------

	public function SelectContact()
	{
		$contacts = mysql_query("SELECT ID, Code, Name FROM Contact WHERE Type=(1)", Project::$db); 
		while ($contact = mysql_fetch_object ($contacts)) 
		{ 
			echo "<option value='$contact->ID'>$contact->Code - $contact->Name</option>\n"; 
		}
		return;
	}

# ====================================================================
#
# Project SelectControl;
#
#
#
# --------------------------------------------------------------------

	public function SelectControl()
	{
		$projects = mysql_query("SELECT ID, Code, Name FROM Project WHERE NOT ID=($this->ID)", Project::$db); 
		while ($project = mysql_fetch_object ($projects)) 
		{ 
			echo "<option value='$project->ID'>$project->Code - $project->Name</option>\n"; 
		}
		return;
	}

# ====================================================================
#
# Project SelectType;
#
#
#
# --------------------------------------------------------------------

	public function SelectType()
	{
		echo "<option value='0'>Activity</option>\n";
		echo "<option value='1'>Product</option>\n";
		return;
	}

# ====================================================================
#
# Project Event Method;
#
#
#
# --------------------------------------------------------------------

	public function Event ($Method, $Line, $Event) 
	{
		Error ($Method, $Line, $Event, Project::$trace);
		return ($this);
	}

# ====================================================================
#
# Project Error Method;
#
#
#
# --------------------------------------------------------------------

	public function Error ($Method, $Line, $Error, $Cause) 
	{
		Error ($Method, $Line, $Error.": ".$Cause, Project::$debug);
		return ($this);
	}

# ====================================================================
# 
# Project Constructor;
# 
# 
# 
# --------------------------------------------------------------------

	public function __construct ($db) 
	{
		Project::$db = $db;
		return;
	}

# ====================================================================
# 
# Project Destructor;
# 
# 
# 
# --------------------------------------------------------------------

	public function __destruct () 
	{
		return;
	}

# ====================================================================
# End Project Class Definition;
# --------------------------------------------------------------------

}
 ?>
