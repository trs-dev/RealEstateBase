#include <stdio.h>
#include <stdlib.h>
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
TextChangeLanguage = "Choose your language: \n 1 - English\n 2 - Ukrainian\n 3 - Exit:\n";
TextOperationsWithTables = "�������� � ���������: \n 1 - �������� ������ ������� � ������� ������� \n 2 - �������� ������� \n 3 - �����:\n";

TextTableName = "����� �������: ";
TextColumnNames = "������� �������: ";

TextCreateTableSuccess = "������� [%s] ������ ��������.\n";

TextInputError = "������� �� ���������. �������� ������.\n";
TextTooManyInputErrors = "�������� ������� �����. ��������� ����-��� ������ ��� ������.\n";

TextTooManyTables = "� ��� ����� ��������� ����������� ������� �������. ������� ��������� ������� � ��������� �� ���.\n";









}
