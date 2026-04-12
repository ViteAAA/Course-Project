/*
 * Точка входа
 * Интерактивное меню
*/

#include <stdio.h>
#include <windows.h>
#include "accountingExportProducts.h"

char filename[MAX_LENGTH_PRODUCT_NAME + 3];

void inputFilename() {
    strcpy(filename, "../");
    char non_formated_filename[MAX_LENGTH_NAME];
    printf("Введите имя файла: ");
    scanf("%s", non_formated_filename);
    strcat(filename, non_formated_filename);
}

void menuPrintOptions() {
    HANDLE *const hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10);
    printf("Выберите пункт меню:\n");
    SetConsoleTextAttribute(hConsole, 15);
    printf("0. Выход\n");
    printf("1. Чтение из файла\n");
    printf("2. Вывод таблицы\n");
    printf("3. Добавление записи\n");
    printf("4. Изменение записи\n");
    printf("5. Удаление записи\n");
    printf("6. Вычисление и вывод статистики\n");
    printf("7. Сохранение в файл\n");
}

void dialogDeleteRecord() {
    printf("Введите номер записи для удаления: ");
    int recordNumber;
    scanf("%d", &recordNumber);
    menuDeleteRecord(recordNumber - 1);
}

void dialogReadFromFile() {
    inputFilename();
    menuReadFromFile(filename);
}


int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    // Вывод пунктов меню
    // Ожидаем ввод пункта меню
    // Определить, какой тип меню выбран
    int choice = -1;


    while (choice != 0) {
        menuPrintOptions();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                dialogReadFromFile();
                break;
            case 2:
                menuPrintTable();
                break;
            case 3:
                menuAddRecord();
                break;
            case 4:
                menuUpdateRecord();
                break;
            case 5:
                dialogDeleteRecord();
                break;
            case 6:
                menuCalcStatistics();
                break;
            case 7:
                menuSaveToFile();
                break;
            default:
                break;
        }
        printf("\n\n");
    }

    return 0;
}

