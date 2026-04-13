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


// SQL TABLE
    char *errmsg = NULL;
    
    int exec_result = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS cards (id INTEGER PRIMARY KEY AUTOINCREMENT, word TEXT NOT NULL, phonetic TEXT, example TEXT, translation TEXT, easiness REAL DEFAULT 2.5, interval INTEGER DEFAULT 1, repetitions INTEGER DEFAULT 0, next_review TEXT DEFAULT (date('now')));", NULL, NULL, &errmsg);
    if (exec_result == SQLITE_OK) {
        printf("Table created.");
    } else {
        printf("Failled to create table.");
    }

    sqlite3_close(db);

    return 0;
}