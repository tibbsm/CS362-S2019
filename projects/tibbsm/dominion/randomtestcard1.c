#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TRUE 1 
#define FALSE 0

int assertTrue(int tf) 
{
    if (tf == FALSE)
    {
        printf("FAILED\n");
        return FALSE;
    } 
    
    printf("PASSED\n");
    return TRUE;    
}

void testVillage(struct gameState *key, double *handCountFails, double *deckCountFails, double *playedCardCountFails, double *numActionsFails, double *total, int itr) 
{
    struct gameState tester;

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

    memcpy(&tester, key, sizeof(struct gameState));

    cardEffect(village, choice1, choice2, choice3, &tester, handpos, &bonus);

    // Village draws 1 cards & discards 1, so the tester state should have the same handCount.
    printf("(Test %d.1) Checking player handCount after playing Village Card: ", itr);
    if (!assertTrue(tester.handCount[tester.whoseTurn] == key->handCount[key->whoseTurn]))
        (*handCountFails)++;

    (*total)++;

    // Village draws 1 cards, so the tester state should have 1 less cards in deckCount.
    printf("(Test %d.2) Checking player deckCount after playing Village card: ", itr);
    if (!assertTrue(tester.deckCount[tester.whoseTurn] == key->deckCount[key->whoseTurn] - 1))
        (*deckCountFails)++;

    (*total)++;

    // Players played card count should be incremented by 1
    printf("(Test %d.3) Checking player's played card count count after playing Village card: ", itr);
    if (!assertTrue(tester.playedCardCount == key->playedCardCount + 1))
        (*playedCardCountFails)++;

    (*total)++;

    // Village grants 2 action, so the tester state should have 2 extra action.
    printf("(Test %d.4) Checking player action count after playing Village card: ", itr);
    if (!assertTrue(tester.numActions == key->numActions + 2))
        (*numActionsFails)++;

    (*total)++;
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    int seed = rand() % 1000;

    int itr = 1000;

    int numPlayer = 2;

    int i;

    struct gameState key;    

    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    
    double total, handCountFails, deckCountFails, playedCardCountFails, numActionsFails;
    total = handCountFails = deckCountFails = playedCardCountFails = numActionsFails = 0;  

    printf("[ TESTING: Village Card ]\n");

    for (i = 0; i < itr; i++)
    {
        initializeGame(numPlayer, k, seed, &key);

        key.whoseTurn = rand() % numPlayer;
        key.deckCount[key.whoseTurn] = rand() % MAX_DECK;
        key.playedCardCount = rand() % MAX_DECK;

        testVillage(&key, &handCountFails, &deckCountFails, &playedCardCountFails, &numActionsFails, &total, i);
    }

    printf("\n\n(Test 1) Checking player handCount after playing Village Card: FAILED %.0f tests.\n", handCountFails);
    printf("(Test 2) Checking player deckCount after playing Village card: FAILED %.0f tests.\n", deckCountFails);
    printf("(Test 3) Checking player's played card count count after playing Village card: FAILED %.0f tests.\n", playedCardCountFails);
    printf("(Test 4) Checking player action count after playing Village card: FAILED %.0f tests.\n", numActionsFails);

    printf("\nPassed %.0f out of %.0f tests.\n", total - (handCountFails + deckCountFails + playedCardCountFails + numActionsFails), total); 
    printf("Failed %.0f out of %.0f tests.\n", (handCountFails + deckCountFails + playedCardCountFails + numActionsFails), total); 
    printf("Pass rate: %.2f%%\n\n", (total - (handCountFails + deckCountFails + playedCardCountFails + numActionsFails))/total * 100); 

    return 0;
}