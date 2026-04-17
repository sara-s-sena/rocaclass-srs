// GOAL: to define the flashcard model and prevent multiple inclusion of the same header file. 

#ifndef CARD_H
#define CARD_H

typedef struct {
    int id;                         // unique card ID (SQLite primary key)
    char word[128];                 // the word or phrase in Portuguese
    char translation[256];          // English or Portuguese gloss
    char phonetic[128];             // Mineiro phonetic transcription
    char example[512];              // example sentence in context
    char explanation[512];          // brief explanation
    float easiness;                 // EF, starts at 2.5
    int interval;                   // days until next review
    int repetitions;                // number of successful reviews
    char next_review[11];           // ISO date: "YYYY-MM-DD"
} Card;

#endif
