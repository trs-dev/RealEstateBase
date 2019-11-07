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
TextWelcome = "Доброго дня! Вітаємо в базі нерухомого майна.";
TextChangeLanguage = "Choose your language: \n 1 - English\n 2 - Ukrainian\n 3 - Exit: ";
TextOperationsWithTables = "Операції з таблицями: \n 1 - Показати список таблиць і вибрати таблицю \n 2 - Створити таблицю \n 3 - Вихід: ";



TextInputError = "Команда не розпізнана. Повторіть спробу.";
TextTooManyInputErrors = "Забагато помилок вводу. Натисніть будь-яку клавішу для виходу.";











}
