#include <stdio.h>
#include "sqlite3.h"

int main() {
    sqlite3* db;
    int result = sqlite3_open("rocaclass.db", &db);

    if (result == SQLITE_OK) {
        printf("The connection opened successfully.\n");
    } else {
        const char* errorMessage = sqlite3_errmsg(db);
        printf("Failed to open database: %s", errorMessage);
        return 1;
    }

    sqlite3_close(db);

    return 0;
}