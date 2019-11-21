#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "resources.h"
#include "resourcesukr.h"
#include "tablesdefinition.h"
#include "commands.h"
#include "navigate.h"

int main()
{

    printf("%s\n", TextWelcome);
    Navigate();



            //test
            /*
   printf("CanCreateTable %d\n", CanCreateTable());
   printf("NumberOfTables %d\n", NumberOfTables());

    for (int i = 0; i<5; i++)
    strcpy(Tables[i].Name, "test");

    printf("%s\n", Tables[0].Name);

    CreateTable("Table # 2", "tt");

   printf("CanCreateTable %d\n", CanCreateTable());
   printf("NumberOfTables %d\n", NumberOfTables());

    SaveDB("newDB.dat");




    printf("All are done!\n");*/

    return 0;
}
