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
        if (Tables[i].name[0]!='\0')
            num++;
    return num;
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
       if (Tables[i].name[0]=='\0')
       {
           NewTablePosition = i;
           break;
       }
    }

    strcpy(Tables[NewTablePosition].name, TableName);






    printf(TextCreateTableSuccess, TableName);

    return 0;
}
int CanCreateTable ()
{
    return NumberOfTables() < MaxNumberOfTables;
}

/*
int InsertInto (struct Table *Tables, char* TableName, struct Record *Records)
{
    return 0;
}*/


