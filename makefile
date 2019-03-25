Ticket: Implementation2.o main.o
	g++ main.o Implementation2.o -o Ticket
Implementation2.o : Implementation2.cpp classes.h 
	g++ -c Implementation2.cpp
main.o : main.cpp classes.h 
	g++ -c main.cpp
clean: 
	rm Askisi1 main.o Implementation2.o

