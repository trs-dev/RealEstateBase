enum ColumnType {ValTEXT, ValINT};

union Record
{
    char ValTEXT[100];
    int ValINT;
};

struct TableColumn
{
    char name[20];
    enum ColumnType type;
    int Index;
} TableColumn;

struct Table
{
    char name[20];
    struct TableColumn Columns[10];
    union Record Records[10][100];
} Table;
