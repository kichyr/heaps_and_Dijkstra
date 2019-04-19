all: utest

utest: storage.o test.o
	g++ storage.o test.o -o utest

storage.o: storage.cpp
	gcc -c storage.cpp -o storage.o

test.o: test.cpp
	gcc -c test.cpp -o test.o

clean:
	rm -rf *.o utest