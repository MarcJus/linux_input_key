all: prog

CC = gcc

prog: *.c
	$(CC) *.c -o prog -pthread

run: 
	sudo ./prog &