# ====================================================================
# Context Commands;
# --------------------------------------------------------------------

USE spcdb;
DROP TABLE Balance;

# ====================================================================
# Context Commands;
# --------------------------------------------------------------------

CREATE TABLE Balance SELECT PaymentID AS AccountID, SUM(Total) As Payments, (0.00) AS Receipts FROM Transaction GROUP BY PaymentID ORDER BY PaymentID; 
INSERT INTO  Balance SELECT ReceiptID AS AccountID, (0.00) AS Payments, SUM(Total) AS Receipts FROM Transaction GROUP BY ReceiptID ORDER BY ReceiptID; 
UPDATE Account SET Payments=(0), Receipts=(0), Balance=(0); 
UPDATE Account INNER JOIN Balance ON ID=AccountID SET Account.Payments=Balance.Payments; 
UPDATE Account INNER JOIN Balance ON ID=AccountID SET Account.Receipts=Balance.Receipts; 
DROP TABLE Balance;
