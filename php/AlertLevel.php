<?php

# ====================================================================
# AlertLevel Class;
#
#
#
# --------------------------------------------------------------------

class AlertLevel 
{

# ====================================================================
# AlertLevel Variables;
# --------------------------------------------------------------------

	var $Height = 15; 
	var $Width = 172; 
	var $Level; 
	var $Color; 
	var $Title; 
	var $State; 
	var $Image; 

# ====================================================================
#
# AlertLevel EchoAlertLevel Method;
#
# echo alert level text string with newline;
#
# --------------------------------------------------------------------

	public function EchoAlertLevel()
	{
		echo "Alert Level is $this->Color $this->Title\n"; 
		return; 
	}

# ====================================================================
#
# AlertLevel EchoAlertImage1 Method;
#
# echo raw alert image;
#
# --------------------------------------------------------------------

	public function EchoAlertImage()
	{
		header("Content-Type: image/png"); 
		$image = imagecreatefrompng($this->Image); 
		imagepng($image); 
		imagedestroy($image); 
		return; 
	}

# ====================================================================
#
# AlertLevel EchoAlertImageTag Method;
#
# echo a standard alert image tag having appropriate attributes;
#
# --------------------------------------------------------------------

	public function EchoAlertImageTag()
	{
		echo "<img style='height: $this->Height; width=: $this->Width;' src='$this->Image' href='http://www.dhs.gov/dhspublic/' title=' Alert Level is $this->Color $this->Title. ' alt='$this->Color $this->Title'/>"; 
		return; 
	}

# ====================================================================
#
# AlertLevel Constructor;
#
# access DHS website and extract current alert level; initialize the
# color and image accordingly;
#
# --------------------------------------------------------------------

	function __construct()
	{
#		$ImagePath = "http://mattshelton.net/bin/images/terror"; 
#		$ImagePath = "http://spc.razzlefratz.net/images"; 
		$ImagePath = "../images"; 
		$xml_source = file_get_contents("http://www.dhs.gov/dhspublic/getAdvisoryCondition"); 
		$xml_parser = xml_parser_create(); 
		xml_parser_set_option($xml_parser, XML_OPTION_CASE_FOLDING, 0); 
		xml_parser_set_option($xml_parser, XML_OPTION_SKIP_WHITE, 1); 
		if(!xml_parse_into_struct($xml_parser, $xml_source, $xml_struct, $index))
		{
			$error = xml_get_error_code($xml_parser); 
			$error = xml_error_string($error); 
			die("xmlread: parse unsuccessful: $error"); 
		}
		xml_parser_free($xml_parser); 
		$this->Title = $xml_struct[0]["attributes"]["CONDITION"]; 
		if(!$this->Title)
		{
			die("Failed to fetch terror alert level from DHS."); 
		}
		switch($this->Title)
		{
			case "SEVERE": $this->Level = 5; 
			$this->Color = "RED"; 
			$this->Image = $ImagePath."/severe.png"; 
			break; 
			case "HIGH": $this->Level = 4; 
			$this->Color = "ORANGE"; 
			$this->Image = $ImagePath."/high.png"; 
			break; 
			case "ELEVATED": $this->Level = 3; 
			$this->Color = "YELLOW"; 
			$this->Image = $ImagePath."/elevated.png"; 
			break; 
			case "GUARDED": $this->Level = 2; 
			$this->Color = "BLUE"; 
			$this->Image = $ImagePath."/guarded.png"; 
			break; 
			case "LOW": $this->Level = 1; 
			$this->Color = "GREEN"; 
			$this->Image = $ImagePath."/low.png"; 
			break; 
			default: $this->Level = 0; 
			$this->Color = "WHITE"; 
			$this->Image = ""; 
			break; 
		}
		return; 
	}

# ====================================================================
#
# AlertLevel Destructor;
#
#
#
# --------------------------------------------------------------------

	function __destruct()
	{
		return; 
	}
}

# ====================================================================
#
# --------------------------------------------------------------------

 ?>
