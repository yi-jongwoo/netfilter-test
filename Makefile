all: netfilter-test

netfilter-test : main.o proto_structures.o
	g++ -o netfilter-test main.o proto_structures.o -lnetfilter_queue

proto_structures.o : proto_structures.cpp proto_structures.h
	g++ -c -o proto_structures.o proto_structures.cpp
main.o : main.cpp proto_structures.h addr_set.h
	g++ -c -o main.o main.cpp

clean :
	rm -f *.o
	rm -f netfilter-test
