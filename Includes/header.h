#ifndef SEMESTERWORK_HEADER_H
#define SEMESTERWORK_HEADER_H

#define MAX_PATH 240
#define MAX_COLS 7
#define MAX_LENGTH 100

extern int countProducts;

extern char toggledFileName[MAX_PATH];
// Date struct
struct ProductDate {
    int day;
    int month;
    int year;
};
// Product struct
struct ProductInfo {
    int id;
    struct ProductDate date;
    char companyName[MAX_LENGTH];
    char productName[MAX_LENGTH];
    float productionCount;
    float exportCount;
    float percentOfExport;
};
// Table Header
struct TableHeader {
    char rows[MAX_COLS][250];
};
// All products
extern struct ProductInfo *products;
// Table Header
extern struct TableHeader table_header;

/**
 * @brief Writing all products in file
 * @param prods All your products
 * @param w_filename Filename for write records
 */
void WriteCustomFile(const struct ProductInfo *prods, const char w_filename[]);

/**
 * @brief Read from your file
 * @param fileName Name of reading file
 */
void ReadCustomFile(const char *fileName);

/**
 * @brief Output all data from file
 */
void OutputData();

/**
 * @brief Input filename
 */
void ToggleFile();

/**
 * @brief Output header of table
 * @param prods Var with all products
 * @param table Var with header of table
 */
void OutputTable(const struct ProductInfo *prods, struct TableHeader table);

/**
 * @brief Add product to products array
 */
void AddItem();

#endif //SEMESTERWORK_HEADER_H