<?php

# =
#
# -

class cmassoc 
{

# ====================================================================
#
#   function combine ($Prefix, $Middle, $Suffix)
#
#   if the prefix string is empty then return the suffix string; if 
#   the suffix string is empty then return the prefix string; else
#   return the concatenation of all three strings;
#
#   Publised 2005 by Charles Maier Associates Limited for internal use;
#
# --------------------------------------------------------------------

   public static function combine($Prefix, $Middle, $Suffix) 
   {
      if(empty($Prefix)) 
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
#   function is_date ($mydate);
#
#
#
# --------------------------------------------------------------------

   public static function is_date($mydate) 
   {
      return(true);
   }
}
 ?>
