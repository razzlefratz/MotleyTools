<?php

# ====================================================================
# 
# class Session
#
#
#
# --------------------------------------------------------------------

class Session 
{
	var $username;
	var $password;
	var $user;

# ====================================================================
# 
# Session Autheticate Method;
#
# get username and password from login screen; authenticate against
# database; update session array with account information; return
# only if all steps are successful;
#
# --------------------------------------------------------------------


#	public function Login ($db)

	function Login ($db) 
	{
		$this->Identify ();
		$this->Authenticate ($db);
		$this->Authorize();
		return (true);
	}

# ====================================================================
# 
# Session NewPassword Method;
#
# change user password;
#
# --------------------------------------------------------------------


#	public function Password ($db)

	function Password ($db) 
	{
		$this->Identify();
		$this->Authenticate ($db);
		if (!$password1 = $_POST['newpassword1']) 
		{
			header (HTTP401, true, 401);
			echo "<h2>".HTTP401."</h2>";
			echo "<p>No Password1.</p>";
			exit;
		}
		if (!$password2 = $_POST['newpassword2']) 
		{
			header (HTTP401, true, 401);
			echo "<h2>".HTTP401."</h2>";
			echo "<p>No Password2.</p>";
			exit;
		}
		if (strcmp($password1, $password2)) 
		{
			header (HTTP401, true, 401);
			echo "<h2>".HTTP401."</h2>";
			echo "<p>Passwords differ.</p>";
			exit;
		}
		$password1 = md5 ($password1);
		$query = "UPDATE Contact SET Password='$password1' WHERE Username='$this->username' AND Password='$this->password'";
		if (!mysql_query($query, $db)) 
		{
			header (HTTP503, true, 503);
			echo "<h2>".HTTP503."</h2>";
			exit;
		}
		$this->password = $password1;
		$this->Authorize();
		return (true);
	}

# ====================================================================
# 
# Session Identify Method;
#
# copy username and password from login screen; convert password to
# md5 checksum; return only if username and password are not empty;
#
# --------------------------------------------------------------------


#	public function Identify()

	function Identify() 
	{
		if (!$this->username = $_POST['username']) 
		{
			header (HTTP401, true, 401);
			echo "<h2>".HTTP401."</h2>";
			echo "<p>No username given.</p>";
			exit;
		}
		if (!$this->password = $_POST['password']) 
		{
			header (HTTP401, true, 401);
			echo "<h2>".HTTP401."</h2>";
			echo "<p>No password given.</p>";
			exit;
		}
		$this->password = md5($this->password);
		return ($this);
	}

# ====================================================================
# 
# Session Authenticate Method;
#
# authenticate username and password; search database for matching  
# username and password pair; return object address on success; do 
# not return on failure; 
#
# --------------------------------------------------------------------


#	public funtion Authenticate ($db)

	function Authenticate ($db) 
	{
		$query = "SELECT * FROM Contact WHERE Username='$this->username' AND Password='$this->password'";
		if (!$users = mysql_query($query, $db)) 
		{
			header (HTTP503, true, 503);
			echo "<h2>".HTTP503."</h2>";
			echo "<p>Database is not accessible.</p>";
			exit;
		}
		if (!$this->user = mysql_fetch_object($users)) 
		{
			header (HTTP401, true, 401);
			echo "<h2>".HTTP401."</h2>";
			echo "<p>Invalid login.</p>";
			exit;
		}
		if (mysql_num_rows($users)> 1) 
		{
			header (HTTP401, true, 401);
			echo "<h2>".HTTP401."</h2>";
			echo "<p>Duplicate accounts.</p>";
			exit;
		}
		return ($this);
	}

# ====================================================================
# 
# Session Authorize Method; 
#
#
#
# --------------------------------------------------------------------

	public function Authorize() 
	{
		session_start ();
		$_SESSION[SESSION_USERNAME]= $this->user->Username;
		$_SESSION[SESSION_PASSWORD]= $this->user->Password;
		$_SESSION[SESSION_FULLNAME]= $this->user->Name;
		$_SESSION[SESSION_INITIALS]= $this->user->Code;
		$_SESSION[SESSION_CONTACTID]= (int)($this->user->ID);
		$_SESSION[SESSION_ACCOUNTID]= (int)($this->user->AccountID);
		$_SESSION[SESSION_PROJECTID]= (int)(1);
		session_commit();
		return ($this);
	}

# ====================================================================
# 
# Session Constructor;
#
#
#
# --------------------------------------------------------------------

	function __construct ($session) 
	{
		session_id ($session);
		return;
	}

# ====================================================================
# 
# Session Destructor;
#
#
#
# --------------------------------------------------------------------

	function __destruct () 
	{
		return;
	}

# ====================================================================
# end Session
# --------------------------------------------------------------------

}
 ?>
