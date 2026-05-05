// I started this program by including four libraries, including "card.h", which defines the structure for storing card data. I began by opening a SQLite3 database, then used the sqlite3_exec function to create the table if it didn't exist. For the statement function, sqlite3_prepare_v2 was useful because it compiles the SQL into a prepared statement, making execution safer and more efficient. For the bind function, sqlite3_bind_text takes five parameters: the statement, the index, the value, the length, and the destructor. This is important because it securely inserts values without manually building SQL strings, reducing errors and preventing SQL injection. In contrast, directly concatenating values into SQL is unsafe and error-prone. Then, I executed sqlite3_step to run the prepared statement and finally used sqlite3_finalize to release resources. Using prepared statements was preferable because they improve performance, ensure type safety, and protect against SQL injection.

#include <stdio.h>
#include "sqlite3.h"
#include "card.h"
#include <string.h>
#include "sm2.h"
#include <time.h>
#include <stdlib.h>


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
if(return_value_finalize_select != SQLITE_OK) {
    printf("return_value_finalize_select ERROR: %s\n", sqlite3_errmsg(db));
    return 1;
}

    return 0;
}

// ADD CARD

int add_card(sqlite3 *db) {
    printf("Enter word: \n");
    char word[128];
    fgets(word, sizeof(word), stdin);
    word[strcspn(word, "\n")] = '\0';
    printf("Enter translation: \n");
    char translation[256];
    fgets(translation, sizeof(translation), stdin);
    translation[strcspn(translation, "\n")] = '\0';
    printf("Enter phonetic: \n");
    char phonetic[128];
    fgets(phonetic, sizeof(phonetic), stdin);
    phonetic[strcspn(phonetic, "\n")] = '\0';
    printf("Enter example: \n");
    char example[512];
    fgets(example, sizeof(example), stdin);
    example[strcspn(example, "\n")] = '\0';
    printf("Enter explanation: \n");
    char explanation[512];
    fgets(explanation, sizeof(explanation), stdin);
    explanation[strcspn(explanation, "\n")] = '\0';

    Card card;
    strcpy(card.word, word);
    strcpy(card.translation, translation);
    strcpy(card.phonetic, phonetic);
    strcpy(card.example, example);
    strcpy(card.explanation, explanation);
    card.easiness = 2.5;
    card.interval = 1;
    card.repetitions = 0;
    time_t t = time(NULL);
    struct tm *now = localtime(&t);

    char buffer[11]; // YYYY-MM-DD
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", now);
    strcpy(card.next_review, buffer);


    // SQLITE3 STATEMENT

    sqlite3_stmt *stmt = NULL;
        
    int return_value_stmt = sqlite3_prepare_v2(db, "INSERT INTO cards (word, translation, phonetic, example, "
    "explanation, easiness, interval, repetitions, next_review) "
    "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)", -1, &stmt, NULL);

    if(return_value_stmt != SQLITE_OK) {
        printf("sqlite3_prepare_v2 ERROR: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    // SQLITE3 BIND

    int return_value_bind_word = sqlite3_bind_text(stmt, 1, card.word, -1, SQLITE_STATIC);
    if(return_value_bind_word != SQLITE_OK) {
        printf("return_value_bind_word ERROR\n");
        return 1;
    }

    int return_value_bind_translation = (sqlite3_bind_text(stmt, 2, card.translation, -1, SQLITE_STATIC));
    if(return_value_bind_translation != SQLITE_OK) {
        printf("return_value_bind_translation ERROR.\n");
        return 1;
    }

    int return_value_bind_phonetic = (sqlite3_bind_text(stmt, 3, card.phonetic, -1, SQLITE_STATIC));
    if(return_value_bind_phonetic != SQLITE_OK) {
        printf("return_value_bind_phonetic ERROR.\n");
        return 1;
    }

    int return_value_bind_example = (sqlite3_bind_text(stmt, 4, card.example, -1, SQLITE_STATIC));
    if(return_value_bind_example != SQLITE_OK) {
        printf("return_value_bind_example ERROR.\n");
        return 1;
    }

    int return_value_bind_explanation = (sqlite3_bind_text(stmt, 5, card.explanation, -1, SQLITE_STATIC));
    if(return_value_bind_explanation != SQLITE_OK) {
        printf("return_value_bind_explanation ERROR.\n");
        return 1;
    }

    int return_value_bind_easiness = (sqlite3_bind_double(stmt, 6, card.easiness));
    if(return_value_bind_easiness != SQLITE_OK) {
        printf("return_value_bind_easiness ERROR.\n");
        return 1;
    }

    int return_value_bind_interval = (sqlite3_bind_int(stmt, 7, card.interval));
    if(return_value_bind_interval != SQLITE_OK) {
        printf("return_value_bind_interval ERROR.\n");
        return 1;
    }

    int return_value_bind_repetitions = (sqlite3_bind_int(stmt, 8, card.repetitions));
    if(return_value_bind_repetitions != SQLITE_OK) {
        printf("return_value_bind_repetitions ERROR.\n");
        return 1;
    }

    int return_value_bind_next_review = (sqlite3_bind_text(stmt, 9, card.next_review, -1, SQLITE_STATIC));
    if(return_value_bind_next_review != SQLITE_OK) {
        printf("return_value_next_review ERROR.\n");
        return 1;
    }

// SQLITE3 STEP

    int return_value_step = sqlite3_step(stmt);
    if(return_value_step != SQLITE_DONE) {
        printf("return_value_step ERROR: %s\n", sqlite3_errmsg(db));
        return 1;
    }

// SQLITE FINALIZE

    int return_value_finalize = sqlite3_finalize(stmt);
    if(return_value_finalize != SQLITE_OK) {
        printf("return_value_finalize ERROR: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    printf("Card added successfully.\n");

    return 0;
}

// REVIEW CARDS

int review_cards(sqlite3 *db) {
    sqlite3_stmt *stmt = NULL;
int return_value_SELECT = sqlite3_prepare_v2(db, "SELECT * FROM cards WHERE date(next_review) <= date('now')", -1, &stmt, NULL);
if(return_value_SELECT != SQLITE_OK) {
    printf("SQL error: %s\n", sqlite3_errmsg(db));
    return 1;
}

while(sqlite3_step(stmt) == SQLITE_ROW) {



    Card card;
    card.id = sqlite3_column_int(stmt, 0);

    const unsigned char *word = sqlite3_column_text(stmt, 1);
    strcpy(card.word, word);
    printf("word: %s\n", word);

    const unsigned char *translation = sqlite3_column_text(stmt, 2);
    strcpy(card.translation, translation);

    const unsigned char *phonetic = sqlite3_column_text(stmt, 3);
    strcpy(card.phonetic, phonetic);
    printf("phonetic: %s\n", phonetic);


    const unsigned char *example = sqlite3_column_text(stmt, 4);
    strcpy(card.example, example);

    const unsigned char *explanation = sqlite3_column_text(stmt, 5);
    strcpy(card.explanation, explanation);

    card.easiness = sqlite3_column_double(stmt, 6);
    card.interval = sqlite3_column_int(stmt, 7);
    card.repetitions = sqlite3_column_int(stmt, 8);

    printf("Press Enter to see the answer.\n");
    char user_buffer_1[128];
    fgets( user_buffer_1, sizeof( user_buffer_1), stdin);
    printf("translation: %s\n", translation);
    printf("example: %s\n", example);
    printf("explanation: %s\n", explanation);


    char q_buffer[8];
    printf("Enter a score from 0 to 5:\n");
    fgets(q_buffer, sizeof(q_buffer), stdin);
    int q = atoi(q_buffer);
    sm2_update(&card, q);


    sqlite3_stmt *stmt_UPDATE = NULL;
    int return_value_UPDATE = sqlite3_prepare_v2(db, "UPDATE cards SET easiness = ?, interval = ?, repetitions = ?, next_review = ? WHERE id = ?", -1, &stmt_UPDATE, NULL);
    if(return_value_UPDATE != SQLITE_OK) {
        printf("SQL error: %s\n", sqlite3_errmsg(db));
        return 1;
}

int return_value_bind_easiness = (sqlite3_bind_double(stmt_UPDATE, 1, card.easiness));
if(return_value_bind_easiness != SQLITE_OK) {
    printf("return_value_bind_easiness ERROR.\n");
    return 1;
}
int return_value_bind_interval = (sqlite3_bind_int(stmt_UPDATE, 2, card.interval));
if(return_value_bind_interval != SQLITE_OK) {
    printf("return_value_bind_interval ERROR.\n");
    return 1;
}

int return_value_bind_repetitions = (sqlite3_bind_int(stmt_UPDATE, 3, card.repetitions));
if(return_value_bind_repetitions != SQLITE_OK) {
    printf("return_value_bind_repetitions ERROR.\n");
    return 1;
}

int return_value_bind_next_review = (sqlite3_bind_text(stmt_UPDATE, 4, card.next_review, -1, SQLITE_STATIC));
if(return_value_bind_next_review != SQLITE_OK) {
    printf("return_value_bind_next_review ERROR.\n");
    return 1;
}

int return_value_bind_id = sqlite3_bind_int(stmt_UPDATE, 5, card.id);
if(return_value_bind_id != SQLITE_OK) {
    printf("return_value_bind_id ERROR.\n");
    return 1;
}

    int return_value_step = sqlite3_step(stmt_UPDATE);
    if(return_value_step != SQLITE_DONE) {
        printf("return_value_step ERROR: %s\n", sqlite3_errmsg(db));
        return 1;
    }

// SQLITE FINALIZE REVIEW CARD

    int return_value_finalize_stmt_update = sqlite3_finalize(stmt_UPDATE);
    if(return_value_finalize_stmt_update != SQLITE_OK) {
        printf("return_value_finalize_stmt_update ERROR: %s\n", sqlite3_errmsg(db));
        return 1;
    }

}
    int return_value_finalize = sqlite3_finalize(stmt);
    if(return_value_finalize != SQLITE_OK) {
        printf("return_value_finalize ERROR: %s\n", sqlite3_errmsg(db));
        return 1;
        
}

    printf("Review session complete.\n");

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

    if(result != SQLITE_OK) {
        printf("sqlite3_open: %s\n", sqlite3_errmsg(db));
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

    if(exec_result != SQLITE_OK) {
        printf("exec_result: %s\n", sqlite3_errmsg(db));
        sqlite3_free(errmsg);
        return 1;
    }


    if (strcmp(argv[1], "--list") == 0) {
        list_cards(db);        
    } else if (strcmp(argv[1], "--add") == 0) {
        add_card(db);
    } else if (strcmp(argv[1], "--review") == 0) {
        review_cards(db);
    }    else {
            printf("invalid command. Usage: %s [--list | --add | --review]\n", argv[0]);
    }

    sqlite3_close(db);

    return 0;
}
