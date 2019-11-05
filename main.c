#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "resources.h"
#include "resourcesukr.h"
#include "tablesdefinition.c"
#include "commands.h"



struct Table Tables;

int MenuIndex; //index of selected menu item




int ShowNavigationMenu (char* DisplayedText, int NumberOfVariants)
{
    int Variant = 0;
    printf("%s\n", DisplayedText);

    for (int ind = 1; ind <= 10; ind++)
    {
        Variant = 0;
        char InputedText[2];
        fgets(InputedText, 2, stdin);
        fflush(stdin); // clear input stream
        if(isdigit(InputedText[0]))
        {
            Variant = atoi(InputedText);
        }
         // debug commands
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
            printf("\n%s\n", TextTooManyInputErrors);
            getchar();
            exit(0);
        }

        // try once more
        printf("\n%s\n", TextInputError);
        printf("%s\n", DisplayedText);
    }


    return 0;
}


int main()
{
    printf("%s\n", TextWelcome);
    MenuIndex = ShowNavigationMenu(TextChangeLanguage, 3);

    switch(MenuIndex)
    {
    case 1:
        break;
    case 2:
        CommandLineParametersUKR();
        TranslateToUKR();
        printf("%s\n", TextWelcome);
        break;
    case 3:
        exit(0);
    }




    strcpy(Tables.name, "test");

    printf("%s\n", Tables.name);












    printf("All are done!\n");

    return 0;
}
