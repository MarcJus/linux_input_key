all: prog

CC = gcc
OBJECTS = main.o input_utils.o keyboard_input.o mouse_input.o

prog: $(OBJECTS)
	$(CC) $(OBJECTS) -o prog -pthread

%.o: %.c
	$(CC) -c $< -o $@

run: 
	sudo ./prog &

clean:
	rm *.o