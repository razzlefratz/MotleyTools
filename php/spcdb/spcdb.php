#!/usr/local/bin/php
<?php

# ====================================================================
# components;
# --------------------------------------------------------------------

include "Constants.php";
include "Functions.php";
include "Game.php";
include "Pool.php";
include "Contact.php";
include "Member.php";
include "Participant.php";
include "Control.php";
include "Project.php";
include "Account.php";
include "Accounts.php";
include "Balance.php";
include "Transaction.php";
include "Database.php";

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

$Pool = new Pool($db);
$Game = new Game($db);
$Contact = new Contact($db);
$Member = new Member($db);
$Participant = new Participant($db);
$Account = new Account($db);
$Accounts = new Accounts($db);
$Balance = new Balance($db);
$Transaction = new Transaction($db);
$Database = new Database($db);

# ====================================================================
#
# --------------------------------------------------------------------

$Accounts->Structure(1, " ", "|  ");

# ====================================================================
#
# --------------------------------------------------------------------

 ?>
