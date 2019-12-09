#include <locale.h>
#include "windows.h"
#include "resources.h"

void CommandLineParametersUKR() //Command Line Parameters for current language
{
    setlocale(LC_CTYPE, "ukr");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}
void TranslateToUKR() //
{
TextWelcome = "������� ���! ³���� � ��� ���������� �����.\n";

TextOperationsWithTables = "�������� � ���������: \n 1 - �������� ������ ������� � ������� ������� \n 2 - �������� ������� \n 3 � �������� ������ � ���� ����� (SELECT) \n 0 - �����:\n";
TextOperationsWithSingleTable = "�������� � �������� [%s]: \n 1 - ³��������� ���� �������\n 2 � ������ ����� \n 3 - ������������� ������� \n 4 - ���������� ������� \n 5 � ������ ������� \n 6 - �������� ������� \n 0 - �����:\n";

TextEditTableTips = " ������������ �������� ��� ��������; Ctrl + E � ���������� ����; Ctrl + X � �������� �����; \n Ctrl + WASD � ���������� ��������� � �����; Ctrl + T � ������������� �������; Ctrl + R � �������� �������; \n Ctrl + Z - �����.\n";
TextViewTableTips = " ������������ �������� ��� ��������;\n Ctrl + Z - �����.\n";

TextTableName = "����� �������: ";
TextColumnNames = "������� ������� (����� ����): ";
TextColumnName = "����� �������: ";
TextRowRecords= "������ ��� ������ (����� ����): ";
TextNewValue = "������ ���� ��������: ";
TextNewColumnName = "������ ���� ����� �������: ";
TextEnterSelectCommand = "������ ������� ������ (SELECT). \n������: SELECT ��������1, ��������2... �� * FROM �������1 JOIN �������2 ON ���������������1 = ���������������2 \n        WHERE ��������1><= ��������1 AND ��������2 ><= ��������2 ORDER BY ��������1 ASC/DESC, ��������2 ASC/DESC, ...\n";

TextRenamingTable = "�������������� ������� [%s]\n";
TextNewName = "���� �����: ";
TextMovingTable = "���������� ������� [%s]\n (0 - �����)\n ���� �������:";

TextSelectTable = "������ ����� ������� ��� �� ������: ";
TextNoTablesInDB = "� ��� ����� ������� ������.\n";

TextCreateTableSuccess = "������� [%s] ������ ��������.\n";
TextDeleteTableSuccess = "������� [%s] ������ ��������.\n";
TextRenameTableSuccess = "������� [%s] ������������� � [%s].\n";

TextNoColumnsInTable = "� ������� ������ �������.\n";
TextTooManyColumns = "� ������� �������� ����������� ������� �������.\n";

TextCreateColumnSuccess = "������� [%s] ������ ��������.\n";
TextDeleteColumnSuccess = "������� [%s] ������ ��������.\n";
TextRenameColumnSuccess = "������� [%s] ������������� � [%s].\n";

TextTooManyRows = "� ������� �������� ����������� ������� �����.\n";
TextCreateRowSuccess = "����� ����� ������ ��������.\n";
TextDeleteRowSuccess = "����� � [%d] ��������.\n";

TextOpenFileError = "������� �������� �����";

TextReturn = "�����";

TextInputError = "������� �� ���������. �������� ������.\n";
TextTooManyInputErrors = "�������� ������� �����. �������� ����-��� ������ ��� ������.\n";

TextTooManyTables = "� ��� ����� ��������� ����������� ������� �������. ������� ��������� ������� � ��������� �� ���.\n";
}
