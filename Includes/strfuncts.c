#include "strfuncts.h"
#include <stdio.h>
// Функция для подсчета реальных символов в UTF-8 строке
int utf8_strlen(const char *s) {
    int count = 0;
    while (*s) {
        if ((*s & 0xc0) != 0x80) count++; // Считаем только начало символа
        s++;
    }
    return count;
}

// Функция для вывода ячейки с фиксированной шириной
void print_cell(const char *text, const int width) {
    const int len = utf8_strlen(text);
    if (len > width) {
        int outSymbols = 0;
        int i = 0;
        for (i = 0; i <= width; i++) {
            putchar(text[i]);
            if ((text[i] & 0xC0) != 0x80) {
                outSymbols++;
            }
        }
        if ((text[i] & 0xC0) == 0x80) {
            putchar(text[i]);
        }
        printf("...");
        // Добиваем пробелами до нужной ширины
        for (i = outSymbols; i < width - 3; i++) {
            putchar(' ');
        }
    }
    else {
        printf("%s", text);
        for (int i = 0; i < width - len; i++) {
            putchar(' ');
        }
    }


    printf(" | ");
}

