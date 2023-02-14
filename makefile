CC = g++
CFLAGS = -g -o p2 -std=-Wc++11

hashtable1.o: hashtable1.cpp hashtable1.h
	g++ -c hashtable1.cpp

hashtable2.o: hashtable2.cpp hashtable2.h
	g++ -c hashtable2.cpp

hashtable3.o: hashtable3.cpp hashtable3.h
	g++ -c hashtable3.cpp

main.o: main.cpp hashtable1.h hashtable2.h hashtable3.h
	g++ -c main.cpp 

p2: main.o hashtable1.o hashtable2.o hashtable3.o
	$(CC) $(CFLAGS) main.o hashtable1.o hashtable2.o hashtable3.o

submit:
	zip submit.zip makefile main.cpp hashtable1.cpp hashtable1.h hashtable2.cpp hashtable2.h hashtable3.cpp hashtable3.h

clean:
	rm *.o p2