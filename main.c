#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <pthread.h>

#include "send_input.h"

int main(int argc, char const *argv[]){

	pthread_t thread;
	InputDescriptor descriptor = {
		KEY_G, 1, &thread
	};
	send_repeat_key(&descriptor);

	sleep(3);

	descriptor.active = 0;
	send_repeat_key(&descriptor);
	return 0;
}
