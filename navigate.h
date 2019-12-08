#ifndef NAVIGATE_H_INCLUDED
#define NAVIGATE_H_INCLUDED

int NavigateMenu();
int SelectedTableIndex; //index of selected table

// navigation
enum NavigationPages {PageChangeLanguage, PageOperationsWithTables, PageSelectTable, PageAddTable, PageOperationsWithSingleTable,
PageRenameTable, PageMoveTable, PageAddColumn, PageAddRow
};
enum NavigationPages Page;
char* DatabaseName;
int Navigate();

#endif // NAVIGATE_H_INCLUDED
