# ====================================================================
# Context Commands;
# --------------------------------------------------------------------

USE spcdb;
DROP TABLE IF EXISTS Account, Contact, Project, Transaction;

# ====================================================================
# Contact Table;
# --------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS Contact (
	ID INT (6) UNSIGNED ZEROFILL AUTO_INCREMENT PRIMARY KEY,
	ControlID INT (6) UNSIGNED ZEROFILL NOT NULL DEFAULT 0 REFERENCES Contact (ID) MATCH FULL,
	Type INT (2) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
	Code CHAR(8) NOT NULL UNIQUE KEY, 
	Name CHAR(64) NOT NULL,
	Title CHAR(36) NOT NULL,
	FirstName VARCHAR(36) NOT NULL,
	MiddleName VARCHAR(36) NOT NULL,
	LastName VARCHAR(36) NOT NULL,
	Honors VARCHAR(36) NOT NULL,
	Organization VARCHAR(36) NOT NULL,
	Division VARCHAR(36) NOT NULL,
	Building VARCHAR(36) NOT NULL,
	Street VARCHAR(36) NOT NULL,
	City VARCHAR(36) NOT NULL,
	State VARCHAR(36) NOT NULL,
	Postcode VARCHAR(36) NOT NULL,
	Phone VARCHAR(36) NOT NULL,
	Fax VARCHAR(36) NOT NULL,
	EMail VARCHAR(255) NOT NULL,
	SSN VARCHAR(12) NOT NULL DEFAULT "0000-00-0000",
	Opened DATE,
	Closed DATE,
	Created TIMESTAMP,
	Updated TIMESTAMP
);

INSERT INTO Contact (Type, Code, Name, FirstName, MiddleName, LastName) VALUES ("1", "SPC", "Lottery SPC", "", "", "");
INSERT INTO Contact (Type, Code, Name, FirstName, MiddleName, LastName) VALUES ("4", "BNH", "Bank of New Hampshire", "", "", "");
INSERT INTO Contact (Type, Code, Name, FirstName, MiddleName, LastName) VALUES ("4", "CITZEN", "Citizens Bank", "", "", "");
INSERT INTO Contact (Type, Code, Name, FirstName, MiddleName, LastName) VALUES ("4", "PAYPAL", "Paypal Online", "", "", "");
INSERT INTO Contact (Type, Code, Name, FirstName, MiddleName, LastName) VALUES ("1", "MC", "Mr. Mike Cassidy", "Mike", "", "Cassidy");
INSERT INTO Contact (Type, Code, Name, FirstName, MiddleName, LastName) VALUES ("1", "MS", "Mr. Mark Schedler", "Mark", "", "Schedler");
INSERT INTO Contact (Type, Code, Name, FirstName, MiddleName, LastName) VALUES ("1", "CFM", "Mr. Charles Maier", "Charles", "", "Maier");
INSERT INTO Contact (Type, Code, Name, FirstName, MiddleName, LastName) VALUES ("2", "YC", "Mr. Yong Chen", "Yong", "", "Chen");
INSERT INTO Contact (Type, Code, Name, FirstName, MiddleName, LastName) VALUES ("2", "GL", "Mr. George Lambert", "George", "", "Lambert");
INSERT INTO Contact (Type, Code, Name, FirstName, MiddleName, LastName) VALUES ("2", "MK", "Mr. Michael Kline", "Mike", "", "Kline");
INSERT INTO Contact (Type, Code, Name, FirstName, MiddleName, LastName) VALUES ("3", "ANO", "Mr. A. N. Other", "Albert", "N.", "Other");
INSERT INTO Contact (Type, Code, Name, FirstName, MiddleName, LastName) VALUES ("3", "FB", "Mr. Frederic Bloggs", "Frederick", "", "Blogs");
INSERT INTO Contact (Type, Code, Name, FirstName, MiddleName, LastName) VALUES ("3", "BC", "Mr. Bill Clinton", "Bill", "", "Clinton");
INSERT INTO Contact (Type, Code, Name, FirstName, MiddleName, LastName) VALUES ("3", "GWB", "Mr. George Walker Bush", "George", "Walker", "Bush");
INSERT INTO Contact (Type, Code, Name, FirstName, MiddleName, LastName) VALUES ("3", "JC", "Mr. James Carter", "James", "", "Carter");

# ====================================================================
# Project Table;
# --------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS Project (
	ID INT (6) UNSIGNED ZEROFILL AUTO_INCREMENT PRIMARY KEY,
	ControlID INT (2) UNSIGNED ZEROFILL NOT NULL DEFAULT 0 REFERENCES Project (ID) MATCH FULL,
	ContactID INT (6) UNSIGNED ZEROFILL NOT NULL DEFAULT 0 REFERENCES Contact (ID) MATCH FULL,
	Type INT (2) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
	Code CHAR(8) NOT NULL UNIQUE KEY, 
	Name CHAR(64) NOT NULL,
	Value FLOAT(12,2) UNSIGNED NOT NULL DEFAULT 0.00, 
	Start DATE,
	End DATE
);

INSERT INTO Project (ControlID, ContactID, Code, Name) VALUES (0, 1, "BUSINESS", "Business Activity");

# ====================================================================
# Account Table;
# --------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS Account (
	ID INT (6) UNSIGNED ZEROFILL AUTO_INCREMENT PRIMARY KEY,
	ControlID INT (2) UNSIGNED ZEROFILL NOT NULL DEFAULT 0 REFERENCES Account (ID) MATCH FULL,
	ContactID INT (6) UNSIGNED ZEROFILL NOT NULL DEFAULT 0 REFERENCES Contact (ID) MATCH FULL,
	Type INT (2) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
	Code CHAR(9) NOT NULL UNIQUE KEY, 
	Name VARCHAR(255) NOT NULL, 
	Receipts FLOAT(12,2) UNSIGNED NOT NULL DEFAULT 0.00, 
	Payments FLOAT(12,2) UNSIGNED NOT NULL DEFAULT 0.00, 
	Turnover FLOAT(12,2) NOT NULL DEFAULT 0.00, 
	Balance  FLOAT(12,2) NOT NULL DEFAULT 0.00, 
	Opened DATE, 
	Closed DATE,
	Created TIMESTAMP,
	Updated TIMESTAMP
);

INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (0,1,"ASSETS","Asset Control",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (0,1,"DEBTS","Debt Control",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (0,1,"REVENUE","Revenue Control",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (0,1,"EXPENSE","Expense Control",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (0,1,"SUSPENSE","Suspense Accounts",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (1,1,"CASH","Cash Control",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (1,1,"BANKS","Bank Control",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (1,1,"CUSTOMERS","Customer Control",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (2,1,"EMPLOYEES","Employee Control",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (2,1,"SUPPLIERS","Supplier Control",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (6,1,"GAMES","Gaming Control",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (6,1,"POOLS","Gaming Control",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (3,1,"DEPOSITS","Member Deposits",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (4,1,"TICKETS","Ticket Control",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (8,1,"MEMBERS","Member Control",NOW());

# ====================================================================
#
# --------------------------------------------------------------------

INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (11,1,"PWRBALL","Power Ball",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (11,1,"MALOTTRY","Massachussetts Lottery",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (11,1,"NHLOTTRY","New Hampshire Lottery",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (18,1,"NH050903","New Hampshire Lottery Drawing",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (18,1,"NH050905","New Hampshire Lottery Drawing",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (18,1,"NH050907","New Hampshire Lottery Drawing",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (17,1,"MA050901","Massachussetts Lottery Drawing",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (17,1,"MA051001","Massachussetts Lottery Drawing",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (16,1,"PB050901","Power Ball Drawing",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (16,1,"PB050908","Power Ball Drawing",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (16,1,"PB050915","Power Ball Drawing",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (16,1,"PB050922","Power Ball Drawing",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (16,1,"PB050929","Power Ball Drawing",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (16,1,"PB051006","Power Ball Drawing",NOW());
INSERT INTO Account (ControlID,ContactID,Code,Name,Updated) VALUES (16,1,"PB051013","Power Ball Drawing",NOW());

# ====================================================================
#
# --------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS Transaction (
	ID INT (6) UNSIGNED ZEROFILL DEFAULT 0 AUTO_INCREMENT PRIMARY KEY,
	ProjectID INT (6) UNSIGNED ZEROFILL NOT NULL DEFAULT 0 REFERENCES Project (ID) MATCH FULL, 
	PaymentID INT (6) UNSIGNED ZEROFILL NOT NULL DEFAULT 0 REFERENCES Account (ID) MATCH FULL, 
	ReceiptID INT (6) UNSIGNED ZEROFILL NOT NULL DEFAULT 0 REFERENCES Account (ID) MATCH FULL, 
	ContactID INT (6) UNSIGNED ZEROFILL NOT NULL DEFAULT 0 REFERENCES Contact (ID) MATCH FULL,
	Type CHAR(2) NOT NULL DEFAULT "NT", 
	InternalCode VARCHAR(36) NOT NULL DEFAULT "",
	ExternalCode VARCHAR(36) NOT NULL DEFAULT "",
	Note VARCHAR(255) NOT NULL DEFAULT "", 
	Count INT (6) UNSIGNED NOT NULL DEFAULT 1, 
	Units VARCHAR(16) NOT NULL DEFAULT "Each", 
	Price FLOAT(12,2) UNSIGNED NOT NULL DEFAULT 0.00, 
	Local FLOAT(12,2) UNSIGNED NOT NULL DEFAULT 1.00, 
	Value FLOAT(12,2) UNSIGNED NOT NULL DEFAULT 0.00, 
	TaxRate FLOAT(12,2) UNSIGNED NOT NULL DEFAULT 0.00, 
	Tax FLOAT(12,2) UNSIGNED NOT NULL DEFAULT 0.00, 
	Total FLOAT(12,2) UNSIGNED NOT NULL DEFAULT 0.00, 
	Receipt FLOAT(12,2) UNSIGNED NOT NULL DEFAULT 0.00, 
	Payment FLOAT(12,2) UNSIGNED NOT NULL DEFAULT 0.00, 
	Balance FLOAT(12,2) UNSIGNED NOT NULL DEFAULT 0.00, 
	Date DATE,
	Paid DATE,
	Due DATE,
	Created TIMESTAMP,
	Updated TIMESTAMP
);

# ====================================================================
#
# --------------------------------------------------------------------

