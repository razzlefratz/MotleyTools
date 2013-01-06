<?php
# =
# 
# Begin Game Class Definition;
# 
# 
# Published 2005 by Charles Maier Associates Limited for internal use;
# Generated 16:32:57 Mon 05 Sep 2005 EDT by MySQL.php;
# 
# -

class Game

{

# =
# Public Game Variables;
# -


# =
# Private Game Variables;
# -

	private $ID = 0;
	private $ContactID = 0;
	private $AccountID = 0;
	private $Code = "";
	private $Name = "";

	private static $debug = 0;
	private static $trace = 0;
	private static $db = NULL;

# =
# 
# Game Debug Property;
# 
# 
# 
# -

	public function GetDebug ()

	{
		return (Game::$debug);
	}

	public function SetDebug ($Debug)

	{
		if(!is_integer($Debug))
		{
			printf("Game: Can't set Debug to '${Debug}': Property is integer");
			return ($this);
		}

		Game::$debug = $Debug;
		return ($this);
	}

# =
# 
# Game Trace Property;
# 
# 
# 
# -

	public function GetTrace ()

	{
		return (Game::$trace);
	}

	public function SetTrace ($Trace)

	{
		if(!is_integer($Trace))
		{
			printf("Game: Can't set Trace to '${Trace}': Property is integer");
			return ($this);
		}

		Game::$trace = $Trace;
		return ($this);
	}

# =
# 
# Game ID Property;
# 
# 
# 
# -

	public function GetID ()

	{
		return ($ID);
	}

	public function SetID ($ID)

	{
		if(!is_integer($ID))
		{
			Game::Error("Can't set ID to '${ID}'", "Property is integer");
			return (false);
		}

		$this->ID = $ID;
		return (true);
	}

# =
# 
# Game ContactID Property;
# 
# 
# 
# -

	public function GetContactID ()

	{
		return ($ContactID);
	}

	public function SetContactID ($ContactID)

	{
		if(!is_integer($ContactID))
		{
			Game::Error("Can't set ContactID to '${ContactID}'", "Property is integer");
			return (false);
		}

		$this->ContactID = $ContactID;
		return (true);
	}

# =
# 
# Game AccountID Property;
# 
# 
# 
# -

	public function GetAccountID ()

	{
		return ($AccountID);
	}

	public function SetAccountID ($AccountID)

	{
		if(!is_integer($AccountID))
		{
			Game::Error("Can't set AccountID to '${AccountID}'", "Property is integer");
			return (false);
		}

		$this->AccountID = $AccountID;
		return (true);
	}

# =
# 
# Game Code Property;
# 
# 
# 
# -

	public function GetCode ()

	{
		return ($Code);
	}

	public function SetCode ($Code)

	{
		if(is_numeric($Code))
		{
			Game::Error("Won't set Code to '${Code}'", "Property is alphanumeric");
			return (false);
		}

		$this->Code = $Code;
		return (true);
	}

# =
# 
# Game Name Property;
# 
# 
# 
# -

	public function GetName ()

	{
		return ($Name);
	}

	public function SetName ($Name)

	{
		$this->Name = $Name;
		return (true);
	}

# =
# 
# Game Clear Method;
# 
# Reset property values;
# 
# -

	public function Clear ()

	{
		Game::Event ("Clearing Object Properties", "");

		$this->ID = 0;
		$this->ContactID = 0;
		$this->AccountID = 0;
		$this->Code = "";
		$this->Name = "";

		return ($this);
	}

# =
# 
# Game Fetch Method;
# 
# Fetch record by either numeric key or alphanumeric code;
# 
# -

	public function Fetch ($Game)

	{
		if (is_numeric($Game))
		{
			$query = "SELECT * FROM Game WHERE ID=(${Game})";
		}
		else
		{
			$query = "SELECT * FROM Game WHERE Code='${Game}'";
		}

		Game::Event($query, "");

		if (!$this->table = mysql_query($query, Game::$db))
		{
			Game::Error("Can't fetch Game '${Game}'",  mysql_error(Game::$db));
			return (false);
		}

		if (!$this->field = mysql_fetch_object ($this->table))
		{
			Game::Error("Can't fetch Game '${Game}'", "No such Game.");
			return (false);
		}

		$this->ID = $this->field->ID;
		$this->ContactID = $this->field->ContactID;
		$this->AccountID = $this->field->AccountID;
		$this->Code = $this->field->Code;
		$this->Name = $this->field->Name;
		return (true);
	}

# =
# 
# Game Store Method;
# 
# Insert a new record or update the old record;
# 
# -

	public function Store ()

	{
		if (empty($this->Code))
		{
			Game::Error("Won't store Game record", "Code property is empty");
			return (false);
		}

		if (empty($this->Name))
		{
			Game::Error("Won't store Game record", "Name property is empty");
			return (false);
		}

		if ($this->ID)
		{
			$query = "UPDATE Game SET ID=('$this->ID'),ContactID=('$this->ContactID'),AccountID=('$this->AccountID'),Code='$this->Code',Name='$this->Name' WHERE ID=($this->ID)";
		}
		else
		{
			$query = "INSERT INTO Game (ID,ContactID,AccountID,Code,Name) VALUES (('$this->'),('$this->ContactID'),('$this->AccountID'),'$this->Code','$this->Name')";
		}

		Game::Event($query, "");

		if (!mysql_query($query, Game::$db))
		{
			Game::Error("Can't store Game $this->Code", mysql_error(Game::$db));
			return (false);
		}

#		if (!$this->ID)
#		{
#			$this->ID = mysql_insert_id(Game::$db);
#		}

		return (true);
	}

# =
# 
# Game Peek Method;
# 
# Reset property values;
# 
# -

	public function Peek ()

	{
		printf ("Game:ID = [$this->ID]\n");
		printf ("Game:ContactID = [$this->ContactID]\n");
		printf ("Game:AccountID = [$this->AccountID]\n");
		printf ("Game:Code = [$this->Code]\n");
		printf ("Game:Name = [$this->Name]\n");
		printf ("\n");
		return ($this);
	}

# =
# 
# Game Error Method;
# 
# 
# 
# -

	public function Error ($error, $cause)

	{
		if (Game::$debug == 1)
		{
			printf("<br><span class='error'>Game: %s;</span><br>", cmassoc::combine($error, ": ",$cause));
		}

		if (Game::$debug == 2)
		{
			printf("Game: %s;\n", cmassoc::combine($error, ": ",$cause));
		}

		return (true);
	}

# =
# 
# Game Event Method;
# 
# 
# 
# -

	public function Event ($event, $label)

	{
		if (Game::$trace == 1)
		{
			printf("<br><span class='error'>Game: %s;</span><br>", cmassoc::combine($event, ": ",$label));
		}

		if (Game::$trace == 2)
		{
			printf("Game: %s;\n", cmassoc::combine($event, ": ",$label));
		}

		return (true);
	}

# =
# 
# Game Constructor;
# 
# 
# 
# -

	public function __construct ($db)

	{
		Game::$db = $db;
		return;
	}

# =
# 
# Game Destructor;
# 
# 
# 
# -

	public function __destruct ()

	{
		return;
	}

# =
# End Game Class Definition;
# -

}

 ?>
