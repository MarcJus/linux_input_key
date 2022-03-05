#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <pthread.h>

#include "keyboard_input.h"
#include "mouse_input.h"

int main(int argc, char const *argv[]){

	int fd = open_keyboard_fd();
	CHECK_WRITE_RETURN_VALUE(fd);

	pthread_t thread;

	int bytes_written;
	bytes_written = start_repeated_key(fd, KEY_G, &thread);
	CHECK_WRITE_RETURN_VALUE(bytes_written);

	sleep(3);

	bytes_written = stop_repeated_key(fd, KEY_G, &thread);
	CHECK_WRITE_RETURN_VALUE(bytes_written);
	
	return 0;
}
