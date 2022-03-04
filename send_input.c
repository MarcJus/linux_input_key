#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "send_input.h"

int send_input_event(int fd, int type, int code, int value){
	struct input_event event = {
		type,
		code,
		value
	};

	int bytes_written = write(fd, &event, sizeof(event));
	CHECK_WRITE_RETURN_VALUE(bytes_written);

	return 0;
}

int open_keyboard_fd(){
	const char *keyboard_path = "/dev/input/event2";
	int keyboard_fd = open(keyboard_path, O_RDWR);
	if(keyboard_fd < 0){
		return keyboard_fd; // ! Erreur
	}
	
	return keyboard_fd;
}

int send_unique_key(ushort key)
{
	// Ouverture du fichier /dev/input/event2
	int keyboard_fd = open_keyboard_fd();
	if(keyboard_fd < 0){
		return keyboard_fd;
	}

	// Envoi de l'événement type 4 code 4
	int error_code = SEND_EVENT_MSC(keyboard_fd);
	CHECK_WRITE_RETURN_VALUE(error_code);

	// Envoie de l'événement touche appuyée
	struct input_event event;
	event.type = EV_KEY;
	event.value = 1;
	event.code = key;

	int bytes_written = write(keyboard_fd, &event, sizeof(event));
	CHECK_WRITE_RETURN_VALUE(bytes_written);
	
	// Envoi de l'événement type 0 code 0
	error_code = SEND_EVENT_REPORT(keyboard_fd, 0);
	CHECK_WRITE_RETURN_VALUE(error_code);

	// Envoi de l'événement type 4 code 4
	error_code = SEND_EVENT_MSC(keyboard_fd);
	CHECK_WRITE_RETURN_VALUE(error_code);

	// Envoi de l'événement touche relachée
	event.type = EV_KEY; // 1
	event.value = 0;
	event.code = key;

	bytes_written = write(keyboard_fd, &event, sizeof(event));
	CHECK_WRITE_RETURN_VALUE(bytes_written);
	
	// Envoi de l'événement type 0 code 0
	error_code = SEND_EVENT_REPORT(keyboard_fd, 0);
	CHECK_WRITE_RETURN_VALUE(error_code);

	return 0;
}

int send_repeat_key(InputDescriptor *descriptor){
	
	// Ouverture du fichier /dev/input/event2
	int keyboard_fd = open_keyboard_fd();
	if(keyboard_fd < 0){
		return keyboard_fd;
	}

	int bytes_written;
	bytes_written = SEND_EVENT_MSC(keyboard_fd);
	CHECK_WRITE_RETURN_VALUE(bytes_written);

	if(descriptor->active == 1){
		bytes_written = SEND_EVENT_TYPE(keyboard_fd, descriptor->key, 1);
		CHECK_WRITE_RETURN_VALUE(bytes_written);

		bytes_written = SEND_EVENT_REPORT(keyboard_fd, 0);
		CHECK_WRITE_RETURN_VALUE(bytes_written);

	}

}