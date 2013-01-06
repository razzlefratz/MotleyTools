<?php
require "HTTP.php";
define ("IPV4SIZE", 18);

# ====================================================================
# 
#   AccessList Class
#
#   Permits or denies referer access based on an access control 
#   list containing IP addresses; the file represents good-guys
#   or bad-guys depending on the Accept or Reject method called
#   by the constructor;
#   
#   Allows HTTP update of the access control file using 'insert'
#   or 'remove' query expressions; the Append and Remove methods
#   may be called from PHP programs but need changes to the exit
#   and return logic, in that case;
#
#   With PHP5, no methods need be called because the constructor
#   is implcitly invoked; with PHP4, the constructor must be 
#   explicitly invoked; for example:
#
#   $blacklist = new AccessList();
#   echo "<h1>Welcome</h1>"
#
#   $blacklist = new AccessList();
#   $blacklist->__construct(); 
#   echo "<h1>Welcome</h1>"
#
#   In the above examples, 'Welcome' is displayed only if the
#   referer meets the access control permit/deny criteria and  
#   no 'insert' or 'remove' expressions appear in the URL;
#   
# --------------------------------------------------------------------

class AccessList 
{

# ====================================================================
#
#  public function Create ($Control) 
#
#  Create an access control file if missing;
#
# --------------------------------------------------------------------


#  public function Create($Control) 

	function Create($Control) 
	{
		if (!file_exists($Control)) 
		{
			if (!$ifp = fopen($Control, "w+")) 
			{
				header(HTTP401, true, 412);
				echo "<h1>".HTTP401."</h1>";
				exit;
			}
			fclose($ifp);
		}
		return;
	}

# ====================================================================
#
#   public function Append ($Control, $Address) 
#
#   Append an IP address to an access control file if missing;
#
# --------------------------------------------------------------------


#  public function Append ($Control, $Address) 

	function Append ($Control, $Address) 
	{
		AccessList::Create($Control);
		if (!$ifp = fopen($Control, "r+")) 
		{
			header(HTTP503, true, 503);
			echo "<h1>".HTTP503."</h1>";
			exit;
		}
		$IPNew = AccessList::IPValue($Address);
		while ($address = fgets($ifp, IPV4SIZE)) 
		{
			$IPOld = AccessList::IPValue($address);
			if ($IPNew == $IPOld) 
			{
				header(HTTP202, true, 202);
				echo "<h1>".HTTP202."</h1>";
				fclose ($ifp);
				exit;
			}
		}
		fputs ($ifp, $Address."\n");
		header(HTTP201, true, 201);
		echo "<h1>".HTTP201."</h1>";
		fclose ($ifp);
		exit;
	}

# ====================================================================
#
#   public function Remove($Control, $Address) 
#
#   Remove an IP address from an access control file if present;
#
# --------------------------------------------------------------------


#  public function Remove($Control, $Address) 

	function Remove($Control, $Address) 
	{
		AccessList::Create($Control);
		if (!$ifp = fopen($Control, "r+")) 
		{
			header(HTTP503, true, 503);
			echo "<h1>".HTTP503."</h1>";
			exit;
		}
		if (!$ofp = fopen($Control, "r+")) 
		{
			header(HTTP500, true, 500);
			echo "<h1>".HTTP500."</h1>";
			exit;
		}
		$IPNew = AccessList::IPValue($Address);
		while ($address = fgets($ifp, IPV4SIZE)) 
		{
			$IPOld = AccessList::IPValue($address);
			if ($IPOld != $IPNew) 
			{
				fputs($ofp, $address);
			}
		}
		ftruncate($ofp, ftell($ofp));
		header(HTTP202, true, 202);
		echo "<h1>".HTTP202."</h1>";
		fclose ($ofp);
		fclose ($ifp);
		exit;
	}

# ====================================================================
#
#   public function Accept($Control, $Address) 
#
#   Accept an IP address if present in an access control file;
#
# --------------------------------------------------------------------


#  public function Accept ($Control, $Address) 

	function Accept ($Control, $Address) 
	{
		AccessList::Create($Control);
		if (!$ifp = fopen($Control, "r")) 
		{
			header(HTTP503, true, 503);
			echo "<h1>".HTTP503."</h1>";
			exit;
		}
		$IPNew = AccessList::IPValue($Address);
		while ($address = fgets($ifp, IPV4SIZE)) 
		{
			$IPOld = AccessList::IPValue($address);
			if ($IPOld == $IPNew) 
			{
				fclose ($ifp);
				return;
			}
		}
		header(HTTP470, true, 470);
		echo "<h1>".HTTP470."</h1>";
		fclose ($ifp);
		exit;
	}

# ====================================================================
#
#   public function Reject($Control, $Address) 
#
#   Reject an IP address if present in an access control file;
#
# --------------------------------------------------------------------


#  public function Reject ($Control, $Address) 

	function Reject ($Control, $Address) 
	{
		AccessList::Create($Control);
		if (!$ifp = fopen($Control, "r")) 
		{
			header(HTTP503, true, 503);
			echo "<h1>".HTTP503."</h1>";
			exit;
		}
		$IPNew = AccessList::IPValue($Address);
		while ($address = fgets($ifp, IPV4SIZE)) 
		{
			$IPOld = AccessList::IPValue($address);
			if ($IPOld == $IPNew) 
			{
				header(HTTP470, true, 470);
				echo "<h1>".HTTP470."</h1>";
				fclose ($ifp);
				exit;
			}
		}
		fclose ($ifp);
		return;
	}

# ====================================================================
#
#   public function IPValue($Address) 
#
#   Convert an IP address string to an integer for fast comparison;
# 
# --------------------------------------------------------------------


#	public function IPValue($Address) 

	function IPValue($Address) 
	{
		$Value = (int)(0);
		$Fields = explode(".", $Address);
		foreach ($Fields as $Field) 
		{
			$Value *= 255;
			$Value += (int)($Field);
		}
		return ($Value);
	}

# ====================================================================
#
#   public function __construct($Control);
#
#   accept or reject a referer if present in an access control file; 
#   update the named access control file if a request is present;
# 
#   The Append and Insert methods, as coded, do not return so the
#   foreach loop will execute only once if an 'insert' or 'remove'
#   expression is present; other expressions are ignored; 
#
# --------------------------------------------------------------------


#  	public function __construct($Control) 

	function __construct() 
	{
		$Control = "AccessList.ipa";
		$Referer = $_SERVER['REMOTE_ADDR'];
		$Request = $_SERVER['QUERY_STRING'];
#		AccessList::Accept($Control, $Referer);
		AccessList::Reject($Control, $Referer);
		$Expressions = explode("&", $Request);
		foreach ($Expressions as $Expression) 
		{
			$token = explode("=", $Expression);
			if (!strcmp($token[0], "insert")) 
			{
				AccessList::Append($Control, $token[1]);
				continue;
			}
			if (!strcmp($token[0], "remove")) 
			{
				AccessList::Remove($Control, $token[1]);
				continue;
			}
		}
		return;
	}

# ====================================================================
#
#   public function __construct($Control);
#
#
# --------------------------------------------------------------------


#  	public function __destruct() 

	function __destruct() 
	{
		return;
	}
}

# ====================================================================
#
# --------------------------------------------------------------------

 ?>

