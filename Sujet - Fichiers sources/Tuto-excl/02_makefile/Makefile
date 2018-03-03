
CC = gcc -Wall -Wextra -ansi

all: graph_test

graph_test: main.o graph_matrix.o
	$(CC) main.o graph_matrix.o -o graph_test

main.o: main.c graph.h
	$(CC) -c main.c -o main.o

graph_matrix.o: graph_matrix.c graph.h
	$(CC) -c graph_matrix.c -o graph_matrix.o

graph_list.o: graph_list.c graph.h
	$(CC) -c graph_list.c -o graph_list.o

clean:
	rm *.o
	rm graph_test

