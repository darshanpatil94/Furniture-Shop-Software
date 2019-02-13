all: output

output: fur_stack.o fur_queue.o fur_tree.o fur_quick.o fur_merge.o fur_bfs.o fur_query.o

fur_stack.o: fur_stack.c
	gcc -g -c -Wall fur_stack.c

fur_queue.o: fur_queue.c
	gcc -g -c -Wall fur_queue.c

fur_tree.o: fur_tree.c
	gcc -g -c -Wall fur_tree.c

fur_quick.o: fur_quick.c
	gcc -g -c -Wall fur_quick.c

fur_merge.o: fur_merge.c
	gcc -g -c -Wall fur_merge.c

fur_bfs.o: fur_bfs.c
	gcc -g -c -Wall fur_bfs.c

fur_query.o: fur_query.c
	gcc -g -c -Wall fur_query.c

stack: fur_stack.o
	gcc -o stack -g fur_stack.o

queue: fur_queue.o
	gcc -o queue -g fur_queue.o

tree: fur_tree.o
	gcc -o tree -g fur_tree.o

quick: fur_quick.o
	gcc -o quick -g fur_quick.o

merge: fur_merge.o
	gcc -o merge -g fur_merge.o

query: fur_query.o
	gcc -o query -g fur_query.o

bfs: fur_bfs.o
	gcc -o bfs -g fur_bfs.o

clean:
	rm -f *.o stack queue quick tree merge bfs query
