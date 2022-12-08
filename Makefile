all: map limits words 
	
map:
	gcc -o map map.c
limits:
	gcc -o limits limits.c
words:
	gcc -o words main.c word_count.c wc_sort.o
main.o: main.c word_count.h
	gcc -c main.o main.c

clean:
	rm -rf words limits map main.o 

