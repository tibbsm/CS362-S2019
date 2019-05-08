default: 
	-make build 
	-make test 

build:
	gcc -o testme testme.c -coverage 
	time ./testme

test:
	gcov testme.c

clean: 
	rm -f testme.c.gcov testme.gcda testme.gcno	 
