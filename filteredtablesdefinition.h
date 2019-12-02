#ifndef FILTEREDTABLEDEFINITION_H_INCLUDED
#define FILTEREDTABLEDEFINITION_H_INCLUDED

struct Table FilteredTable; //Filtered Table to display

int FilteredTableNumberOfColumns();
int FilteredTableNumberOfRows();
int FindFilteredTableColumnPositionByIndex (int ColumnIndex);
int FindFilteredTableColumnPositionByName (char ColumnName[MaxColumnNameLenght]);
int FindFilteredTableRowPositionByIndex (int RowIndex);

#endif // FILTEREDTABLEDEFINITION_H_INCLUDED

