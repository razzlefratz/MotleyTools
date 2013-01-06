# ====================================================================
# Template User Privilege Query;
# --------------------------------------------------------------------

UPDATE user SET Host='ariel.cmassoc.net,User='',Password=PASSWORD(''),Select_priv='Y',Insert_priv='Y',Update_priv='Y',Delete_priv='Y',Create_priv='Y',Drop_priv='Y',Create_tmp_table_priv='Y';

UPDATE db SET Select_priv='Y',Insert_priv='Y',Update_priv='Y',Delete_priv='Y',Create_priv='Y',Drop_priv='Y',Create_tmp_table_priv='Y' WHERE Host='ariel.cmassoc.net' AND User='root';

# ====================================================================
#
# Template DB Privilege Query;
# --------------------------------------------------------------------

FLUSH PRIVILEGES;

