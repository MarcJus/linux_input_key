#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <pthread.h>

#include "send_input.h"

int main(int argc, char const *argv[]){

	int error_code;

	error_code = send_unique_key(KEY_L);
	if(error_code < 0){
		perror("Erreur 1er L");
		return -1;
	}
	error_code = send_unique_key(KEY_L);
	if(error_code < 0){
		perror("Erreur 2e L");
		return -1;
	}
	error_code = send_unique_key(KEY_ENTER);
	if(error_code < 0){
		perror("Erreur 1er enter");
		return -1;
	}
	error_code = send_unique_key(KEY_ENTER);
	if(error_code < 0){
		perror("Erreur 2e enter");
		return -1;
	}

	printf("C'est bon\n");

	// int fd = open_keyboard_fd();
	// CHECK_WRITE_RETURN_VALUE(fd);
	// send_unique_key(KEY_L);
	return 0;
}
