#ifndef PROJECT_OF_COURCE_PRODUCTMANAGER_H
#define PROJECT_OF_COURCE_PRODUCTMANAGER_H

#define MAX_PRODUCTS 1000
#define MAX_LENGTH_NAME 100
#define MAX_LENGTH_PRODUCT_NAME 100

// Date struct
typedef struct {
    int day;
    int month;
    int year;
} ProductDate;
// Product struct
typedef struct {
    int id;
    ProductDate date;
    char companyName[MAX_LENGTH_NAME];
    char productName[MAX_LENGTH_PRODUCT_NAME];
    float productionCount;
    float exportCount;
    float percentOfExport;
} ProductInfo;

extern ProductInfo products[MAX_PRODUCTS];

/**
 * @brief Read from file
 */
void menuReadFromFile(const char *filename);

/**
 * @brief Output table
 */
void menuPrintTable();

/**
 * @brief Add product
 */
void menuAddRecord();

/**
 * @brief Update record
 */
void menuUpdateRecord();

/**
 * @brief Delete record
 */
void menuDeleteRecord();

/**
 * @brief Statistics
 */
void menuCalcStatistics();

/**
 * @brief Save the table
 */
void menuSaveToFile();

#endif //PROJECT_OF_COURCE_PRODUCTMANAGER_H