#!/usr/local/bin/php
<?php
include "MySQL-Defs.php";
if (!isset($argv[1]))
{
	printf ("usage: database table\n");
	exit (1);
}
if (!$db = mysql_connect (HOSTNAME, USERNAME, PASSWORD)) 
{
	printf ("Can't connect to server: %s\n", mysql_error($db));
	exit;
}
if (!mysql_select_db($argv[1], $db)) 
{
	printf ("Can't select database $argv[1]: %s\n", mysql_error($db));
	exit;
}
if ($Fields = mysql_query("SHOW COLUMNS FROM $argv[2]", $db)) 
{
	printf ("CREATE TABLE IF NOT EXISTS $argv[2] (\n");
	while ($Field = mysql_fetch_object ($Fields)) 
	{
		printf (" $Field->Field");
		printf (" $Field->Type");
                if ($Field->Null == "NO")
                {
			printf(" not null");
		}
                if ($Field->Key == "PRI")
                {
			print (" primary key");
		}
                if (!$Field->Default)
                {
			printf (" default %s", $Field->Default);
		}
                if (!$Field->Extra)
                {
			printf (" %s", $Field->Extra);
		}
		printf (",\n");
	}
	printf (");\n");
        mysql_free_result ($Fields);
}
exit (0);
 ?>
