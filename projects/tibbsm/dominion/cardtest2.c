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

    int i;
    int flag;

    initializeGame(numPlayer, k, seed, &key);

    printf("[ TESTING: Smithy room Card - Part Two ]\n");

    memcpy(&tester, &key, sizeof(struct gameState));


    for (i = 0; i < key.handCount[player]; i++) {
        // printf("%d) %d %d\n", i, key.hand[player][i], tester.hand[player][i]);
        if (key.hand[player][i] != tester.hand[player][i]) {
            flag = 0;
        }
    }  

    cardEffect(smithy, choice1, choice2, choice3, &tester, handpos, &bonus);

    // Smithy room should not alter the numPlayers variable of the gamestate.
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

    // Smithy room should not alter the outpostPlayed variable of the gamestate.
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

    // Smithy room should not alter the outpostTurn variable of the gamestate.
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

    // Smithy room should not alter the whoseTurn variable of the gamestate.
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

    // Smithy room should not alter the phase variable of the gamestate.
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

    // Smithy room should not alter the numActions variable of the gamestate.
    printf("(Test 6) Checking gameState's numActions variable: ");  
    if (tester.numActions != key.numActions)
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

    // Smithy room should not alter the numBuys variable of the gamestate.
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

    // Smithy room should not alter the original cards in the players hand.
    printf("(Test 9) Checking that original cards in the hand are still there: ");  
    flag = 1;
    for (i = 0; i < key.handCount[player]; i++) {
        // printf("%d) %d %d\n", i, key.hand[player][i], tester.hand[player][i]);
        if (key.hand[player][i] != tester.hand[player][i]) {
            flag = 0;
        }
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

    // Smithy room should be the last card added to playedCards.
    printf("(Test 10) Checking playedCards variable: ");  
    if (tester.playedCards[tester.playedCardCount - 1] == smithy)
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