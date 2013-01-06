<?php

# ====================================================================
# 
# Begin Participant Class Definition;
# 
# 
# Published 2005 by Charles Maier Associates Limited for internal use;
# Generated 04:04:33 Sat 03 Sep 2005 EDT by MySQL.php;
# 
# --------------------------------------------------------------------

class Participant 
{

# ====================================================================
# Public Participant Variables;
# --------------------------------------------------------------------

	public $debug = 0;
	public $trace = 0;

# ====================================================================
# Private Participant Variables;
# --------------------------------------------------------------------

	private $ID = 0;
	private $PoolID = 0;
	private $ContactID = 0;
	private $Priority = 0;
	private $Status = 0;
	private $Joined = NULL;
	private $table = NULL;
	private $field = NULL;
	private $query = NULL;
	private $db = NULL;

# ====================================================================
# 
# Participant Debug Property;
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
			printf ("Participant: Can't set Debug to '${Debug}': Property is integer");
			return ($this);
		}
		self::$debug = $Debug;
		return ($this);
	}

# ====================================================================
# 
# Participant Trace Property;
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
			printf ("Participant: Can't set Trace to '${Trace}': Property is integer");
			return ($this);
		}
		self::$trace = $Trace;
		return ($this);
	}

# ====================================================================
# 
# Participant ID Property;
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
# Participant PoolID Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetPoolID () 
	{
		return ($PoolID);
	}
	public function SetPoolID ($PoolID) 
	{
		if(!is_integer($PoolID)) 
		{
			self::Error("Can't set PoolID to '${PoolID}'", "Property is integer");
			return (false);
		}
		$this->PoolID = $PoolID;
		return (true);
	}

# ====================================================================
# 
# Participant ContactID Property;
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
			self::Error("Can't set ContactID to '${ContactID}'", "Property is integer");
			return (false);
		}
		$this->ContactID = $ContactID;
		return (true);
	}

# ====================================================================
# 
# Participant Priority Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetPriority () 
	{
		return ($Priority);
	}
	public function SetPriority ($Priority) 
	{
		if(!is_integer($Priority)) 
		{
			self::Error("Can't set Priority to '${Priority}'", "Property is integer");
			return (false);
		}
		$this->Priority = $Priority;
		return (true);
	}

# ====================================================================
# 
# Participant Status Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetStatus () 
	{
		return ($Status);
	}
	public function SetStatus ($Status) 
	{
		if(!is_integer($Status)) 
		{
			self::Error("Can't set Status to '${Status}'", "Property is integer");
			return (false);
		}
		$this->Status = $Status;
		return (true);
	}

# ====================================================================
# 
# Participant Joined Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetJoined () 
	{
		return ($Joined);
	}
	public function SetJoined ($Joined) 
	{
		if(!is_date($Joined)) 
		{
			self::Error("Can't set Joined to '${Joined}'", "Property is date");
			return (false);
		}
		$this->Joined = $Joined;
		return (true);
	}

# ====================================================================
# 
# Participant Clear Method;
# 
# Reset property values;
# 
# --------------------------------------------------------------------

	public function Clear () 
	{
		self::Event ("Clearing Object Properties", "");
		$this->ID = 0;
		$this->PoolID = 0;
		$this->ContactID = 0;
		$this->Priority = 0;
		$this->Status = 0;
		$this->Joined = NULL;
		return ($this);
	}

# ====================================================================
# 
# Participant Fetch Method;
# 
# Fetch record by either numeric key or alphanumeric code;
# 
# --------------------------------------------------------------------

	public function Fetch ($Participant) 
	{
		if (is_numeric($Participant)) 
		{
			$query = "SELECT * FROM Participant WHERE ID=(${Participant})";
		}
		else 
		{
			$query = "SELECT * FROM Participant WHERE Code='${Participant}'";
		}
		self::Event($query, "");
		if (!$this->table=mysql_query($query, $this->db)) 
		{
			self::Error("Can't fetch Participant '${Participant}'", mysql_error($this->db));
			return (false);
		}
		if (!$this->field=mysql_fetch_object($this->table)) 
		{
			self::Error("Can't fetch Participant '${Participant}'", "No such Participant.");
			return (false);
		}
		$this->ID = $this->field->ID;
		$this->PoolID = $this->field->PoolID;
		$this->ContactID = $this->field->ContactID;
		$this->Priority = $this->field->Priority;
		$this->Status = $this->field->Status;
		$this->Joined = $this->field->Joined;
		return (true);
	}

# ====================================================================
# 
# Participant Store Method;
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
#			self::Error("Won't store Participant record", "Code property is empty");
#			return (false);
#		}


#		if (empty($this->Name))
#		{
#			self::Error("Won't store Participant record", "Name property is empty");
#			return (false);
#		}

			$query = "UPDATE Participant SET ID=($ID),PoolID=($field->Field),ContactID=($field->Field),Priority=($field->Field),Status=($field->Field),Joined='$field->Field' WHERE ID=($this->ID)";
		}
		else 
		{
			$query = "INSERT INTO Participant (ID,PoolID,ContactID,Priority,Status,Joined) VALUES (($field->Field),($field->Field),($field->Field),($field->Field),($field->Field),'$field->Field')";
		}
		self::Event($query, "");
		if (!mysql_query($query, $this->db)) 
		{
			self::Error("Can't store Participant $this->Code", mysql_error($this->db));
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
# Participant Peek Method;
# 
# Reset property values;
# 
# --------------------------------------------------------------------

	public function Peek () 
	{
		printf ("Participant:ID = [$this->ID]\n");
		printf ("Participant:PoolID = [$this->PoolID]\n");
		printf ("Participant:ContactID = [$this->ContactID]\n");
		printf ("Participant:Priority = [$this->Priority]\n");
		printf ("Participant:Status = [$this->Status]\n");
		printf ("Participant:Joined = [$this->Joined]\n");
		printf ("\n");
		return ($this);
	}

# ====================================================================
# 
# Participant Error Method;
# 
# 
# 
# --------------------------------------------------------------------

	public function Error ($error, $cause) 
	{
		if (self::$debug == 1) 
		{
			printf ("<br><span class='error'>Participant: %s;</span><br>", cmassoc::combine($error, ": ", $cause));
		}
		if (self::$debug == 2) 
		{
			printf ("Participant: %s;\n", cmassoc::combine($error, ": ", $cause));
		}
		return (true);
	}

# ====================================================================
# 
# Participant Event Method;
# 
# 
# 
# --------------------------------------------------------------------

	public function Event ($event, $label) 
	{
		if (self::$trace == 1) 
		{
			printf ("<br><span class='error'>Participant: %s;</span><br>", cmassoc::combine($event, ": ", $label));
		}
		if (self::$trace == 2) 
		{
			printf ("Participant: %s;\n", cmassoc::combine($event, ": ", $label));
		}
		return (true);
	}

# ====================================================================
# 
# Participant Constructor;
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
# Participant Destructor;
# 
# 
# 
# --------------------------------------------------------------------

	public function __destruct () 
	{
		return;
	}

# ====================================================================
# End Participant Class Definition;
# --------------------------------------------------------------------

}
 ?>
