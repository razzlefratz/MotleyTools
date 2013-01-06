<?php

# ====================================================================
# Begin Class Definition;
# --------------------------------------------------------------------

class MySQL 
{

# ====================================================================
# Constants;
# --------------------------------------------------------------------

	private $stylesheet = "http://spc.razzlefratz.net/styles/spcdb.css";
	private $wwwroot = "http://spc.razzlefratz.net";
	private $library = "/disk2/www/spc/php/classes";
	private $website = "/disk2/www/spc";

# ====================================================================
# Variables;
# --------------------------------------------------------------------

	private static $db;

# ====================================================================
#
# MySQL Tables Method;
#
#
#
# --------------------------------------------------------------------

	public function Tables ($database) 
	{
		if (!mysql_select_db ($database, self::$db)) 
		{
			MySQL::Error("Can't use ${database} database", mysql_error (self::$db));
			exit;
		}
		$query = "SHOW TABLES FROM ${database}";
		if (!$tables = mysql_query ($query, self::$db)) 
		{
			MySQL::Error("Can't find any tables in ${database} database", mysql_error (self::$db));
			return;
		}
		while ($table = mysql_fetch_row ($tables)) 
		{
			MySQL::Event($table[0]);
			MySQL::Object ($table[0]);
		}
		mysql_free_result ($tables);
		return;
	}

# ====================================================================
#
# MySQL Object Method;
#
#
#
# --------------------------------------------------------------------

	public function Object ($table) 
	{
		$query = "SHOW FIELDS FROM ${table}";
		if (!$fields = mysql_query ($query, self::$db)) 
		{
			MySQL::Error ("Can't find any fields in ${table} table", mysql_error(self::$db));
			return (false);
		}
		mysql_free_result ($fields);
		if (!$ofp = fopen ("$this->library/${table}-object.php", "w")) 
		{
			MySQL::Event ("Can't open ${table}.php");
			return ($this);
		}
		fputs ($ofp, "<?php\n");
		fputs ($ofp, "# =\n");
		fputs ($ofp, "# \n");
		fputs ($ofp, "# Begin $table Class Definition;\n");
		fputs ($ofp, "# \n");
		fputs ($ofp, "# \n");
		fprintf ($ofp, "# Published %s by Charles Maier Associates Limited for internal use;\n", date ("Y"));
		fprintf ($ofp, "# Generated %s by MySQL.php;\n", date ("H:i:s D d M Y T"));
		fputs ($ofp, "# \n");
		fputs ($ofp, "# -\n\n");
		fputs ($ofp, "class $table\n\n");
		fputs ($ofp, "{\n\n");
		self::Variables($ofp, $table);
		self::DebugProperty($ofp, $table);
		self::TraceProperty($ofp, $table);
		self::TableProperties($ofp, $table);
		self::ClearMethod($ofp, $table);
		self::FetchMethod($ofp, $table);
		self::StoreMethod($ofp, $table);
		self::ErrorMethod($ofp, $table);
		self::EventMethod($ofp, $table);
		self::PeekMethod($ofp, $table);
		self::Constructor($ofp, $table);
		self::Destructor($ofp, $table);
		fputs ($ofp, "# =\n");
		fputs ($ofp, "# End ${table} Class Definition;\n");
		fputs ($ofp, "# -\n\n");
		fputs ($ofp, "}\n\n");
		fputs ($ofp, " ?>");
		return ($this);
	}

# ====================================================================
#
# MySQL Variables Method;
#
#
#
# --------------------------------------------------------------------

	public function Variables($ofp, $table) 
	{
		$query = "SHOW FIELDS FROM ${table}";
		fputs ($ofp, "# =\n");
		fputs ($ofp, "# Public ${table} Variables;\n");
		fputs ($ofp, "# -\n\n");
		fputs ($ofp, "\n");
		fputs ($ofp, "# =\n");
		fputs ($ofp, "# Private ${table} Variables;\n");
		fputs ($ofp, "# -\n\n");
		$fields = mysql_query ($query, self::$db);
		while ($field = mysql_fetch_object ($fields)) 
		{
			fprintf ($ofp, "\tprivate \$%s = %s;\n", $field->Field, self::Initial ($field));
		}
		fputs ($ofp, "\tprivate static \$debug = 0;\n");
		fputs ($ofp, "\tprivate static \$trace = 0;\n");
		fputs ($ofp, "\tprivate static \$db = NULL;\n");
		fputs ($ofp, "\n");
		return ($this);
	}

# ====================================================================
#
# MySQL DebugProperty Method;
#
#
#
# --------------------------------------------------------------------

	public function DebugProperty ($ofp, $table) 
	{
		fputs ($ofp, "# =\n# \n");
		fputs ($ofp, "# ${table} Debug Property;\n");
		fputs ($ofp, "# \n# Get and Set Error display mode;\n# \n");
		fputs ($ofp, "# -\n\n");
		fputs ($ofp, "\tpublic function GetDebug ()\n\n");
		fputs ($ofp, "\t{\n");
		fputs ($ofp, "\t\treturn (self::\$debug);\n");
		fputs ($ofp, "\t}\n\n");
		fputs ($ofp, "\tpublic function SetDebug (\$Debug)\n\n");
		fputs ($ofp, "\t{\n");
		fputs ($ofp, "\t\tif(!is_integer(\$Debug))\n");
		fputs ($ofp, "\t\t{\n");
		fputs ($ofp, "\t\t\tprintf(\"${table}: Can't set Debug to '\$\{Debug}': Property is integer\");\n");
		fputs ($ofp, "\t\t\treturn (\$this);\n");
		fputs ($ofp, "\t\t}\n\n");
		fputs ($ofp, "\t\tself::\$debug = \$Debug;\n");
		fputs ($ofp, "\t\treturn (\$this);\n");
		fputs ($ofp, "\t}\n\n");
		return ($this);
	}

# ====================================================================
#
# MySQL TraceProperty Method;
#
#
#
# --------------------------------------------------------------------

	public function TraceProperty ($ofp, $table) 
	{
		fputs ($ofp, "# =\n# \n");
		fputs ($ofp, "# ${table} Trace Property;\n");
		fputs ($ofp, "# \n# Get and Set Event display mode;\n# \n");
		fputs ($ofp, "# -\n\n");
		fputs ($ofp, "\tpublic function GetTrace ()\n\n");
		fputs ($ofp, "\t{\n");
		fputs ($ofp, "\t\treturn (${table}::\$trace);\n");
		fputs ($ofp, "\t}\n\n");
		fputs ($ofp, "\tpublic function SetTrace (\$Trace)\n\n");
		fputs ($ofp, "\t{\n");
		fputs ($ofp, "\t\tif(!is_integer(\$Trace))\n");
		fputs ($ofp, "\t\t{\n");
		fputs ($ofp, "\t\t\tprintf(\"${table}: Can't set Trace to '\$\{Trace}': Property is integer\");\n");
		fputs ($ofp, "\t\t\treturn (\$this);\n");
		fputs ($ofp, "\t\t}\n\n");
		fputs ($ofp, "\t\t${table}::\$trace = \$Trace;\n");
		fputs ($ofp, "\t\treturn (\$this);\n");
		fputs ($ofp, "\t}\n\n");
		return ($this);
	}

# ====================================================================
#
# MySQL TableProperties Method;
#
#
#
# --------------------------------------------------------------------

	public function TableProperties ($ofp, $table) 
	{
		$query = "SHOW FIELDS FROM ${table}";
		$fields = mysql_query ($query, self::$db);
		while ($field = mysql_fetch_object ($fields)) 
		{
			fputs ($ofp, "# =\n# \n");
			fputs ($ofp, "# ${table} $field->Field Property;\n");
			fputs ($ofp, "# \n# \n# \n");
			fputs ($ofp, "# -\n\n");
			fputs ($ofp, "\tpublic function Get$field->Field ()\n\n");
			fputs ($ofp, "\t{\n");
			fputs ($ofp, "\t\treturn (\$$field->Field);\n");
			fputs ($ofp, "\t}\n\n");
			fputs ($ofp, "\tpublic function Set$field->Field (\$$field->Field)\n\n");
			fputs ($ofp, "\t{\n");
			if (!strcmp($field->Field, "Code")) 
			{
				fputs ($ofp, "\t\tif(is_numeric(\$$field->Field))\n");
				fputs ($ofp, "\t\t{\n");
				fputs ($ofp, "\t\t\t${table}::Error(\"Won't set $field->Field to '\$\{$field->Field}'\", \"Property is alphanumeric\");\n");
				fputs ($ofp, "\t\t\treturn (false);\n");
				fputs ($ofp, "\t\t}\n\n");
			}
			else if (!strncmp($field->Type, "int", strlen("int"))) 
			{
				fputs ($ofp, "\t\tif(!is_integer(\$$field->Field))\n");
				fputs ($ofp, "\t\t{\n");
				fputs ($ofp, "\t\t\t${table}::Error(\"Can't set $field->Field to '\$\{$field->Field}'\", \"Property is integer\");\n");
				fputs ($ofp, "\t\t\treturn (false);\n");
				fputs ($ofp, "\t\t}\n\n");
			}
			else if (!strncmp($field->Type, "float", strlen("float"))) 
			{
				fputs ($ofp, "\t\tif(!is_float(\$$field->Field))\n");
				fputs ($ofp, "\t\t{\n");
				fputs ($ofp, "\t\t\t${table}::Error(\"Can't set $field->Field to '\$\{$field->Field}'\", \"Property is float\");\n");
				fputs ($ofp, "\t\t\treturn (false);\n");
				fputs ($ofp, "\t\t}\n\n");
			}
			else if (!strncmp($field->Type, "date", strlen("date"))) 
			{
				fputs ($ofp, "\t\tif(!is_date(\$$field->Field))\n");
				fputs ($ofp, "\t\t{\n");
				fputs ($ofp, "\t\t\t${table}::Error(\"Can't set $field->Field to '\$\{$field->Field}'\", \"Property is date\");\n");
				fputs ($ofp, "\t\t\treturn (false);\n");
				fputs ($ofp, "\t\t}\n\n");
			}
			fputs ($ofp, "\t\t\$this->$field->Field = \$$field->Field;\n");
			fputs ($ofp, "\t\treturn (true);\n");
			fputs ($ofp, "\t}\n\n");
		}
		return ($this);
	}

# ====================================================================
#
# MySQL ClearMethod Method;
#
#
#
# --------------------------------------------------------------------

	public function ClearMethod ($ofp, $table) 
	{
		$query = "SHOW FIELDS FROM ${table}";
		fputs ($ofp, "# =\n# \n");
		fputs ($ofp, "# ${table} Clear Method;\n");
		fputs ($ofp, "# \n# Reset table properties;\n# \n");
		fputs ($ofp, "# -\n\n");
		fputs ($ofp, "\tpublic function Clear ()\n\n");
		fputs ($ofp, "\t{\n");
		fputs ($ofp, "\t\t${table}::Event (\"Clearing Object Properties\", \"\");\n\n");
		$fields = mysql_query ($query, self::$db);
		while ($field = mysql_fetch_object ($fields)) 
		{
			fprintf ($ofp, "\t\t\$this->%s = %s;\n", $field->Field, self::Initial ($field));
		}
		fputs ($ofp, "\n");
		fputs ($ofp, "\t\treturn (\$this);\n");
		fputs ($ofp, "\t}\n\n");
		return ($this);
	}

# ====================================================================
#
# MySQL FetchMethod Method;
#
#
#
# --------------------------------------------------------------------

	public function FetchMethod ($ofp, $table) 
	{
		$query = "SHOW FIELDS FROM ${table}";
		fputs ($ofp, "# =\n# \n");
		fputs ($ofp, "# ${table} Fetch Method;\n");
		fputs ($ofp, "# \n# Fetch record by either numeric key or alphanumeric code;\n# \n");
		fputs ($ofp, "# -\n\n");
		fputs ($ofp, "\tpublic function Fetch (\$${table})\n\n");
		fputs ($ofp, "\t{\n");
		fputs ($ofp, "\t\tif (is_numeric(\$${table}))\n");
		fputs ($ofp, "\t\t{\n");
		fputs ($ofp, "\t\t\t\$query = \"SELECT * FROM ${table} WHERE ID=(\$\{${table}})\";\n");
		fputs ($ofp, "\t\t}\n");
		fputs ($ofp, "\t\telse\n");
		fputs ($ofp, "\t\t{\n");
		fputs ($ofp, "\t\t\t\$query = \"SELECT * FROM ${table} WHERE Code='\$\{${table}}'\";\n");
		fputs ($ofp, "\t\t}\n\n");
		fputs ($ofp, "\t\t${table}::Event(\$query, \"\");\n\n");
		fputs ($ofp, "\t\tif (!\$this->table = mysql_query(\$query, self::\$db))\n");
		fputs ($ofp, "\t\t{\n");
		fputs ($ofp, "\t\t\t${table}::Error(\"Can't fetch ${table} '\$\{${table}}'\",  mysql_error(self::\$db));\n");
		fputs ($ofp, "\t\t\treturn (false);\n");
		fputs ($ofp, "\t\t}\n\n");
		fputs ($ofp, "\t\tif (!\$this->field = mysql_fetch_object (\$this->table))\n");
		fputs ($ofp, "\t\t{\n");
		fputs ($ofp, "\t\t\t${table}::Error(\"Can't fetch ${table} '\$\{${table}}'\", \"No such ${table}.\");\n");
		fputs ($ofp, "\t\t\treturn (false);\n");
		fputs ($ofp, "\t\t}\n\n");
		$fields = mysql_query ($query, self::$db);
		while ($field = mysql_fetch_object ($fields)) 
		{
			fprintf ($ofp, "\t\t\$this->$field->Field = \$this->field->$field->Field;\n");
		}
		fputs ($ofp, "\t\treturn (true);\n");
		fputs ($ofp, "\t}\n\n");
		return ($this);
	}

# ====================================================================
#
# MySQL StoreMethod Method;
#
#
#
# --------------------------------------------------------------------

	public function StoreMethod ($ofp, $table) 
	{
		$query = "SHOW FIELDS FROM ${table}";
		fputs ($ofp, "# =\n# \n");
		fputs ($ofp, "# ${table} Store Method;\n");
		fputs ($ofp, "# \n# Insert a new record or update the old record;\n# \n");
		fputs ($ofp, "# -\n\n");
		fputs ($ofp, "\tpublic function Store ()\n\n");
		fputs ($ofp, "\t{\n");
		fputs ($ofp, "#\t\tif (empty(\$this->Code))\n");
		fputs ($ofp, "#\t\t{\n");
		fputs ($ofp, "#\t\t\t${table}::Error(\"Won't store ${table} record\", \"Code property is empty\");\n");
		fputs ($ofp, "#\t\t\treturn (false);\n");
		fputs ($ofp, "#\t\t}\n\n");
		fputs ($ofp, "#\t\tif (empty(\$this->Name))\n");
		fputs ($ofp, "#\t\t{\n");
		fputs ($ofp, "#\t\t\t${table}::Error(\"Won't store ${table} record\", \"Name property is empty\");\n");
		fputs ($ofp, "#\t\t\treturn (false);\n");
		fputs ($ofp, "#\t\t}\n\n");
		fputs ($ofp, "\t\tif (\$this->ID)\n");
		fputs ($ofp, "\t\t{\n");
		$fields = mysql_query ($query, self::$db);
		$field = mysql_fetch_object ($fields);
		fputs ($ofp, "\t\t\t\$query = \"UPDATE ${table} SET $field->Field=%s", self::Content($field));
		while ($field = mysql_fetch_object ($fields)) 
		{
			fprintf ($ofp, ",$field->Field=%s", self::Content($field));
		}
		fputs ($ofp, " WHERE ID=(\$this->ID)\";\n");
		fputs ($ofp, "\t\t}\n");
		fputs ($ofp, "\t\telse\n");
		fputs ($ofp, "\t\t{\n");
		$fields = mysql_query ($query, self::$db);
		$field = mysql_fetch_object ($fields);
		fprintf ($ofp, "\t\t\t\$query = \"INSERT INTO ${table} ($field->Field");
		while ($field = mysql_fetch_object ($fields)) 
		{
			fprintf ($ofp, ",$field->Field");
		}
		$fields = mysql_query ($query, self::$db);
		$field = mysql_fetch_object ($fields);
		fprintf ($ofp, ") VALUES (%s", self::Content($field));
		while ($field = mysql_fetch_object ($fields)) 
		{
			fprintf ($ofp, ",%s", self::Content ($field));
		}
		fputs ($ofp, ")\";\n");
		fputs ($ofp, "\t\t}\n\n");
		fputs ($ofp, "\t\t${table}::Event(\$query, \"\");\n\n");
		fputs ($ofp, "\t\tif (!mysql_query(\$query, self::\$db))\n");
		fputs ($ofp, "\t\t{\n");
		fputs ($ofp, "\t\t\t${table}::Error(\"Can't store ${table} \$this->Code\", mysql_error(self::\$db));\n");
		fputs ($ofp, "\t\t\treturn (false);\n");
		fputs ($ofp, "\t\t}\n\n");
		fputs ($ofp, "#\t\tif (!\$this->ID)\n");
		fputs ($ofp, "#\t\t{\n");
		fputs ($ofp, "#\t\t\t\$this->ID = mysql_insert_id(self::\$db);\n");
		fputs ($ofp, "#\t\t}\n\n");
		fputs ($ofp, "\t\treturn (true);\n");
		fputs ($ofp, "\t}\n\n");
		return ($this);
	}

# ====================================================================
#
# MySQL PeekMethod Method;
#
#
#
# --------------------------------------------------------------------

	public function PeekMethod ($ofp, $table) 
	{
		$query = "SHOW FIELDS FROM ${table}";
		fputs ($ofp, "# =\n# \n");
		fputs ($ofp, "# ${table} Peek Method;\n");
		fputs ($ofp, "# \n# Echo property values;\n# \n");
		fputs ($ofp, "# -\n\n");
		fputs ($ofp, "\tpublic function Peek ()\n\n");
		fputs ($ofp, "\t{\n");
		$fields = mysql_query ($query, self::$db);
		while ($field = mysql_fetch_object ($fields)) 
		{
			fprintf ($ofp, "\t\tprintf (\"${table}:$field->Field = [\$this->$field->Field]\\n\");\n");
		}
		fprintf ($ofp, "\t\tprintf (\"\\n\");\n");
		fputs ($ofp, "\t\treturn (\$this);\n");
		fputs ($ofp, "\t}\n\n");
		return ($this);
	}

# ====================================================================
#
# MySQL ErrorMethod Method;
#
#
#
# --------------------------------------------------------------------

	public function ErrorMethod ($ofp, $table) 
	{
		fputs ($ofp, "# =\n# \n");
		fputs ($ofp, "# ${table} Error Method;\n");
		fputs ($ofp, "# \n# \n# \n");
		fputs ($ofp, "# -\n\n");
		fputs ($ofp, "\tpublic function Error (\$Error, \$Cause)\n\n");
		fputs ($ofp, "\t{\n");
		fputs ($ofp, "\t\t\tCMAssoc::Event(get_class(\$this), \$Event, \$Label, \$this->Trace)\n");
		fputs ($ofp, "#\t\tif (self::\$debug == 1)\n");
		fputs ($ofp, "#\t\t{\n");
		fputs ($ofp, "#\t\t\tprintf(\"<br><span class='error'>${table}: %s.</span><br>\", cmassoc::combine(\$Error, \": \",\$Cause));\n");
		fputs ($ofp, "#\t\t}\n\n");
		fputs ($ofp, "#\t\tif (self::\$debug == 2)\n");
		fputs ($ofp, "#\t\t{\n");
		fputs ($ofp, "#\t\t\tprintf(\"${table}: %s.\\n\", cmassoc::combine(\$Error, \": \",\$Cause));\n");
		fputs ($ofp, "#\t\t}\n\n");
		fputs ($ofp, "\t\treturn (true);\n");
		fputs ($ofp, "\t}\n\n");
		return ($this);
	}

# ====================================================================
#
# MySQL EventMethod Method;
#
#
#
# --------------------------------------------------------------------

	public function EventMethod ($ofp, $table) 
	{
		fputs ($ofp, "# =\n# \n");
		fputs ($ofp, "# ${table} Event Method;\n");
		fputs ($ofp, "# \n# \n# \n");
		fputs ($ofp, "# -\n\n");
		fputs ($ofp, "\tpublic function Event (\$Event, \$Label)\n\n");
		fputs ($ofp, "\t{\n");
		fputs ($ofp, "\t\t\tCMAssoc::Event(get_class(\$this), \$Event, \$Label, \$this->Trace)\n");
		fputs ($ofp, "#\t\tif (self::\$trace == 1)\n");
		fputs ($ofp, "#\t\t{\n");
		fputs ($ofp, "#\t\t\tprintf(\"<br><span class='event'>${table}: %s.</span><br>\", cmassoc::combine(\$Event, \": \",\$Label));\n");
		fputs ($ofp, "#\t\t}\n\n");
		fputs ($ofp, "#\t\tif (self::\$trace == 2)\n");
		fputs ($ofp, "#\t\t{\n");
		fputs ($ofp, "#\t\t\tprintf(\"${table}: %s.\\n\", cmassoc::combine(\$Event, \": \",\$Label));\n");
		fputs ($ofp, "#\t\t}\n\n");
		fputs ($ofp, "\t\treturn (true);\n");
		fputs ($ofp, "\t}\n\n");
		return ($this);
	}

# ====================================================================
#
# MySQL Constructor;
#
#
#
# --------------------------------------------------------------------

	public function Constructor($ofp, $table) 
	{
		fputs ($ofp, "# =\n# \n");
		fputs ($ofp, "# ${table} Constructor;\n");
		fputs ($ofp, "# \n# \n# \n");
		fputs ($ofp, "# -\n\n");
		fputs ($ofp, "\tpublic function __construct (\$db)\n\n");
		fputs ($ofp, "\t{\n");
		fputs ($ofp, "\t\tself::\$db = \$db;\n");
		fputs ($ofp, "\t\treturn;\n");
		fputs ($ofp, "\t}\n\n");
		return ($this);
	}

# ====================================================================
#
# MySQL Destructor;
#
#
#
# --------------------------------------------------------------------

	public function Destructor($ofp, $table) 
	{
		fputs ($ofp, "# =\n# \n");
		fputs ($ofp, "# ${table} Destructor;\n");
		fputs ($ofp, "# \n# \n# \n");
		fputs ($ofp, "# -\n\n");
		fputs ($ofp, "\tpublic function __destruct ()\n\n");
		fputs ($ofp, "\t{\n");
		fputs ($ofp, "\t\treturn;\n");
		fputs ($ofp, "\t}\n\n");
		return ($this);
	}

# ====================================================================
#
# MySQL Initial Method;
#
#
#
# --------------------------------------------------------------------

	public function Initial ($field) 
	{
		if (!strncmp ($field->Type, "int", strlen ("int"))) 
		{
			return ((int)($field->Default));
		}
		if (!strncmp ($field->Type, "float", strlen ("float"))) 
		{

#      			return ((float)($field->Default));

			return ("$field->Default");
		}
		if (!strncmp ($field->Type, "char", strlen ("char"))) 
		{
			return ("\"$field->Default\"");
		}
		if (!strncmp ($field->Type, "varchar", strlen ("varchar"))) 
		{
			return ("\"$field->Default\"");
		}
		if (!strncmp ($field->Type, "date", strlen ("date"))) 
		{
			return ("NULL");
		}
		if (!strncmp ($field->Type, "timestamp", strlen ("timestamp"))) 
		{
			return ("NULL");
		}
		if ($field->Default == NULL) 
		{
			return ("NULL");
		}
		return ("$field->Default");
	}

# ====================================================================
#
# MySQL Content Method;
#
#
#
# --------------------------------------------------------------------

	public function Content ($field) 
	{
		if (!strncmp ($field->Type, "int", strlen ("int"))) 
		{
			return ("(\$this->$field->Field)");
		}
		if (!strncmp ($field->Type, "float", strlen ("float"))) 
		{
			return ("(\$this->$field->Field)");
		}
		if (!strncmp ($field->Type, "char", strlen ("char"))) 
		{
			return ("'\$this->$field->Field'");
		}
		if (!strncmp ($field->Type, "varchar", strlen ("varchar"))) 
		{
			return ("'\$this->$field->Field'");
		}
		if (!strncmp ($field->Type, "date", strlen ("date"))) 
		{
			return ("'\$this->$field->Field'");
		}
		if (!strncmp ($field->Type, "timestamp", strlen ("timestamp"))) 
		{
			return ("'\$this->$field->Field'");
		}
		return ("('\$this->$field->Field')");
	}

# ====================================================================
#
# MySQL Error Method;
#
# --------------------------------------------------------------------

	private function Error ($Error, $Cause) 
	{
		echo get_class($this).": ".$Error.": ".$Cause."\n";
		return;
	}

# ====================================================================
#
# MySQL Event Method;
#
# --------------------------------------------------------------------

	private function Event ($Event) 
	{
		echo get_class($this).": ".$Event."\n";
		return;
	}

# ====================================================================
#
# Constructor Method;
#
# --------------------------------------------------------------------

	public function __construct ($hostname, $username, $password) 
	{
		if (!self::$db = mysql_connect ($hostname, $username, $password)) 
		{
			MySQL::Event ("Can't connect to MySQL server on ${hostname}");
			exit;
		}
		return;
	}

# ====================================================================
#
# Destructor Method;
#
#
#
# --------------------------------------------------------------------

	public function __destruct () 
	{
		return;
	}

# ====================================================================
# End MySQL Class Definition;
# --------------------------------------------------------------------

}
 ?>
