
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

void testAdventurer(struct gameState *key, double *handCountFails, double *deckCountFails, double *lastCardFails, 
    double *penUltCardFails, double *playedCardCountFails, double *discardCountFails, double *discardFails, double *total, int itr) 
{
    struct gameState tester;

    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

    memcpy(&tester, key, sizeof(struct gameState));

    cardEffect(adventurer, choice1, choice2, choice3, &tester, handpos, &bonus);

    // Adventurer draws two cards & discards one, so the tester state should have 1 more card in handCount.
    printf("(Test %d.1) Checking player handCount after playing adventurer card: ", itr);
    if (!assertTrue(tester.handCount[tester.whoseTurn] != key->handCount[key->whoseTurn] + 2 - 1))
        (*handCountFails)++;

    (*total)++;   

    // Adventurer draws two cards, so the tester state should have 2 less cards in deckCount.
    printf("(Test %d.2) Checking player deckCount after playing adventurer card: ", itr);
    if (!assertTrue(tester.deckCount[tester.whoseTurn] != key->deckCount[key->whoseTurn] - 2))
        (*deckCountFails)++;

    (*total)++;

    // Adventurer draws two treasure cards, so the last card in tester should be a treasure card.
    printf("(Test %d.3) Checking player's last card in hand after playing adventurer card: ", itr);
    if (!assertTrue(tester.hand[tester.whoseTurn][tester.handCount[tester.whoseTurn]-1] == copper ||
                    tester.hand[tester.whoseTurn][tester.handCount[tester.whoseTurn]-1] == silver ||
                    tester.hand[tester.whoseTurn][tester.handCount[tester.whoseTurn]-1] == gold))
        (*lastCardFails)++;

    (*total)++;

    // Adventurer draws two treasure cards, so the second to last card in tester should be a treasure card.
    printf("(Test %d.4) Checking player's second to last card in hand after playing adventurer card: ", itr);
    if (!assertTrue(tester.hand[tester.whoseTurn][tester.handCount[tester.whoseTurn]-2] == copper ||
                    tester.hand[tester.whoseTurn][tester.handCount[tester.whoseTurn]-2] == silver ||
                    tester.hand[tester.whoseTurn][tester.handCount[tester.whoseTurn]-2] == gold))
        (*penUltCardFails)++;

    (*total)++;

    // Players played card count should be incremented by 1
    printf("(Test %d.5) Checking player's played card count count after playing adventurer card: ", itr);
    if (!assertTrue(tester.playedCardCount == key->playedCardCount + 1))
        (*playedCardCountFails)++;

    (*total)++;

    // Reset tester
    memcpy(&tester, key, sizeof(struct gameState));

    // Arrange deck so that 2 adventurer cards will be drawn, followed by 2 coppers
    int deckCount = tester.deckCount[tester.whoseTurn]-1;
    tester.deck[tester.whoseTurn][deckCount] = adventurer;
    tester.deck[tester.whoseTurn][--deckCount] = adventurer;
    tester.deck[tester.whoseTurn][--deckCount] = copper;
    tester.deck[tester.whoseTurn][--deckCount] = copper;

    cardEffect(adventurer, choice1, choice2, choice3, &tester, handpos, &bonus);

    // Adventurer should have added two adventurer cards to the discard pile.
    printf("(Test %d.6) Checking discardCount variable: ", itr);
    if (!assertTrue(tester.discardCount[tester.whoseTurn] == 2))
        (*discardCountFails)++;

    (*total)++;

    // Adventurer should have added two adventurer cards to the discard pile.
    printf("(Test %d.7) Checking discard pile for correct cards: ", itr);
    if (!assertTrue(tester.discard[tester.whoseTurn][0] == adventurer && tester.discard[tester.whoseTurn][1] == adventurer))
        (*discardFails)++;

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
    
    double handCountFails, deckCountFails, lastCardFails, penUltCardFails, playedCardCountFails, discardCountFails, discardFails, total;
    handCountFails = deckCountFails = lastCardFails = penUltCardFails = playedCardCountFails = total = 0; 

    printf("[ TESTING: Adventurer Card ]\n");

    for (i = 0; i < itr; i++)
    {
        initializeGame(numPlayer, k, seed, &key);

        key.whoseTurn = rand() % numPlayer;
        key.deckCount[key.whoseTurn] = rand() % MAX_DECK;
        key.playedCardCount = rand() % MAX_DECK;

        testAdventurer(&key, &handCountFails, &deckCountFails, &lastCardFails, &penUltCardFails, 
            &playedCardCountFails, &discardCountFails, &discardFails, &total, i);
    }

    printf("\n\n(Test 1) Checking player handCount after playing adventurer card: FAILED %.0f tests.\n", handCountFails);
    printf("(Test 2) Checking player deckCount after playing adventurer card: FAILED %.0f tests.\n", deckCountFails);
    printf("(Test 3) Checking player's last card in hand after playing adventurer card: FAILED %.0f tests.\n", lastCardFails);
    printf("(Test 4) Checking player's second to last card in hand after playing adventurer card: FAILED %.0f tests.\n", penUltCardFails);
    printf("(Test 5) Checking player's played card count count after playing adventurer card: FAILED %.0f tests.\n", playedCardCountFails);
    printf("(Test 6) Checking discardCount variable: FAILED %.0f tests.\n", discardCountFails);  
    printf("(Test 7) Checking discard pile for correct cards: FAILED %.0f tests.\n", discardFails);  

    printf("\nPassed %.0f out of %.0f tests.\n", total - (handCountFails + deckCountFails + lastCardFails + penUltCardFails + playedCardCountFails + discardCountFails + discardFails), total); 
    printf("Failed %.0f out of %.0f tests.\n", handCountFails + deckCountFails + lastCardFails + penUltCardFails + playedCardCountFails + discardCountFails + discardFails, total); 
    printf("Pass rate: %.2f%%\n\n", (total - handCountFails + deckCountFails + lastCardFails + penUltCardFails + playedCardCountFails + discardCountFails + discardFails)/total * 100); 

    return 0;
}