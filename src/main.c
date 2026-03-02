#include "data_win.h"

#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <path to data.win or game.unx>\n", argv[0]);
        return 1;
    }

    const char* filePath = argv[1];
    printf("Loading %s...\n", filePath);

    DataWin* dataWin = DataWin_parse(filePath);

    printf("Loaded successfully!\n\n");
    DataWin_printSummary(dataWin);

    DataWin_free(dataWin);
    printf("Freed all resources. Clean exit.\n");

    return 0;
}
