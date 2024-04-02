all: main

main: main.o copy_file.o
	gcc -o main main.o copy_file.o -L lcopy_file

copy_file.o: copy_file.c
	gcc -c copy_file.c

main.o: main.c 
	gcc -c main.c 

clean:
	rm -f main main.o copy_file.o libcopy_file.a