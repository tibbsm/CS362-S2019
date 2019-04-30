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

    initializeGame(numPlayer, k, seed, &key);

    printf("[ TESTING: Adventurer Card ]\n");

    memcpy(&tester, &key, sizeof(struct gameState));

    cardEffect(adventurer, choice1, choice2, choice3, &tester, handpos, &bonus);

struct gameState {
  int discard[MAX_PLAYERS][MAX_DECK];
  int discardCount[MAX_PLAYERS];
  int playedCards[MAX_DECK];
  int playedCardCount;
};

    // Adventurer draws two cards & discards one, so the tester state should have 1 more card in handCount.
    printf("(Test 1) Checking player handCount after playing adventurer card: ");
    if (tester.handCount[player] != key.handCount[player] + 2 - 1)
    {   
        fails++;
        total++;
        printf("FAILED\n");
    } else {
        passes++;
        total++;
        printf("PASSED\n");
    }

    // Adventurer draws two cards, so the tester state should have 2 less cards in deckCount.
    printf("(Test 2) Checking player deckCount after playing adventurer card: ");
    if (tester.deckCount[player] != key.deckCount[player] - 2)
    {   
        fails++;
        total++;
        printf("FAILED\n");
    } else {
        passes++;
        total++;
        printf("PASSED\n");
    }

    // Adventurer draws two treasure cards, so the last card in tester should be a treasure card.
    printf("(Test 3) Checking player's last card in hand after playing adventurer card: ");
    if (tester.hand[player][tester.handCount[player]-1] == copper ||
        tester.hand[player][tester.handCount[player]-1] == silver ||
        tester.hand[player][tester.handCount[player]-1] == gold)
    {
        passes++;
        total++;
        printf("PASSED\n");
    } else {   
        fails++;
        total++;
        printf("FAILED\n");
    }   

    // Adventurer draws two treasure cards, so the second to last card in tester should be a treasure card.
    printf("(Test 4) Checking player's second to last card in hand after playing adventurer card: ");
    if (tester.hand[player][tester.handCount[player]-2] == copper ||
        tester.hand[player][tester.handCount[player]-2] == silver ||
        tester.hand[player][tester.handCount[player]-2] == gold)
    {
        passes++;
        total++;
        printf("PASSED\n");
    } else {   
        fails++;
        total++;
        printf("FAILED\n");
    }  

    // Players played card count should be incremented by 1
    printf("(Test 5) Checking player's played card count count after playing adventurer card: ");
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