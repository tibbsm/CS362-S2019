#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int seed = 1000;

    int numPlayer = 4;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int player = 0;
    struct gameState key, tester;
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, 
        smithy, village, baron, great_hall};

    double passes = 0, fails = 0, total = 0;

    initializeGame(numPlayer, k, seed, &key);

    printf("[ TESTING: Smithy Card ]\n");

    memcpy(&tester, &key, sizeof(struct gameState));

    cardEffect(smithy, choice1, choice2, choice3, &tester, handpos, &bonus);

    // smithy draws 3 cards & discards 1, so the tester state should have 2 more card in handCount.
    printf("(Test 1) Checking player handCount after playing Smithy Card: ");
    if (tester.handCount[player] != key.handCount[player] + 2)
    {   
        fails++;
        total++;
        printf("FAILED\n");
    } else {
        passes++;
        total++;
        printf("PASSED\n");
    }

    // smithy draws 3 cards, so the tester state should have 3 less cards in deckCount.
    printf("(Test 2) Checking player deckCount after playing Smithy card: ");
    if (tester.deckCount[player] != key.deckCount[player] - 4)
    {   
        fails++;
        total++;
        printf("FAILED\n");
    } else {
        passes++;
        total++;
        printf("PASSED\n");
    }

    // Players played card count should be incremented by 1
    printf("(Test 3) Checking player's played card count count after playing smithy card: ");
    if (tester.playedCardCount == key.playedCardCount + 1)
    {
        passes++;
        total++;
        printf("PASSED\n");
    } else {   
        fails++;
        total++;
        printf("FAILED\n");
    } 

    printf("Passed %.0f out of %.0f tests.\n", passes, total); 
    printf("Failed %.0f out of %.0f tests.\n", fails, total); 
    printf("Pass rate: %.2f%%\n\n", passes/total * 100); 

    return 0;
}