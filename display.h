#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

int ConsoleWidth;
int ConsoleHeight;
int TableHeight();

void PrintLine(char Symbol, int Lenght);
const char* TextRecordFormat(int Lenght);
const char* NumRecordFormat(int Lenght);

int ColumnWidth(int TablePosition, int ColumnPosition);
int FilteredTableColumnWidth(int ColumnPosition);
void ShowTable(int TablePosition, int CurrentColumn, int CurrentRow, int StartFromColumn, int StartFromRow);
void EditTable(int TablePosition);
void ShowFilteredTable(int CurrentColumn, int CurrentRow, int StartFromColumn, int StartFromRow);
void DisplayFilteredTable();

#endif // DISPLAY_H_INCLUDED
