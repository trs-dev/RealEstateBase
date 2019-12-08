#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

int SaveDB (char* FileName);
int OpenDB (char* FileName);

int CanCreateTable();
int CreateTable(char* TableName, char* ColumnNames);
int DeleteTable(int TablePosition);
int RenameTable (int TablePosition, char* NewTableName);
int MoveTable (int TablePosition, int NewTableIndex);

int CanAddColumn (int TablePosition);
int AddColumn (int TablePosition, char* ColumnName);
int DeleteColumn (int TablePosition, int ColumnPosition);
int RenameColumn (int TablePosition, int ColumnPosition, char* NewColumnName);
int MoveColumn (int TablePosition, int ColumnPosition, int NewColumnIndex);

int CanAddRow (int TablePosition);
int AddRow (int TablePosition, char* Records);
int DeleteRow (int TablePosition, int RowPosition);
int MoveRow (int TablePosition, int RowPosition, int NewRowIndex);

int SetValue (int TablePosition, int RowPosition, int ColumnPosition, char* NewValue);

#endif // COMMANDS_H_INCLUDED
