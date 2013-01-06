<?php
# =
# 
# Begin Drawing Class Definition;
# 
# 
# Published 2005 by Charles Maier Associates Limited for internal use;
# Generated 16:32:57 Mon 05 Sep 2005 EDT by MySQL.php;
# 
# -

class Drawing

{

# =
# Public Drawing Variables;
# -


# =
# Private Drawing Variables;
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
# Drawing Debug Property;
# 
# 
# 
# -

	public function GetDebug ()

	{
		return (Drawing::$debug);
	}

	public function SetDebug ($Debug)

	{
		if(!is_integer($Debug))
		{
			printf("Drawing: Can't set Debug to '${Debug}': Property is integer");
			return ($this);
		}

		Drawing::$debug = $Debug;
		return ($this);
	}

# =
# 
# Drawing Trace Property;
# 
# 
# 
# -

	public function GetTrace ()

	{
		return (Drawing::$trace);
	}

	public function SetTrace ($Trace)

	{
		if(!is_integer($Trace))
		{
			printf("Drawing: Can't set Trace to '${Trace}': Property is integer");
			return ($this);
		}

		Drawing::$trace = $Trace;
		return ($this);
	}

# =
# 
# Drawing ID Property;
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
			Drawing::Error("Can't set ID to '${ID}'", "Property is integer");
			return (false);
		}

		$this->ID = $ID;
		return (true);
	}

# =
# 
# Drawing ContactID Property;
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
			Drawing::Error("Can't set ContactID to '${ContactID}'", "Property is integer");
			return (false);
		}

		$this->ContactID = $ContactID;
		return (true);
	}

# =
# 
# Drawing AccountID Property;
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
			Drawing::Error("Can't set AccountID to '${AccountID}'", "Property is integer");
			return (false);
		}

		$this->AccountID = $AccountID;
		return (true);
	}

# =
# 
# Drawing Code Property;
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
			Drawing::Error("Won't set Code to '${Code}'", "Property is alphanumeric");
			return (false);
		}

		$this->Code = $Code;
		return (true);
	}

# =
# 
# Drawing Name Property;
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
# Drawing Clear Method;
# 
# Reset property values;
# 
# -

	public function Clear ()

	{
		Drawing::Event ("Clearing Object Properties", "");

		$this->ID = 0;
		$this->ContactID = 0;
		$this->AccountID = 0;
		$this->Code = "";
		$this->Name = "";

		return ($this);
	}

# =
# 
# Drawing Fetch Method;
# 
# Fetch record by either numeric key or alphanumeric code;
# 
# -

	public function Fetch ($Drawing)

	{
		if (is_numeric($Drawing))
		{
			$query = "SELECT * FROM Drawing WHERE ID=(${Drawing})";
		}
		else
		{
			$query = "SELECT * FROM Drawing WHERE Code='${Drawing}'";
		}

		Drawing::Event($query, "");

		if (!$this->table = mysql_query($query, Drawing::$db))
		{
			Drawing::Error("Can't fetch Drawing '${Drawing}'",  mysql_error(Drawing::$db));
			return (false);
		}

		if (!$this->field = mysql_fetch_object ($this->table))
		{
			Drawing::Error("Can't fetch Drawing '${Drawing}'", "No such Drawing.");
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
# Drawing Store Method;
# 
# Insert a new record or update the old record;
# 
# -

	public function Store ()

	{
		if (empty($this->Code))
		{
			Drawing::Error("Won't store Drawing record", "Code property is empty");
			return (false);
		}

		if (empty($this->Name))
		{
			Drawing::Error("Won't store Drawing record", "Name property is empty");
			return (false);
		}

		if ($this->ID)
		{
			$query = "UPDATE Drawing SET ID=('$this->ID'),ContactID=('$this->ContactID'),AccountID=('$this->AccountID'),Code='$this->Code',Name='$this->Name' WHERE ID=($this->ID)";
		}
		else
		{
			$query = "INSERT INTO Drawing (ID,ContactID,AccountID,Code,Name) VALUES (('$this->'),('$this->ContactID'),('$this->AccountID'),'$this->Code','$this->Name')";
		}

		Drawing::Event($query, "");

		if (!mysql_query($query, Drawing::$db))
		{
			Drawing::Error("Can't store Drawing $this->Code", mysql_error(Drawing::$db));
			return (false);
		}

#		if (!$this->ID)
#		{
#			$this->ID = mysql_insert_id(Drawing::$db);
#		}

		return (true);
	}

# =
# 
# Drawing Peek Method;
# 
# Reset property values;
# 
# -

	public function Peek ()

	{
		printf ("Drawing:ID = [$this->ID]\n");
		printf ("Drawing:ContactID = [$this->ContactID]\n");
		printf ("Drawing:AccountID = [$this->AccountID]\n");
		printf ("Drawing:Code = [$this->Code]\n");
		printf ("Drawing:Name = [$this->Name]\n");
		printf ("\n");
		return ($this);
	}

# =
# 
# Drawing Error Method;
# 
# 
# 
# -

	public function Error ($error, $cause)

	{
		if (Drawing::$debug == 1)
		{
			printf("<br><span class='error'>Drawing: %s;</span><br>", cmassoc::combine($error, ": ",$cause));
		}

		if (Drawing::$debug == 2)
		{
			printf("Drawing: %s;\n", cmassoc::combine($error, ": ",$cause));
		}

		return (true);
	}

# =
# 
# Drawing Event Method;
# 
# 
# 
# -

	public function Event ($event, $label)

	{
		if (Drawing::$trace == 1)
		{
			printf("<br><span class='error'>Drawing: %s;</span><br>", cmassoc::combine($event, ": ",$label));
		}

		if (Drawing::$trace == 2)
		{
			printf("Drawing: %s;\n", cmassoc::combine($event, ": ",$label));
		}

		return (true);
	}

# =
# 
# Drawing Constructor;
# 
# 
# 
# -

	public function __construct ($db)

	{
		Drawing::$db = $db;
		return;
	}

# =
# 
# Drawing Destructor;
# 
# 
# 
# -

	public function __destruct ()

	{
		return;
	}

# =
# End Drawing Class Definition;
# -

}

 ?>
