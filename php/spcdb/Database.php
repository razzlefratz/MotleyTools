<?php
class Database 
{

# ====================================================================
# Public Database Variables;
# --------------------------------------------------------------------


# ====================================================================
# Private Database Variables;
# --------------------------------------------------------------------

	private static $trace = 0;
	private static $debug = 0;
	private $db = NULL;

# ====================================================================
#
# Database Debug Property;
#
# Enable or disable debug messages; debug messages appear prior to
# each error return; 0 mean no messages, 1 means print as text and
# 2 means print as HTML;
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
			printf ("Database: Can't set Debug to '${Debug}': Property is integer.");
			return ($this);
		}
		self::$debug = $Debug;
		return ($this);
	}

# ====================================================================
#
# Database Trace Property;
#
# Enable or disable trace messages; trace messages appear prior to
# special events and each database query; 
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
			printf ("Database: Can't set Trace to '${Trace}': Property is integer.");
			return ($this);
		}
		self::$trace = $trace;
		return ($this);
	}

# ====================================================================
#
# Database GetID Method;
#
# Return the numeric primary key of an existing table record given
# the numeric primary key or the alphanumeric secondary key;
# Return 0 if the record does not exist in the table;
#
# --------------------------------------------------------------------

	public function GetID ($Key, $Table, $DB) 
	{
		if (is_numeric($Key)) 
		{
			$query = "SELECT ID FROM ${Table} WHERE ID=(${Key})";
		}
		else 
		{
			$query = "SELECT ID FROM ${Table} WHERE Code='${Key}'";
		}
		Database::Event ($query, "");
		if (!$table=mysql_query($query, $DB)) 
		{
			Database::Error ("Can't find ${Table} '${Key}'", mysql_error($DB));
			return (0);
		}
		if (!$field=mysql_fetch_object($table)) 
		{
			Database::Error ("Can't find ${Table} '${Key}'", "No such ${Table}");
			return (0);
		}
		return (intval($field->ID));
	}

# ====================================================================
#
# Database CheckID Method;
#
# Return the numeric primary key of an existing table record given
# the numeric primary key or the alphanumeric secondary key;
# Return 0 if the record does not exist in the table;
#
# --------------------------------------------------------------------

	public function CheckID ($Table, $ID, $DB) 
	{
		if (!is_numeric($ID)) 
		{
			Database::Error ("Can't Check ${Table} ID '${ID}'", "ID must be integer");
			return (false);
		}
		$query = "SELECT ID FROM ${Table} WHERE ID=(${ID})";
		Database::Event ($query, "");
		if (!$table=mysql_query($query, $DB)) 
		{
			Database::Error ("Can't find ${Table} '${ID}'", mysql_error($DB));
			return (false);
		}
		if (!$field=mysql_fetch_object($table)) 
		{
			Database::Error ("Can't find ${Table} '${ID}'", "No such ${Table}");
			return (false);
		}
		return (true);
	}

# ====================================================================
#
# Database Event Method;
#
#
#
# --------------------------------------------------------------------

	public function Event ($event, $label) 
	{
		if (self::$trace == 1) 
		{
			printf ("<br><span class='event'>Database: %s;/span><br>", cmassoc::combine($event, ": ", $label));
		}
		if (self::$trace == 2) 
		{
			printf ("Database: %s;n", cmassoc::combine($event, ": ", $label));
		}
		return ($this);
	}

# ====================================================================
#
# Database Error Method;
#
#
#
# --------------------------------------------------------------------

	public function Error ($error, $cause) 
	{
		if (self::$debug == 1) 
		{
			printf ("<br><span class='error'>Database: %s;/span><br>", cmassoc::combine($error, ": ", $cause));
		}
		if (self::$debug == 2) 
		{
			printf ("Database: %s;n", cmassoc::combine($error, ": ", $cause));
		}
		return ($this);
	}

# ====================================================================
#
# Database Constructor;
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
# Database Destructor;
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
