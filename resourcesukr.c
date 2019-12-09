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
TextWelcome = "Доброго дня! Вітаємо в базі нерухомого майна.\n";

TextOperationsWithTables = "Операції з таблицями: \n 1 - Показати список таблиць і вибрати таблицю \n 2 - Створити таблицю \n 3 – Виконати вибірку з бази даних (SELECT) \n 0 - Вихід:\n";
TextOperationsWithSingleTable = "Операції з таблицею [%s]: \n 1 - Відобразити вміст таблиці\n 2 – Додати рядок \n 3 - Перейменувати таблицю \n 4 - Перемістити таблицю \n 5 – Додати колонку \n 6 - Видалити таблицю \n 0 - Назад:\n";

TextEditTableTips = " Користуйтеся стрілками для навігації; Ctrl + E – Редагувати поле; Ctrl + X – Видалити рядок; \n Ctrl + WASD – Перемістити стовпчики і рядки; Ctrl + T – Перейменувати колонку; Ctrl + R – Видалити колонку; \n Ctrl + Z - Назад.\n";
TextViewTableTips = " Користуйтеся стрілками для навігації;\n Ctrl + Z - Назад.\n";

TextTableName = "Назва таблиці: ";
TextColumnNames = "Колонки таблиці (через кому): ";
TextColumnName = "Назва стовпця: ";
TextRowRecords= "Введіть дані записів (через кому): ";
TextNewValue = "Введіть нове значення: ";
TextNewColumnName = "Введіть нову назву стовпця: ";
TextEnterSelectCommand = "Введіть команду вибору (SELECT). \nВигляд: SELECT Стовпець1, Стовпець2... чи * FROM Таблиця1 JOIN Таблиця2 ON СтовпецьТаблиці1 = СтовпецьТаблиці2 \n        WHERE Стовпець1><= Значення1 AND Стовпець2 ><= Значення2 ORDER BY Стовпець1 ASC/DESC, Стовпець2 ASC/DESC, ...\n";

TextRenamingTable = "Перейменування таблиці [%s]\n";
TextNewName = "Нова назва: ";
TextMovingTable = "Переміщення таблиці [%s]\n (0 - Назад)\n Нова позиція:";

TextSelectTable = "Введіть номер таблиці для її вибору: ";
TextNoTablesInDB = "В базі даних таблиці відсутні.\n";

TextCreateTableSuccess = "Таблицю [%s] успішно створено.\n";
TextDeleteTableSuccess = "Таблицю [%s] успішно видалено.\n";
TextRenameTableSuccess = "Таблицю [%s] перейменовано в [%s].\n";

TextNoColumnsInTable = "В таблиці відсутні стовпці.\n";
TextTooManyColumns = "В таблиці створено максимальну кількість колонок.\n";

TextCreateColumnSuccess = "Колонку [%s] успішно створено.\n";
TextDeleteColumnSuccess = "Колонку [%s] успішно видалено.\n";
TextRenameColumnSuccess = "Колонку [%s] перейменовано в [%s].\n";

TextTooManyRows = "В таблиці створено максимальну кількість рядків.\n";
TextCreateRowSuccess = "Новий рядок успішно створено.\n";
TextDeleteRowSuccess = "Рядок № [%d] видалено.\n";

TextOpenFileError = "Помилка відкриття файлу";

TextReturn = "Назад";

TextInputError = "Команда не розпізнана. Повторіть спробу.\n";
TextTooManyInputErrors = "Забагато помилок вводу. Натисніть будь-яку клавішу для виходу.\n";

TextTooManyTables = "В базі даних досягнуто максимальної кількості таблиць. Видаліть непотрібну таблицю і спробуйте ще раз.\n";
}
