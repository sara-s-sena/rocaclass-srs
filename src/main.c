// I started this program by including four libraries, including "card.h", which defines the structure for storing card data. I began by opening a SQLite3 database, then used the sqlite3_exec function to create the table if it didn't exist. For the statement function, sqlite3_prepare_v2 was useful because it compiles the SQL into a prepared statement, making execution safer and more efficient. For the bind function, sqlite3_bind_text takes five parameters: the statement, the index, the value, the length, and the destructor. This is important because it securely inserts values without manually building SQL strings, reducing errors and preventing SQL injection. In contrast, directly concatenating values into SQL is unsafe and error-prone. Then, I executed sqlite3_step to run the prepared statement and finally used sqlite3_finalize to release resources. Using prepared statements was preferable because they improve performance, ensure type safety, and protect against SQL injection.

#include <stdio.h>
#include "sqlite3.h"
#include "card.h"
#include <string.h>
#include "sm2.h"



// the interactive review loop

int list_cards(sqlite3 *db) {
    sqlite3_stmt *stmt = NULL;


    int return_value_SELECT = sqlite3_prepare_v2(db, "SELECT * FROM cards", -1, &stmt, NULL);
    if(return_value_SELECT != SQLITE_OK) {
        printf("SQL error: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    while(sqlite3_step(stmt) == SQLITE_ROW) {

// SQLITE SELECT / sqlite3_column_*()
        const unsigned char *word = sqlite3_column_text(stmt, 1);
        printf("word: %s\n", word);

        const unsigned char *translation = sqlite3_column_text(stmt, 2);
        printf("translation: %s\n", translation);

        const unsigned char *phonetic = sqlite3_column_text(stmt, 3);
        printf("phonetic: %s\n", phonetic);

        const unsigned char *example = sqlite3_column_text(stmt, 4);
        printf("example: %s\n", example);

        const unsigned char *explanation = sqlite3_column_text(stmt, 5);
        printf("explanation: %s\n", explanation);

        double easiness = sqlite3_column_double(stmt, 6);
        printf("easiness: %f\n", easiness);

        int interval = sqlite3_column_int(stmt, 7);
        printf("interval: %d\n", interval);

        int repetitions = sqlite3_column_int(stmt, 8);
        printf("repetitions: %d\n", repetitions);

        const unsigned char *next_review = sqlite3_column_text(stmt, 9);
        printf("next_review: %s\n", next_review);
    }

    int return_value_finalize_select = sqlite3_finalize(stmt);
    if(return_value_finalize_select == SQLITE_OK) {
        printf("return_value_finalize_select OK.\n");
    }   else {
        printf("return_value_finalize_select ERROR.\n");
        return 1;
    }

    return 0;
}


int main(int argc, char *argv[]) {

// ARGC CHECK

    if (argc < 2) {
        printf("Usage: %s [--list | --add | --review]\n", argv[0]);
        return 1;
    }


    sqlite3* db;
    int result = sqlite3_open("rocaclass.db", &db);

    if (result == SQLITE_OK) {
        printf("The connection opened successfully.\n");
    } else {
        const char* errorMessage = sqlite3_errmsg(db);
        printf("Failed to open database: %s\n", errorMessage);
        return 1;
    }


// SQLITE3 TABLE

    char *errmsg = NULL;
    
    int exec_result = sqlite3_exec(db, "CREATE TABLE IF NOT EXISTS cards ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "word TEXT NOT NULL, "
        "translation TEXT, "
        "phonetic TEXT, "
        "example TEXT, "
        "explanation TEXT, "
        "easiness REAL DEFAULT 2.5, "
        "interval INTEGER DEFAULT 1, "
        "repetitions INTEGER DEFAULT 0, "
        "next_review TEXT DEFAULT (date('now')));", NULL, NULL, &errmsg);
    if (exec_result == SQLITE_OK) {
        printf("Table created.\n");
    }   else {
            printf("Failed to create table: %s\n", errmsg);
            sqlite3_free(errmsg);
            return 1;
    }

    if (strcmp(argv[1], "--list") == 0) {
        list_cards(db);        
    } else if (strcmp(argv[1], "--add") == 0) {
        printf("--add not yet implemented.\n");
    }   else {
            printf("invalid command. Usage: %s [--list | --add | --review]\n", argv[0]);
    }

    sqlite3_close(db);

    return 0;
}
