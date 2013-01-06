# ====================================================================
# Context Commands;
# --------------------------------------------------------------------

USE spcdb;
DROP TABLE IF EXISTS Game, Participant, Contact, Pool, Project, Control, Transaction, Account; 

# ====================================================================
# Contact Table;
# --------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS Contact (
	ID INT (6) UNSIGNED ZEROFILL AUTO_INCREMENT PRIMARY KEY,
	ContactID INT (6) UNSIGNED ZEROFILL NOT NULL DEFAULT 0 REFERENCES Contact (ID) MATCH FULL,
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
	ProjectID INT (2) UNSIGNED ZEROFILL NOT NULL DEFAULT 0 REFERENCES Project (ID) MATCH FULL,
	ContactID INT (6) UNSIGNED ZEROFILL NOT NULL DEFAULT 0 REFERENCES Contact (ID) MATCH FULL,
	Code CHAR(8) NOT NULL UNIQUE KEY, 
	Name CHAR(64) NOT NULL
);

INSERT INTO Project (ProjectID, ContactID, Code, Name) VALUES (0, 1, "BUSINESS", "Business Activity");

# ====================================================================
# Account Table;
# --------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS Account (
	ID INT (6) UNSIGNED ZEROFILL AUTO_INCREMENT PRIMARY KEY,
	AccountID INT (2) UNSIGNED ZEROFILL NOT NULL DEFAULT 0 REFERENCES Account (ID) MATCH FULL,
	ContactID INT (6) UNSIGNED ZEROFILL NOT NULL DEFAULT 0 REFERENCES Contact (ID) MATCH FULL,
	Type INT (2) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
	Code CHAR(8) NOT NULL UNIQUE KEY, 
	Name VARCHAR(255) NOT NULL, 
	Receipts FLOAT(12,2) UNSIGNED NOT NULL DEFAULT 0.00, 
	Payments FLOAT(12,2) UNSIGNED NOT NULL DEFAULT 0.00, 
	Balance  FLOAT(12,2) NOT NULL DEFAULT 0.00, 
	Opened DATE, 
	Closed DATE,
	Created TIMESTAMP,
	Updated TIMESTAMP
);

INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (0,1,"PROFIT","Profit",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (1,1,"ASSETS","Asset Control",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (1,1,"DEBTS","Debt Control",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (1,1,"REVENUE","Revenue Control",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (1,1,"EXPENSE","Expense Control",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (2,1,"CASH","Cash Control",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (2,1,"BANK","Bank Control",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (2,1,"MEMBERS","Member Control",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (2,1,"CUSTOMER","Customer Control",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (3,1,"EMPLOYEE","Employee Control",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (3,1,"SUPPLIER","Supplier Control",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (6,1,"GAMES","Gaming Control",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (6,1,"POOLS","Gaming Control",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (4,1,"DEPOSITS","Member Deposits",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (5,1,"TICKETS","Ticket Control",NOW());

# ====================================================================
#
# --------------------------------------------------------------------

INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (12,1,"PWRBALL","Power Ball",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (12,1,"MALOTTRY","Mass Lottery",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (12,1,"NHLOTTRY","New Hampshire Lottery",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (18,1,"NH050903","New Hampshire Lottery",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (18,1,"NH050905","New Hampshire Lottery",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (18,1,"NH050907","New Hampshire Lottery",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (17,1,"MA050901","New Hampshire Lottery",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (17,1,"MA051001","New Hampshire Lottery",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (16,1,"PB050901","New Hampshire Lottery",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (16,1,"PB050908","New Hampshire Lottery",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (16,1,"PB050915","New Hampshire Lottery",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (16,1,"PB050922","New Hampshire Lottery",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (16,1,"PB050929","New Hampshire Lottery",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (16,1,"PB051006","New Hampshire Lottery",NOW());
INSERT INTO Account (AccountID,ContactID,Code,Name,Updated) VALUES (16,1,"PB051013","New Hampshire Lottery",NOW());

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
# Pool Table;
# --------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS Game (
	ID INT (6) UNSIGNED ZEROFILL NOT NULL DEFAULT 0 AUTO_INCREMENT PRIMARY KEY,
	ContactID INT (6) UNSIGNED ZEROFILL NOT NULL DEFAULT 0 REFERENCES Contact (ID) MATCH FULL,
	AccountID INT (6) UNSIGNED ZEROFILL NOT NULL DEFAULT 0 REFERENCES Account (ID) MATCH FULL,
	Code CHAR(16) NOT NULL UNIQUE, 
	Name VARCHAR(255) NOT NULL
);

INSERT INTO Game (Code, Name) VALUES ("POWERBALL", "As seen on TV.");
INSERT INTO Game (Code, Name) VALUES ("MASS_LOTTERY", "Massachusetts State Lottery. Huge jackpots. Lots of Winners.");
INSERT INTO Game (Code, Name) VALUES ("NH_LOTTERY", "New Hampshire State Lottery. Tiny Jackpots. No winners.");

# ====================================================================
# Pool Table;
# --------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS Pool (
	ID INT (6) UNSIGNED ZEROFILL NOT NULL DEFAULT 0 AUTO_INCREMENT PRIMARY KEY,
	ContactID INT (6) UNSIGNED ZEROFILL NOT NULL DEFAULT 0 REFERENCES Contact (ID) MATCH FULL,
	AccountID INT (6) UNSIGNED ZEROFILL NOT NULL DEFAULT 0 REFERENCES Account (ID) MATCH FULL,
	GameID INT (6) UNSIGNED ZEROFILL NOT NULL DEFAULT 0 REFERENCES Game (ID) MATCH FULL,
	Type INT (2) UNSIGNED ZEROFILL NOT NULL DEFAULT 0,
	Code CHAR(8) NOT NULL UNIQUE, 
	Name CHAR(64) NOT NULL, 
	Rules VARCHAR (255) NOT NULL,
	Opened DATE, 
	Closed DATE,
	Cancelled DATE,
	Drawing DATE,
	Cleared DATE,
	Created TIMESTAMP,
	Updated TIMESTAMP
);

INSERT INTO Pool (GameID, Code, Name, Rules) VALUES (2, "P00001", "None", "Government Employees Only; $1.00 Tickets; 100 Ticket Limit per Game;");
INSERT INTO Pool (GameID, Code, Name, Rules) VALUES (2, "P00002", "None", "Government Employees Only; $1.00 Tickets; 100 Ticket Limit per Game;");
INSERT INTO Pool (GameID, Code, Name, Rules) VALUES (2, "P00003", "None", "Government Employees Only; $1.00 Tickets; 100 Ticket Limit per Game;");
INSERT INTO Pool (GameID, Code, Name, Rules) VALUES (1, "P00004", "None", "Anybody; $2.00 Tickets; 5 Ticket Minimum Purchase; Happy Hour at Sulley's Bar every Friday;");
INSERT INTO Pool (GameID, Code, Name, Rules) VALUES (1, "P00005", "None", "Anybody; $2.00 Tickets; 5 Ticket Minimum Purchase; Happy Hour at Sulley's Bar every Friday;");
INSERT INTO Pool (GameID, Code, Name, Rules) VALUES (1, "P00006", "None", "Anybody; $2.00 Tickets; 5 Ticket Minimum Purchase; Happy Hour at Sulley's Bar every Friday;");
INSERT INTO Pool (GameID, Code, Name, Rules) VALUES (3, "P00007", "None", "Anybody; $1.00 Tickets; No Minimum; No Maximum;");
INSERT INTO Pool (GameID, Code, Name, Rules) VALUES (3, "P00008", "None", "Anybody; $1.00 Tickets; No Minimum; No Maximum;");
INSERT INTO Pool (GameID, Code, Name, Rules) VALUES (3, "P00009", "None", "Anybody; $1.00 Tickets; No Minimum; No Maximum;");
INSERT INTO Pool (GameID, Code, Name, Rules) VALUES (1, "P00010", "None", "American Legion Charity; $2.00 Tickets; Save the Children Fund; Make a difference!");
INSERT INTO Pool (GameID, Code, Name, Rules) VALUES (1, "P00011", "None", "American Legion Charity; $2.00 Tickets; Save the Children Fund; Make a difference!");
INSERT INTO Pool (GameID, Code, Name, Rules) VALUES (1, "P00012", "None", "American Legion Charity; $2.00 Tickets; Save the Children Fund; Make a difference!");

# ====================================================================
#mbertParticipant Table;
# --------------------------------------------------------------------

CREATE TABLE IF NOT EXISTS Participant (
	ID INT (6) UNSIGNED ZEROFILL NOT NULL DEFAULT 0 AUTO_INCREMENT PRIMARY KEY,
	PoolID INT (6) UNSIGNED ZEROFILL NOT NULL DEFAULT 0 REFERENCES Pool (ID) MATCH FULL, 
	ContactID INT (6) UNSIGNED ZEROFILL NOT NULL DEFAULT 0 REFERENCES Contact (ID) MATCH FULL,
	Priority INT (2) UNSIGNED ZEROFILL NOT NULL DEFAULT 0, 
	Status INT (2) UNSIGNED ZEROFILL NOT NULL DEFAULT 0, 
	Joined DATE
);

INSERT INTO Participant (PoolID, ContactID, Priority, Status) VALUES ( 6, 1, 0, 0);
INSERT INTO Participant (PoolID, ContactID, Priority, Status) VALUES ( 9, 12, 0, 0);
INSERT INTO Participant (PoolID, ContactID, Priority, Status) VALUES ( 7, 1, 0, 0);
INSERT INTO Participant (PoolID, ContactID, Priority, Status) VALUES ( 7, 2, 0, 0);
INSERT INTO Participant (PoolID, ContactID, Priority, Status) VALUES ( 7, 3, 0, 0);
INSERT INTO Participant (PoolID, ContactID, Priority, Status) VALUES ( 8, 3, 0, 0);
INSERT INTO Participant (PoolID, ContactID, Priority, Status) VALUES ( 9, 3, 0, 0);
INSERT INTO Participant (PoolID, ContactID, Priority, Status) VALUES ( 6, 2, 0, 0);
INSERT INTO Participant (PoolID, ContactID, Priority, Status) VALUES ( 6, 12, 0, 0);
INSERT INTO Participant (PoolID, ContactID, Priority, Status) VALUES ( 6, 11, 0, 0);
INSERT INTO Participant (PoolID, ContactID, Priority, Status) VALUES ( 7, 11, 0, 0);
INSERT INTO Participant (PoolID, ContactID, Priority, Status) VALUES ( 8, 11, 0, 0);
INSERT INTO Participant (PoolID, ContactID, Priority, Status) VALUES ( 9, 11, 0, 0);
INSERT INTO Participant (PoolID, ContactID, Priority, Status) VALUES ( 9, 12, 0, 0);
INSERT INTO Participant (PoolID, ContactID, Priority, Status) VALUES ( 9, 12, 0, 0);

