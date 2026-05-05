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
void outputInConsoleOneProd(ProductInfo prod) {
    printf("{\n");
    printf("  \"id\": %d,\n", prod.id);
    printf("  \"date\": {\n");
    // Здесь я предположил стандартные поля для даты, подставь свои, если они другие
    printf("    \"day\": %d,\n", prod.date.day);
    printf("    \"month\": %d,\n", prod.date.month);
    printf("    \"year\": %d\n", prod.date.year);
    printf("  },\n");
    printf("  \"companyName\": \"%s\",\n", prod.companyName);
    printf("  \"productName\": \"%s\",\n", prod.productName);
    printf("  \"productionCount\": %.2f,\n", prod.productionCount);
    printf("  \"exportCount\": %.2f,\n", prod.exportCount);
    printf("  \"percentOfExport\": %.2f\n", prod.percentOfExport);
    printf("}\n");
}

ProductDate SplitStringToDate(const char *str) {
    return (ProductDate) {
        .day = strtol(str, NULL, 10),
        .month = strtol(str + 3, NULL, 10),
        .year = strtol(str + 6, NULL, 10)
    };
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
        return;
    }
    fseek(in, 0, SEEK_END);

    const int capacity = (int)ftell(in);
    char *buff = malloc(capacity + 1);
    fseek(in, 0, SEEK_SET);


    const size_t bytes_read = fread(buff, 1, capacity, in);
    buff[bytes_read] = '\0';
    splitInfo(buff);
    free(buff);
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
    printf("\n");
    if (productsCount + 1 > MAX_PRODUCTS) {
        puts("Превышено максимальное количество записей (1000)");
        return;
    }
    puts("Добавление записи:");

    while (getchar() != '\n' && getchar() != EOF) {}

    ProductInfo newProduct;
    char test_str[MAX_LENGTH_NAME];
    char *endPtr;
    newProduct.id = productsCount + 1;

    printf("Введите дату: ");
    fgets(test_str, sizeof(test_str), stdin);
    newProduct.date = SplitStringToDate(test_str);

    printf("Введите название компании: ");
    fgets(test_str, sizeof(test_str), stdin);
    test_str[strcspn(test_str, "\n")] = '\0';
    strcpy(newProduct.companyName, test_str);

    printf("Введите название продукта: ");
    fgets(test_str, sizeof(test_str), stdin);
    test_str[strcspn(test_str, "\n")] = '\0';
    strcpy(newProduct.productName, test_str);

    printf("Введите количество произведенного товара, млн.р: ");
    fgets(test_str, sizeof(test_str), stdin);
    newProduct.productionCount = strtof(test_str, NULL);

    printf("Введите количество товара, отправленного на экспорт, млн.р: ");
    fgets(test_str, sizeof(test_str), stdin);
    newProduct.exportCount = strtof(test_str, NULL);

    newProduct.percentOfExport = (newProduct.exportCount / newProduct.productionCount) * 100;

    outputInConsoleOneProd(newProduct);
    products[productsCount++] = newProduct;
    puts("Запись успешно добавлена");
};

int isInvalid() {
    if (products->id <= 0) {
        puts("Таблица пуста");
        return 1;
    }
    return 0;
}

void menuUpdateRecord() {
    if (isInvalid()) {
        return;
    }
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    // plug("Обновление записи");
    puts("Введите номер записи");
    char char_num_of_record[MAX_LENGTH_NAME];
    fgets(char_num_of_record, sizeof(char_num_of_record), stdin);
    const int index_of_record = strtol(char_num_of_record, NULL, 10) - 1;
    char input_string[MAX_LENGTH_NAME];
    puts("Введите дату");
    fgets(input_string, sizeof(input_string), stdin);
    products[index_of_record].date = SplitStringToDate(input_string);

    puts("Введите название компании");
    fgets(input_string, sizeof(input_string), stdin);
    input_string[strcspn(input_string, "\n")] = 0; // ЧИСТИМ ТУТ
    strcpy(products[index_of_record].companyName, input_string);

    puts("Введите название продукта");
    fgets(input_string, sizeof(input_string), stdin);
    input_string[strcspn(input_string, "\n")] = 0; // И ТУТ
    strcpy(products[index_of_record].productName, input_string);

    puts("Введите количество произведенных продуктов");
    fgets(input_string, sizeof(input_string), stdin);
    products[index_of_record].productionCount = strtof(input_string, NULL);

    puts("Введите количество продуктов для экспорта");
    fgets(input_string, sizeof(input_string), stdin);
    products[index_of_record].exportCount = strtof(input_string, NULL);

    products[index_of_record].percentOfExport = (products[index_of_record].exportCount / products[index_of_record].productionCount) * 100;
};

void menuDeleteRecord(const int id_of_deleting_record) {
    if (isInvalid()) {
        return;
    }
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
    if (isInvalid()) {
        return;
    }
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
    char filename[MAX_LENGTH_NAME];
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Ошибка при открытии файла");
        return;
    }

    for (int i = 0; i < productsCount; i++) {
        fprintf(file, "%d;%d.%d.%d;%s;%s;%.2f;%.2f;%.2f\n",
                products[i].id,
                products[i].date.day,
                products[i].date.month,
                products[i].date.year,
                products[i].companyName,
                products[i].productName,
                products[i].productionCount,
                products[i].exportCount,
                products[i].percentOfExport);
    }

    fclose(file);
    printf("Данные успешно сохранены в %s\n", filename);

};

