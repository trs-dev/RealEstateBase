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

int NumberOfRows (int TablePosition)
{
    int num = 0;
    for (int i = 0; i<MaxNumberOfRows; i++)
        if (Tables[TablePosition].Rows[i].Index>0)
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

int FindColumnPositionByIndex (int TablePosition, int ColumnIndex)
{
    for (int i = 0; i<MaxNumberOfColumns; i++)
    {
        if (Tables[TablePosition].Columns[i].Index==ColumnIndex)
        {
            return i;
        }
    }
    return -1;
}

int FindColumnPositionByName (int TablePosition, char ColumnName[MaxColumnNameLenght])
{
    for (int i = 0; i<MaxNumberOfColumns; i++)
    {
        if (strcmp(Tables[TablePosition].Columns[i].Name, ColumnName)==0)
        {
            return i;
        }
    }
    return -1;
}

int FindRowPositionByIndex (int TablePosition, int RowIndex)
{
    for (int i = 0; i<MaxNumberOfRows; i++)
    {
        if (Tables[TablePosition].Rows[i].Index==RowIndex)
        {
            return i;
        }
    }
    return -1;
}
