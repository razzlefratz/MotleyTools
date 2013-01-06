<?php

# ====================================================================
# 
# Begin Ledger Class Definition;
# 
# 
# Published 2005 by Charles Maier Associates Limited for internal use;
# Generated 04:04:33 Sat 03 Sep 2005 EDT by MySQL.php;
# 
# --------------------------------------------------------------------

class Ledger 
{

# ====================================================================
# Public Ledger Variables;
# --------------------------------------------------------------------


# ====================================================================
# Private Ledger Variables;
# --------------------------------------------------------------------

	private $ID = 0;
	private $AccountID = 0;
	private $Code = "";
	private $Name = "";
	public $debug = 0;
	public $trace = 0;
	private $db = NULL;

# ====================================================================
# 
# Ledger Debug Property;
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
			printf ("Ledger: Can't set Debug to '${Debug}': Property is integer");
			return ($this);
		}
		self::$debug = $Debug;
		return ($this);
	}

# ====================================================================
# 
# Ledger Trace Property;
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
			printf ("Ledger: Can't set Trace to '${Trace}': Property is integer");
			return ($this);
		}
		self::$trace = $Trace;
		return ($this);
	}

# ====================================================================
# 
# Ledger ID Property;
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
			self::Error("Can't set ID to '${ID}'", "Property is integer");
			return (false);
		}
		$this->ID = $ID;
		return (true);
	}

# ====================================================================
# 
# Ledger AccountID Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetAccountID () 
	{
		return ($AccountID);
	}
	public function SetAccountID ($AccountID) 
	{
		if(!is_integer($AccountID)) 
		{
			self::Error("Can't set AccountID to '${AccountID}'", "Property is integer");
			return (false);
		}
		$this->AccountID = $AccountID;
		return (true);
	}

# ====================================================================
# 
# Ledger Code Property;
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
			self::Error("Won't set Code to '${Code}'", "Property is alphanumeric");
			return (false);
		}
		$this->Code = $Code;
		return (true);
	}

# ====================================================================
# 
# Ledger Name Property;
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
# Ledger Clear Method;
# 
# Reset property values;
# 
# --------------------------------------------------------------------

	public function Clear () 
	{
		self::Event ("Clearing Object Properties", "");
		$this->ID = 0;
		$this->AccountID = 0;
		$this->Code = "";
		$this->Name = "";
		return ($this);
	}

# ====================================================================
# 
# Ledger Fetch Method;
# 
# Fetch record by either numeric key or alphanumeric code;
# 
# --------------------------------------------------------------------

	public function Fetch ($Ledger) 
	{
		if (is_numeric($Ledger)) 
		{
			$query = "SELECT * FROM Ledger WHERE ID=(${Ledger})";
		}
		else 
		{
			$query = "SELECT * FROM Ledger WHERE Code='${Ledger}'";
		}
		self::Event($query, "");
		if (!$this->table=mysql_query($query, $this->db)) 
		{
			self::Error("Can't fetch Ledger '${Ledger}'", mysql_error($this->db));
			return (false);
		}
		if (!$this->field=mysql_fetch_object($this->table)) 
		{
			self::Error("Can't fetch Ledger '${Ledger}'", "No such Ledger.");
			return (false);
		}
		$this->ID = $this->field->ID;
		$this->AccountID = $this->field->AccountID;
		$this->Code = $this->field->Code;
		$this->Name = $this->field->Name;
		return (true);
	}

# ====================================================================
# 
# Ledger Store Method;
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
#			self::Error("Won't store Ledger record", "Code property is empty");
#			return (false);
#		}
#		if (empty($this->Name))
#		{
#			self::Error("Won't store Ledger record", "Name property is empty");
#			return (false);
#		}

			$query = "UPDATE Ledger SET ID=($ID),AccountID=($field->Field),Code='$field->Field',Name='$field->Field' WHERE ID=($this->ID)";
		}
		else 
		{
			$query = "INSERT INTO Ledger (ID,AccountID,Code,Name) VALUES (($field->Field),($field->Field),'$field->Field','$field->Field')";
		}
		self::Event($query, "");
		if (!mysql_query($query, $this->db)) 
		{
			self::Error("Can't store Ledger $this->Code", mysql_error($this->db));
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
# Ledger Peek Method;
# 
# Reset property values;
# 
# --------------------------------------------------------------------

	public function Peek () 
	{
		printf ("Ledger:ID = [$this->ID]\n");
		printf ("Ledger:AccountID = [$this->AccountID]\n");
		printf ("Ledger:Code = [$this->Code]\n");
		printf ("Ledger:Name = [$this->Name]\n");
		printf ("\n");
		return ($this);
	}

# ====================================================================
# 
# Ledger Error Method;
# 
# 
# 
# --------------------------------------------------------------------

	public function Error ($error, $cause) 
	{
		if (self::$debug == 1) 
		{
			printf ("<br><span class='error'>Ledger: %s;</span><br>", cmassoc::combine($error, ": ", $cause));
		}
		if (self::$debug == 2) 
		{
			printf ("Ledger: %s;\n", cmassoc::combine($error, ": ", $cause));
		}
		return (true);
	}

# ====================================================================
# 
# Ledger Event Method;
# 
# 
# 
# --------------------------------------------------------------------

	public function Event ($event, $label) 
	{
		if (self::$trace == 1) 
		{
			printf ("<br><span class='error'>Ledger: %s;</span><br>", cmassoc::combine($event, ": ", $label));
		}
		if (self::$trace == 2) 
		{
			printf ("Ledger: %s;\n", cmassoc::combine($event, ": ", $label));
		}
		return (true);
	}

# ====================================================================
# 
# Ledger Constructor;
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
# Ledger Destructor;
# 
# 
# 
# --------------------------------------------------------------------

	public function __destruct () 
	{
		return;
	}

# ====================================================================
# End Ledger Class Definition;
# --------------------------------------------------------------------

}
 ?>
