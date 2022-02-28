#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

int send_event_msc(int keyboard_fd){

	struct input_event event;
	event.type = EV_MSC; // 4
	event.code = MSC_SCAN; // 4
	event.value = 0x7000a; // ! Au hasard

	int bytes_written = write(keyboard_fd, &event, sizeof(event));
	if(bytes_written < 0){
		perror("Erreur write ");
		exit(EXIT_FAILURE);
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
		perror("Erreur write ");
		exit(EXIT_FAILURE);
	}
	// printf("event report\n");
	return 0;
}

int send_key(ushort key)
{
	const char *keyboard_path = "/dev/input/event2";
	int keyboard_fd = open(keyboard_path, O_RDWR);
	if(keyboard_path < 0){
		return keyboard_fd; // ! Erreur
	}

	send_event_msc(keyboard_fd);

	struct input_event event;
	event.type = EV_KEY;
	event.value = 1;
	event.code = key;

	int bytes_written = write(keyboard_fd, &event, sizeof(event));
	if(bytes_written < 0){
		return bytes_written;
	}
	
	send_event_report(keyboard_fd);

	send_event_msc(keyboard_fd);

	event.type = EV_KEY;
	event.value = 0;
	event.code = key;

	bytes_written = write(keyboard_fd, &event, sizeof(event));
	if(bytes_written < 0){
		return bytes_written;
	}
	
	send_event_report(keyboard_fd);

	return 0;
}