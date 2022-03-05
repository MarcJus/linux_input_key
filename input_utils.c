#include "input_utils.h"

int send_input_event(int fd, int type, int code, int value){
	struct input_event event;
	event.type = type;
	event.code = code;
	event.value = value;

	int bytes_written = write(fd, &event, sizeof(event));
	CHECK_WRITE_RETURN_VALUE(bytes_written);

	return 0;
}