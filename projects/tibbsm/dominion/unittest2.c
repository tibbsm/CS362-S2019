#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int i = 0;
    int seed = 1000;

    // Seg faults on more than 4 players
    int numPlayer = 4;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int player = 0;
    struct gameState key, tester;
    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, 
        smithy, village, baron, great_hall};

    int flag = 0;

    double passes = 0, fails = 0, total = 0;

    initializeGame(numPlayer, k, seed, &key);

    printf("[ TESTING: Council Room Card ]\n");

    memcpy(&tester, &key, sizeof(struct gameState));

    cardEffect(council_room, choice1, choice2, choice3, &tester, handpos, &bonus);

    // council_room draws 4 cards & discards 1, so the tester state should have 3 more card in handCount.
    printf("(Test 1) Checking player handCount after playing Council Room Card: ");
    if (tester.handCount[player] != key.handCount[player] + 3)
    {   
        fails++;
        total++;
        printf("FAILED\n");
    } else {
        passes++;
        total++;
        printf("PASSED\n");
    }

    // council_room draws four cards, so the tester state should have 4 less cards in deckCount.
    printf("(Test 2) Checking player deckCount after playing adventurer card: ");
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
    printf("(Test 3) Checking player's played card count count after playing council room card: ");
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

    // Council card grants the player another buy action, so tester should have 1 more.
    printf("(Test 4) Checking player's number of buy actions: ");
    if (tester.numBuys == key.numBuys + 1)
    {
        passes++;
        total++;
        printf("PASSED\n");
    } else {   
        fails++;
        total++;
        printf("FAILED\n");
    } 

    flag = 1;
    // Council card grants each other player another card, so each other player should have +1 card in hand
    printf("(Test 5) Checking other %d player(s)'s hand counts: ", numPlayer - 1);
    for (i = 1; i < numPlayer; i++ )
    {
        if (tester.handCount[player+1] != key.handCount[player+1] + 1)
            flag = 0;
    }
    if (flag == 0)
    {   
        fails++;
        total++;
        printf("FAILED\n");
    } else {
        passes++;
        total++;
        printf("PASSED\n");
    }

    printf("Passed %.0f out of %.0f tests.\n", passes, total); 
    printf("Failed %.0f out of %.0f tests.\n", fails, total); 
    printf("Pass rate: %.2f%%\n\n", passes/total * 100); 

    return 0;
}