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
    union Record Cells[MaxNumberOfColumns][MaxNumberOfRows];
} Table;

struct Table Tables[]; //main database


#endif // TABLEDEFINITION_H_INCLUDED
