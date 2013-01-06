<?php

# ====================================================================
# 
# Published 2005 by Charles Maier Associates Limited for internal use;
#
# --------------------------------------------------------------------

require "HTTP.php";
require "Constants.php";

# ====================================================================
# Public Variables;
# --------------------------------------------------------------------

static $Debug = MESSAGE_HTML;
static $Trace = MESSAGE_HTML;

# ====================================================================
#
# Connect function;
#
# connect to server and database; return database resource variable
# on success or NULL on failure; HOSTNAME, USERNAME, PASSWORD and 
# DATABASE are defined in Constants.php; 
#
# --------------------------------------------------------------------

function Connect () 
{
	if (!$db = mysql_connect (HOSTNAME, USERNAME, PASSWORD)) 
	{
		Failure ("Can't connect to server");
		exit;
	}
	if (!mysql_select_db (DATABASE, $db)) 
	{
		Failure ("Can't select database: ".mysql_error($db));
		exit;
	}
	return($db);
}

# ====================================================================
#
# Authorize function;
#
#
#
# --------------------------------------------------------------------

function Authenticated($db)
{
	if (!$Username = $_POST['Username'])
	{
		Problem ("Can't identify user");
		exit;
	}
	if (!$Password = $_POST['Password'])
	{
		Problem ("Can't identify you");
		exit;
	}
	$Password = md5($Password);
	$SQL = "SELECT * FROM ".REGISTER." WHERE Username='$Username' AND Password='$Password'";
	if (!$Users = mysql_query($SQL, $db)) 
	{
		Failure ("Can't authenticate user");
		exit;
	}
	if (!$User = mysql_fetch_object($Users))
	{
		Failure ("Can't authenticate user");
		exit;
	}
	if (!mysql_num_rows($Users)) 
	{
		Problem ("Invalid login");
		exit;
	}
	$_SESSION['Username']= $User->Username;
	$_SESSION['Password']= $User->Password;
	$_SESSION['Function']= $User->Function;
 	return (true);
}

# ====================================================================
#
# Authorized function;
#
#
#
# --------------------------------------------------------------------

function Authorized($db)
{
	if (!$Username = $_SESSION['Username'])
	{
		return (false);
	}
	if (!$Password = $_SESSION['Password'])
	{
		return (false);
	}
	$query = "SELECT * FROM ".REGISTER." WHERE Username='$Username' AND Password='$Password'";
	if (!$Users = mysql_query($query,$db)) 
	{
		Failure ("Can't access database");
		return (false);
	}
	if (!$User = mysql_fetch_object($Users)) 
	{
		Problem ("Can't authenticate user");
		return (false);
	}
	if (!mysql_num_rows($Users)) 
	{
		Problem ("Can't authenticate user");
		return (false);
	}
 	return (true);
}

# ====================================================================
#
# Problem function;
#
#
#
# --------------------------------------------------------------------

function Problem ( $Message ) 
{
#	header (HTTP401, true, 401);
	echo "<html><head><link href='".STYLESHEET."' rel='stylesheet' type='text/css'></head><body><h2>".HTTP400."</h2><h3>$Message.</h3></body></html>";
#	echo "<html><head><link href='/styles/faedb.css' rel='stylesheet' type='text/css'/></head><body><!-- bgsound src='/sounds/error.wav'/ --><div class='problem'>No, No, No!</br>Bad Engineer! Bad Engineer!</br>$Message.</div></body></html>";
	return;
}

# ====================================================================
#
# Failure function;
#
#
#
# --------------------------------------------------------------------

function Failure ( $Message ) 
{
#	header (HTTP500, true, 500);
	echo "<html><head><link href='".STYLESHEET."' rel='stylesheet' type='text/css'></head><body><h2>".HTTP500."</h2><h3>$Message.</h3></body></html>";
#	echo "<html><head><link href='/styles/faedb.css' rel='stylesheet' type='text/css'/></head><body><!-- bgsound src='/sounds/error.wav'/ --><div class='failure'>Oh My God!</br>$Message.</br>Do something!</div></body></html>";
	return;
}

# ====================================================================
#
# is_date function;
#
# return true of variable is a valid date;
#
# --------------------------------------------------------------------

function is_date ($string) 
{
	return (true);
	if (eregi("^[0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2}$", $string)) 
	{
		$date_arr = explode('-', $string);
		if (($date_arr[0]>=1000) && ($date_arr[0]<=9999)) 
		{
			if (checkdate($date_arr[1], $date_arr[2], $date_arr[0])) 
			{
				unset($date_arr);
				return (true);
			}
		}
		unset($date_arr);
	}
	return (false);
}

# ====================================================================
#
# Combine function;
#
# combine a prefix and suffix string separated by a delimiter; if
# the prefix string is empty then return the suffix string; if the 
# suffix string is empty then return the prefix string; otherwise, 
# return the concatenation of all three strings;
#
# --------------------------------------------------------------------

function Combine ( $Prefix, $Middle, $Suffix ) 
{
	if (empty($Prefix)) 
	{
		return($Suffix);
	}
	if(empty($Suffix)) 
	{
		return($Prefix);
	}
	return($Prefix.$Middle.$Suffix);
}

# ====================================================================
#
# Event function;           
#
#
#
# --------------------------------------------------------------------

function Event ( $Method, $Lineno, $Event, $Mode ) 
{
	$Message = $Method." (".$Lineno."): ".$Event;
	switch($Mode) 
	{
		case MESSAGE_HTML: 
			echo "<br/><span class='event'>".$Message."</span><br/>";
			break;
		case MESSAGE_TEXT: 
			echo "\n".$Message;
			break;
	}
	return;
}

# ====================================================================
#
# Error function;
#
#
#
# --------------------------------------------------------------------

function Error ( $Method, $Lineno, $Error, $Mode ) 
{
	$Message = $Method." (".$Lineno."): ".$Error;
	switch($Mode) 
	{
		case MESSAGE_HTML: 
			echo "<br/><span class='error'>".$Message."</span><br/>";
			break;
		case MESSAGE_TEXT: 
			echo "\n".$Message;
			break;
	}
	return;
}

# ====================================================================
#
# Database NewID Method;
#
#
#
# --------------------------------------------------------------------

function NewID($Width, $Key, $Table, $Database)
{
	$Query = "SELECT MAX($Table.$Key) AS $Key FROM $Table";
	if ($Tuples = mysql_query($Query, $Database))
	{
		$Tuple = mysql_fetch_object($Tuples);
		$Key = (int)($Tuple->$Key)+1;
		$Key = str_pad ($Key, $Width, "0", STR_PAD_LEFT);
		return($Key);
	}
	return;
}

# ====================================================================
#
# Database GetID Method;
#
# Return the numeric primary key of an existing table record given
# the numeric primary key or the alphanumeric secondary key;
# Return false if the record does not exist in the table;
#
# --------------------------------------------------------------------

function ID ($Key, $Table, $db) 
{
	if (is_numeric($Key)) 
	{
		$query = "SELECT ID FROM $Table WHERE ID=($Key)";
	}
	else 
	{
		$query = "SELECT ID FROM $Table WHERE Code='$Key'";
	}
	Event (__METHOD__, __LINENO__, $query, $Trace);
	if (!$table = mysql_query($query, $db)) 
	{
		Error (__METHOD__, __LINENO, "Can't find ${Table} '$Key': ".mysql_error($db), $Debug);
		return (false);
	}
	if (!$field = mysql_fetch_object($table)) 
	{
		Error (__METHOD__, __LINE__, "Can't find ${Table} '$Key': No such ${Table}", $Debug);
		return (false);
	}
	return ((int)($field->ID));
}

# ====================================================================
#
# Database GetCode Method;
#
# Return the alphanumeric secondary key of an existing table record 
# given the numeric primary key or the alphanumeric secondary key;
# Return false if the record does not exist in the table;
#
# --------------------------------------------------------------------

function Code ($Key, $Table, $db) 
{
	if (is_numeric($Key)) 
	{
		$query = "SELECT ID FROM ${Table} WHERE ID=(${Key})";
	}
	else 
	{
		$query = "SELECT ID FROM ${Table} WHERE Code='${Key}'";
	}
	Event (__METHOD__, __LINENO__, $query, $Trace);
	if (!$table = mysql_query($query, $db)) 
	{
		Error (__METHOD__, __LINE__, "Can't find ${Table} '${Key}': ".mysql_error($db), $Debug);
		return (false);
	}
	if (!$field = mysql_fetch_object($table)) 
	{
		Error (__METHOD__, __LINE__, "Can't find ${Table} '${Key}': No such ${Table}", $Debug);
		return (false);
	}
	return ($field->Code);
}

# ====================================================================
#
# Database Lookup Method;
#
# Return the value of a field of a table record that satisfies an 
# SQL 'WHERE' clause; 
#
# --------------------------------------------------------------------

function Lookup ( $db, $Table, $Field, $Clause ) 
{
	$query = "SELECT ${Field} FROM ${Table} WHERE ${Clause}";
	if (!$table = mysql_query($query, $db)) 
	{
		Error (__METHOD__, __LINE__, "Can't fetch ${Field} in ${Table} where ${Clause}: ".mysql_error($db), $Debug);
		return (false);
	}
	if (!$field = mysql_fetch_object($table)) 
	{
		Error (__METHOD__, __LINE__, "Can't lookup '${Field}' in ${Table} where ${Clause}: No such record", $Debug);
		return (false);
	}
	return ($field->$Field);
}

# ====================================================================
#
# Database Navigate Method;
#
# echo page links based on database Page and Link table definitions; 
#
# --------------------------------------------------------------------

function Navigate ($db) 
{
	$Page = $_SERVER['REQUEST_URI'];
	$Page = explode("?", $Page, 2);
	$query = "SELECT Link.Text, That.Page, That.Name FROM Page AS This JOIN Link ON This.ID=Link.PageID JOIN Page AS That ON That.ID=Link.LinkID WHERE This.Page='$Page[0]'";
	if ($Links = mysql_query($query, $db)) 
	{
		while ($Link = mysql_fetch_object($Links)) 
		{
			echo " [<a href='$Link->Page' title=' $Link->Name '>$Link->Text</a>] ";
		}
	}
	return;
}

# ====================================================================
# 
# Legend function;
#
# Produce a multi-column Legend from a table;
#
# --------------------------------------------------------------------

function Legend($db, $query, $columns) 
{
	if (!$table = mysql_query($query, $db)) 
	{
		Failure ("Can't fetch type table");
		return (false);
	}
	for ($count = 0; $tuple = mysql_fetch_object($table); $count++) 
	{
		$label[$count] = $tuple->Code;
		$title[$count] = $tuple->Name;
	}
	$block = ceil($count/$columns);
	for ($lower = 0; $lower < $block; $lower++) 
	{
		echo "<tr>";
		for ($upper = $lower; $upper < $count; $upper += $block) 
		{
			echo "<td><b>$label[$upper]</b> is $title[$upper]</td>";
		}
		echo "</tr>";
	}
	return(true);
}

# ====================================================================
# 
# Catalog function;
#
# Produce a multi-column Legend from a table;
#
# --------------------------------------------------------------------

function Catalog($db, $query, $frame, $columns) 
{
	if (!$units = mysql_query($query, $db)) 
	{
		Failure ("Can't access database");
		return (false);
	}
	for ($lower = $count = 0; $unit = mysql_fetch_object($units); $count++) 
	{
		$index[$count] = $unit->ID;
		$label[$count] = $unit->Code;
	}
	echo "<tr>";
	for ($upper = $block = ceil($count/$columns); $lower < $count; $upper += $block) 
	{
		$lower++;
		echo "<td><ol start='$lower'>";
		$lower--;
		while ($lower < $upper) 
		{
			if ($lower < $count)
			{
				echo "<li><a href='$frame?".$index[$lower]."'>".$label[$lower]."</a></li>";
			}
			$lower++;
		}
		echo "</ol></td>";
	}
	echo "</tr>";
	return(true);
}

# ====================================================================
# 
# Tabulate function;
#
# Produce a multi-column Legend from a table;
#
# --------------------------------------------------------------------

function Tabulate($db, $query, $frame, $columns) 
{
	if (!$table = mysql_query($query, $db)) 
	{
		Failure ("Can't access database");
		return (false);
	}
	for ($lower = $count = 0; $tuple = mysql_fetch_object($table); $count++) 
	{
		$index[$count] = $tuple->ID;
		$label[$count] = $tuple->Code;
		$title[$count] = $tuple->Name;
		$items[$count] = $tuple->Count;
	}
	echo "<tr>";
	for ($upper = $block = ceil($count/$columns); $lower < $count; $upper += $block) 
	{
		$lower++;
		echo "<td><ol start='$lower'>";
		$lower--;
		while ($lower < $upper) 
		{
			if ($lower < $count)
			{
				if ($items[$lower])
				{
					echo "<li><a href='$frame?".$index[$lower]."' title='".$title[$lower]."'>".$label[$lower]."</a> (".$items[$lower].")</li>";
				}
				else
				{
					echo "<li><a href='$frame?".$index[$lower]."' title='".$title[$lower]."'>".$label[$lower]."</a></li>";
				}
			}
			$lower++;
		}
		echo "</ol></td>";
	}
	echo "</tr>";
	return(true);
}

# ====================================================================
#
# StageColor Method;
#
#
#
# --------------------------------------------------------------------

function StageColor($StageID)

{
	switch((int)($StageID))
	{
		case 0:
			echo "<td class='task' style='background: white;'>NONE</td>";
			break;
		case 1:
			echo "<td class='task' style='background: yellow; color: black;'>NEED</td>";
			break;
		case 2:
			echo "<td class='task' style='background: silver; color: black;'>STOP</td>";
			break;
		case 3:
			echo "<td class='task' style='background: orange; color: black;'>TEST</td>";
			break;
		case 4:
			echo "<td class='task' style='background: green; color: yellow;'>PASS</td>";
			break;
		case 5:
			echo "<td class='task' style='background: red; color: white;'>FAIL</td>";
			break;
		case 6:
			echo "<td class='task' style='background: blue; color: white;'>DONE</td>";
			break;
		default:
			echo "<td class='task'>&nbsp;</td>";
			break;
	}
	return;
}

 ?>
