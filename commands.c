#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "resources.h"
#include "tablesdefinition.h"


/*
int StartWith(const char *str, const char *prefix)
{
    return strncmp(prefix, str, strlen(prefix)) == 0;
}


int ParseCommand (char* InputedText)
{
    if (StartWith(InputedText, "CREATE TABLE"))
        {
        }
    return 0;
}
*/

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



//Database Commands
int SaveDB (char* FileName)
{
    FILE * fp;
    char *c;
    int FileSize = MaxNumberOfTables * sizeof(struct Table);
    //Open file
    if ((fp = fopen(FileName, "wb")) == NULL)
    {
        perror(TextOpenFileError);
        return 1;
    }
    //Write to file
    c = (char *)Tables;
    for (int i = 0; i < FileSize; i++)
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

int CreateTable (char* TableName, char* ColumnNames)
{
    if(!CanCreateTable())
    {
         printf(TextTooManyTables);
         return 0;
    }
    // find position for new table
    int NewTablePosition = -1;
    for (int i = 0; i<MaxNumberOfTables; i++)
    {
       if (Tables[i].Name[0]=='\0')
       {
           NewTablePosition = i;
           break;
       }
    }
    Tables[NewTablePosition].Index = NumberOfTables()+1;
    strcpy(Tables[NewTablePosition].Name, TableName);

    //parser for column names
    int ColumnIndex = 0;
    char *PartOfStr;
    PartOfStr = strtok(ColumnNames,"/"); // get first column name

    while (PartOfStr != NULL)
   {
       if (PartOfStr[0]=='$') // Integer Column
       {
           PartOfStr +=1; // delete first symbol
           Tables[NewTablePosition].Columns[ColumnIndex].Type = ValNUM;// Integer Column
       }
       else
       {
           Tables[NewTablePosition].Columns[ColumnIndex].Type = ValTEXT;// Text Column
       }

      strcpy(Tables[NewTablePosition].Columns[ColumnIndex].Name, PartOfStr); // Set Column name

      Tables[NewTablePosition].Columns[ColumnIndex].Index = NumberOfTables(NewTablePosition)+1;
      PartOfStr = strtok (NULL,"/"); // get next column name
   }
    printf(TextCreateTableSuccess, TableName);
    return 0;
}
int CanCreateTable ()
{
    return NumberOfTables() < MaxNumberOfTables;
}

int DeleteTable (int TablePosition)
{
    char OldTableName[MaxTableNameLenght];
    strcpy(OldTableName, Tables[TablePosition].Name);

    int OldTableIndex = Tables[TablePosition].Index;

    Tables[TablePosition].Index = 0;
    strcpy(Tables[TablePosition].Name, "\0");

    //shift indexes of tables
    for (int i = 0; i<MaxNumberOfTables; i++)
    {
       if (Tables[i].Index > OldTableIndex)
       {
           Tables[i].Index--;
       }
    }

    printf(TextDeleteTableSuccess, OldTableName);
    return 0;
}







/*
int InsertInto (struct Table *Tables, char* TableName, struct Record *Records)
{
    return 0;
}*/


