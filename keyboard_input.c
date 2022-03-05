#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "keyboard_input.h"

int open_keyboard_fd(){
	const char *keyboard_path = "/dev/input/event2";
	int keyboard_fd = open(keyboard_path, O_RDWR);
	
	return keyboard_fd;
}

int send_unique_key(int key)
{
	// Ouverture du fichier /dev/input/event2
	int keyboard_fd = open_keyboard_fd();
	if(keyboard_fd < 0){
		return keyboard_fd;
	}

	int bytes_written, error_code;
	struct input_event event;

	// Envoi de l'événement type 4 code 4
	error_code = SEND_EVENT_MSC(keyboard_fd);
	CHECK_WRITE_RETURN_VALUE(error_code);

	// Envoi de l'événement touche appuyée
	bytes_written = SEND_EVENT_KEY(keyboard_fd, key, 1);
	CHECK_WRITE_RETURN_VALUE(bytes_written);
	
	// Envoi de l'événement type 0 code 0
	error_code = SEND_EVENT_REPORT(keyboard_fd, 0);
	CHECK_WRITE_RETURN_VALUE(error_code);

	// Envoi de l'événement type 4 code 4
	error_code = SEND_EVENT_MSC(keyboard_fd);
	CHECK_WRITE_RETURN_VALUE(error_code);

	// Envoi de l'événement touche relachée
	bytes_written = SEND_EVENT_KEY(keyboard_fd, key, 0);
	CHECK_WRITE_RETURN_VALUE(bytes_written);
	
	// Envoi de l'événement type 0 code 0
	error_code = SEND_EVENT_REPORT(keyboard_fd, 0);
	CHECK_WRITE_RETURN_VALUE(error_code);

	return 0;
}

int start_repeated_key(int keyboard_fd, int key, pthread_t *thread){

	int bytes_written = 0;

	bytes_written = SEND_EVENT_KEY(keyboard_fd, key, 1);
	CHECK_WRITE_RETURN_VALUE(bytes_written);

	bytes_written = SEND_EVENT_REPORT(keyboard_fd, 0);
	CHECK_WRITE_RETURN_VALUE(bytes_written);

	RepeatKeyArguments args = {
		keyboard_fd, key
	};
	pthread_create(thread, NULL, thread_send_repeat_key, &args);

	return 0;
}

int stop_repeated_key(int keyboard_fd, int key, pthread_t *thread){

	int bytes_written = 0;

	pthread_cancel(*thread);

	bytes_written = SEND_EVENT_KEY(keyboard_fd, key, 0);
	CHECK_WRITE_RETURN_VALUE(bytes_written);

	bytes_written = SEND_EVENT_REPORT(keyboard_fd, 0);
	CHECK_WRITE_RETURN_VALUE(bytes_written);

	return 0;
}

/**
 * @brief Thread à part qui envoie simule l'appui long d'une touche. 1) type : 1 ; code : key ; value : 2,
 * 2) type : 0 ; code ; 0 value : 1
 * 
 * @param args 
 * @return void* 
 */
void *thread_send_repeat_key(void *args){
	
	while(1){
		RepeatKeyArguments repeatKeyArguments = *(RepeatKeyArguments *)args;
		int keyboard_fd = repeatKeyArguments.fd;
		
		int bytes_written;
		bytes_written = SEND_EVENT_KEY(keyboard_fd, repeatKeyArguments.key, 2);
		if(bytes_written < 1){
			pthread_exit(NULL);
		}

		bytes_written  = SEND_EVENT_REPORT(keyboard_fd, 1);
		if(bytes_written < 1){
			pthread_exit(NULL);
		}

	}
}
