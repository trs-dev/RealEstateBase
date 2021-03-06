#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "resources.h"
#include "resourcesukr.h"
#include "tablesdefinition.h"
#include "commands.h"
#include "navigate.h"

int SelectedTableIndex; //index of selected table
enum NavigationPages Page = PageChangeLanguage;
char* DatabaseName = "DatabaseENG.dat";


int ShowNavigationMenu (char* DisplayedText, int NumberOfVariants, char* AdditionalData)
{
    int variant = -1;
    printf(DisplayedText, AdditionalData);

    for (int ind = 1; ind <= 10; ind++)
    {
        char inputedText[200];
        printf(" >>> ");
        fgets(inputedText, 2, stdin);
        fflush(stdin); // clear input stream
        if(isdigit(inputedText[0]))
        {
            variant = atoi(inputedText);
        }
        if (variant >= 0 && variant <= NumberOfVariants) //if all is ok
            return variant;

        if (ind==10) // if there are Too Many Input Errors
        {
            printf(TextTooManyInputErrors);
            getchar();
            exit(0);
        }

        // try once more
        printf(TextInputError);
        printf(DisplayedText, AdditionalData);
    }
    return 0;
}


int Navigate () // Navigation function. Otherwise ShowPage functions will newer end.
{
    while (1)
    {
        switch(Page)
        {
        case PageChangeLanguage:
            ShowPageChangeLanguage();
            break;
        case PageOperationsWithTables:
            ShowPageOperationsWithTables();
            break;
        case PageSelectTable:
            ShowPageSelectTable();
            break;
        case PageAddTable:
            ShowPageAddTable();
            break;
        case PageOperationsWithSingleTable:
            ShowPageOperationsWithSingleTable();
            break;
        case PageRenameTable:
            ShowPageRenameTable();
            break;
        case PageMoveTable:
            ShowPageMoveTable();
            break;
        case PageAddColumn:
            ShowPageAddColumn();
            break;
        case PageAddRow:
            ShowPageAddRow();
            break;
        }
    }
    return 0;
}


int PrintListOfTables()
{
        int numberOfTablesLocal = NumberOfTables();
    printf("-----------------------------------------------------------------------\n");
        if (numberOfTablesLocal == 0)
        {
            printf(TextNoTablesInDB);
        }
        else
        {
            for (int i = 1; i <= numberOfTablesLocal; i++)
            {
                int tablePosition = FindTablePositionByIndex(i);
                printf("%d -> %s\n", Tables[tablePosition].Index, Tables[tablePosition].Name);
            }
        }
    printf("-----------------------------------------------------------------------\n");

    return 0;
}

int ShowPageChangeLanguage()
{
    int MenuIndex = ShowNavigationMenu(TextChangeLanguage, 2, "");

    switch(MenuIndex)
    {
    case 1:
        Page = PageOperationsWithTables;
        OpenDB(DatabaseName);
        break;
    case 2:
        CommandLineParametersUKR();
        TranslateToUKR();
        printf(TextWelcome);
        Page = PageOperationsWithTables;
        DatabaseName = "DatabaseUKR.dat";
        OpenDB(DatabaseName);
        break;
    case 0:
        exit(0);
    }
    return 0;
}

int ShowPageOperationsWithTables()
{
    int MenuIndex = ShowNavigationMenu(TextOperationsWithTables, 3, "");

    switch(MenuIndex)
    {
    case 1:
        Page = PageSelectTable;
        break;
    case 2:
        Page = PageAddTable;
        break;
    case 3:
        printf(TextEnterSelectCommand);
        char inputedCommand[500];
        fgets(inputedCommand, 500, stdin);
        fflush(stdin); // clear input stream

        inputedCommand[strlen(inputedCommand) - 1] = '\0';// remove Enter
        ParseCommand(inputedCommand);
        DisplayFilteredTable();
        break;
    case 0:
        SaveDB(DatabaseName);
        exit(0);
    }
    return 0;
}

int ShowPageAddTable()
{
    printf(TextTableName);
    char inputedTableName[MaxTableNameLenght];
    fgets(inputedTableName, MaxTableNameLenght, stdin);
    fflush(stdin); // clear input stream

    printf(TextColumnNames);
    char inputedColumnNames[MaxColumnNameLenght*MaxNumberOfColumns+MaxNumberOfColumns];
    fgets(inputedColumnNames, MaxColumnNameLenght*MaxNumberOfColumns+MaxNumberOfColumns, stdin);
    fflush(stdin); // clear input stream

    // remove Enter
    inputedTableName[strlen(inputedTableName) - 1] = '\0';
    inputedColumnNames[strlen(inputedColumnNames) - 1] = '\0';

    CreateTable(inputedTableName, inputedColumnNames);

    Page = PageOperationsWithTables;
    return 0;
}


int ShowPageSelectTable()
{
    PrintListOfTables();

    printf("0 -> %s\n", TextReturn);
    int MenuIndex = ShowNavigationMenu(TextSelectTable, NumberOfTables(), "");

    if (MenuIndex>0)
    {
       SelectedTableIndex = MenuIndex;
       Page = PageOperationsWithSingleTable;
    }
    else
        Page = PageOperationsWithTables;
    return 0;
}

int ShowPageOperationsWithSingleTable()
{
    int MenuIndex = ShowNavigationMenu(TextOperationsWithSingleTable, 6, Tables[FindTablePositionByIndex(SelectedTableIndex)].Name);

    switch(MenuIndex)
    {
    case 1:
        EditTable(FindTablePositionByIndex(SelectedTableIndex));
        break;
    case 2:
        //add row
        Page = PageAddRow;
        break;
    case 3:
        Page = PageRenameTable;
        break;
    case 4:
        Page = PageMoveTable;
        break;
    case 5:
        Page = PageAddColumn;
        break;
    case 6:
        DeleteTable(FindTablePositionByIndex(SelectedTableIndex));
        Page = PageOperationsWithTables;
        break;
    case 0:
        Page = PageOperationsWithTables;
        break;
    }
    return 0;
}

int ShowPageRenameTable()
{
    printf(TextRenamingTable, Tables[FindTablePositionByIndex(SelectedTableIndex)].Name);
    printf(TextNewName);

    char inputedTableName[MaxTableNameLenght];
    fgets(inputedTableName, MaxTableNameLenght, stdin);
    fflush(stdin); // clear input stream

    // remove Enter
    inputedTableName[strlen(inputedTableName) - 1] = '\0';

    RenameTable(FindTablePositionByIndex(SelectedTableIndex),inputedTableName);

    Page = PageOperationsWithSingleTable;
    return 0;
}


int ShowPageMoveTable()
{
    int newTableIndex = ShowNavigationMenu(TextMovingTable, NumberOfTables(), Tables[FindTablePositionByIndex(SelectedTableIndex)].Name);

    if (newTableIndex > 0)
    {
        MoveTable(FindTablePositionByIndex(SelectedTableIndex), newTableIndex);
    }

    Page = PageOperationsWithSingleTable;
    return 0;
}

int ShowPageAddColumn()
{
    printf(TextColumnName);
    char inputedColumnNames[MaxColumnNameLenght];
    fgets(inputedColumnNames, MaxColumnNameLenght, stdin);
    fflush(stdin); // clear input stream

    // remove Enter
    inputedColumnNames[strlen(inputedColumnNames) - 1] = '\0';

    AddColumn(FindTablePositionByIndex(SelectedTableIndex), inputedColumnNames);

    Page = PageOperationsWithSingleTable;
    return 0;
}

int ShowPageAddRow()
{
    printf(TextRowRecords);
    char inputedRowRecords[MaxCellTextLenght*MaxNumberOfColumns+MaxNumberOfColumns];
    fgets(inputedRowRecords, MaxCellTextLenght*MaxNumberOfColumns+MaxNumberOfColumns, stdin);
    fflush(stdin); // clear input stream

    // remove Enter
    inputedRowRecords[strlen(inputedRowRecords) - 1] = '\0';

    AddRow(FindTablePositionByIndex(SelectedTableIndex), inputedRowRecords);

    Page = PageOperationsWithSingleTable;
    return 0;
}
