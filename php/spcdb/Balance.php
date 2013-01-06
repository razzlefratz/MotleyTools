<?php

# ====================================================================
# 
# Begin Balance Class Definition;
# 
# 
# Published 2005 by Charles Maier Associates Limited for internal use;
# Generated 17:08:18 Thu 01 Sep 2005 EDT by MySQL.php;
# 
# --------------------------------------------------------------------

class Balance

{

# ====================================================================
# Public Balance Variables;
# --------------------------------------------------------------------

# ====================================================================
# Private Balance Variables;
# --------------------------------------------------------------------

	private $ID = 0;
	private $Code = "";
	private $Name = "";

	private $table = NULL;
	private $field = NULL;
	private $query = NULL;

	private static $debug = 0;
	private static $trace = 0;
	private static $db = NULL;

# ====================================================================
# 
# Balance Debug Property;
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
			printf ("Balance: Can't set Debug to '${Debug}': Property is integer");
			return ($this);
		}
		self::$debug = $Debug;
		return ($this);
	}

# ====================================================================
# 
# Balance Trace Property;
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
			printf ("Balance: Can't set Trace to '${Trace}': Property is integer");
			return ($this);
		}
		self::$trace = $Trace;
		return ($this);
	}

# ====================================================================
# 
# Balance ID Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetID () 
	{
		return ($this->ID);
	}

#       public function SetID ($Date)
#
#       {
#               if(!is_integer($ID))
#               {
#                       Balance::Error("Can't set ID to '${ID}'", "Property is integer");
#                       return (false);
#               }
#
#               $this->ID = $Date;
#               return (true);
#       }


# ====================================================================
# 
# Balance Code Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetCode () 
	{
		return ($this->Code);
	}

#       public function SetCode ($Code)
#
#       {
#               $this->Code = $Code;
#               return (true);
#       }


# ====================================================================
# 
# Balance Name Property;
# 
# 
# 
# --------------------------------------------------------------------

	public function GetName () 
	{
		return ($this->Name);
	}

#       public function SetName ($Code)
#
#       {
#               $this->Name = $Code;
#               return (true);
#       }


# ====================================================================
# 
# Balance Clear Method;
# 
# Reset property values;
# 
# --------------------------------------------------------------------

	public function Clear () 
	{
		Balance::Event ("Clearing Object Properties", "");
		$this->ID = 0;
		$this->Code = "";
		$this->Name = "";
		return ($this);
	}

# ====================================================================
#
# Balance UpdateAccountBalances Method;
#
# Update Account table Receipts, Payments and Balances using query;
# create Balance table having an AccountID, Receipts and Payments 
# column; join Account and Balance tables with update; remove the 
# Balance table;
#
# This should be faster than looping because the Myquery engine does 
# all the work;
#
# --------------------------------------------------------------------

   public function UpdateAccountBalances () 
   {
      $table = "BALANCE";
      $query = "DROP TABLE IF EXISTS ${table}";
      Balance::Event ($query, "");
      if (!mysql_query($query, self::$db)) 
      {
         Balance::Error ("Can't remove old ${table} table", mysql_error(self::$db));
         return (false);
      }
      $query = "CREATE TEMPORARY TABLE ${table} SELECT ReceiptID AS AccountID, SUM(Total) As Receipts, (0) AS Payments FROM Transaction GROUP BY ReceiptID ORDER BY ReceiptID";
      Balance::Event ($query, "");
      if (!mysql_query($query, self::$db)) 
      {
         Balance::Error ("Can't compute ${table} table Receipts", mysql_error(self::$db));
         return (false);
      }
      $query = "INSERT INTO  ${table} SELECT PaymentID AS AccountID, (0) AS Receipts, SUM(Total) AS Payments FROM Transaction GROUP BY PaymentID ORDER BY PaymentID";
      Balance::Event ($query, "");
      if (!mysql_query($query, self::$db)) 
      {
         Balance::Error ("Can't compute ${table} table Payments", mysql_error(self::$db));
         return (false);
      }
      $query = "UPDATE Account SET Receipts=(0.00), Payments=(0.00), Balance=(0.00)";
      Balance::Event ($query, "");
      if (!mysql_query($query, self::$db)) 
      {
         Balance::Error ("Can't clear Account table balances", mysql_error(self::$db));
         return (false);
      }
      $query = "UPDATE Account INNER JOIN ${table} ON ID=AccountID SET Account.Receipts=${table}.Receipts";
      Balance::Event ($query, "");
      if (!mysql_query($query, self::$db)) 
      {
         Balance::Error ("Can't update Account table Receipts", mysql_error(self::$db));
         return (false);
      }
      $query = "UPDATE Account INNER JOIN ${table} ON ID=AccountID SET Account.Payments=${table}.Payments";
      Balance::Event ($query, "");
      if (!mysql_query($query, self::$db)) 
      {
         Balance::Error ("Can't update Account table Payments", mysql_error(self::$db));
         return (false);
      }
      $query = "DROP TABLE IF EXISTS ${table}";
      Balance::Event ($query, "");
      if (!mysql_query($query, self::$db)) 
      {
         Balance::Error ("Can't remove new ${table} table", mysql_error(self::$db));
         return (false);
      }
      return (true);
   }

# ====================================================================
#
# Balance UpdateAccountBalance Method;
#
# Compute and return the current Account Balance;
#
# --------------------------------------------------------------------

   public function UpdateAccountBalance ($AccountID) 
   {
      Balance::Event ("Updating Balance for Account ${AccountID}.", "");
      if (!is_integer($AccountID)) 
      {
         Balance::Error ("Can't update Balance for Account '${AccountID}'", "Key must be integer.");
         return (false);
      }
      $Receipts = Balance::Receipts($AccountID);
      $Payments = Balance::Payments($AccountID);
      $query = "UPDATE Account SET Receipts=(${Receipts}), Payments=(${Payments}), Balance=((${Receipts})-(${Payments})) WHERE ID=(${AccountID})";
      Balance::Event ($query, "");
      if (!mysql_query($query, self::$db)) 
      {
         Balance::Error ("Can't update Balance for Account '${AccountID}'");
         return (false);
      }
      return (true);
   }

# ====================================================================
#
# Balance Receipts Method;
#
# Compute and return the current total of Account Receipts;
#
# --------------------------------------------------------------------

   public function Receipts ($AccountID) 
   {
      if (!is_integer($AccountID)) 
      {
         Balance::Error ("Can't update Balance for Account '${AccountID}'", "Key must be integer.");
         return (false);
      }
      $query = "SELECT SUM(Total) AS Receipts FROM Transaction WHERE ReceiptID=(${AccountID})";
      Balance::Event ($query, "");
      if (!$table = mysql_query($query, self::$db)) 
      {
         Balance::Error ("Can't compute Receipts for Account '${AccountID}'", mysql_error(self::$db));
         return (false);
      }
      if (!$field = mysql_fetch_object($table)) 
      {
         Balance::Error ("Can't compute Receipts for Account '${AccountID}'", "None exist.");
         return (false);
      }
      return (floatval($field->Receipts));
   }

# ====================================================================
#
# Balance Payments Method;
#
# Compute and return the current total of Account Payments;
#
# --------------------------------------------------------------------

   public function Payments ($AccountID) 
   {
      if (!is_integer($AccountID)) 
      {
         Balance::Error ("Can't update Balance for Account '${AccountID}'", "Key must be integer.");
         return (false);
      }
      $query = "SELECT SUM(Total) AS Payments FROM Transaction WHERE PaymentID=(${AccountID})";
      Balance::Event ($query, "");
      if (!$table = mysql_query($query, self::$db)) 
      {
         Balance::Error ("Can't compute Payments for Account '${AccountID}'", mysql_error($this->$db));
         return (false);
      }
      if (!$field = mysql_fetch_object($table)) 
      {
         Balance::Error ("Can't compute Payments for Account ${AccountID}", "None exist.");
         return (false);
      }
      return (floatval($field->Payments));
   }

# ====================================================================
#
# Balance Collect Method;
#
#
#
# --------------------------------------------------------------------

   public function Collect ($ControlID) 
   {
      $Transaction = new Transaction(self::$db);
      $query = "SELECT ID, AccountID, Code FROM Account WHERE AccountID=(${ControlID})";
      if (!$control = mysql_query($query, self::$db)) 
      {
         Balance::Error ("Can't Collect on Account '${Control}'", mysql_error(self::$db));
         return;
      }
      while (!$account = mysql_fetch_object($control)) 
      {
         $query = "SELECT FROM Transaction WHERE ReceiptID=($account->ID)";
         Balance::Event ($query, "");
         if (!$table = mysql_query($query, self::$db)) 
         {
            Balance::Error ("Can't collect Receipts for Account '$account->ID'", mysql_error(self::$db));
            return (false);
         }
         while (!$field = mysql_fetch_object($table)) 
         {
            $Transaction->SetDate('');
            $Transaction->SetPaymentID($field->ReceiptID);
            $Transaction->SetReceiptID($ControlID);
            $Transaction->SetCount($field->Count);
            $Transaction->SetUnits($field->Units);
            $Transaction->SetPrice($field->Price);
            $Transaction->Store();
         }
      }
      return;
   }

# ====================================================================
# 
# Balance Peek Method;
# 
# Reset property values;
# 
# --------------------------------------------------------------------

	public function Peek () 
	{
		printf ("Balance->Date = [$this->Date]\n");
		printf ("Balance->Code = [$this->Code]\n");
		printf ("Balance->Note = [$this->Note]\n");
		printf ("Balance->Count = [$this->Count]\n");
		printf ("Balance->Units = [$this->Units]\n");
		printf ("Balance->Price = [$this->Price]\n");
		printf ("Balance->Payment = [$this->Payment]\n");
		printf ("Balance->Receipt = [$this->Receipt]\n");
		printf ("\n");
		return ($this);
	}

# ====================================================================
#
# Balance Error ( Method;
#
#
#
# --------------------------------------------------------------------

   public function Error ($error, $cause) 
   {
      if (self::$debug == 1) 
      {
         printf ("<br><span class='error'>Balance: %s;/span><br>", cmassoc::combine($error, ": ", $cause));
      }
      if (self::$debug == 2) 
      {
         printf ("Balance: %s;n", cmassoc::combine($error, ": ", $cause));
      }
      return ($this);
   }

# ====================================================================
#
# Balance Event Method;
#
#
#
# --------------------------------------------------------------------

   public function Event ($event, $label) 
   {
      if (self::$trace == 1) 
      {
         printf ("<br><span class='event'>Balance: %s;/span><br>", cmassoc::combine($event, ": ", $label));
      }
      if (self::$trace == 2) 
      {
         printf ("Balance: %s;n", cmassoc::combine($event, ": ", $label));
      }
      return ($this);
   }

# ==================================================================== 
# 
# Balance Constructor; 
# 
# 
# 
# -------------------------------------------------------------------- 

   public function __construct ($db) 
   {
      self::$db = $db;
      return;
   }

# ==================================================================== 
# 
# Balance Destructor; 
# 
# 
# 
# -------------------------------------------------------------------- 

   public function __destruct () 
   {
      return;
   }

# ====================================================================
# End Balance Class Definition;
# --------------------------------------------------------------------

}
 ?>
