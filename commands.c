#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


//Tables Commands
int CreateTable (struct Table *Tables, char* TableName, struct TableColumn *TableColumns)
{

    return 0;
}

int InsertInto (struct Table *Tables, char* TableName, struct Record *Records)
{
    return 0;
}


