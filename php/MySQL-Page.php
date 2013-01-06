<?php

# ====================================================================
# Begin Class Definition;
# --------------------------------------------------------------------

class MySQLPage 
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
			self::Error("Can't use ${database} database", mysql_error (self::$db));
			exit;
		}
		$query = "SHOW TABLES FROM ${database}";
		if (!$tables = mysql_query ($query, self::$db)) 
		{
			self::Error("Can't find any tables in ${database} database", mysql_error (self::$db));
			return;
		}
		while ($table = mysql_fetch_row ($tables)) 
		{
			self::Event($table[0]);
#			self::InputPage ($table[0]);
			self::StorePage ($table[0]);
		}
		mysql_free_result ($tables);
		return;
	}

# ====================================================================
#
# MySQL InputPage Method;
#
#
#
# --------------------------------------------------------------------

	public function InputPage ($table) 
	{
		$query = "SHOW FIELDS FROM ${table}";
		if (!$fields = mysql_query ($query, self::$db)) 
		{
			self::Error ("Can't find any fields in ${table} table", mysql_error(self::$db));
			return (false);
		}
		if (!$ofp = fopen ("$this->website/${table}-Input.php", "w")) 
		{
			self::Event ("Can't open ${table}.php");
			return (false);
		}
		fputs ($ofp, "<?php\n");
		fputs ($ofp, "include \"php/modules/CMAssoc.php\";\n");
		fputs ($ofp, "\$db = CMAssoc::Connect();\n");
		fputs ($ofp, " ?>\n");
		fputs ($ofp, "<html>\n");
		fputs ($ofp, "\t<head>\n");
		fputs ($ofp, "\t\t<title>\n");
		fputs ($ofp, "\t\t\t${table}\n");
		fputs ($ofp, "\t\t\t</title>\n");
		fputs ($ofp, "\t\t<link href='$this->stylesheet' rel='stylesheet' type='text/css'/>\n");
		fputs ($ofp, "\t\t</head>\n");
		fputs ($ofp, "\t<body>\n");
		fputs ($ofp, "\t\t<h1>\n");
		fputs ($ofp, "\t\t\t${table} Input\n");
		fputs ($ofp, "\t\t\t</h1>\n");
		fputs ($ofp, "\t\t<form method='post' action='$this->wwwroot/${table}-Store.php'>\n");
		fputs ($ofp, "\t\t\t<table class='form'>\n");
		while ($field = mysql_fetch_object($fields)) 
		{
			if (!strcmp($field->Field, "ID")) 
			{
				continue;
			}
			if (!strcmp($field->Field, "ControlID")) 
			{
				self::Select ($ofp, "Account", "account");
				continue;
			}
			if (!strcmp($field->Field, "PaymentID")) 
			{
				self::Select ($ofp, "Account", "account");
				continue;
			}
			if (!strcmp($field->Field, "ReceiptID")) 
			{
				self::Select ($ofp, "Account", "account");
				continue;
			}
			if (!strcmp($field->Field, "AccountID")) 
			{
				self::Select ($ofp, "Account", "account");
				continue;
			}
			if (!strcmp($field->Field, "ContactID")) 
			{
				self::Select ($ofp, "Contact", "contact");
				continue;
			}
			if (!strcmp($field->Field, "ProjectID")) 
			{
				self::Select ($ofp, "Project", "project");
				continue;
			}
			if (!strcmp($field->Field, "GameID")) 
			{
				self::Select ($ofp, "Game", "game");
				continue;
			}
			if (!strcmp($field->Field, "PoolID")) 
			{
				self::Select ($ofp, "Pool", "pool");
				continue;
			}
			if (!strcmp($field->Field, "Type")) 
			{
		fputs ($ofp, "\t\t\t\t<tr>\n");
		fputs ($ofp, "\t\t\t\t\t<td>\n");
		fputs ($ofp, "\t\t\t\t\t\tEnter ${table} $field->Field:\n");
		fputs ($ofp, "\t\t\t\t\t\t</td>\n");
		fputs ($ofp, "\t\t\t\t\t<td>\n");
		fputs ($ofp, "\t\t\t\t\t\t<select name='$field->Field'/>\n");
		fputs ($ofp, "\t\t\t\t\t\t\t<option value='0'>NONE</option>\n");
		fputs ($ofp, "\t\t\t\t\t\t\t<option value='1'>ONE</option>\n");
		fputs ($ofp, "\t\t\t\t\t\t\t<option value='2'>TWO</option>\n");
		fputs ($ofp, "\t\t\t\t\t\t\t</select>\n");
		fputs ($ofp, "\t\t\t\t\t\t</td>\n");
		fputs ($ofp, "\t\t\t\t\t</tr>\n");
				continue;
			}
			if (!strcmp($field->Field, "Created")) 
			{
				continue;
			}
			if (!strcmp($field->Field, "Updated")) 
			{
				continue;
			}
			fputs ($ofp, "\t\t\t\t<tr>\n");
			fputs ($ofp, "\t\t\t\t\t<td>\n");
			fputs ($ofp, "\t\t\t\t\t\tEnter ${table} $field->Field:\n");
			fputs ($ofp, "\t\t\t\t\t\t</td>\n");
			fputs ($ofp, "\t\t\t\t\t<td>\n");
			fputs ($ofp, "\t\t\t\t\t\t<input type='text' name='$field->Field'/>\n");
			fputs ($ofp, "\t\t\t\t\t\t</td>\n");
			fputs ($ofp, "\t\t\t\t\t</tr>\n");
		}
		fputs ($ofp, "\t\t\t\t</table>\n");
		fputs ($ofp, "\t\t\t<div>\n");
		fputs ($ofp, "\t\t\t\t<input type='submit' value='send'/>\n");
		fputs ($ofp, "\t\t\t\t<input type='reset'/>\n");
		fputs ($ofp, "\t\t\t\t</div>\n");
		fputs ($ofp, "\t\t\t</form>\n");
		fputs ($ofp, "\t\t</body>\n");
		fputs ($ofp, "\t</html>\n");
		mysql_free_result ($fields);
		return ($this);
	}

# ====================================================================
#
# MySQL StorePage Method;
#
#
#
# --------------------------------------------------------------------

	public function StorePage ($table) 
	{
		$query = "SHOW FIELDS FROM ${table}";
		if (!$fields = mysql_query ($query, self::$db)) 
		{
			self::Error ("Can't find any fields in ${table} table", mysql_error(self::$db));
			return (false);
		}
		if (!$ofp = fopen ("$this->website/${table}-Store.php", "w")) 
		{
			self::Event ("Can't open ${table}.php");
			return (false);
		}
		fputs ($ofp, "<html>\n");
		fputs ($ofp, "\t<head>\n");
		fputs ($ofp, "\t\t<title>\n");
		fputs ($ofp, "\t\t\t${table}\n");
		fputs ($ofp, "\t\t\t<title>\n");
		fputs ($ofp, "\t\t<link href='$this->stylesheet' rel='stylesheet' type='text/css'/>\n");
		fputs ($ofp, "\t\t</head>\n");
		fputs ($ofp, "\t<body>\n");
		fputs ($ofp, "<?php\n");
		fputs ($ofp, "\tinclude \"php/modules/HTTP.php\";\n");
		fputs ($ofp, "\tinclude \"php/modules/SPCDefs.php\";\n");
		fputs ($ofp, "\tinclude \"php/modules/CMAssoc.php\";\n");
		fputs ($ofp, "\tinclude \"php/classes/${table}.php\";\n");
		fputs ($ofp, "\t\$db = CMAssoc::Connect();\n");
		fputs ($ofp, "\t\$${table} = new ${table}(\$db);\n");
		fputs ($ofp, "\t\$${table}->SetDebug(WEBPAGE)->SetTrace(WEBPAGE);\n");
		while ($field = mysql_fetch_object($fields)) 
		{
			if (!strcmp($field->Field, "ID")) 
			{
				continue;
			}
			if (!strcmp($field->Field, "ControlID")) 
			{
				continue;
			}
			if (!strcmp($field->Field, "Created")) 
			{
				continue;
			}
			if (!strcmp($field->Field, "Updated")) 
			{
				continue;
			}
			fputs ($ofp, "\t\$${table}->Set$field->Field(\$_POST['$field->Field']);\n");
		}
		fputs ($ofp, "\tif (!\$${table}->Store())\n");
		fputs ($ofp, "\t{\n");
		fputs ($ofp, "\t\techo \"<p>Failed.</p>\";\n");
		fputs ($ofp, "\t}\n");
		fputs ($ofp, "\telse\n");
		fputs ($ofp, "\t{\n");
		fputs ($ofp, "\t\techo \"<p>Done.</p>\";\n");
		fputs ($ofp, "\t}\n\n");
		fputs ($ofp, " ?>\n");
		fputs ($ofp, "\t\t</body>\n");
		fputs ($ofp, "\t</html>\n");
		mysql_free_result ($fields);
		return ($this);
	}

# ====================================================================
#
# MySQL Select Method;
#
# --------------------------------------------------------------------

	private function Select($ofp, $table, $label) 
	{
		fputs ($ofp, "\t\t\t\t<tr>\n");
		fputs ($ofp, "\t\t\t\t\t<td>\n");
		fputs ($ofp, "\t\t\t\t\t\tEnter ${table}:\n");
		fputs ($ofp, "\t\t\t\t\t\t</td>\n");
		fputs ($ofp, "\t\t\t\t\t<td>\n");
		fputs ($ofp, "\t\t\t\t\t\t<select name='${table}ID'/>\n");
		fputs ($ofp, "<?php\n");
		fputs ($ofp, "\$${label}s = mysql_query(\"SELECT ID, Code, Name FROM ${table}\", \$db);\n");
		fputs ($ofp, "while (\$${label} = mysql_fetch_object (\$${label}s))\n");
		fputs ($ofp, "{\n");
		fputs ($ofp, "\techo \"<option value='\$${label}->ID'>\$${label}->Code - \$${label}->Name</option>\";\n");
		fputs ($ofp, "}\n");
		fputs ($ofp, " ?>\n");
		fputs ($ofp, "\t\t\t\t\t\t\t</select>\n");
		fputs ($ofp, "\t\t\t\t\t\t</td>\n");
		fputs ($ofp, "\t\t\t\t\t</tr>\n");
		return;
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
			self::Event ("Can't connect to MySQL server on ${hostname}");
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
