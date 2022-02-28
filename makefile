all: prog

CC = gcc

prog: *.c
	$(CC) *.c -o prog

run: 
	sudo ./prog &