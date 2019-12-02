#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "resources.h"
#include "tablesdefinition.h"
#include "filteredtablesdefinition.h"
#include "display.h"

#define max(x, y) ( (x) > (y) ? (x) : (y) )
#define min(x, y) ( (x) < (y) ? (x) : (y) )

#define minPos(x, y) ( ((x) < (y))&& (x>0) ? (x) : (y) )

enum Conditions {Equal, More, Less};

int StartWith(const char *str, const char *prefix)
{
    return strncmp(prefix, str, strlen(prefix)) == 0;
}
int ParseCommand (char* InputedText)
{
    if (StartWith(InputedText, "SELECT "))
        {
            char* partFROM = strstr (InputedText, " FROM ");
            char* partJOIN = strstr (InputedText, " JOIN ");
            char* partON = strstr (InputedText, " ON ");
            char* partWHERE = strstr (InputedText, " WHERE ");
            char* partORDERBY = strstr (InputedText, " ORDER BY ");

            int strLen = strlen(InputedText);

            if (partFROM == NULL)
                return -1;

                //find position of SQL elements
            int partFROMposition = partFROM - InputedText;
            int partJOINposition = 0;
            int partONposition = 0;
            int partWHEREposition = 0;
            int partORDERBYposition = 0;

            if (partJOIN != NULL)
                partJOINposition = partJOIN - InputedText;
            if (partON != NULL)
                partONposition = partON - InputedText;
            if (partWHERE != NULL)
                partWHEREposition = partWHERE - InputedText;
            if (partORDERBY != NULL)
                partORDERBYposition = partORDERBY - InputedText;

            //parse SELECT command
            char columns[(MaxColumnNameLenght+2)*MaxNumberOfColumns];
            strncpy (columns, InputedText + 7, partFROMposition-7);
            columns[partFROMposition-7] = '\0';

            int nextPosition = minPos(minPos(partJOINposition, partWHEREposition),minPos(partORDERBYposition, strLen));

            char tableName[MaxTableNameLenght];
            strncpy (tableName, InputedText + partFROMposition + 6, nextPosition-partFROMposition-6);
            tableName[nextPosition-partFROMposition-6] = '\0';

            ParseCommandSelect(columns, tableName);

            //parse JOIN command
            if (partJOIN != NULL)
            {
                char joinTableName[MaxTableNameLenght];
                strncpy (joinTableName, InputedText + partJOINposition + 6, partONposition-partJOINposition-6);
                joinTableName[partONposition-partJOINposition-6] = '\0';

                nextPosition = minPos(partWHEREposition,minPos(partORDERBYposition, strLen));

                char joinParameters[MaxColumnNameLenght*2+3];
                strncpy (joinParameters, InputedText + partONposition + 4, nextPosition-partONposition-4);
                joinParameters[nextPosition-partONposition-4] = '\0';
                int joinParametersLen = strlen(joinParameters);

                char* partEquals = strstr (joinParameters, " = ");
                int partEqualsPosition = 0;
                if (partEquals != NULL)
                    partEqualsPosition = partEquals - joinParameters;

                char firstColumnName[MaxColumnNameLenght];
                strncpy (firstColumnName, joinParameters, partEqualsPosition);
                firstColumnName[partEqualsPosition] = '\0';

                char secondColumnName[MaxColumnNameLenght];
                strncpy (secondColumnName, joinParameters+partEqualsPosition+3, joinParametersLen-partEqualsPosition-3);
                secondColumnName[joinParametersLen-partEqualsPosition-3] = '\0';

                ParseCommandJoin(firstColumnName, joinTableName, secondColumnName);
            }

            //parse WHERE command
            {
                nextPosition = minPos(partORDERBYposition, strLen);

                char whereParameters[(MaxColumnNameLenght*2+8)*MaxNumberOfColumns];
                strncpy (whereParameters, InputedText + partWHEREposition + 7, nextPosition-partWHEREposition-7);
                whereParameters[nextPosition-partWHEREposition-7] = '\0';

                ParseCommandWhere(whereParameters);
            }




        }
    return 0;
}


int ParseCommandSelect (char Columns[(MaxColumnNameLenght+2)*MaxNumberOfColumns], char Table[MaxTableNameLenght])
{
    int ColumnsPosition[MaxNumberOfColumns];
    for (int i=0; i<MaxNumberOfColumns; i++)
        ColumnsPosition[i]=-1;
    int TablePosition=-1;

    for(int i=0; i<MaxNumberOfTables; i++)
    {
        if (strcmp(Tables[i].Name, Table)==0)
        {
            TablePosition = i;
            break;
        }
    }

    if (TablePosition<0)
        return 1;

    if (strcmp(Columns, "*")==0) //select all columns
    {
        for(int i=1; i<=MaxNumberOfColumns; i++)
        {
            int poz = FindColumnPositionByIndex(TablePosition,i);
            if (poz < 0)
                break;
            ColumnsPosition[i-1]=poz;
        }
    }
    else //find columns by names
    {
        int columnIndex = 0;
        char *partOfStr;
        partOfStr = strtok(Columns,","); // get first column name

        while (partOfStr != NULL)
        {
            if (partOfStr[0]==' ')
                partOfStr +=1; // delete first symbol

            int poz = FindColumnPositionByName(TablePosition, partOfStr);
            if (poz < 0)
                return 1;
            ColumnsPosition[columnIndex]=poz;
            partOfStr = strtok (NULL,","); // get next column name
            columnIndex++;
        }
    }

    Select(ColumnsPosition, TablePosition);
    return 0;
}

int ParseCommandJoin (char BaseColumn[MaxColumnNameLenght], char JoinedTable[MaxTableNameLenght], char JoinedColumn[MaxColumnNameLenght])
{
    int joinedTablePosition = -1;
    for(int i=0; i<MaxNumberOfTables; i++)
    {
        if (strcmp(Tables[i].Name, JoinedTable)==0)
        {
            joinedTablePosition = i;
            break;
        }
    }
    if (joinedTablePosition<0)
        return 1;

    int baseColumnPosition=-1;
    int joinedColumnPosition=-1;

    baseColumnPosition = FindFilteredTableColumnPositionByName(BaseColumn);
    joinedColumnPosition = FindColumnPositionByName(joinedTablePosition, JoinedColumn);

    if (baseColumnPosition<0 || joinedColumnPosition<0)
        return 1;


    Join(baseColumnPosition, joinedTablePosition, joinedColumnPosition);
    return 0;
}

int ParseCommandWhere (char whereParameters[(MaxColumnNameLenght*2+8)*MaxNumberOfColumns])
{
    enum Conditions condition;
    int partANDposition;
    int strLen = strlen(whereParameters);

    while (strLen > 0)
    {
        partANDposition = 0;

        char* partAND = strstr (whereParameters, " AND ");

        if (partAND != NULL)
            partANDposition = partAND - whereParameters;

        int nextPosition = minPos(partANDposition, strLen);
        int partConditionPosition = 0;

        char* partCondition = strstr (whereParameters, " = ");
        if (partCondition != NULL && (partANDposition == 0 || partCondition - whereParameters<partANDposition))
        {
            partConditionPosition = partCondition - whereParameters;
            condition = Equal;
        }
        partCondition = strstr (whereParameters, " > ");
        if (partCondition != NULL && (partANDposition == 0 || partCondition - whereParameters<partANDposition))
        {
            partConditionPosition = partCondition - whereParameters;
            condition = More;
        }
        partCondition = strstr (whereParameters, " < ");
        if (partCondition != NULL && (partANDposition == 0 || partCondition - whereParameters<partANDposition))
        {
            partConditionPosition = partCondition - whereParameters;
            condition = Less;
        }

        char columnName[MaxColumnNameLenght];
        strncpy (columnName, whereParameters, partConditionPosition);
        columnName[partConditionPosition] = '\0';

        char value[MaxCellTextLenght];
        strncpy (value, whereParameters+partConditionPosition+3, nextPosition-partConditionPosition-3);
        value[nextPosition-partConditionPosition-3] = '\0';

        Where(columnName, condition, value);

        if (partAND != NULL)
        {
            whereParameters += partANDposition+5;
            strLen = strlen(whereParameters);
        }
        else
            break;
    }
    return 0;
}


int Select (int ColumnsPosition[MaxNumberOfColumns], int TablePosition)
{
    memset(&FilteredTable, 0, sizeof(Table)); //clear FilteredTable

    for (int i = 0; i < MaxNumberOfColumns; i++)
    {
        if (ColumnsPosition[i]<0)
            break;

        FilteredTable.Columns[i].Index = i+1;
        FilteredTable.Columns[i].Type = Tables[TablePosition].Columns[ColumnsPosition[i]].Type;
        strcpy(FilteredTable.Columns[i].Name, Tables[TablePosition].Columns[ColumnsPosition[i]].Name);

        for (int r = 1; r<= NumberOfRows(TablePosition); r++)
        {
            int rowPosition = FindRowPositionByIndex(TablePosition, r);
            if (rowPosition<0)
                break;

            if (FilteredTable.Columns[i].Type == ValNUM) // Integer Column
                FilteredTable.Rows[r-1].Records[i].ValNUM = Tables[TablePosition].Rows[rowPosition].Records[ColumnsPosition[i]].ValNUM;
            else
                strcpy(FilteredTable.Rows[r-1].Records[i].ValTEXT, Tables[TablePosition].Rows[rowPosition].Records[ColumnsPosition[i]].ValTEXT);
            FilteredTable.Rows[rowPosition].Index = r;
        }
    }
    return 0;
}

int Join(int BaseColumnPosition, int JoinedTablePosition, int JoinedColumnPosition)
{
    int replaseColumnPositipn = -1;
    for (int i = 0; i < MaxNumberOfColumns; i++)
    {
        if(i!= JoinedColumnPosition && Tables[JoinedTablePosition].Columns[i].Index>0)
        {
            replaseColumnPositipn = i;
            break;
        }
    }
    for (int i = 0; i < MaxNumberOfRows; i++)
    {
        if (FilteredTable.Rows[i].Index > 0)
        {
            int poz = -1;
            for (int r=0; r<MaxNumberOfRows;r++)
            {
                if (FilteredTable.Rows[i].Records[BaseColumnPosition].ValNUM == Tables[JoinedTablePosition].Rows[r].Records[JoinedColumnPosition].ValNUM)
                {
                    poz = r;
                    break;
                }
            }
            if(Tables[JoinedTablePosition].Columns[replaseColumnPositipn].Type == ValNUM)
                FilteredTable.Rows[i].Records[BaseColumnPosition].ValNUM = Tables[JoinedTablePosition].Rows[poz].Records[replaseColumnPositipn].ValNUM;
            else
                strcpy(FilteredTable.Rows[i].Records[BaseColumnPosition].ValTEXT, Tables[JoinedTablePosition].Rows[poz].Records[replaseColumnPositipn].ValTEXT);
        }
    }

    if(Tables[JoinedTablePosition].Columns[replaseColumnPositipn].Type == ValTEXT)
        FilteredTable.Columns[BaseColumnPosition].Type = ValTEXT;

    strcpy(FilteredTable.Columns[BaseColumnPosition].Name, Tables[JoinedTablePosition].Columns[replaseColumnPositipn].Name);

    return 0;
}

int Where(char ColumnName[MaxColumnNameLenght], enum Conditions Condition, char value[MaxCellTextLenght])
{
    int columnPosition = FindFilteredTableColumnPositionByName(ColumnName);

    switch(Condition)
    {
    case Equal:
        for (int i = 0; i < MaxNumberOfRows; i++)
        {
             if ((FilteredTable.Columns[columnPosition].Type == ValTEXT &&
                 strcmp(FilteredTable.Rows[i].Records[columnPosition].ValTEXT, value))||
                 (FilteredTable.Columns[columnPosition].Type == ValNUM &&
                 FilteredTable.Rows[i].Records[columnPosition].ValNUM != atoi(value)))
                 FilteredTable.Rows[i].Index = 0;
        }
        break;
    case More:
        for (int i = 0; i < MaxNumberOfRows; i++)
        {
            if (!(FilteredTable.Rows[i].Records[columnPosition].ValNUM > atoi(value)))
                FilteredTable.Rows[i].Index = 0;
        }
        break;
    case Less:
        for (int i = 0; i < MaxNumberOfRows; i++)
        {
            if (!(FilteredTable.Rows[i].Records[columnPosition].ValNUM < atoi(value)))
                FilteredTable.Rows[i].Index = 0;
        }
        break;
    }

    //fixing FilteredTable indexes

    int index = 1;
    for (int i = 0; i < MaxNumberOfRows; i++)
    {
        if (FilteredTable.Rows[i].Index>0)
        {
            FilteredTable.Rows[i].Index = index;
            index++;
        }
    }
}








