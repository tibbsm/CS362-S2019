CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)


#########

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


randomtestresults:
	echo " ▼ [ START OF Random Test 1(randomtestadventurer.c) ] ▼ \n" >> randomtestresults.out
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o  $(CFLAGS)
	./randomtestadventurer >> randomtestresults.out
	gcov -fb dominion.c >> randomtestresults.out
	echo " ▲ [ END OF Random Test 1(randomtestadventurer.c) ] ▲ \n" >> randomtestresults.out
	echo " ▼ [ START OF Random Test 2(randomtestcard1.c) ] ▼ \n" >> randomtestresults.out
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o  $(CFLAGS)
	./randomtestcard1 >> randomtestresults.out
	gcov -fb dominion.c >> randomtestresults.out
	echo " ▲ [ END OF Random Test 2(randomtestcard1.c) ] ▲ \n" >> randomtestresults.out
	echo " ▼ [ START OF Random Test 3(randomtestcard2.c) ] ▼ \n" >> randomtestresults.out
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o  $(CFLAGS)
	./randomtestcard2 >> randomtestresults.out
	gcov -fb dominion.c >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out
	echo " ▲ [ END OF Random Test 3(randomtestcard2.c) ] ▲ \n" >> randomtestresults.out

unittestresults: unittest1.c dominion.o rngs.o
	echo " ▼ [ START OF UNITTEST 1 (unittest1.c) ] ▼ \n" >> unittestresults.out
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o  $(CFLAGS)
	./unittest1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	echo " ▲ [ END OF UNITTEST 1 (unittest1.c) ] ▲ \n" >> unittestresults.out

	echo " ▼ [ START OF UNITTEST 2 (unittest2.c) ] ▼ \n" >> unittestresults.out
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o  $(CFLAGS)
	./unittest2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	echo " ▲ [ END OF UNITTEST 2 (unittest2.c) ] ▲ \n" >> unittestresults.out

	echo " ▼ [ START OF UNITTEST 3 (unittest3.c) ] ▼ \n" >> unittestresults.out
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o  $(CFLAGS)
	./unittest3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	echo " ▲ [ END OF UNITTEST 3 (unittest3.c) ] ▲ \n" >> unittestresults.out

	echo " ▼ [ START OF UNITTEST 4 (unittest4.c) ] ▼ \n" >> unittestresults.out
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o  $(CFLAGS)
	./unittest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	echo " ▲ [ END OF UNITTEST 4 (unittest4.c) ] ▲ \n" >> unittestresults.out

	echo " ▼ [ START OF UNITTEST 5 (cardtest1.c) ] ▼ \n" >> unittestresults.out
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o  $(CFLAGS)
	./cardtest1 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	echo " ▲ [ END OF UNITTEST 5 (cardtest1.c) ] ▲ \n" >> unittestresults.out

	echo " ▼ [ START OF UNITTEST 6 (cardtest2.c) ] ▼ \n" >> unittestresults.out
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o  $(CFLAGS)
	./cardtest2 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	echo " ▲ [ END OF UNITTEST 6 (cardtest1.c) ] ▲ \n" >> unittestresults.out

	echo " ▼ [ START OF UNITTEST 7 (cardtest3.c) ] ▼ \n" >> unittestresults.out
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o  $(CFLAGS)
	./cardtest3 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	echo " ▲ [ END OF UNITTEST 7 (cardtest1.c) ] ▲ \n" >> unittestresults.out

	echo " ▼ [ START OF UNITTEST 8 (cardtest4.c) ] ▼ \n" >> unittestresults.out
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o  $(CFLAGS)
	./cardtest4 >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	echo " ▲ [ END OF UNITTEST 8 (cardtest1.c) ] ▲ \n" >> unittestresults.out

cleantest:
	rm -f unittestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe 
