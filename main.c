#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "resources.h"
#include "resourcesukr.h"
#include "tablesdefinition.h"
#include "commands.h"




int MenuIndex; //index of selected menu item
int SelectedTableIndex; //index of selected table

// navigation
enum NavigationPages {PageChangeLanguage, PageOperationsWithTables, PageSelectTable, PageAddTable, PageOperationsWithSingleTable};
int Page = PageChangeLanguage;

char* DatabaseName = "DatabaseENG.dat";



int ShowNavigationMenu (char* DisplayedText, int NumberOfVariants, char* AdditionalData)
{
    int Variant = -1;
    printf(DisplayedText, AdditionalData);

    for (int ind = 1; ind <= 10; ind++)
    {
        Variant = 0;
        char InputedText[200];
        printf(" >>> ");
        fgets(InputedText, 2, stdin);
        fflush(stdin); // clear input stream
        if(isdigit(InputedText[0]))
        {
            Variant = atoi(InputedText);
        }
         // debug output
         /*
        printf("You enter: %d\n", InputedText);
        printf("Variant: %d\n", Variant);
        printf("isdigit: %d\n", isdigit(InputedText[0]));
        printf("Variant > 0: %d\n", Variant > 0);
        printf("Variant <= NumberOfVariants: %d\n", Variant <= NumberOfVariants);
        */

        if (Variant >= 0 && Variant <= NumberOfVariants) //if all is ok
            return Variant;

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


int Navigate ()
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


        }




    }
    return 0;
}


int ShowPageChangeLanguage()
{
    MenuIndex = ShowNavigationMenu(TextChangeLanguage, 2, "");

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
    MenuIndex = ShowNavigationMenu(TextOperationsWithTables, 2, "");

    switch(MenuIndex)
    {
    case 1:
        Page = PageSelectTable;
        break;
    case 2:
        Page = PageAddTable;
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
    char InputedTableName[MaxTableNameLenght];
    fgets(InputedTableName, MaxTableNameLenght, stdin);
    fflush(stdin); // clear input stream

    printf(TextColumnNames);
    char InputedColumnNames[MaxTableNameLenght];
    fgets(InputedColumnNames, MaxTableNameLenght, stdin);
    fflush(stdin); // clear input stream


    // remove Enter
    InputedTableName[strlen(InputedTableName) - 1] = '\0';
    InputedColumnNames[strlen(InputedColumnNames) - 1] = '\0';

    CreateTable(InputedTableName, InputedColumnNames);

    Page = PageOperationsWithTables;
    return 0;
}

int ShowPageSelectTable()
{
    int NumberOfTablesLocal = NumberOfTables();
    printf("-----------------------------------------------------------------------\n");
        if (NumberOfTablesLocal == 0)
        {
            printf(TextNoTablesInDB);
        }
        else
        {
            for (int i = 1; i <= NumberOfTablesLocal; i++)
            {
                int TablePosition = FindTablePositionByIndex(i);
                printf("%d -> %s\n", Tables[TablePosition].Index, Tables[TablePosition].Name);
            }
        }

    printf("-----------------------------------------------------------------------\n");
    printf("0 -> %s\n", TextReturn);


    MenuIndex = ShowNavigationMenu(TextSelectTable, NumberOfTablesLocal, "");

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
    MenuIndex = ShowNavigationMenu(TextOperationsWithSingleTable, 3, Tables[FindTablePositionByIndex(SelectedTableIndex)].Name);

    switch(MenuIndex)
    {
    case 1:

        break;
    case 2:

        break;
    case 3:
        DeleteTable(FindTablePositionByIndex(SelectedTableIndex));
        Page = PageOperationsWithTables;
        break;
    case 0:
        Page = PageOperationsWithTables;
        break;
    }
    return 0;
}



























int main()
{

    printf("%s\n", TextWelcome);
    Navigate();



            //test
   printf("CanCreateTable %d\n", CanCreateTable());
   printf("NumberOfTables %d\n", NumberOfTables());

    for (int i = 0; i<5; i++)
    strcpy(Tables[i].Name, "test");

    printf("%s\n", Tables[0].Name);

    CreateTable("Table # 2", "tt");

   printf("CanCreateTable %d\n", CanCreateTable());
   printf("NumberOfTables %d\n", NumberOfTables());

    SaveDB("newDB.dat");




    printf("All are done!\n");

    return 0;
}
