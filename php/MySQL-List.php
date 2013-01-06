#!/usr/local/bin/php
<?php
include "MySQL-Defs.php";
if (!$db = mysql_connect (HOSTNAME, USERNAME, PASSWORD)) 
{
   printf ("Can't connect to server: %s\n", mysql_error($db));
   exit;
}
if (!$places = mysql_list_dbs ($db)) 
{
   printf ("Can't enumerate databases: %s\n", mysql_error($db));
   exit;
}
while ($place = mysql_fetch_object ($places)) 
{
   if (!mysql_select_db($place->Database, $db)) 
   {
      printf ("Can't select database $place->Database: %s\n", mysql_error($db));
      continue;
   }
   if ($tables = mysql_query ("SHOW TABLES FROM $place->Database", $db)) 
   {
      print ("[$place->Database]\n");
      while ($table = mysql_fetch_row ($tables)) 
      {
         if ($fields = mysql_query("SHOW COLUMNS FROM $table[0]", $db)) 
         {
            print (".  [$table[0]]\n");
            while ($field = mysql_fetch_object ($fields)) 
            {
               printf (".  .  [%s]\n", $field->Field);
               printf (".  .  .  Type=[%s]\n", $field->Type);
               printf (".  .  .  Null=[%s]\n", $field->Null);
               printf (".  .  .  Key=[%s]\n", $field->Key);
               printf (".  .  .  Default=[%s]\n", $field->Default);
               printf (".  .  .  Extra=[%s]\n", $field->Extra);
            }
            mysql_free_result ($fields);
         }
      }
      mysql_free_result ($tables);
   }
}
mysql_free_result ($places);
exit;
 ?>
