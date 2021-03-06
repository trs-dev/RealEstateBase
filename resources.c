char* TextWelcome = "Hello! Welcome to Real Estate Base.\n";
char* TextChangeLanguage = "Choose your language: \n 1 - English\n 2 - Ukrainian\n 0 - Exit:\n";

char* TextOperationsWithTables = "Operations with tables: \n 1 - Show tables list and choose table\n 2 - Add new table \n 3 - Execute SELECT database command \n 0 - Exit:\n";
char* TextOperationsWithSingleTable = "Operations with table [%s]: \n 1 - Display all data\n 2 - Add row \n 3 - Rename table \n 4 - Move table \n 5 - Add columns \n 6 - Delete table \n 0 - Return:\n";

char* TextEditTableTips = " Press arrow keys to navigate; Ctrl + E - Edit entry; Ctrl + X - Remove row; \n Ctrl + WASD - Move columns and rows; Ctrl + T - Rename column; Ctrl + R - Remove column; \n Ctrl + Z - Return.\n";
char* TextViewTableTips = " Press arrow keys to navigate;\n Ctrl + Z - Return.\n";

char* TextTableName = "Table name: ";
char* TextColumnNames = "Column names (separated by comma): ";
char* TextColumnName = "Column name: ";
char* TextRowRecords = "Enter row records(separated by comma): ";
char* TextNewValue = "Enter new value: ";
char* TextNewColumnName = "Enter new column name: ";
char* TextEnterSelectCommand = "Enter SELECT command. \nSyntax: SELECT ColumnName1, ColumnName2... or * FROM TableName1 JOIN TableName2 ON Table1Column = Table2Column\n        WHERE ColumName1 ><= Value1 AND ColumnName2 ><= Value2 ORDER BY ColumnName1 ASC/DESC, ColumnName2 ASC/DESC, ...\n";

char* TextRenamingTable = "Renaming of table [%s]\n";
char* TextNewName = "New name: ";

char* TextMovingTable = "Moving table [%s]\n (0 for Return)\n New position:";

char* TextSelectTable = "Enter the table number to select it: ";
char* TextNoTablesInDB = "There are no tables in the database.\n";

char* TextCreateTableSuccess = "Table [%s] successfully created.\n";
char* TextDeleteTableSuccess = "Table [%s] has been deleted.\n";
char* TextRenameTableSuccess = "Table [%s] has been renamed to [%s].\n";

char* TextNoColumnsInTable = "There are no Columns in Table.\n";
char* TextTooManyColumns = "There are too many Columns in Table.\n";

char* TextCreateColumnSuccess = "Column [%s] successfully created.\n";
char* TextDeleteColumnSuccess = "Column [%s] has been deleted.\n";
char* TextRenameColumnSuccess = "Column [%s] has been renamed to [%s].\n";

char* TextTooManyRows = "There are too many Rows in Table.\n";
char* TextCreateRowSuccess = "New row successfully created.\n";
char* TextDeleteRowSuccess = "Row [%d] has been deleted.\n";

char* TextOpenFileError = "Error occured while opening file";

char* TextReturn = "Return";

char* TextInputError = "Command not recognized. Please try again.\n";
char* TextTooManyInputErrors = "There are too many unrecognized commands entered. Press any key for Exit.\n";

char* TextTooManyTables = "The database has reached the maximum number of tables. Delete the unnecessary spreadsheet and try again.\n";
