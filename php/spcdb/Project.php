<?php

# ====================================================================
# 
# Begin Project Class Definition;
# 
# 
# Published 2005 by Charles Maier Associates Limited for internal use;
# Generated 12:37:26 Sat 03 Sep 2005 EDT by MySQL.php;
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
	private $Code = "";
	private $Name = "";
	private static $debug = 0;
	private static $trace = 0;
	private $table = NULL;
	private $field = NULL;
	private $query = NULL;
	private $db = NULL;

# ====================================================================
# 
# Project Debug Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetDebug () 
	{
		return (self::$debug);
	}
	public function SetDebug ($Debug) 
	{
		if(!is_integer($Debug)) 
		{
			printf ("Project: Can't set Debug to '${Debug}': Property is integer");
			return ($this);
		}
		self::$debug = $Debug;
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
		return (self::$trace);
	}
	public function SetTrace ($Trace) 
	{
		if(!is_integer($Trace)) 
		{
			printf ("Project: Can't set Trace to '${Trace}': Property is integer");
			return ($this);
		}
		self::$trace = $Trace;
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
			Project::Error("Can't set ID to '${ID}'", "Property is integer");
			return (false);
		}
		$this->ID = $ID;
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
			Project::Error("Won't set Code to '${Code}'", "Property is alphanumeric");
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
# Project Clear Method;
# 
# Reset property values;
# 
# --------------------------------------------------------------------

	public function Clear () 
	{
		Project::Event ("Clearing Object Properties", "");
		$this->ID = 0;
		$this->Code = "";
		$this->Name = "";
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
		Project::Event($query, "");
		if (!$this->table=mysql_query($query, $this->db)) 
		{
			Project::Error("Can't fetch Project '${Project}'", mysql_error($this->db));
			return (false);
		}
		if (!$this->field=mysql_fetch_object($this->table)) 
		{
			Project::Error("Can't fetch Project '${Project}'", "No such Project.");
			return (false);
		}
		$this->ID = $this->field->ID;
		$this->Code = $this->field->Code;
		$this->Name = $this->field->Name;
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
		if ($this->ID) 
		{

#		if (empty($this->Code))
#		{
#			Project::Error("Won't store Project record", "Code property is empty");
#			return (false);
#		}


#		if (empty($this->Name))
#		{
#			Project::Error("Won't store Project record", "Name property is empty");
#			return (false);
#		}

			$query = "UPDATE Project SET ID=($ID),Code='$field->Field',Name='$field->Field' WHERE ID=($this->ID)";
		}
		else 
		{
			$query = "INSERT INTO Project (ID,Code,Name) VALUES (($field->Field),'$field->Field','$field->Field')";
		}
		Project::Event($query, "");
		if (!mysql_query($query, $this->db)) 
		{
			Project::Error("Can't store Project $this->Code", mysql_error($this->db));
			return (false);
		}

#		if (!$this->ID)
#		{
#			$this->ID = mysql_insert_id($this->db);
#		}

		return (true);
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
		printf ("Project:ID = [$this->ID]\n");
		printf ("Project:Code = [$this->Code]\n");
		printf ("Project:Name = [$this->Name]\n");
		printf ("\n");
		return ($this);
	}

# ====================================================================
# 
# Project Error Method;
# 
# 
# 
# --------------------------------------------------------------------

	public function Error ($error, $cause) 
	{
		if (self::$debug == 1) 
		{
			printf ("<br><span class='error'>Project: %s;</span><br>", cmassoc::combine($error, ": ", $cause));
		}
		if (self::$debug == 2) 
		{
			printf ("Project: %s;\n", cmassoc::combine($error, ": ", $cause));
		}
		return (true);
	}

# ====================================================================
# 
# Project Event Method;
# 
# 
# 
# --------------------------------------------------------------------

	public function Event ($event, $label) 
	{
		if (self::$trace == 1) 
		{
			printf ("<br><span class='error'>Project: %s;</span><br>", cmassoc::combine($event, ": ", $label));
		}
		if (self::$trace == 2) 
		{
			printf ("Project: %s;\n", cmassoc::combine($event, ": ", $label));
		}
		return (true);
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
		$this->db = $db;
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
