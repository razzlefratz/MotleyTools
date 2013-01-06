#!/usr/local/bin/php
<?php

# ====================================================================
# components;
# --------------------------------------------------------------------

include "Constants.php";
include "Functions.php";
include "Database.php";
include "Game.php";
include "Pool.php";
include "Contact.php";
include "Member.php";
include "Participant.php";
include "Control.php";
include "Project.php";
include "Account.php";
include "Balance.php";
include "Transaction.php";

# ====================================================================
# variables;
# --------------------------------------------------------------------

$database="spcdb";
$hostname="localhost";
$username="root";
$password="letmein";
$Debug = 2;
$Trace = 2;
$db;

# ====================================================================
# Connect to MYSQL server;
# --------------------------------------------------------------------

if (!$db=mysql_connect($hostname, $username, $password)) 
{
	printf ("spcdb: Can't connect to MySQL server.\n");
	return;
}

# ====================================================================
# Select spcdb database;
# --------------------------------------------------------------------

if (!mysql_select_db($database, $db)) 
{
	printf ("spcdb: Can't use database $database: %s;n", mysql_error($db));
	return;
}

# ====================================================================
# Invoke Object Instances;
# --------------------------------------------------------------------

$Database = new Database($db);
$Pool = new Pool($db);
$Contact = new Contact($db);
$Member = new Member($db);
$Participant = new Participant($db);
$Account = new Account ($db);
$Transaction = new Transaction($db);

# ====================================================================
# Create Transactions; 
# --------------------------------------------------------------------

$Database->SetDebug(2);
$Database->SetTrace(2);
$Transaction->SetDebug(2);
$Transaction->SetTrace(2);
$Account->SetDebug(0);
$Account->SetTrace(0);
$Account->SetCode("CFM");
$Account->SetAccountID(4);
$Account->Store();
         
if (true) 
{
	$Transaction->SetDebug($Debug)->SetTrace($Trace);
	$Transaction->SetReceiptAccount("PB050901");
	$Transaction->SetUnits("Ticket");
	$Transaction->SetPrice(2.00);
	$Transaction->SetNote("Tuesdays Lottery");
	$Transaction->Peek();
	$Transaction->SetPaymentAccount("CFM");
	$Transaction->SetCount(30);
	$Transaction->SetInternalCode("12346");
	$Transaction->Store();
	$Transaction->Peek();
	$Transaction->SetPaymentAccount("MC");
	$Transaction->SetCount(12);
	$Transaction->SetInternalCode("12347");
	$Transaction->Store();
	$Transaction->Peek();
	$Transaction->SetPaymentAccount("MS");
	$Transaction->SetCount(10);
	$Transaction->SetInternalCode("12348");
	$Transaction->Store();
	$Transaction->Peek();
	$Transaction->SetPaymentAccount("MC");
	$Transaction->SetCount(100);
	$Transaction->SetInternalCode("12349");
	$Transaction->Store();
	$Transaction->Peek();
}

$Account->SetDebug(2);
$Account->SetTrace(2);
if (!$table = $Account->Transactions("CFM")) 
{
	printf ("bailing out\n");
	exit;
}
while ($field = mysql_fetch_object($table)) 
{
	printf ("%s;", $field->Code);
	printf ("%s;", $field->Note);
	printf ("%s;", $field->Count);
	printf ("%s;", $field->Units);
	printf ("%s;", $field->Price);
	printf ("%s;", $field->Total);
	printf ("%s;", $field->Payment);
	printf ("%s;", $field->Receipt);
	printf ("\n");
}

$Account->Structure(1);
$Account->UpdateBalances();

if (!$array = $Account->Component_Array(6))
{
	printf ("bailing out\n");
	exit;
}
print_r ($array);


# ====================================================================
#
# --------------------------------------------------------------------

 ?>
