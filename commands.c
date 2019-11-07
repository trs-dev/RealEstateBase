#include <stdio.h>
#include <stdlib.h>
#include <string.h>




extern const int MaxNumberOfTables;
extern enum ColumnType;
extern union Record;
extern struct TableColumn;
extern struct Table;

extern struct Table Tables[];




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
/*
int CreateTable (char* TableName, struct TableColumn *TableColumns)
{

    return 0;
}*/
int CanCreateTable ()
{
    for (int i = 0; i<MaxNumberOfTables; i++)
    {
        if (Tables[i].name[0]=='\0')
        {
            return 1;
        }
    }
    return 0;
}


/*
int InsertInto (struct Table *Tables, char* TableName, struct Record *Records)
{
    return 0;
}*/


