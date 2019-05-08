default: 
	-make build 
	-make test 
	-make clean 

build:
	gcc -o testme testme.c -coverage 
	./testme

test:
	gcov testme.c

clean: 
	rm -f testme.c.gcov testme.gcda testme.gcno	 
