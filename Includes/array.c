#include "header.h"
#include "array.h"

#include <stdlib.h>

void PutElement(const struct ProductInfo item) {
    struct ProductInfo *temp = realloc(products, (countProducts + 1) * sizeof(struct ProductInfo));
    temp[countProducts] = item;
    products = temp;
}
