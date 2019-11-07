#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "resources.h"
#include "resourcesukr.h"
#include "tablesdefinition.h"
#include "commands.h"




int MenuIndex; //index of selected menu item
enum NavigationPages {PageChangeLanguage, PageOperationsWithTables, PageAddTable};
int Page = PageChangeLanguage;


int ShowNavigationMenu (char* DisplayedText, int NumberOfVariants)
{
    int Variant = 0;
    printf(DisplayedText);

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

        if (Variant > 0 && Variant <= NumberOfVariants) //if all is ok
            return Variant;

        if (ind==10) // if there are Too Many Input Errors
        {
            printf(TextTooManyInputErrors);
            getchar();
            exit(0);
        }

        // try once more
        printf(TextInputError);
        printf(DisplayedText);
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
        case PageAddTable:
            ShowPageAddTable();
            break;


        }




    }
    return 0;
}


int ShowPageChangeLanguage()
{
    MenuIndex = ShowNavigationMenu(TextChangeLanguage, 3);

    switch(MenuIndex)
    {
    case 1:
        Page = PageOperationsWithTables;
        break;
    case 2:
        CommandLineParametersUKR();
        TranslateToUKR();
        printf(TextWelcome);
        Page = PageOperationsWithTables;
        break;
    case 3:
        exit(0);
    }
}

int ShowPageOperationsWithTables()
{
    MenuIndex = ShowNavigationMenu(TextOperationsWithTables, 3);

    switch(MenuIndex)
    {
    case 1:
        break;
    case 2:
        Page = PageAddTable;
        break;
    case 3:
        exit(0);
    }
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
}



int main()
{
    printf("%s\n", TextWelcome);
    Navigate();



            //test
   printf("CanCreateTable %d\n", CanCreateTable());
   printf("NumberOfTables %d\n", NumberOfTables());

    for (int i = 0; i<5; i++)
    strcpy(Tables[i].name, "test");

    printf("%s\n", Tables[0].name);

    CreateTable("Table # 2", "tt");

   printf("CanCreateTable %d\n", CanCreateTable());
   printf("NumberOfTables %d\n", NumberOfTables());






    printf("All are done!\n");

    return 0;
}
