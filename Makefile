all: lista
lista: main.o
	g++ main.cpp -o ejecutable
	./ejecutable
main.o: 
	g++ -c main.cpp
clean:	
	rm -rf *o main