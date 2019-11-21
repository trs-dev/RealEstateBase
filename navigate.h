#ifndef NAVIGATE_H_INCLUDED
#define NAVIGATE_H_INCLUDED


int NavigateMenu();

int MenuIndex; //index of selected menu item
int SelectedTableIndex; //index of selected table

// navigation
enum NavigationPages {PageChangeLanguage, PageOperationsWithTables, PageSelectTable, PageAddTable, PageOperationsWithSingleTable,
PageRenameTable, PageMoveTable, PageAddColumn, PageAddRow
};
int Page;

char* DatabaseName;

int Navigate();





#endif // NAVIGATE_H_INCLUDED
