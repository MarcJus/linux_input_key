#include "mouse_input.h"

int open_mouse_fd(){
	int fd = open("/dev/input/event5", O_RDWR);

	return fd;
}

int send_mouse_input(int mouse_fd, DIRECTION direction, int value){
	int error_code = 0;

	error_code = SEND_EVENT_REPORT(mouse_fd, 0);
	CHECK_WRITE_RETURN_VALUE(error_code);

	error_code = SEND_MOUSE_EVENT(mouse_fd, direction, value);
	CHECK_WRITE_RETURN_VALUE(error_code);

}

