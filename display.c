#include <windows.h>
#include "resources.h"
#include "commands.h"
#include "tablesdefinition.h"


int ConsoleWidth = 110;
int ConsoleHeight = 30;

int TableHeight()
{
    return ConsoleHeight-5;
}

void PrintLine(char Symbol, int Lenght)
{
    for (int i=1; i<=Lenght; i++)
        printf("%c", Symbol);

    printf("\n");
}

const char* TextRecordFormat(int Lenght)
{
    char str[3];
    sprintf(str, "%d", Lenght);
    static char format[8];
    strcpy(format, "|%");
    strcat(format, str);
    strcat(format, ".");
    strcat(format, str);
    strcat(format, "s");
    return format;
}
const char* NumRecordFormat(int Lenght)
{
    char str[3];
    sprintf(str, "%d", Lenght);
    static char format[8];
    strcpy(format, "|%");
    strcat(format, str);
    strcat(format, "d");
    return format;
}


int ColumnWidth(int TablePosition, int ColumnPosition)
{
    int result = 5;
    int columnNameWidth = strlen(Tables[TablePosition].Columns[ColumnPosition].Name);
    result = max(result, columnNameWidth);

    if (Tables[TablePosition].Columns[ColumnPosition].Type == ValNUM)
    {
        int maxVal = 0;
        for (int i=0;i<NumberOfRows(TablePosition); i++)
        {
           maxVal = max(maxVal, Tables[TablePosition].Rows[FindRowPositionByIndex(TablePosition,i)].Records[ColumnPosition].ValNUM);
        }

        char str[13];
        sprintf(str, "%d", maxVal);
        int columnIntWidth = strlen(str);
        result = max(result, columnIntWidth);
    }
    else if (Tables[TablePosition].Columns[ColumnPosition].Type == ValTEXT)
    {
        for (int i=0;i<NumberOfRows(TablePosition); i++)
        {
           result = max(result, strlen(Tables[TablePosition].Rows[FindRowPositionByIndex(TablePosition,i)].Records[ColumnPosition].ValTEXT));
        }
    }
    return result;
}




void ShowTable(int TablePosition, int CurrentColumn, int CurrentRow, int StartFromColumn, int StartFromRow)
{
    int itemsCount = 20; //items to show
    int columnsWidth [MaxNumberOfColumns];
    for (int i = 0; i< MaxNumberOfColumns; i++)
    {
        columnsWidth[i] = ColumnWidth(TablePosition, i);
    }
    system("cls");
    printf("\t%s\n ",Tables[TablePosition].Name);
    PrintLine('-', ConsoleWidth);
    printf(" ");
    //print column names
    int currentTableWidth = 0;
    int currentNumberOfColumns = 0;
    for (int i = StartFromColumn; i<= NumberOfColumns(TablePosition); i++)
    {
        int pos = FindColumnPositionByIndex(TablePosition, i);
        if (currentTableWidth+columnsWidth[pos]>=ConsoleWidth)
            break;
        currentTableWidth+=columnsWidth[pos]+1;
        currentNumberOfColumns++;
        char* format = TextRecordFormat(columnsWidth[pos]);     // construct format of printing record
        printf(format, Tables[TablePosition].Columns[pos].Name);        // print formated record
    }
    printf("|\n ");
    PrintLine('=',currentTableWidth+1);

    //print rows
    for (int r = StartFromRow; r<=StartFromRow+TableHeight(); r++)
    {
        int rowPos = FindRowPositionByIndex(TablePosition, r);
        if (rowPos<0)
            break;
        for (int i = 1; i<= currentNumberOfColumns; i++)
        {
            int pos = FindColumnPositionByIndex(TablePosition, i+StartFromColumn);
            if (pos<0)
                break;
            if (Tables[TablePosition].Columns[pos].Type == ValTEXT)
            {
                char* format = TextRecordFormat(columnsWidth[pos]);     // construct format of printing record
                printf(format, Tables[TablePosition].Rows[rowPos].Records[pos].ValTEXT);        // print formated record
            }
            else if (Tables[TablePosition].Columns[pos].Type == ValNUM)
            {
                char* format = NumRecordFormat(columnsWidth[pos]);     // construct format of printing record
                printf(format, Tables[TablePosition].Rows[rowPos].Records[pos].ValNUM);        // print formated record
            }
        }
        printf("|\n ");
    }
    PrintLine('=',currentTableWidth+1);

}

void DisplayTable(int TablePosition)
{
    int CurrentRow = 1;
    int CurrentColumn = 1;
    int StartFromColumn = 1;
    int StartFromRow = 1;


    ShowTable(TablePosition, CurrentColumn, CurrentRow, StartFromColumn, StartFromRow);
    while(1)
    {
        Sleep(100);
        if(GetAsyncKeyState(VK_UP))
        {
            keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0);
            if(CurrentRow > 1)
            {
                CurrentRow--;
                if (StartFromRow > CurrentRow)
                    StartFromRow = CurrentRow;
                ShowTable(TablePosition, CurrentColumn, CurrentRow, StartFromColumn, StartFromRow);
            }
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);
            if(CurrentRow < NumberOfRows(TablePosition))
            {
                CurrentRow++;
                if (StartFromRow + TableHeight() > CurrentRow)
                    StartFromRow++;
                ShowTable(TablePosition, CurrentColumn, CurrentRow, StartFromColumn, StartFromRow);
            }
        }
        if(GetAsyncKeyState(VK_RETURN))
        {
            keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);

            ShowTable(TablePosition, CurrentColumn, CurrentRow, StartFromColumn, StartFromRow);
        }
        if(GetAsyncKeyState(VK_ESCAPE))
        {
            keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0);
            break;
        }
    }

}





