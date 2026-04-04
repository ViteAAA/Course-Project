#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "strfuncts.h"
#include "header.h"

struct ProductInfo *products = NULL;
int countProducts = 100;
char toggledFileName[MAX_PATH] = "";
struct TableHeader table_header;

void CountOfProducts(const char *filename) {
    int ch;
    int len = 0;
    FILE* in = fopen(filename, "r");
    // fseek(in, 0, SEEK_END);
    // rewind(in);
    while ((ch = fgetc(in)) != EOF) {
        if ((char)ch == '\n') {
            len++;
        }
    }
    products = malloc((len) * sizeof(struct ProductInfo));
    countProducts = len;
    fclose(in);
}

float CalculatePercent(const float part, const float total) {
    if (total) {
        return part / total * 100;
    }
    return 0;
}

void WriteCustomFile(const struct ProductInfo *prods, const char w_filename[]) {


    FILE* fp = fopen(w_filename, "w");

    if (fp == NULL) {
        return;
    }

    for (int i = 0; i < MAX_COLS; ++i) {
        fprintf(fp, "%s;", table_header.rows[i]);
    }
    fprintf(fp, "\n");

    for (int i = 0; i < countProducts; ++i) {
        fprintf(fp, "%d;", prods[i].id);
        fprintf(fp, "%d.%d.%d;", prods[i].date.day, prods[i].date.month, prods[i].date.year);
        fprintf(fp, "%s;", prods[i].companyName);
        fprintf(fp, "%s;", prods[i].productName);
        fprintf(fp, "%.3f;", prods[i].productionCount);
        fprintf(fp, "%.3f;", prods[i].exportCount);
        fprintf(fp, "%.3f;", prods[i].percentOfExport);
        fprintf(fp, "\n");
    }

    fclose(fp);
}

void ParseLine(char *txt, const int pIndex) {
    char *endPtr;
    if (products == NULL) {
        return;
    }

    char *token = strtok(txt, ";");
    if (token) {
        products[pIndex].id = strtol(token, &endPtr, 10);
    }

    // printf("%d", products[pIndex].id);
    token = strtok(NULL, ";");
    if (token) {
        char *ptr = token;
        products[pIndex].date.day = (int)strtol(ptr, &ptr, 10);
        if (*ptr == '.') ptr++; // Пропускаем точку

        // 2. Читаем месяц
        products[pIndex].date.month = (int)strtol(ptr, &ptr, 10);
        if (*ptr == '.') ptr++; // Пропускаем точку

        // 3. Читаем год
        products[pIndex].date.year = (int)strtol(ptr, &ptr, 10);
        // printf("\n%d\n%d\n%d", products->date.day, products->date.moth, products->date.year);
    }

    token = strtok(NULL, ";");

    if (token) {
        strncpy(products[pIndex].companyName, token, 99);
        products[pIndex].companyName[99] = '\0';
    }

    token = strtok(NULL, ";");
    if (token) {
        strncpy(products[pIndex].productName, token, 99);
        products[pIndex].productName[99] = '\0';
    }
    token = strtok(NULL, ";");
    if (token) {
        products[pIndex].productionCount = strtof(token, &endPtr);
    }

    token = strtok(NULL, "\n"); // Ищем до конца строки
    if (token) {
        // ВАЖНО: используем strtof, но token может указывать на строку с пробелом" 0"
        products[pIndex].exportCount = strtof(token, &endPtr);
    }
    if (products[pIndex].productionCount != 0) {
        products[pIndex].percentOfExport = CalculatePercent(products[pIndex].exportCount, products[pIndex].productionCount);
    }
}

void ParseHeader(char *head) {
    const char *token = strtok(head, ";");
    if (token) {
        strncpy(table_header.rows[0], token, 99);
        table_header.rows[0][99] = '\0';
    }
    for (int i = 1; i < MAX_COLS; i++) {
        token = strtok(NULL, ";\n");
        if (token) {
            strncpy(table_header.rows[i], token, 99);
            table_header.rows[i][99] = '\0';
        }
    }
    strcpy(table_header.rows[MAX_COLS - 1], "Доля экспорта");
}

void ReadCustomFile(const char *fileName) {
    char formatedFileName[MAX_PATH];
    sprintf(formatedFileName, "../%s", fileName);
    CountOfProducts(formatedFileName);
    FILE* in = fopen(formatedFileName, "r");

    fseek(in, 0, SEEK_END);
    if (in == NULL) {
        return;
    }

    const int capacity = ftell(in);
    char *buff = malloc((capacity + 1) * sizeof(char));
    if (buff == NULL) { // Затем проверяем память!
        fclose(in);
        free(buff);
        return;
    }

    fseek(in, 0, SEEK_SET);
    int ch;
    int i = 0;
    while ((ch = fgetc(in)) != EOF) {
        buff[i++] = (char)ch;
    }
    buff[i] = '\0';


    char *current_line = strchr(buff, '\n');
    if (current_line != NULL) {
        current_line++;
        // 1. Считаем длину строки до знака \n
        const size_t length = current_line - buff;

        // 2. Создаем буфер для хранения этой строки (+1 для '\0')
        char line[256];

        // 3. Копируем ровно столько символов, сколько до \n
        strncpy(line, buff, length);
        line[length] = '\0'; // ВАЖНО: strncpy не ставит ноль сам, если лимит достигнут

        ParseHeader(line);
    }
    else {
        current_line = buff;
    }

    for (i = 0; i < countProducts; i++) {
        // Находим конец текущей строки (\n)
        char *next_line = strchr(current_line, '\n');

        if (next_line) {
            *next_line = '\0'; // Временно "отрезаем" строку для ParseLine
        }

        // Вызываем твою ParseLine (в ней strtok теперь сработает правильно)
        ParseLine(current_line, i);

        if (next_line) {
            *next_line = '\n';      // Возвращаем \n на место, чтобы buff не портился
            current_line = next_line + 1; // Переходим к следующей строке
        } else {
            break; // Если \n больше нет, выходим
        }
    }


    fclose(in);
    free(buff);

}

void OutputData() {
    if (products == NULL) {
        return;
    }
    for (int i = 0; i < countProducts; i++) {
        printf("%d {\n"
               "    id: %d,\n"
               "    date {\n"
               "        day: %d,\n"
               "        month: %d,\n"
               "        year: %d,\n"
               "    },\n"
               "    CompanyName: %s,\n"
               "    ProductName: %s,\n"
               "    ProductionCount: %.3f,\n"
               "    ExportCount: %.3f,\n"
               "    PercentOfExport: %.3f%c\n"
               "}\n", i, products[i].id, products[i].date.day, products[i].date.month, products[i].date.year, products[i].companyName, products[i].productName, products[i].productionCount, products[i].exportCount, products[i].percentOfExport, '%');
    }
}

void ToggleFile() {
    char filename[MAX_PATH];
    printf("Введите название файла\n");
    fgets(filename, MAX_PATH, stdin);
    filename[strcspn(filename, "\r\n")] = '\0';
    strcpy(toggledFileName, filename);
}

void AddItem() {
    struct ProductInfo item;
    char str[100];
    fgets(str, sizeof(str), stdin);
    item.id = strtol(str, NULL, 10);
    fgets(str, sizeof(str), stdin);
    // item.companyName = str;

}

void OutputTable(const struct ProductInfo *prods, const struct TableHeader table) {
    printf("\n");
    print_cell(table.rows[0], 3);
    print_cell(table.rows[1], 10);
    print_cell(table.rows[2], 20);
    print_cell(table.rows[3], 26);
    print_cell(table.rows[4], 20);
    print_cell(table.rows[5], 16);
    print_cell(table.rows[6], 16);
    printf("\n");

    printf("-----------------------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < countProducts; i++) {
        // ID и Дата (фиксированные, можно обычным printf)
        printf("%3.3d | %02d.%02d.%d | ",
               prods[i].id,
               prods[i].date.day, prods[i].date.month, prods[i].date.year);

        // Колонки с русским текстом через нашу функцию
        print_cell(prods[i].companyName, 20);
        print_cell(prods[i].productName, 26);

        // Числа
        printf("%20.2f | %16.2f | %17.2f|\n",
               prods[i].productionCount,
               prods[i].exportCount,
               prods[i].percentOfExport);
    }
    printf("-----------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\n");
}