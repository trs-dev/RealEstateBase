//define maximum size of database and tables
#define MaxNumberOfTablesVal 10
#define MaxNumberOfColumnsVal 10
#define MaxNumberOfRowsVal 100

//define maximum length of cells and names fields
#define MaxTableNameLenghtVal 20
#define MaxColumnNameLenghtVal 20
#define MaxCellTextLenghtVal 100
#define CellNumericTypeVal int

//sets maximum size of database and tables
const int MaxNumberOfTables = MaxNumberOfTablesVal;
const int MaxNumberOfColumns = MaxNumberOfColumnsVal;
const int MaxNumberOfRows = MaxNumberOfRowsVal;

//sets maximum length of cells and names fields
const int MaxTableNameLenght = MaxTableNameLenghtVal;
const int MaxColumnNameLenght = MaxColumnNameLenghtVal;
const int MaxCellTextLenght = MaxCellTextLenghtVal;




enum ColumnType {ValTEXT, ValNUM};

union Record
{
    char ValTEXT[MaxCellTextLenghtVal];
    CellNumericTypeVal ValNUM;
};

struct TableColumn
{
    char name[MaxColumnNameLenght];
    enum ColumnType type;
    int Index;
} TableColumn;

struct Table
{
    char name[MaxTableNameLenght];
    struct TableColumn Columns[MaxNumberOfColumns];
    union Record Cells[MaxNumberOfColumns][MaxNumberOfRows];
} Table;


struct Table Tables[MaxNumberOfTables]; //main database
