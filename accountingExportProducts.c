#include "accountingExportProducts.h"

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

ProductInfo products[MAX_PRODUCTS];

void plug(char s[50]) {
    puts(s);
    puts("В данный момент нет функции чтения из файла, нажмите Enter для продолжения\n");
    // Сейчас, чтобы сразу не выскакивала табличка
    getch();
}

void writeInId(const char *str, const int id_of_prod) {
    char *endPtr;
    products[id_of_prod].id = strtol(str, &endPtr, 10);
    printf("\n%d\n", products[id_of_prod].id);
    // end
}

void splitInfo(const char *str) {
    int type_of_convert = 0;
    int count_of_prods = 0;
    char record[strlen(str)];
    int j = 0;
    for (int i = 0; i < strlen(str); i++) {
        record[j] = str[i];
        if (str[i] == ';') {
            record[i] = '\0';
            switch (type_of_convert) {
                case 0:
                    writeInId(record, count_of_prods);
                    break;
                default:
                    printf("\n%s\n", record);
                    break;
            }
            type_of_convert++;
            strcpy(record, "");
            j = 0;
        }
        else if (str[i] == '\n') {
            count_of_prods++;
            type_of_convert = 0;
            strcpy(record, "");
        }
        else {
            j++;
        }
    }
}

void menuReadFromFile(const char *filename) {
    // plug("Чтение из файла");
    FILE* in = fopen(filename, "r");
    if (in == NULL) {
        fclose(in);
        return;
    }
    fseek(in, 0, SEEK_END);

    const int capacity = ftell(in);
    char buff[capacity + 1];
    fseek(in, 0, SEEK_SET);






    int ch;
    int i = 0;
    while ((ch = fgetc(in)) != EOF) {

        buff[i++] = (char)ch;
    }
    buff[i] = '\0';
    splitInfo(buff);
    fclose(in);

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
