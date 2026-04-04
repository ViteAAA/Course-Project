#include "accountingExportProducts.h"

#include <stdio.h>
#include <conio.h>

void plug(char s[50]) {
    puts(s);
    puts("В данный момент нет функции чтения из файла, нажмите Enter для продолжения\n");
    // Сейчас, чтобы сразу не выскакивала табличка
    getch();
}

void menuReadFromFile() {
    plug("Чтение из файла");
};
void menuPrintTable() {
    plug("Вывод таблицы");
};
void menuAddRecord() {
    plug("Добавление записи");
};
void menuUpdateRecord() {
    plug("Обновление записи");
};
void menuDeleteRecord() {
    plug("Удаление записи");
};
void menuCalcStatistics() {
    plug("Статистика");
};
void menuSaveToFile() {
    plug("Сохранение в файл");
};
