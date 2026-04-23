// GOAL: Implement the SM2 spaced repetition algorithm to update card scheduling and review dates.

#include "card.h"
#include "sm2.h"
#include <time.h>
#include <string.h>


void sm2_update(Card *card, int q) { 
if (q < 3) {
    card->interval = 1;
    card->repetitions = 0;
}       else {
            card->repetitions++;
            if (card->repetitions == 1) {
                card->interval = 1;
            
            }   else if (card->repetitions == 2) {
                card->interval = 6;
            
            }   else {
                    card->interval = card->interval * card->easiness;
            }        

}


        card->easiness = card->easiness + (0.1 - (5 - q) * (0.08 + (5 - q) * 0.02));
        if (card->easiness < 1.3) {
            card->easiness = 1.3;
}

        time_t t = time(NULL);
        struct tm *now = localtime(&t);
        now->tm_mday += card->interval;
        mktime(now);
        char buffer[11];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", now);
        strcpy(card->next_review, buffer);



}