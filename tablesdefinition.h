#ifndef TABLEDEFINITION_H_INCLUDED
#define TABLEDEFINITION_H_INCLUDED


//define maximum size of database and tables
#define MaxNumberOfTables 10
#define MaxNumberOfColumns 10
#define MaxNumberOfRows 100

//define maximum length of cells and names fields
#define MaxTableNameLenght 20
#define MaxColumnNameLenght 20
#define MaxCellTextLenght 100
#define CellNumericType int

enum ColumnType {ValTEXT, ValNUM};

union Record
{
    char ValTEXT[MaxCellTextLenght];
    CellNumericType ValNUM;
};

struct TableRow
{
    union Record Records[MaxNumberOfColumns];
    int Index;
} TableRow;


struct TableColumn
{
    char Name[MaxColumnNameLenght];
    enum ColumnType Type;
    int Index;
} TableColumn;

struct Table
{
    char Name[MaxTableNameLenght];
    int Index;
    struct TableColumn Columns[MaxNumberOfColumns];
    struct TableRow Rows[MaxNumberOfRows];
} Table;

struct Table Tables[MaxNumberOfTables]; //main database

int NumberOfTables ();
int NumberOfColumns (int TablePosition);
int FindTablePositionByIndex (int TableIndex);
int FindColumnPositionByIndex (int TableIndex, int ColumnIndex);

#endif // TABLEDEFINITION_H_INCLUDED
