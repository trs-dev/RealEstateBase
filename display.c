#include <windows.h>
#include <stdio.h>
#include "resources.h"
#include "commands.h"
#include "tablesdefinition.h"
#include "filteredtablesdefinition.h"
#include "display.h"

int ConsoleWidth = 110;
int ConsoleHeight = 30;

int TableHeight()
{
    return ConsoleHeight-15;
};

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
        for (int i=1;i<=NumberOfRows(TablePosition); i++)
           maxVal = max(maxVal, abs(Tables[TablePosition].Rows[FindRowPositionByIndex(TablePosition,i)].Records[ColumnPosition].ValNUM));

        char str[13];
        sprintf(str, "%d", maxVal);
        int columnIntWidth = strlen(str)+1;
        result = max(result, columnIntWidth);
    }
    else if (Tables[TablePosition].Columns[ColumnPosition].Type == ValTEXT)
    {
        for (int i=1;i<=NumberOfRows(TablePosition); i++)
           result = max(result, strlen(Tables[TablePosition].Rows[FindRowPositionByIndex(TablePosition,i)].Records[ColumnPosition].ValTEXT));
    }
    return result;
}

int FilteredTableColumnWidth(int ColumnPosition)
{
    int result = 5;
    int columnNameWidth = strlen(FilteredTable.Columns[ColumnPosition].Name);
    result = max(result, columnNameWidth);

    if (FilteredTable.Columns[ColumnPosition].Type == ValNUM)
    {
        int maxVal = 0;
        for (int i=1;i<=MaxNumberOfRows; i++)
           maxVal = max(maxVal, abs(FilteredTable.Rows[i].Records[ColumnPosition].ValNUM));

        char str[13];
        sprintf(str, "%d", maxVal);
        int columnIntWidth = strlen(str)+1;
        result = max(result, columnIntWidth);
    }
    else if (FilteredTable.Columns[ColumnPosition].Type == ValTEXT)
    {
        for (int i=1;i<=MaxNumberOfRows; i++)
           result = max(result, strlen(FilteredTable.Rows[i].Records[ColumnPosition].ValTEXT));
    }
    return result;
}



void ShowTable(int TablePosition, int CurrentColumn, int CurrentRow, int StartFromColumn, int StartFromRow)
{
    int columnsWidth [MaxNumberOfColumns];
    for (int i = 0; i< MaxNumberOfColumns; i++)
        columnsWidth[i] = ColumnWidth(TablePosition, i);
    system("cls");
    printf("\t%s\n ",Tables[TablePosition].Name);
    PrintLine('-', ConsoleWidth);
    printf("    ");
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
    printf("|\n    ");
    PrintLine('=',currentTableWidth+1);

    //print rows
    for (int r = StartFromRow; r<=StartFromRow+TableHeight(); r++)
    {
        if (r == CurrentRow)
            printf(">");
        else
            printf(" ");

        int rowPos = FindRowPositionByIndex(TablePosition, r);
        if (rowPos<0)
            break;
        printf("%3d", r);
        for (int i = 1; i<= currentNumberOfColumns; i++)
        {
            int pos = FindColumnPositionByIndex(TablePosition, i+StartFromColumn-1);
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
        printf("|\n");
        if (r==StartFromRow+TableHeight())
            printf(" ");
    }
    printf("   ");
    PrintLine('=',currentTableWidth+1);
    printf(TextEditTableTips);

}

void EditTable(int TablePosition)
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
                if (StartFromRow + TableHeight() < CurrentRow)
                    StartFromRow++;
                ShowTable(TablePosition, CurrentColumn, CurrentRow, StartFromColumn, StartFromRow);
            }
        }

        if(GetAsyncKeyState(VK_LEFT))
        {
            keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
            if(CurrentColumn > 1)
            {
                CurrentColumn--;
                if (StartFromColumn > CurrentColumn)
                    StartFromColumn = CurrentColumn;
                ShowTable(TablePosition, CurrentColumn, CurrentRow, StartFromColumn, StartFromRow);
            }
        }
        if(GetAsyncKeyState(VK_RIGHT))
        {
            keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
            if(CurrentColumn < NumberOfColumns(TablePosition))
            {
                CurrentColumn++;
                StartFromColumn++;
                ShowTable(TablePosition, CurrentColumn, CurrentRow, StartFromColumn, StartFromRow);
            }
        }

        if(GetAsyncKeyState('W') && GetAsyncKeyState(VK_CONTROL))
        {
            keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
            keybd_event('W', 0, KEYEVENTF_KEYUP, 0);
            if(CurrentRow > 1)
            {
                MoveRow (TablePosition, FindRowPositionByIndex(TablePosition, CurrentRow), CurrentRow-1);
                CurrentRow--;
                if (StartFromRow > CurrentRow)
                    StartFromRow = CurrentRow;
                ShowTable(TablePosition, CurrentColumn, CurrentRow, StartFromColumn, StartFromRow);
            }
        }
        if(GetAsyncKeyState('S') && GetAsyncKeyState(VK_CONTROL))
        {
            keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
            keybd_event('S', 0, KEYEVENTF_KEYUP, 0);
            if(CurrentRow < NumberOfRows(TablePosition))
            {
                MoveRow (TablePosition, FindRowPositionByIndex(TablePosition, CurrentRow), CurrentRow+1);
                CurrentRow++;
                if (StartFromRow + TableHeight() < CurrentRow)
                    StartFromRow++;
                ShowTable(TablePosition, CurrentColumn, CurrentRow, StartFromColumn, StartFromRow);
            }
        }

        if(GetAsyncKeyState('A') && GetAsyncKeyState(VK_CONTROL))
        {
            keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
            keybd_event('A', 0, KEYEVENTF_KEYUP, 0);
            if(CurrentColumn > 1)
            {
                MoveColumn (TablePosition, FindColumnPositionByIndex(TablePosition, CurrentColumn), CurrentColumn-1);
                CurrentColumn--;
                if (StartFromColumn > CurrentColumn)
                    StartFromColumn = CurrentColumn;
                ShowTable(TablePosition, CurrentColumn, CurrentRow, StartFromColumn, StartFromRow);
            }
        }
        if(GetAsyncKeyState('D') && GetAsyncKeyState(VK_CONTROL))
        {
            keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
            keybd_event('D', 0, KEYEVENTF_KEYUP, 0);
            if(CurrentColumn < NumberOfColumns(TablePosition))
            {
                MoveColumn (TablePosition, FindColumnPositionByIndex(TablePosition, CurrentColumn), CurrentColumn+1);
                CurrentColumn++;
                StartFromColumn++;
                ShowTable(TablePosition, CurrentColumn, CurrentRow, StartFromColumn, StartFromRow);
            }
        }

        if(GetAsyncKeyState('E') && GetAsyncKeyState(VK_CONTROL))
        {
            keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
            keybd_event('E', 0, KEYEVENTF_KEYUP, 0);
            printf(TextNewValue);
            keybd_event(VK_ESCAPE, 0, 0, 0);               //press ESCAPE to clear line
            keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0); //release ESCAPE
            char inputedRowRecord[MaxCellTextLenght];
            fgets(inputedRowRecord, MaxCellTextLenght, stdin);
            fflush(stdin); // clear input stream
            inputedRowRecord[strlen(inputedRowRecord) - 1] = '\0';// remove Enter
            SetValue (TablePosition, FindRowPositionByIndex(TablePosition, CurrentRow), FindColumnPositionByIndex(TablePosition, CurrentColumn), inputedRowRecord);
            ShowTable(TablePosition, CurrentColumn, CurrentRow, StartFromColumn, StartFromRow);
        }
        if(GetAsyncKeyState('T') && GetAsyncKeyState(VK_CONTROL))
        {
            keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
            keybd_event('T', 0, KEYEVENTF_KEYUP, 0);
            printf(TextNewColumnName);
            keybd_event(VK_ESCAPE, 0, 0, 0);               //press ESCAPE to clear line
            keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0); //release ESCAPE
            char inputedColumnName[MaxColumnNameLenght];
            fgets(inputedColumnName, MaxColumnNameLenght, stdin);
            fflush(stdin); // clear input stream
            inputedColumnName[strlen(inputedColumnName) - 1] = '\0';// remove Enter
            RenameColumn (TablePosition, FindColumnPositionByIndex(TablePosition, CurrentColumn), inputedColumnName);
            ShowTable(TablePosition, CurrentColumn, CurrentRow, StartFromColumn, StartFromRow);
        }

        if(GetAsyncKeyState('X') && GetAsyncKeyState(VK_CONTROL))
        {
            keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
            keybd_event('X', 0, KEYEVENTF_KEYUP, 0);
            DeleteRow(TablePosition, FindRowPositionByIndex(TablePosition, CurrentRow));
            if (CurrentRow>1)
                CurrentRow--;
            if (StartFromRow > CurrentRow)
                StartFromRow = CurrentRow;
            ShowTable(TablePosition, CurrentColumn, CurrentRow, StartFromColumn, StartFromRow);
        }
        if(GetAsyncKeyState('R') && GetAsyncKeyState(VK_CONTROL))
        {
            keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
            keybd_event('R', 0, KEYEVENTF_KEYUP, 0);
            DeleteColumn(TablePosition, FindColumnPositionByIndex(TablePosition, CurrentColumn));
            if (CurrentColumn>1)
                CurrentColumn--;
            if (StartFromColumn> CurrentColumn)
                StartFromColumn = CurrentColumn;
            ShowTable(TablePosition, CurrentColumn, CurrentRow, StartFromColumn, StartFromRow);
        }
        if(GetAsyncKeyState('Z') && GetAsyncKeyState(VK_CONTROL))
        {
            keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
            keybd_event('Z', 0, KEYEVENTF_KEYUP, 0);
            keybd_event(VK_ESCAPE, 0, 0, 0);               //press ESCAPE to clear line
            keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0); //release ESCAPE
            break;
        }
    }

}


void ShowFilteredTable(int CurrentColumn, int CurrentRow, int StartFromColumn, int StartFromRow)
{
    int columnsWidth [MaxNumberOfColumns];
    for (int i = 0; i< MaxNumberOfColumns; i++)
    {
        columnsWidth[i] = FilteredTableColumnWidth(i);
    }
    system("cls");
    //print column names
    int currentTableWidth = 0;
    int currentNumberOfColumns = 0;
    for (int i = StartFromColumn; i< FilteredTableNumberOfColumns(); i++)
    {
        if (currentTableWidth+columnsWidth[i]>=ConsoleWidth)
            break;
        currentTableWidth+=columnsWidth[i]+1;
        currentNumberOfColumns++;
        char* format = TextRecordFormat(columnsWidth[i]);     // construct format of printing record
        printf(format, FilteredTable.Columns[i].Name);        // print formated record
    }
    printf("|\n");
    PrintLine('=',currentTableWidth+1);

    //print rows
    for (int r = StartFromRow; r<=StartFromRow+TableHeight(); r++)
    {
        int rowPos = FindFilteredTableRowPositionByIndex(r);
        if (rowPos<0)
            break;
        for (int i = 1; i<= currentNumberOfColumns; i++)
        {
            int pos = i+StartFromColumn-1;
            if (pos<0)
                break;
            if (FilteredTable.Columns[pos].Type == ValTEXT)
            {
                char* format = TextRecordFormat(columnsWidth[pos]);     // construct format of printing record
                printf(format, FilteredTable.Rows[rowPos].Records[pos].ValTEXT);        // print formated record
            }
            else if (FilteredTable.Columns[pos].Type == ValNUM)
            {
                char* format = NumRecordFormat(columnsWidth[pos]);     // construct format of printing record
                printf(format, FilteredTable.Rows[rowPos].Records[pos].ValNUM);        // print formated record
            }
        }
        printf("|\n");
    }
    PrintLine('=',currentTableWidth+1);
    printf(TextViewTableTips);
}

void DisplayFilteredTable()
{
    int CurrentRow = 1;
    int CurrentColumn = 0;
    int StartFromColumn = 0;
    int StartFromRow = 1;

    ShowFilteredTable(CurrentColumn, CurrentRow, StartFromColumn, StartFromRow);
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
                ShowFilteredTable(CurrentColumn, CurrentRow, StartFromColumn, StartFromRow);
            }
        }
        if(GetAsyncKeyState(VK_DOWN))
        {
            keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);
            if(CurrentRow < FilteredTableNumberOfRows())
            {
                CurrentRow++;
                StartFromRow++;
                ShowFilteredTable(CurrentColumn, CurrentRow, StartFromColumn, StartFromRow);
            }
        }

        if(GetAsyncKeyState(VK_LEFT))
        {
            keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
            if(CurrentColumn > 0)
            {
                CurrentColumn--;
                if (StartFromColumn > CurrentColumn)
                    StartFromColumn = CurrentColumn;
                ShowFilteredTable(CurrentColumn, CurrentRow, StartFromColumn, StartFromRow);
            }
        }
        if(GetAsyncKeyState(VK_RIGHT))
        {
            keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0);
            if(CurrentColumn < FilteredTableNumberOfColumns()-1)
            {
                CurrentColumn++;
                StartFromColumn++;
                ShowFilteredTable(CurrentColumn, CurrentRow, StartFromColumn, StartFromRow);
            }
        }

        if(GetAsyncKeyState('Z') && GetAsyncKeyState(VK_CONTROL))
        {
            keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
            keybd_event('Z', 0, KEYEVENTF_KEYUP, 0);
            keybd_event(VK_ESCAPE, 0, 0, 0);               //press ESCAPE to clear line
            keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0); //release ESCAPE
            break;
        }
    }

}
