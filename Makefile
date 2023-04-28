all: netfilter-test

netfilter-test : main.o
	g++ -o netfilter-test main.o -lnetfilter_queue

main.o : main.cpp
	g++ -c -o main.o main.cpp

clean :
	rm -f *.o
	rm -f netfilter-test
