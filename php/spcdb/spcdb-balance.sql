# ====================================================================
# Context Commands;
# --------------------------------------------------------------------

USE spcdb;

# ====================================================================
# Context Commands;
# --------------------------------------------------------------------

DROP TABLE IF EXISTS Balance;
CREATE TABLE Balance SELECT Date, Account.Code AS Account, Note, Count, Units, Price, Total AS Payment, (0.00) AS Receipt FROM Account JOIN Transaction ON Account.ID=ReceiptID WHERE PaymentID=(13) ORDER BY Date; 
INSERT INTO  Balance SELECT Date, Account.Code AS Account, Note, Count, Units, Price, (0.00) AS Payment, Total AS Receipt FROM Account JOIN Transaction ON Account.ID=PaymentID WHERE ReceiptID=(13) ORDER BY Date; 
SELECT * FROM Balance;

# ====================================================================
# Context Commands;
# --------------------------------------------------------------------

DROP TABLE IF EXISTS Balance;
CREATE TABLE Balance SELECT Date, Account.Code AS Account, Note, Count, Units, Price, Total AS Payment, (0.00) AS Receipt FROM Account JOIN Transaction ON Account.ID=ReceiptID WHERE PaymentID=(6) ORDER BY Date; 
INSERT INTO  Balance SELECT Date, Account.Code AS Account, Note, Count, Units, Price, (0.00) AS Payment, Total AS Receipt FROM Account JOIN Transaction ON Account.ID=PaymentID WHERE ReceiptID=(6) ORDER BY Date; 
SELECT * FROM Balance;

