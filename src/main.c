#include <stdio.h>
#include "sqlite3.h"
#include "card.h"
#include <string.h>

int main() {
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



    Card card;
    strcpy(card.word, "Trem (Lit. 'Train')");
    strcpy(card.translation, "Thing");
    strcpy(card.phonetic, "Trayng");
    strcpy(card.example, "Esse trem tá quente demais.");
    strcpy(card.explanation, "Any object, tool, food, or thing you can't ‒ or won't ‒ name in the moment.");
    card. easiness = 2.5;
    card.interval = 1;
    card.repetitions = 0;
    strcpy(card.next_review, "2026-04-15");


// SQLITE3 STATEMENT

    sqlite3_stmt *stmt = NULL;
        
    int return_value_stmt = sqlite3_prepare_v2(db, "INSERT INTO cards (word, translation, phonetic, example, "
    "explanation, easiness, interval, repetitions, next_review) "
    "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)", -1, &stmt, NULL);

    if(return_value_stmt == SQLITE_OK) {
        printf("sqlite3_prepare_v2 OK.\n");
    }   else {
            printf("sqlite3_prepare_v2 ERROR.\n");
            return 1;

            printf("SQL error: %s\n", sqlite3_errmsg(db));
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
    if(return_value_step == SQLITE_DONE) {
        printf("sqlite3_value_step OK.\n");
    }   else {
            printf("sqlite3_value_step ERROR.\n");
            return 1;
    }

// SQLITE FINALIZE

    int return_value_finalize = sqlite3_finalize(stmt);
    if(return_value_finalize == SQLITE_OK) {
        printf("return_value_finalize OK.\n");
    }   else {
            printf("return_value_finalize ERROR.\n");
            return 1;
    }

    sqlite3_close(db);

    return 0;
}