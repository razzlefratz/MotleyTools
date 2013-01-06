<?php

# ====================================================================
# 
# Begin Pool Class Definition;
# 
# 
# Published 2005 by Charles Maier Associates Limited for internal use;
# Generated 12:37:26 Sat 03 Sep 2005 EDT by MySQL.php;
# 
# --------------------------------------------------------------------

class Pool 
{

# ====================================================================
# Public Pool Variables;
# --------------------------------------------------------------------


# ====================================================================
# Private Pool Variables;
# --------------------------------------------------------------------

	private $ID = 0;
	private $ContactID = 0;
	private $AccountID = 0;
	private $GameID = 0;
	private $Type = 0;
	private $Code = "";
	private $Name = "";
	private $Rules = "";
	private $Opened = NULL;
	private $Closed = NULL;
	private $Cancelled = NULL;
	private $Drawing = NULL;
	private $Cleared = NULL;
	private $Created = NULL;
	private $Updated = NULL;
	private static $debug = 0;
	private static $trace = 0;
	private $table = NULL;
	private $field = NULL;
	private $query = NULL;
	private $db = NULL;

# ====================================================================
# 
# Pool Debug Property;
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
			printf ("Pool: Can't set Debug to '${Debug}': Property is integer");
			return ($this);
		}
		self::$debug = $Debug;
		return ($this);
	}

# ====================================================================
# 
# Pool Trace Property;
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
			printf ("Pool: Can't set Trace to '${Trace}': Property is integer");
			return ($this);
		}
		self::$trace = $Trace;
		return ($this);
	}

# ====================================================================
# 
# Pool ID Property;
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
			Pool::Error("Can't set ID to '${ID}'", "Property is integer");
			return (false);
		}
		$this->ID = $ID;
		return (true);
	}

# ====================================================================
# 
# Pool ContactID Property;
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
			Pool::Error("Can't set ContactID to '${ContactID}'", "Property is integer");
			return (false);
		}
		$this->ContactID = $ContactID;
		return (true);
	}

# ====================================================================
# 
# Pool AccountID Property;
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
			Pool::Error("Can't set AccountID to '${AccountID}'", "Property is integer");
			return (false);
		}
		$this->AccountID = $AccountID;
		return (true);
	}

# ====================================================================
# 
# Pool GameID Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetGameID () 
	{
		return ($GameID);
	}
	public function SetGameID ($GameID) 
	{
		if(!is_integer($GameID)) 
		{
			Pool::Error("Can't set GameID to '${GameID}'", "Property is integer");
			return (false);
		}
		$this->GameID = $GameID;
		return (true);
	}

# ====================================================================
# 
# Pool Type Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetType () 
	{
		return ($Type);
	}
	public function SetType ($Type) 
	{
		if(!is_integer($Type)) 
		{
			Pool::Error("Can't set Type to '${Type}'", "Property is integer");
			return (false);
		}
		$this->Type = $Type;
		return (true);
	}

# ====================================================================
# 
# Pool Code Property;
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
			Pool::Error("Won't set Code to '${Code}'", "Property is alphanumeric");
			return (false);
		}
		$this->Code = $Code;
		return (true);
	}

# ====================================================================
# 
# Pool Name Property;
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
# Pool Rules Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetRules () 
	{
		return ($Rules);
	}
	public function SetRules ($Rules) 
	{
		$this->Rules = $Rules;
		return (true);
	}

# ====================================================================
# 
# Pool Opened Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetOpened () 
	{
		return ($Opened);
	}
	public function SetOpened ($Opened) 
	{
		if(!is_date($Opened)) 
		{
			Pool::Error("Can't set Opened to '${Opened}'", "Property is date");
			return (false);
		}
		$this->Opened = $Opened;
		return (true);
	}

# ====================================================================
# 
# Pool Closed Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetClosed () 
	{
		return ($Closed);
	}
	public function SetClosed ($Closed) 
	{
		if(!is_date($Closed)) 
		{
			Pool::Error("Can't set Closed to '${Closed}'", "Property is date");
			return (false);
		}
		$this->Closed = $Closed;
		return (true);
	}

# ====================================================================
# 
# Pool Cancelled Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetCancelled () 
	{
		return ($Cancelled);
	}
	public function SetCancelled ($Cancelled) 
	{
		if(!is_date($Cancelled)) 
		{
			Pool::Error("Can't set Cancelled to '${Cancelled}'", "Property is date");
			return (false);
		}
		$this->Cancelled = $Cancelled;
		return (true);
	}

# ====================================================================
# 
# Pool Drawing Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetDrawing () 
	{
		return ($Drawing);
	}
	public function SetDrawing ($Drawing) 
	{
		if(!is_date($Drawing)) 
		{
			Pool::Error("Can't set Drawing to '${Drawing}'", "Property is date");
			return (false);
		}
		$this->Drawing = $Drawing;
		return (true);
	}

# ====================================================================
# 
# Pool Cleared Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetCleared () 
	{
		return ($Cleared);
	}
	public function SetCleared ($Cleared) 
	{
		if(!is_date($Cleared)) 
		{
			Pool::Error("Can't set Cleared to '${Cleared}'", "Property is date");
			return (false);
		}
		$this->Cleared = $Cleared;
		return (true);
	}

# ====================================================================
# 
# Pool Created Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetCreated () 
	{
		return ($Created);
	}
	public function SetCreated ($Created) 
	{
		$this->Created = $Created;
		return (true);
	}

# ====================================================================
# 
# Pool Updated Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetUpdated () 
	{
		return ($Updated);
	}
	public function SetUpdated ($Updated) 
	{
		$this->Updated = $Updated;
		return (true);
	}

# ====================================================================
# 
# Pool Clear Method;
# 
# Reset property values;
# 
# --------------------------------------------------------------------

	public function Clear () 
	{
		Pool::Event ("Clearing Object Properties", "");
		$this->ID = 0;
		$this->ContactID = 0;
		$this->AccountID = 0;
		$this->GameID = 0;
		$this->Type = 0;
		$this->Code = "";
		$this->Name = "";
		$this->Rules = "";
		$this->Opened = NULL;
		$this->Closed = NULL;
		$this->Cancelled = NULL;
		$this->Drawing = NULL;
		$this->Cleared = NULL;
		$this->Created = NULL;
		$this->Updated = NULL;
		return ($this);
	}

# ====================================================================
# 
# Pool Fetch Method;
# 
# Fetch record by either numeric key or alphanumeric code;
# 
# --------------------------------------------------------------------

	public function Fetch ($Pool) 
	{
		if (is_numeric($Pool)) 
		{
			$query = "SELECT * FROM Pool WHERE ID=(${Pool})";
		}
		else 
		{
			$query = "SELECT * FROM Pool WHERE Code='${Pool}'";
		}
		Pool::Event($query, "");
		if (!$this->table=mysql_query($query, $this->db)) 
		{
			Pool::Error("Can't fetch Pool '${Pool}'", mysql_error($this->db));
			return (false);
		}
		if (!$this->field=mysql_fetch_object($this->table)) 
		{
			Pool::Error("Can't fetch Pool '${Pool}'", "No such Pool.");
			return (false);
		}
		$this->ID = $this->field->ID;
		$this->ContactID = $this->field->ContactID;
		$this->AccountID = $this->field->AccountID;
		$this->GameID = $this->field->GameID;
		$this->Type = $this->field->Type;
		$this->Code = $this->field->Code;
		$this->Name = $this->field->Name;
		$this->Rules = $this->field->Rules;
		$this->Opened = $this->field->Opened;
		$this->Closed = $this->field->Closed;
		$this->Cancelled = $this->field->Cancelled;
		$this->Drawing = $this->field->Drawing;
		$this->Cleared = $this->field->Cleared;
		$this->Created = $this->field->Created;
		$this->Updated = $this->field->Updated;
		return (true);
	}

# ====================================================================
# 
# Pool Store Method;
# 
# Insert a new record or update the old record;
# 
# --------------------------------------------------------------------

	public function Store () 
	{
		if (empty($this->Code)) 
		{
			Pool::Error("Won't store Pool record", "Code property is empty");
			return (false);
		}
		if (empty($this->Name)) 
		{
			Pool::Error("Won't store Pool record", "Name property is empty");
			return (false);
		}
		if (!Database::CheckID("Contact", $this->ContactID, $this->db)) 
		{
			Pool::Error("Won't store Pool record '$this->code'", "ContactID is invalid");
			return (false);
		}
		if (!Database::CheckID("Account", $this->AccountID, $this->db)) 
		{
			Pool::Error("Won't store Pool record '$this->Code'", "AccountID is invalid");
			return (false);
		}
		if (!Database::CheckID("Game", $this->GameID, $This->db)) 
		{
			Pool::Error("Won't store Pool record '$this->Code'", "GameID is invalid");
			return (false);
		}
		if ($this->ID) 
		{
			$query = "UPDATE Pool SET ID=($ID),ContactID=($field->Field),AccountID=($field->Field),GameID=($field->Field),Type=($field->Field),Code='$field->Field',Name='$field->Field',Rules='$field->Field',Opened='$field->Field',Closed='$field->Field',Cancelled='$field->Field',Drawing='$field->Field',Cleared='$field->Field',Created='$field->Field',Updated='$field->Field' WHERE ID=($this->ID)";
		}
		else 
		{
			$query = "INSERT INTO Pool (ID,ContactID,AccountID,GameID,Type,Code,Name,Rules,Opened,Closed,Cancelled,Drawing,Cleared,Created,Updated) VALUES (($field->Field),($field->Field),($field->Field),($field->Field),($field->Field),'$field->Field','$field->Field','$field->Field','$field->Field','$field->Field','$field->Field','$field->Field','$field->Field','$field->Field','$field->Field')";
		}
		Pool::Event($query, "");
		if (!mysql_query($query, $this->db)) 
		{
			Pool::Error("Can't store Pool $this->Code", mysql_error($this->db));
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
# Pool Peek Method;
# 
# Reset property values;
# 
# --------------------------------------------------------------------

	public function Peek () 
	{
		printf ("Pool:ID = [$this->ID]\n");
		printf ("Pool:ContactID = [$this->ContactID]\n");
		printf ("Pool:AccountID = [$this->AccountID]\n");
		printf ("Pool:GameID = [$this->GameID]\n");
		printf ("Pool:Type = [$this->Type]\n");
		printf ("Pool:Code = [$this->Code]\n");
		printf ("Pool:Name = [$this->Name]\n");
		printf ("Pool:Rules = [$this->Rules]\n");
		printf ("Pool:Opened = [$this->Opened]\n");
		printf ("Pool:Closed = [$this->Closed]\n");
		printf ("Pool:Cancelled = [$this->Cancelled]\n");
		printf ("Pool:Drawing = [$this->Drawing]\n");
		printf ("Pool:Cleared = [$this->Cleared]\n");
		printf ("Pool:Created = [$this->Created]\n");
		printf ("Pool:Updated = [$this->Updated]\n");
		printf ("\n");
		return ($this);
	}

# ====================================================================
# 
# Pool Error Method;
# 
# 
# 
# --------------------------------------------------------------------

	public function Error ($error, $cause) 
	{
		if (self::$debug == 1) 
		{
			printf ("<br><span class='error'>Pool: %s;</span><br>", cmassoc::combine($error, ": ", $cause));
		}
		if (self::$debug == 2) 
		{
			printf ("Pool: %s;\n", cmassoc::combine($error, ": ", $cause));
		}
		return (true);
	}

# ====================================================================
# 
# Pool Event Method;
# 
# 
# 
# --------------------------------------------------------------------

	public function Event ($event, $label) 
	{
		if (self::$trace == 1) 
		{
			printf ("<br><span class='error'>Pool: %s;</span><br>", cmassoc::combine($event, ": ", $label));
		}
		if (self::$trace == 2) 
		{
			printf ("Pool: %s;\n", cmassoc::combine($event, ": ", $label));
		}
		return (true);
	}

# ====================================================================
# 
# Pool Constructor;
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
# Pool Destructor;
# 
# 
# 
# --------------------------------------------------------------------

	public function __destruct () 
	{
		return;
	}

# ====================================================================
# End Pool Class Definition;
# --------------------------------------------------------------------

}
 ?>
