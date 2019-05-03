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
    int numPlayer = 2;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int player = 0;
    struct gameState key, tester;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, 
        smithy, village, baron, great_hall};
    double passes = 0, fails = 0, total = 0;

    // int flag;

    initializeGame(numPlayer, k, seed, &key);

    printf("[ TESTING: Great Hall Card ]\n");

    memcpy(&tester, &key, sizeof(struct gameState));

    cardEffect(great_hall, choice1, choice2, choice3, &tester, handpos, &bonus);

    // Great Hall should not alter the numPlayers variable of the gamestate.
    printf("(Test 1) Checking gameState's numPlayers variable: ");  
    if (tester.numPlayers != key.numPlayers)
    {   
        fails++;
        total++;
        printf("FAILED\n");
    } else {
        passes++;
        total++;
        printf("PASSED\n");
    }

    // Great Hall should not alter the outpostPlayed count
    printf("(Test 2) Checking gameState's outpostPlayed variable: ");  
    if (tester.outpostPlayed != key.outpostPlayed)
    {   
        fails++;
        total++;
        printf("FAILED\n");
    } else {
        passes++;
        total++;
        printf("PASSED\n");
    }

    // Great Hall should not alter the outpostTurn variable of the gamestate.
    printf("(Test 3) Checking gameState's outpostTurn variable: ");  
    if (tester.outpostTurn != key.outpostTurn)
    {   
        fails++;
        total++;
        printf("FAILED\n");
    } else {
        passes++;
        total++;
        printf("PASSED\n");
    }

    // Great Hall should not alter the whoseTurn variable of the gamestate.
    printf("(Test 4) Checking gameState's whoseTurn variable: ");  
    if (tester.whoseTurn != key.whoseTurn)
    {   
        fails++;
        total++;
        printf("FAILED\n");
    } else {
        passes++;
        total++;
        printf("PASSED\n");
    }

    // Great Hall should not alter the phase variable of the gamestate.
    printf("(Test 5) Checking gameState's phase variable: ");  
    if (tester.phase != key.phase)
    {   
        fails++;
        total++;
        printf("FAILED\n");
    } else {
        passes++;
        total++;
        printf("PASSED\n");
    }

    // Great Hall should increment the numActions variable of the gamestate.
    printf("(Test 6) Checking gameState's numActions variable: ");  
    if (tester.numActions != key.numActions + 1)
    {   
        fails++;
        total++;
        printf("FAILED\n");
    } else {
        passes++;
        total++;
        printf("PASSED\n");
    }

    // Adventurer should not alter the coins variable of the gamestate.
    printf("(Test 7) Checking gameState's coins variable: ");  
    if (tester.coins != key.coins)
    {   
        fails++;
        total++;
        printf("FAILED\n");
    } else {
        passes++;
        total++;
        printf("PASSED\n");
    }

    // Great Hall should not alter the numBuys variable of the gamestate.
    printf("(Test 8) Checking gameState's numBuys variable: ");  
    if (tester.numBuys == key.numBuys)
    {   
        passes++;
        total++;
        printf("PASSED\n");
    } else {
        fails++;
        total++;
        printf("FAILED\n");
    }

    // Great Hall should be the last card added to playedCards.
    printf("(Test 9) Checking playedCards variable: ");  
    if (tester.playedCards[tester.playedCardCount - 1] == great_hall)
    {   
        fails++;
        total++;
        printf("FAILED\n");
    } else {
        passes++;
        total++;
        printf("PASSED\n");
    }


    // Great Hall draws 1 cards & discards one, so the tester state should have the 1 less card in handCount.
    printf("(Test 10) Checking player handCount after playing outpost card: ");
    if (tester.handCount[player] != key.handCount[player] - 1 + 1)
    {   
        fails++;
        total++;
        printf("FAILED\n");
    } else {
        passes++;
        total++;
        printf("PASSED\n");
    }

    // Great Hall draws 1 cards & discards one, so the tester state should have the same amount of cards in handCount.
    printf("(Test 11) Checking player handCount after playing great hall card: ");
    if (tester.handCount[player] != key.handCount[player] + 1 - 1)
    {   
        fails++;
        total++;
        printf("FAILED\n");
    } else {
        passes++;
        total++;
        printf("PASSED\n");
    }

    // Great Hall draws 1 cards, so the tester state should have 1 less cards in deckCount.
    printf("(Test 12) Checking player deckCount after playing great hall card: ");
    if (tester.deckCount[player] != key.deckCount[player] - 1)
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