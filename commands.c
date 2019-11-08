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
        if (Tables[i].Name[0]!='\0')
            num++;
    return num;
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

    printf(TextCreateTableSuccess, TableName);
    return 0;
}
int CanCreateTable ()
{
    return NumberOfTables() < MaxNumberOfTables;
}

int DeleteTable (int TableIndex)
{
    char OldTableName[MaxTableNameLenght];
    strcpy(OldTableName, Tables[TableIndex].Name);

    Tables[TableIndex].Index = 0;
    strcpy(Tables[TableIndex].Name, "\0");

    printf(TextDeleteTableSuccess, OldTableName);
    return 0;
}







/*
int InsertInto (struct Table *Tables, char* TableName, struct Record *Records)
{
    return 0;
}*/


