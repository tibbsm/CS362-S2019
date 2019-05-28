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

void testGreatHall(struct gameState *key, double *numPlayersFails, double *outpostPlayedFails, double *outpostTurnFails, 
    double *whoseTurnFails, double *phaseFails, double *numActionsFails, double *coinsFails, double *numBuysFails, 
    double *playedCardsFails, double *handCountFails, double *deckCountFails, double *total, int itr) 
{
    struct gameState tester;

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

    memcpy(&tester, key, sizeof(struct gameState));

    cardEffect(great_hall, choice1, choice2, choice3, &tester, handpos, &bonus);

        // Great Hall should not alter the numPlayers variable of the gamestate.
    printf("(Test %d.1) Checking gameState's numPlayers variable: ", itr);  
    if (!assertTrue(tester.numPlayers == key->numPlayers))
        (*numPlayersFails)++;

    (*total)++;

    // Great Hall should not alter the outpostPlayed count
    printf("(Test %d.2) Checking gameState's outpostPlayed variable: ", itr);  
    if (!assertTrue(tester.outpostPlayed == key->outpostPlayed))
        (*outpostPlayedFails)++;

    (*total)++;

    // Great Hall should not alter the outpostTurn variable of the gamestate.
    printf("(Test %d.3) Checking gameState's outpostTurn variable: ", itr);  
    if (!assertTrue(tester.outpostTurn == key->outpostTurn))
        (*outpostPlayedFails)++;

    (*total)++;

    // Great Hall should not alter the whoseTurn variable of the gamestate.
    printf("(Test %d.4) Checking gameState's whoseTurn variable: ", itr);  
    if (!assertTrue(tester.whoseTurn == key->whoseTurn))
        (*whoseTurnFails)++;

    (*total)++;

    // Great Hall should not alter the phase variable of the gamestate.
    printf("(Test %d.5) Checking gameState's phase variable: ", itr);  
    if (!assertTrue(tester.phase == key->phase))
        (*phaseFails)++;

    (*total)++;

    // Great Hall should increment the numActions variable of the gamestate.
    printf("(Test %d.6) Checking gameState's numActions variable: ", itr);  
    if (!assertTrue(tester.numActions == key->numActions + 1))
        (*numActionsFails)++;

    (*total)++;        

    // Adventurer should not alter the coins variable of the gamestate.
    printf("(Test %d.7) Checking gameState's coins variable: ", itr);  
    if (!assertTrue(tester.coins == key->coins))
        (*coinsFails)++;

    (*total)++;

    // Great Hall should not alter the numBuys variable of the gamestate.
    printf("(Test %d.8) Checking gameState's numBuys variable: ", itr);  
    if (!assertTrue(tester.numBuys == key->numBuys))
        (*numBuysFails)++;

    (*total)++;

    // Great Hall should be the last card added to playedCards.
    printf("(Test %d.9) Checking playedCards variable: ", itr);  
    if (!assertTrue(tester.playedCards[tester.playedCardCount - 1] == great_hall))
        (*playedCardsFails)++;

    (*total)++;

    // Great Hall draws 1 cards & discards one, so the tester state should have the same amount of cards in handCount.
    printf("(Test %d.10) Checking player handCount after playing great hall card: ", itr);
    if (!assertTrue(tester.handCount[tester.whoseTurn] == key->handCount[key->whoseTurn] - 1 + 1))
        (*handCountFails)++;

    (*total)++;

    // Great Hall draws 1 cards, so the tester state should have 1 less cards in deckCount.
    printf("(Test %d.11) Checking player deckCount after playing great hall card: ", itr);
    if (!assertTrue(tester.deckCount[tester.whoseTurn] == key->deckCount[key->whoseTurn] - 1))
        (*deckCountFails)++;

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
    
    double total, numPlayersFails,outpostPlayedFails,outpostTurnFails,whoseTurnFails,phaseFails,
        numActionsFails,coinsFails,numBuysFails,playedCardsFails,handCountFails,deckCountFails;

    total = numPlayersFails = outpostPlayedFails = outpostTurnFails = whoseTurnFails = phaseFails = 
        numActionsFails = coinsFails = numBuysFails = playedCardsFails = handCountFails = deckCountFails = 0;  

    printf("[ TESTING: Great Hall Card ]\n");

    for (i = 0; i < itr; ++i)
    {
        initializeGame(numPlayer, k, seed, &key);

        key.whoseTurn = rand() % numPlayer;
        key.deckCount[key.whoseTurn] = rand() % MAX_DECK;
        key.playedCardCount = rand() % MAX_DECK;

        testGreatHall(&key, &numPlayersFails, &outpostPlayedFails, &outpostTurnFails, &whoseTurnFails, &phaseFails, 
            &numActionsFails, &coinsFails, &numBuysFails, &playedCardsFails, &handCountFails, &deckCountFails, &total, i);
    }

    printf("\n(Test 1) Checking gameState's numPlayers variable: FAILED %.0f tests.\n", numPlayersFails);  
    printf("(Test 2) Checking gameState's outpostPlayed variable: FAILED %.0f tests.\n", outpostPlayedFails);  
    printf("(Test 3) Checking gameState's outpostTurn variable: FAILED %.0f tests.\n", outpostTurnFails);  
    printf("(Test 4) Checking gameState's whoseTurn variable: FAILED %.0f tests.\n", whoseTurnFails);  
    printf("(Test 5) Checking gameState's phase variable: FAILED %.0f tests.\n", phaseFails);  
    printf("(Test 6) Checking gameState's numActions variable: FAILED %.0f tests.\n", numActionsFails);  
    printf("(Test 7) Checking gameState's coins variable: FAILED %.0f tests.\n", coinsFails);  
    printf("(Test 8) Checking gameState's numBuys variable: FAILED %.0f tests.\n", numBuysFails);  
    printf("(Test 9) Checking playedCards variable: FAILED %.0f tests.\n", playedCardsFails);  
    printf("(Test 10) Checking player handCount after playing great hall card: FAILED %.0f tests.\n", handCountFails);
    printf("(Test 11) Checking player deckCount after playing great hall card: FAILED %.0f tests.\n", deckCountFails);

    double fails = numPlayersFails + outpostPlayedFails + outpostTurnFails + whoseTurnFails + phaseFails + numActionsFails + 
        coinsFails + numBuysFails + playedCardsFails + handCountFails + deckCountFails; 
    double passes = total - fails;
    printf("\nPassed %.0f out of %.0f tests.\n", passes, total); 
    printf("Failed %.0f out of %.0f tests.\n", fails, total); 
    printf("Pass rate: %.2f%%\n\n", passes/total * 100); 

    return 0;
}