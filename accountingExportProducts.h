#ifndef PROJECT_OF_COURCE_PRODUCTMANAGER_H
#define PROJECT_OF_COURCE_PRODUCTMANAGER_H

#define MAX_PRODUCTS 1000
#define MAX_LENGTH_NAME 100
#define MAX_LENGTH_PRODUCT_NAME 100
#define COLUMNS_COUNT 6

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

typedef struct {
    char companyName[MAX_LENGTH_NAME];
    float totalProduction;
} CompanyStat;

extern ProductInfo products[MAX_PRODUCTS];
extern int productsCount;

/**
 * @brief This function reed from your file all data and parse in structure
 * @param filename a name of reading file
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
 * @brief Function to add a id
*/
void writeInId(const char *str, int id_of_prod);

/**
 * @brief Delete record
 */
void menuDeleteRecord(int id_of_deleting_record);

/**
 * @brief Function to add a date
*/
void writeInDate(const char *str, int id_of_prod);

/**
 * @brief Function to add a company name
*/
void writeInCompanyName(const char *str, int id_of_prod);

/**
 * @brief Function to add a product name
*/
void writeInProductName(const char *str, int id_of_prod);

/**
 * @brief Function to add a production count
*/
void writeInProductionCount(const char *str, int id_of_prod);

/**
 * @brief Function to add an export count
*/
void writeInExportCount(const char *str, int id_of_prod);

/**
 * @brief Statistics
 */
void menuCalcStatistics();

/**
 * @brief Save the table
 */
void menuSaveToFile();

#endif //PROJECT_OF_COURCE_PRODUCTMANAGER_H