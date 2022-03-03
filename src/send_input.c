#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

typedef struct {
	/**
	 * @brief Touche à entrer, définie dans input-event-code.h
	 * 
	 */
	ushort key;

	/**
	 * @brief Indique si la touche doit etre enfoncée ou non.
	 * 0 si elle est levée, 1 si elle est enfoncée
	 * 
	 */
	int active;
} InputDescriptor;

int send_event_msc(int keyboard_fd){

	struct input_event event;
	event.type = EV_MSC; // 4
	event.code = MSC_SCAN; // 4
	event.value = 0x7000a; // ! Au hasard

	int bytes_written = write(keyboard_fd, &event, sizeof(event));
	if(bytes_written < 0){
		return bytes_written;
	}

	return 0;
}

int send_event_report(int keyboard_fd){

	struct input_event event;
	event.type = EV_SYN; // 0
	event.code = SYN_REPORT; // 0
	event.value = 0;

	int bytes_written = write(keyboard_fd, &event, sizeof(event));
	if(bytes_written < 0){
		return bytes_written;
	}
	// printf("event report\n");
	return 0;
}

int send_input_event(int fd, int type, int code, int value){
	struct input_event event = {
		type,
		code,
		value
	};

	int bytes_written = write(fd, &event, sizeof(event));
	if(bytes_written < 0){
		return bytes_written;
	}
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
	int error_code = send_event_msc(keyboard_fd);
	if(error_code < 0){
		return error_code;
	}

	// Envoie de l'événement touche appuyée
	struct input_event event;
	event.type = EV_KEY;
	event.value = 1;
	event.code = key;

	int bytes_written = write(keyboard_fd, &event, sizeof(event));
	if(bytes_written < 0){
		return bytes_written;
	}
	
	// Envoi de l'événement type 0 code 0
	error_code = send_event_report(keyboard_fd);
	if(error_code < 0){
		return error_code;
	}

	// Envoi de l'événement type 4 code 4
	error_code = send_event_msc(keyboard_fd);
	if(error_code < 0){
		return error_code;
	}

	// Envoi de l'événement touche relachée
	event.type = EV_KEY; // 1
	event.value = 0;
	event.code = key;

	bytes_written = write(keyboard_fd, &event, sizeof(event));
	if(bytes_written < 0){
		return bytes_written;
	}
	
	// Envoi de l'événement type 0 code 0
	error_code = send_event_report(keyboard_fd);
	if(error_code < 0){
		return error_code;
	}

	return 0;
}

int send_repeat_key(InputDescriptor *descriptor){
	
}