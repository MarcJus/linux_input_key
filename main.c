#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <linux/joystick.h>

#include "send_input.h"

int main(int argc, char const *argv[]){


	send_unique_key(KEY_L);
	send_unique_key(KEY_L);
	send_unique_key(KEY_ENTER);
	// send_unique_key(KEY_ENTER);
	return 0;
}
