#include "talking.h"

#include <stdio.h>
#include <stdlib.h>

void AskQuest(int *turn) {
    printf("Введите номер варианта:\n"
        "1. Прочитать данные из файла\n"
        "2. Внести данные в файл\n"
        "3. Выход\n"
    );
    *turn = 0;
    char buffer[10];
    fgets(buffer, sizeof(buffer), stdin);
    char *endPtr;
    *turn = strtol(buffer, &endPtr, 10);
}
