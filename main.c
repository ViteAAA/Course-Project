#include <stdio.h>
#include <windows.h>
#include <stdbool.h>


#include "Includes/header.h"
#include "Includes/talking.h"

void ChooseFileForRead() {
    ToggleFile();
    if (strcmp(toggledFileName, "") != 0) {
        ReadCustomFile(toggledFileName);
    }
    else {
        puts("NET");
    }
    OutputTable(products, table_header);
}



int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    int turn = 0;
    boolean isExit = false;

    while (!isExit) {
        AskQuest(&turn);
        switch (turn) {
            case 1:
                ChooseFileForRead();
                break;
            case 2:
                if (products != NULL) {
                    ToggleFile();
                    if (strcmp(toggledFileName, "") != 0) {
                        WriteCustomFile(products, toggledFileName);
                    }
                }
                else {
                    puts("Нет данных\n");
                }
                break;
            case 3:
                isExit = true;
            default:
                break;
        }
    }
    puts("End");



    free(products);
    return 0;
}
