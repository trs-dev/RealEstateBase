#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "resources.h"
#include "tablesdefinition.h"

#define max(x, y) ( (x) > (y) ? (x) : (y) )
#define min(x, y) ( (x) < (y) ? (x) : (y) )


//Database Commands
int SaveDB (char* FileName)
{
    FILE * fp;
    char *c;
    int fileSize = MaxNumberOfTables * sizeof(struct Table);
    //Open file
    if ((fp = fopen(FileName, "wb")) == NULL)
    {
        perror(TextOpenFileError);
        return 1;
    }
    //Write to file
    c = (char *)Tables;
    for (int i = 0; i < fileSize; i++)
    {
        putc(*c, fp);
        c++;
    }
    fclose(fp);
    return 0;
}
int OpenDB (char* FileName)
{
    FILE * fp;
    char *c;
    int i;
    int *pti = (int *)malloc(sizeof(int));

    if ((fp = fopen(FileName, "r")) == NULL)
    {
        perror(TextOpenFileError);
        return 1;
    }
        c = (char *)Tables;
    while ((i= getc(fp))!=EOF)
    {
        *c = i;
        c++;
    }

    free(pti);
    fclose(fp);
    return 0;
}




//Tables Commands
int CanCreateTable ()
{
    return NumberOfTables() < MaxNumberOfTables;
}
int CreateTable (char* TableName, char* ColumnNames)
{
    if(!CanCreateTable())
    {
         printf(TextTooManyTables);
         return 0;
    }
    // find position for new table
    int newTablePosition = -1;
    for (int i = 0; i<MaxNumberOfTables; i++)
    {
       if (Tables[i].Name[0]=='\0')
       {
           newTablePosition = i;
           break;
       }
    }
    Tables[newTablePosition].Index = NumberOfTables()+1;
    strcpy(Tables[newTablePosition].Name, TableName);

    //parser for column names
    int columnIndex = 0;
    char *partOfStr;
    partOfStr = strtok(ColumnNames,","); // get first column name

    while (partOfStr != NULL)
   {
       if (partOfStr[0]==' ')
           partOfStr +=1; // delete first symbol

       if (partOfStr[0]=='$') // Integer Column
       {
           partOfStr +=1; // delete first symbol
           Tables[newTablePosition].Columns[columnIndex].Type = ValNUM;// Integer Column
       }
       else
       {
           Tables[newTablePosition].Columns[columnIndex].Type = ValTEXT;// Text Column
       }

      strcpy(Tables[newTablePosition].Columns[columnIndex].Name, partOfStr); // Set Column name

      Tables[newTablePosition].Columns[columnIndex].Index = columnIndex+1;
      partOfStr = strtok (NULL,","); // get next column name
      columnIndex++;
   }
    printf(TextCreateTableSuccess, TableName);
    return 0;
}

int DeleteTable (int TablePosition)
{
    char oldTableName[MaxTableNameLenght];
    strcpy(oldTableName, Tables[TablePosition].Name);

    int oldTableIndex = Tables[TablePosition].Index;

    //strcpy(Tables[TablePosition].Name, "\0");
    memset(&Tables[TablePosition], 0, sizeof(Table));
    Tables[TablePosition].Index = 0;

    //shift indexes of tables
    for (int i = 0; i<MaxNumberOfTables; i++)
    {
       if (Tables[i].Index > oldTableIndex)
       {
           Tables[i].Index--;
       }
    }

    printf(TextDeleteTableSuccess, oldTableName);
    return 0;
}

int RenameTable (int TablePosition, char* NewTableName)
{
    char oldTableName[MaxTableNameLenght];
    strcpy(oldTableName, Tables[TablePosition].Name);
    strcpy(Tables[TablePosition].Name, NewTableName);
    printf(TextRenameTableSuccess, oldTableName, NewTableName);
    return 0;
}

int MoveTable (int TablePosition, int NewTableIndex)
{
    int OldTableIndex = Tables[TablePosition].Index;
    int shiftDirection = 1;
    if (OldTableIndex < NewTableIndex)
    {
        shiftDirection = -1;
    }

    //shift indexes of tables
    for (int i = 0; i<MaxNumberOfTables; i++)
    {
        if (Tables[i].Index == OldTableIndex)
        {
            Tables[i].Index = NewTableIndex;
        }
        else if (((Tables[i].Index > min(OldTableIndex, NewTableIndex)) && (Tables[i].Index < max(OldTableIndex, NewTableIndex)))
                 || (Tables[i].Index==NewTableIndex))
        {
            Tables[i].Index += shiftDirection;
        }
    }

    return 0;
}

//Columns Commands
int CanAddColumn (int TablePosition)
{
    return NumberOfColumns(TablePosition) < MaxNumberOfColumns;
}
int AddColumn (int TablePosition, char* ColumnName)
{
    if(!CanAddColumn(TablePosition))
    {
         printf(TextTooManyColumns);
         return 0;
    }
    // find position for new column
    int newColumnPosition = -1;
    for (int i = 0; i<MaxNumberOfColumns; i++)
    {
       if (Tables[TablePosition].Columns[i].Name[0]=='\0')
       {
           newColumnPosition = i;
           break;
       }
    }
    Tables[TablePosition].Columns[newColumnPosition].Index = NumberOfColumns(TablePosition)+1;

     if (ColumnName[0]=='$') // Integer Column
       {
           ColumnName +=1; // delete first symbol
           Tables[TablePosition].Columns[newColumnPosition].Type = ValNUM;// Integer Column
       }
       else
       {
           Tables[TablePosition].Columns[newColumnPosition].Type = ValTEXT;// Text Column
       }
    strcpy(Tables[TablePosition].Columns[newColumnPosition].Name, ColumnName);
    printf(TextCreateColumnSuccess, ColumnName);
    return 0;
}

int DeleteColumn (int TablePosition, int ColumnPosition)
{
    char oldColumnName[MaxColumnNameLenght];
    strcpy(oldColumnName, Tables[TablePosition].Columns[ColumnPosition].Name);

    int oldColumnIndex = Tables[TablePosition].Columns[ColumnPosition].Index;

    Tables[TablePosition].Columns[ColumnPosition].Index = 0;
    strcpy(Tables[TablePosition].Columns[ColumnPosition].Name, "\0");

    for (int i = 0; i<MaxNumberOfRows; i++)
    {
        strcpy(Tables[TablePosition].Rows[i].Records[ColumnPosition].ValTEXT, "\0");
    }

    //shift indexes of columns
    for (int i = 0; i<MaxNumberOfColumns; i++)
    {
       if (Tables[TablePosition].Columns[i].Index > oldColumnIndex)
       {
           Tables[TablePosition].Columns[i].Index--;
       }
    }

    printf(TextDeleteColumnSuccess, oldColumnName);
    return 0;
}

int RenameColumn (int TablePosition, int ColumnPosition, char* NewColumnName)
{
    char oldColumnName[MaxColumnNameLenght];
    strcpy(oldColumnName, Tables[TablePosition].Columns[ColumnPosition].Name);
    strcpy(Tables[TablePosition].Columns[ColumnPosition].Name, NewColumnName);
    printf(TextRenameColumnSuccess, oldColumnName, NewColumnName);
    return 0;
}

int MoveColumn (int TablePosition, int ColumnPosition, int NewColumnIndex)
{
    int OldColumnIndex = Tables[TablePosition].Columns[ColumnPosition].Index;
    int shiftDirection = 1;
    if (OldColumnIndex < NewColumnIndex)
    {
        shiftDirection = -1;
    }
    //shift indexes of columns
    for (int i = 0; i<MaxNumberOfColumns; i++)
    {
        if (Tables[TablePosition].Columns[i].Index == OldColumnIndex)
        {
            Tables[TablePosition].Columns[i].Index = NewColumnIndex;
        }
        else if (((Tables[TablePosition].Columns[i].Index > min(OldColumnIndex, NewColumnIndex)) && (Tables[TablePosition].Columns[i].Index < max(OldColumnIndex, NewColumnIndex)))
                 || (Tables[TablePosition].Columns[i].Index==NewColumnIndex))
        {
            Tables[TablePosition].Columns[i].Index += shiftDirection;
        }
    }

    return 0;
}

//Rows Commands
int CanAddRow (int TablePosition)
{
    return NumberOfRows(TablePosition) < MaxNumberOfRows;
}
int AddRow (int TablePosition, char* Records)
{
    if(!CanAddRow(TablePosition))
    {
         printf(TextTooManyRows);
         return 0;
    }
    // find position for new row
    int newRowPosition = -1;
    for (int i = 0; i<MaxNumberOfRows; i++)
    {
       if (Tables[TablePosition].Rows[i].Index <= 0)
       {
           newRowPosition = i;
           break;
       }
    }
    Tables[TablePosition].Rows[newRowPosition].Index = NumberOfRows(TablePosition)+1;

    //parser for records
    int columnIndex = 1;
    char *partOfStr;
    partOfStr = strtok(Records,","); // get first record

    while (partOfStr != NULL)
   {
        if (partOfStr[0]==' ')
            partOfStr +=1; // delete first symbol

       int columnPosition = FindColumnPositionByIndex(TablePosition, columnIndex);
       if (Tables[TablePosition].Columns[columnPosition].Type == ValNUM) // Integer Column
       {
           Tables[TablePosition].Rows[newRowPosition].Records[columnPosition].ValNUM = atoi(partOfStr);
       }
       else
       {
           strcpy(Tables[TablePosition].Rows[newRowPosition].Records[columnPosition].ValTEXT, partOfStr);
       }
      partOfStr = strtok (NULL,","); // get next column name
      columnIndex++;
   }


    printf(TextCreateRowSuccess);
    return 0;
}

int DeleteRow (int TablePosition, int RowPosition)
{
    int oldRowIndex = Tables[TablePosition].Rows[RowPosition].Index;
    Tables[TablePosition].Rows[RowPosition].Index = 0;


    for (int i = 0; i<MaxNumberOfRows; i++)
    {
        strcpy(Tables[TablePosition].Rows[RowPosition].Records[i].ValTEXT, "\0");
    }

    //shift indexes of rows
    for (int i = 0; i<MaxNumberOfRows; i++)
    {
       if (Tables[TablePosition].Rows[i].Index > oldRowIndex)
       {
           Tables[TablePosition].Rows[i].Index--;
       }
    }

    printf(TextDeleteRowSuccess, oldRowIndex);
    return 0;
}

int MoveRow (int TablePosition, int RowPosition, int NewRowIndex)
{
    int OldRowIndex = Tables[TablePosition].Rows[RowPosition].Index;
    int shiftDirection = 1;
    if (OldRowIndex < NewRowIndex)
    {
        shiftDirection = -1;
    }
    //shift indexes of columns
    for (int i = 0; i<MaxNumberOfColumns; i++)
    {
        if (Tables[TablePosition].Rows[i].Index == OldRowIndex)
        {
            Tables[TablePosition].Rows[i].Index = NewRowIndex;
        }
        else if (((Tables[TablePosition].Rows[i].Index > min(OldRowIndex, NewRowIndex)) && (Tables[TablePosition].Rows[i].Index < max(OldRowIndex, NewRowIndex)))
                 || (Tables[TablePosition].Rows[i].Index==NewRowIndex))
        {
            Tables[TablePosition].Rows[i].Index += shiftDirection;
        }
    }

    return 0;
}

int SetValue (int TablePosition, int RowPosition, int ColumnPosition, char* NewValue)
{

    if (Tables[TablePosition].Columns[ColumnPosition].Type == ValNUM) // Integer Column
       {
           Tables[TablePosition].Rows[RowPosition].Records[ColumnPosition].ValNUM = atoi(NewValue);
       }
    else
       {
           strcpy(Tables[TablePosition].Rows[RowPosition].Records[ColumnPosition].ValTEXT, NewValue);
       }

    return 0;
}
