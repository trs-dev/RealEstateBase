#include "tablesdefinition.h"

struct Table Tables[MaxNumberOfTables]; //main database


//Tables, Columns and Rows counters/finders
int NumberOfTables ()
{
    int num = 0;
    for (int i = 0; i<MaxNumberOfTables; i++)
        if (Tables[i].Index>0)
            num++;
    return num;
}

int NumberOfColumns (int TablePosition)
{
    int num = 0;
    for (int i = 0; i<MaxNumberOfColumns; i++)
        if (Tables[TablePosition].Columns[i].Index>0)
            num++;
    return num;
}

int FindTablePositionByIndex (int TableIndex)
{
    for (int i = 0; i<MaxNumberOfTables; i++)
    {
        if (Tables[i].Index==TableIndex)
        {
            return i;
        }
    }
    return -1;
}

int FindColumnPositionByIndex (int TableIndex, int ColumnIndex)
{
    for (int i = 0; i<MaxNumberOfColumns; i++)
    {
        if (Tables[TableIndex].Columns[i].Index==ColumnIndex)
        {
            return i;
        }
    }
    return -1;
}
