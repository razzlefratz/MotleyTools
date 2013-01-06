<?php

# ====================================================================
# 
# Begin Control Class Definition;
# 
# 
# Published 2005 by Charles Maier Associates Limited for internal use;
# Generated 02:38:24 Mon 29 Aug 2005 EDT by MySQL.php;
# 
# --------------------------------------------------------------------

class Control 
{

# ====================================================================
# Public Variables;
# --------------------------------------------------------------------

	private static $debug = 0;
	private static $trace = 0;

# ====================================================================
# Private Variables;
# --------------------------------------------------------------------

	private $ID = 0;
	private $AccountID = 0;
	private $Code = "";
	private $Name = "";
	private $table = NULL;
	private $field = NULL;
	private $query = NULL;
	private $db = NULL;

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
		if (!is_integer($Debug)) 
		{
			printf ("Control: Can't set Debug to '${Debug}': Property is integer.\n");
			return ($this);
		}
		self::$debug = $Debug;
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
		if (!is_integer($Trace)) 
		{
			printf ("Control: Can't set Trace to '${Trace}': Property is integer.\n");
			return ($this);
		}
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
		return ($this->ID);
	}

#       public function SetID ($ID)
#
#       {
#               if (!is_integer($ID))
#               {
#                       Control::Error ("Can't set ID to        '${ID}'", "Property is integer");
#                       return (false);
#               }
#
#               $this->ID = $ID;
#               return (true);
#       }


# ====================================================================
# 
# Public Property AccountID;
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
			Control::Error ("Can't set AccountID to '${AccountID}'", "Property is integer");
			return (false);
		}
		$this->AccountID = $AccountID;
		return (true);
	}

# ====================================================================
# 
# Public Property Code;
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
# Public Property Name;
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
#  Clear Method;
# 
# 
# 
# --------------------------------------------------------------------

	public function Clear () 
	{
		Control::Event ("Clearing Object Properties", "");
		$this->ID = 0;
		$this->AccountID = 0;
		$this->Code = "";
		$this->Name = "";
		return (true);
	}

# ====================================================================
# 
# Control Fetch Method;
# 
# 
# 
# --------------------------------------------------------------------

	public function Fetch ($Control) 
	{
		if (is_numeric($Control)) 
		{
			$query = "SELECT * FROM Control WHERE ID=(${Control})";
		}
		else 
		{
			$query = "SELECT * FROM Control WHERE Code='${Control}'";
		}
		Control::Event ($query, "");
		if (!$table=mysql_query($query, $this->db)) 
		{
			Control::Error ("Can't fetch Control '${Control}'", mysql_error($this->db));
			return (false);
		}
		if (!$field=mysql_fetch_object($table)) 
		{
			Control::Error ("Can't fetch Control '${Control}'", "No such Control.\n");
			return (false);
		}
		$this->ID = $field->ID;
		$this->AccountID = $field->AccountID;
		$this->Code = $field->Code;
		$this->Name = $field->Name;
		return (true);
	}

# ====================================================================
# 
# Control Store Method;
# 
# 
# 
# --------------------------------------------------------------------

	public function Store () 
	{
		if ($this->ID) 
		{
			$query = "UPDATE Control        SET AccountID=($this->AccountID),Code='$this->Code',Name='$this->Name' WHERE ID=($this->ID)";
		}
		else 
		{
			$query = "INSERT INTO Control (AccountID,Code,Name) VALUES (($this->AccountID),'$this->Code','$this->Name')";
		}
		Control::Event ($query, "");
		if (!mysql_query($query, $this->db)) 
		{
			Control::Error ("Can't store Control $this->Code", mysql_error($this->db));
			return (false);
		}

#
# Causes repeating update problems;
#
#               if (!$this->ID)
#               {
#                       $this->ID = mysql_insert_id($this->db);
#               }

		return (true);
	}

# ====================================================================
#
# Control Error Method;
#
#
#
# --------------------------------------------------------------------

	public function Error ($error, $cause) 
	{
		if (self::$debug == 1) 
		{
			printf ("<br><span class='error'>Control: %s;</span><br>", cmassoc::combine($error, ": ", $cause));
		}
		if (self::$debug == 2) 
		{

#                       printf ("Control: %s;\n", cmassoc::combine($error, ": ", $cause));

		}
		return ($this);
	}

# ====================================================================
#
# Control Event Method;
#
#
#
# --------------------------------------------------------------------

	public function Event ($event, $label) 
	{
		if (self::$trace == 1) 
		{
			printf ("<br><span class='error'>Control: %s;</span><br>", cmassoc::combine($event, ": ", $label));
		}
		if (self::$trace == 2) 
		{
			printf ("Control: %s;\n", cmassoc::combine($event, ": ", $label));
		}
		return ($this);
	}

# ====================================================================
#
# Control SetAccount Method;
#
#
#
# --------------------------------------------------------------------

	public function SetAccount ($Account) 
	{
		if (!$AccountID=spcdb::GetID($Account, "Account", $this->db)) 
		{
			Control::Error ("Can't set AccountID to ${Account}", "No        such Account");
			return (false);
		}
		$this->AccountID = $AccountID;
		return (true);
	}

# ====================================================================
# 
# Control Constructor;
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
# Control Destructor;
# 
# 
# 
# --------------------------------------------------------------------

	public function __destruct () 
	{
		return;
	}

# ====================================================================
# End Control Class Definition;
# --------------------------------------------------------------------

}
 ?>
