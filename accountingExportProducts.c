#include "accountingExportProducts.h"

#include <stdio.h>
// #include <conio.h>
#include <stdlib.h>
#include <string.h>

ProductInfo products[MAX_PRODUCTS];
int productsCount;


CompanyStat statistics[MAX_PRODUCTS];
int statisticsCount;

void ClearBuff(const char *str) {
    if (str == NULL) return;

    // Ищем символ заменяющий перенос строки
    char *newline = strchr(str, '\n');

    if (newline != NULL) {
        // Если нашли, просто заменяем его на символ конца строки '\0'
        *newline = '\0';
    }
    else {
        // Если '\n' НЕ нашли, значит строка не поместилась, и в буфере остался мусор.
        // Только в этом случае вычищаем stdin!
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
    }
}

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
void resetCalculateTable() {
    statisticsCount = 0;
}

ProductDate SplitStringToDate(const char *str) {
    // Если строка пустая, возвращаем нулевую дату
    if (str == NULL || *str == '\0') {
        return (ProductDate){0, 0, 0};
    }

    char *next_ptr;
    ProductDate date;

    // 1. Читаем день. next_ptr указывает на символ СРАЗУ после числа (на точку/слэш)
    date.day = (int) strtol(str, &next_ptr, 10);

    // Если символ после числа — разделитель, пропускаем его (+1)
    if (*next_ptr == '.' || *next_ptr == '/' || *next_ptr == '-') {
        next_ptr++;
    }

    // 2. Читаем месяц. next_ptr сдвигается на символ после месяца
    date.month = (int) strtol(next_ptr, &next_ptr, 10);

    // Снова пропускаем разделитель (+1), если он есть
    if (*next_ptr == '.' || *next_ptr == '/' || *next_ptr == '-') {
        next_ptr++;
    }

    // 3. Читаем год. Последний аргумент NULL, так как дальше читать не нужно
    date.year = (int) strtol(next_ptr, NULL, 10);


    return date;
}

/**
 * @brief Function to check if table is empty
 * @return boolean if invalid
 */
int isInvalid() {
    if (productsCount == 0) {
        puts("Таблица пуста");
        return 1;
    }
    return 0;
}

int ValidateProductionAndExport(const float *production, const float *exportCount) {
    if (*production <= 0) {
        return 0;
    }
    if (*exportCount < 0) {
        return 0;
    }
    if (*exportCount > *production) {
        return 0;
    }
    return 1;
}

void validName(char *str) {
    if (fgets(str, MAX_LENGTH_NAME, stdin) == NULL) {
        validName(str);
    }

    // Ищем символ переноса строки
    const size_t len = strcspn(str, "\n");

    if (str[len] == '\n') {
        // Если '\n' найден, значит строка поместилась полностью, буфер чист
        str[len] = '\0';
    } else {
        // Если '\n' НЕТ, значит введенная строка была слишком длинной
        puts("Слишком длинная строка! Ограничение превышено. Повторите ввод:");

        // Вот теперь очищаем хвост, который не поместился в fgets

        ClearBuff(str);
        validName(str); // Возврат к началу цикла для повторного ввода

    }
    // Проверка на пустой ввод (если пользователь просто нажал Enter)
    if (strlen(str) == 0) {
        puts("Строка не должна быть пустой! Повторите ввод:");
        validName(str);
    }
}


/**
 * @brief Function to check if date is valid
 * @param date date to check
 * @return boolean
 */
int isValidDate(const ProductDate *date) {
    const int days_in_months[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (date->day <= 0 || date->month <= 0 || date->year <= 0) {
        return 0;
    }
    if (days_in_months[date->month] < date->day) {
        // printf("%d", days_in_months[date->month]);
        return 0;
    }
    if (date->year > 9999) {
        return 0;
    }
    if (date->month > 12) {
        return 0;
    }

    return 1;
}


void writeInId(const int id_of_prod) {
    products[id_of_prod].id = id_of_prod + 1;
}

void writeInDate(const char *str, const int id_of_prod, int *exit) {
    products[id_of_prod].date = SplitStringToDate(str);
    if (!isValidDate(&products[id_of_prod].date)) {
        products[id_of_prod].date.day = 0;
        products[id_of_prod].date.month = 0;
        products[id_of_prod].date.year = 0;
        *exit = 0;
        puts("Не верная дата");
        return;
    }
    *exit = 1;
}

void writeInCompanyName(const char *str, const int id_of_prod) {
    strcpy(products[id_of_prod].companyName, str);
}

void writeInProductName(const char *str, const int id_of_prod) {
    strcpy(products[id_of_prod].productName, str);
}

void writeInProductionCount(const char *str, const int id_of_prod) {
    char *endPtr;
    products[id_of_prod].productionCount = strtof(str, &endPtr);
}

void writeInExportCount(const char *str, const int id_of_prod) {
    char *endPtr;
    products[id_of_prod].exportCount = strtof(str, &endPtr);
}

void writeInPercentOfExport(const int id_of_prod) {
    products[id_of_prod].percentOfExport = products[id_of_prod].exportCount / products[id_of_prod].productionCount *
                                           100;
}

/**
 * @brief Function to split info into a struct
 * @param str String to split
*/
int splitInfo(const char *str) {
    int type_of_convert = 1;
    int count_of_prods = 0;

    // Считаем длину один раз и добавляем +1 для '\0'
    const int str_len = strlen(str);
    char record[str_len + 1];

    int exit_flag = 1; // Переименовано, чтобы не путать с функцией exit()
    int j = 0;

    for (int i = 0; i < str_len; i++) {
        if (str[i] == ';') {
            record[j] = '\0';
            switch (type_of_convert) {
                case 1:
                    writeInDate(record, count_of_prods, &exit_flag);
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
                default: break;
            }
            type_of_convert++;
            j = 0;
        }
        else if (str[i] == '\n') {
            record[j] = '\0';
            switch (type_of_convert) {
                case 1:
                    writeInDate(record, count_of_prods, &exit_flag);
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
                default: break;
            }
            writeInId(count_of_prods);
            count_of_prods++;
            type_of_convert = 1;
            j = 0;
        }
        else {
            record[j] = str[i];
            j++;
        }

        if (!exit_flag) {
            puts("В структуру попали неверные данные, структура будет очищена");
            productsCount = 0;
            return 0;
        }
    }

    // Обработка последней строки, если файл/строка не заканчивались на '\n'
    if (j > 0) {
        record[j] = '\0';
        switch (type_of_convert) {
            case 1:
                writeInDate(record, count_of_prods, &exit_flag);
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
            default: break;
        }
        writeInId(count_of_prods);
        count_of_prods++;
    }

    productsCount = count_of_prods; // Убрано +1, так как count_of_prods считает точно
    return 1;
}




void menuReadFromFile(const char *filename) {
    resetCalculateTable();
    // plug("Чтение из файла");
    FILE *in = fopen(filename, "r");
    if (in == NULL) {
        puts("Данный файл не найден");
        return;
    }
    fseek(in, 0, SEEK_END);

    const int capacity = (int) ftell(in);
    char *buff = malloc(capacity + 1);
    fseek(in, 0, SEEK_SET);



    const size_t bytes_read = fread(buff, 1, capacity, in);
    buff[bytes_read] = '\0';
    const char *new_buff = strchr(buff, '\n')  + 1;
    const int v = splitInfo(new_buff);
    free(buff);
    fclose(in);
    if (v) {
        puts("Данные успешно прочитаны");
    }
}

void menuPrintTable() {
    if (isInvalid()) {
        return;
    }

    // Печатаем заголовок таблицы (один раз перед циклом, если у тебя массив)
    printf("| %-3s | %-10s | %-30s | %-40s | %-30s | %-30s | %-25s|\n",
           "ID", "Дата", "Наименование предприятия", "Наименование изделия", "Выпущено, млн.р.",
           "В том числе на экспорт, млн.р.", "Доля экспорта в доходе, %");
    printf(
        "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    // Печать строки данных
    for (int i = 0; i < productsCount; i++) {
        printf("| %03d | %02d.%02d.%-4d | %-30.30s | %-40.40s | %30.2f | %30.2f | %25.2f|\n",
               products[i].id,
               products[i].date.day, products[i].date.month, products[i].date.year,
               products[i].companyName,
               products[i].productName,
               products[i].productionCount,
               products[i].exportCount,
               products[i].percentOfExport);
    }
    printf(
        "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
};

void writeRecord(ProductInfo *newProduct, const int prod_id) {
    newProduct->id = prod_id;
    char test_str[MAX_LENGTH_NAME];
    int exit = 1;
    while (exit) {
        printf("Введите дату: ");
        fgets(test_str, sizeof(test_str), stdin);
        newProduct->date = SplitStringToDate(test_str);
        if (isValidDate(&newProduct->date)) {
            exit = 0;
        }
        printf("\n");
    }

    printf("Введите название компании: ");
    validName(test_str);
    strcpy(newProduct->companyName, test_str);

    printf("Введите название продукта: ");
    validName(test_str);
    strcpy(newProduct->productName, test_str);

    exit = 1;
    while (exit) {
        printf("Введите количество произведенного товара, млн.р: ");
        fgets(test_str, sizeof(test_str), stdin);
        newProduct->productionCount = strtof(test_str, NULL);

        printf("Введите количество товара, отправленного на экспорт, млн.р: ");
        fgets(test_str, sizeof(test_str), stdin);
        newProduct->exportCount = strtof(test_str, NULL);


        if (ValidateProductionAndExport(&newProduct->productionCount, &newProduct->exportCount)) {
            newProduct->percentOfExport = (newProduct->exportCount / newProduct->productionCount) * 100;
            exit = 0;
        } else {
            puts("Ошибка ввода: проверьте корректность данных.");
        }
    }
}


void menuAddRecord() {
    resetCalculateTable();
    printf("\n");
    if (productsCount + 1 > MAX_PRODUCTS) {
        puts("Превышено максимальное количество записей (1000)");
        return;
    }
    puts("Добавление записи:");

    // int c;
    // while ((c = getchar()) != '\n' && c != EOF) {
    // }

    ProductInfo newProduct = {
        .id = 0,
        .date = {
            .day = 0,
            .month = 0,
            .year = 0,
        },
        .companyName = "",
        .productName = "",
        .productionCount = 0,
        .exportCount = 0,
        .percentOfExport = 0
    };

    writeRecord(&newProduct, productsCount + 1);


    // outputInConsoleOneProd(newProduct);
    products[productsCount++] = newProduct;
    puts("Запись успешно добавлена");
};


void menuUpdateRecord() {
    resetCalculateTable();
    if (isInvalid()) {
        return;
    }
    // plug("Обновление записи");
    puts("Введите номер записи");
    char char_num_of_record[MAX_LENGTH_NAME];
    if (fgets(char_num_of_record, sizeof(char_num_of_record), stdin) != NULL) {
        ClearBuff(char_num_of_record); // И буфер чист, и строка без '\n'
    }
    const int index_of_record = strtol(char_num_of_record, NULL, 10) - 1;
    if (index_of_record > productsCount) {
        printf("Такого индекса в таблице нет, максимальный индекс - %d\n", productsCount);
        return;
    }


    writeRecord(&products[index_of_record], index_of_record + 1);

    printf("Запись %d успешно изменена \n", index_of_record + 1);
}

void menuDeleteRecord(const int id_of_deleting_record) {
    resetCalculateTable();
    if (isInvalid()) {
        printf("Введен не верный номер записи\n");
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
    printf("Запись %d успешно удалена \n", id_of_deleting_record + 1);
    // outputInConsole();
}

void swap(CompanyStat *a, CompanyStat *b) {
    const CompanyStat tmp = *a;
    *a = *b;
    *b = tmp;
}

void merge(CompanyStat arr[], const int left, const int mid, const int right) {
    const int n1 = mid - left + 1;
    const int n2 = right - mid;

    // Создаем временные массивы для левой и правой половин
    CompanyStat *L = malloc(n1 * sizeof(CompanyStat));
    CompanyStat *R = malloc(n2 * sizeof(CompanyStat));

    // Копируем данные во временные массивы
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    // Слияние элементов обратно в arr[]
    while (i < n1 && j < n2) {
        // strcmp(a, b) < 0 означает, что строка 'a' идет раньше 'b' в алфавите
        if (strcmp(L[i].companyName, R[j].companyName) <= 0) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Копируем оставшиеся элементы левого массива, если они есть
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Копируем оставшиеся элементы правого массива, если они есть
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Освобождаем выделенную временную память
    free(L);
    free(R);
}

// Основная рекурсивная функция сортировки слиянием
void mergeSort(CompanyStat arr[], const int left, const int right) {
    if (left >= right) return;

    // Находим середину массива
    const int mid = left + (right - left) / 2;

    // Сортируем первую и вторую половины
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    // Объединяем отсортированные половины
    merge(arr, left, mid, right);
}

void printBar(const float value, const int width) {
    const int barLen = (int) (value / 100 * (float) width);
    for (int i = 0; i < barLen; ++i) {
        putchar('#');
    }
}

void summation(int *uniqueCount, CompanyStat *stats) {
    *uniqueCount = 0; // Обнуляем счетчик перед началом сборки данных

    // Временные массивы для накопления физических объемов
    float totalProduction[MAX_PRODUCTS] = {0};
    float totalExport[MAX_PRODUCTS] = {0};

    for (int i = 0; i < productsCount; ++i) {
        int idx = -1;

        // Ищем, добавляли ли мы уже эту компанию в stats
        for (int j = 0; j < *uniqueCount; ++j) {
            if (strcmp(stats[j].companyName, products[i].companyName) == 0) {
                idx = j;
                break;
            }
        }

        if (idx == -1) {
            // Защита от переполнения локальных массивов и stats
            if (*uniqueCount >= MAX_PRODUCTS) {
                break;
            }

            // Регистрируем новую компанию в stats
            strcpy(stats[*uniqueCount].companyName, products[i].companyName);

            // Начинаем копить суммы в параллельных массивах под тем же индексом
            totalProduction[*uniqueCount] = products[i].productionCount;
            totalExport[*uniqueCount] = products[i].exportCount;

            *uniqueCount += 1;
        } else {
            // Компания уже есть — суммируем её показатели в параллельные массивы
            totalProduction[idx] += products[i].productionCount;
            totalExport[idx] += products[i].exportCount;
        }
    }

    // ВТОРОЙ ЭТАП: Считаем процент доли экспорта для каждой уникальной компании
    for (int i = 0; i < *uniqueCount; ++i) {
        if (totalProduction[i] > 0.0f) {
            // Формула: (общий экспорт / общее производство) * 100
            stats[i].percentOfExport = (totalExport[i] / totalProduction[i]) * 100.0f;
        } else {
            // Защита от деления на ноль, если производство равно 0
            stats[i].percentOfExport = 0.0f;
        }
    }
}



/**
 * @brief Function creat export dependence chart for the company
 * @param count count of all necessary companies
 * @param stats struct of companies
 * @param maxProd max share of export for build graph
 */
void printGraph(const int count, CompanyStat *stats, const float maxProd) {
    for (int i = 0; i < count; ++i) {
        printf("%-30s | ", stats[i].companyName);
        printBar(stats[i].percentOfExport, 40); // 40 символов ширина бара
        printf(" (%.2f)\n", stats[i].percentOfExport);
    }
}

void printTableFromGraph(const int count, CompanyStat *stats) {
    printf("Статистика производства по компаниям:\n\n");
    if (stats == NULL || count <= 0) {
        printf("Данные для отображения отсутствуют.\n");
        return;
    }

    // Печать шапки таблицы
    // -30 — левое выравнивание, 30 символов под имя
    // 25 — правое выравнивание, 25 символов под процент
    printf("\n%s\n", "---------------------------------------------------------");
    printf("| %-30s | %20s |\n", "Наименование предприятия", "Доля экспорта в %");
    printf("%s\n", "---------------------------------------------------------");

    // Печать строк таблицы
    for (int i = 0; i < count; i++) {
        // %.1f%% выведет число с одним знаком после запятой и добавит знак %
        printf("| %-30s | %19.1f%% |\n", stats[i].companyName, stats[i].percentOfExport);
    }

    printf("%s\n", "---------------------------------------------------------");
}

void menuCalcStatistics() {
    CompanyStat stats[MAX_PRODUCTS];
    int uniqueCount = 0;
    if (productsCount == 0) {
        puts("Вначале введите данные");
        return;
    }
    summation(&uniqueCount, stats);

    mergeSort(stats, 0, uniqueCount - 1);


    // Найдём максимум для масштабирования бара
    float maxProd = 0;
    for (int i = 0; i < uniqueCount; ++i) {
        if (stats[i].percentOfExport > maxProd) {
            maxProd = stats[i].percentOfExport;
        }
    }

    printTableFromGraph(uniqueCount, stats);

    printGraph(uniqueCount, stats, maxProd);

    for (int i = 0; i < uniqueCount; i++) {
        strcpy(statistics[i].companyName, stats[i].companyName);
        statistics[i].percentOfExport = stats[i].percentOfExport;
    }
    statisticsCount = uniqueCount;
}

void saveStruct(FILE *file) {
    fprintf(file, "Наименование предприятия;Доля экспорта в доходе\n");
    for (int i = 0; i < productsCount; i++) {
        fprintf(file, "%s;%f\n",
                products[i].companyName,
                products[i].percentOfExport);
    }

}

void menuSaveToFile(const char *filename) {
    if (statisticsCount == 0) {
        puts("Вначале выполните расчет");
        return;
    }

    ClearBuff(filename);

    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Ошибка при открытии файла");
        return;
    }
    saveStruct(file);

    fclose(file);
    printf("Данные успешно сохранены");
}
