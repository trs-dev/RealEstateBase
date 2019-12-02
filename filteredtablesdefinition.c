#include "tablesdefinition.h"

struct Table FilteredTable; //Filtered Table to display


int FilteredTableNumberOfColumns ()
{
    int num = 0;
    for (int i = 0; i<MaxNumberOfColumns; i++)
        if (FilteredTable.Columns[i].Index>0)
            num++;
    return num;
}

int FilteredTableNumberOfRows ()
{
    int num = 0;
    for (int i = 0; i<MaxNumberOfRows; i++)
        if (FilteredTable.Rows[i].Index>0)
            num++;
    return num;
}


int FindFilteredTableColumnPositionByIndex (int ColumnIndex)
{
    for (int i = 0; i<MaxNumberOfColumns; i++)
        if (FilteredTable.Columns[i].Index==ColumnIndex)
            return i;
    return -1;
}

int FindFilteredTableColumnPositionByName (char ColumnName[MaxColumnNameLenght])
{
    for (int i = 0; i<MaxNumberOfColumns; i++)
        if (strcmp(FilteredTable.Columns[i].Name, ColumnName)==0)
            return i;
    return -1;
}

int FindFilteredTableRowPositionByIndex (int RowIndex)
{
    for (int i = 0; i<MaxNumberOfRows; i++)
        if (FilteredTable.Rows[i].Index==RowIndex)
            return i;
    return -1;
}

