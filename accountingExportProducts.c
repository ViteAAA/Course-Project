#include "accountingExportProducts.h"

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

ProductInfo products[MAX_PRODUCTS];
int productsCount;

void outputInConsole() {
    for (int i = 0; i < productsCount; i++) {
        printf("{\n");
        printf("  \"id\": %d,\n", products[i].id);
        printf("  \"date\": {\n");
        // Здесь я предположил стандартные поля для даты, подставь свои, если они другие
        printf("    \"day\": %d,\n", products[i].date.day);
        printf("    \"month\": %d,\n", products[i].date.month);
        printf("    \"year\": %d\n", products[i].date.year);
        printf("  },\n");
        printf("  \"companyName\": \"%s\",\n", products[i].companyName);
        printf("  \"productName\": \"%s\",\n", products[i].productName);
        printf("  \"productionCount\": %.2f,\n", products[i].productionCount);
        printf("  \"exportCount\": %.2f,\n", products[i].exportCount);
        printf("  \"percentOfExport\": %.2f\n", products[i].percentOfExport);
        printf("}\n");
    }
}


void plug(char s[50]) {
    puts(s);
    puts("В данный момент нет функции чтения из файла, нажмите Enter для продолжения\n");
    // Сейчас, чтобы сразу не выскакивала табличка
    getch();
}

/**
 * @brief Function to add a id
*/
void writeInId(const char *str, const int id_of_prod) {
    char *endPtr;
    products[id_of_prod].id = strtol(str, &endPtr, 10);
    // printf("\n%d\n", products[id_of_prod].id);
    // end
}

/**
 * @brief Function to add a date
*/
void writeInDate(const char *str, const int id_of_prod) {
    char *endPtr;
    products[id_of_prod].date.day = strtol(str, &endPtr, 10);
    str += 2;
    products[id_of_prod].date.month = strtol(str, &endPtr, 10);
    str += 2;
    products[id_of_prod].date.year = strtol(str, &endPtr, 10);
}

/**
 * @brief Function to add a company name
*/
void writeInCompanyName(const char *str, const int id_of_prod) {
    strcpy(products[id_of_prod].companyName, str);
}

/**
 * @brief Function to add a product name
*/
void writeInProductName(const char *str, const int id_of_prod) {
    strcpy(products[id_of_prod].productName, str);
}

/**
 * @brief Function to add a production count
*/
void writeInProductionCount(const char *str, const int id_of_prod) {
    char *endPtr;
    products[id_of_prod].productionCount = strtof(str, &endPtr);
}

/**
 * @brief Function to add an export count
*/
void writeInExportCount(const char *str, const int id_of_prod) {
    char *endPtr;
    products[id_of_prod].exportCount = strtof(str, &endPtr);
}

/**
 * @brief Function to add a percent of export
*/
void writeInPercentOfExport(const int id_of_prod) {
    products[id_of_prod].percentOfExport = products[id_of_prod].exportCount / products[id_of_prod].productionCount * 100;
}

/**
 * @brief Function to split info into a struct
*/
void splitInfo(const char *str) {
    int type_of_convert = 0;
    int count_of_prods = 0;
    char record[strlen(str)];
    int j = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == ';') {
            record[j] = '\0';
            switch (type_of_convert) {
                case 0:
                    writeInId(record, count_of_prods);
                    break;
                case 1:
                    writeInDate(record, count_of_prods);
                    break;
                case 2:
                    writeInCompanyName(record, count_of_prods);
                    break;
                case 3:
                    writeInProductName(record, count_of_prods);
                    break;
                case 4:
                    writeInProductionCount(record, count_of_prods);
                    break;
                case 5:
                    writeInExportCount(record, count_of_prods);
                    writeInPercentOfExport(count_of_prods);
                    break;
                default:
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
            record[j] = str[i];
            j++;
        }
    }
    productsCount = count_of_prods - 1;
    outputInConsole();
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
    if (products[0].id == 0) {
        puts("Таблица пуста");
        return;
    }
    // Печатаем заголовок таблицы (один раз перед циклом, если у тебя массив)
    printf("| %-3s | %-10s | %-30s | %-30s | %-30s | %-30s | %-25s|\n",
           "ID", "Дата", "Наименование предприятия", "Наименование изделия", "Выпущено, млн.р.", "В том числе на экспорт, млн.р.", "Доля экспорта в доходе, %");
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    // Печать строки данных
    for (int i = 0; i < productsCount; i++) {
        printf("| %03d | %02d.%02d.%-4d | %-30.15s | %-30.15s | %30.2f | %30.2f | %25.2f|\n",
               products[i].id,
               products[i].date.day, products[i].date.month, products[i].date.year,
               products[i].companyName,
               products[i].productName,
               products[i].productionCount,
               products[i].exportCount,
               products[i].percentOfExport);
    }
    printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
};

void menuAddRecord() {
    plug("Добавление записи");
};

void menuUpdateRecord() {
    plug("Обновление записи");
};

void menuDeleteRecord(const int id_of_deleting_record) {
    if (id_of_deleting_record > productsCount || id_of_deleting_record < 0) {
        puts("Неверный id");
        return;
    }
    for (int i = id_of_deleting_record; i < productsCount; i++) {
        products[i] = products[i + 1];
        products[i].id -= 1;
    }
    productsCount--;

    outputInConsole();
};

void menuCalcStatistics() {
    plug("Статистика");
};

void menuSaveToFile() {
    plug("Сохранение в файл");
};

