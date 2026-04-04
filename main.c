/*
 * Точка входа
 * Интерактивное меню
*/

#include <stdio.h>
#include <windows.h>
#include "accountingExportProducts.h"


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
                menuReadFromFile();
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
                menuDeleteRecord();
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

