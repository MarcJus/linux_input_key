#ifndef MOUSE_EVENT
#define MOUSE_EVENT

#include "input_utils.h"

typedef enum DIRECTION{
	X, Y
} DIRECTION;

/**
 * @brief Déplace la souris
 */
#define SEND_MOUSE_EVENT(fd, direction, value) send_input_event(fd, EV_REL, direction, value);

int open_mouse_fd();

int send_mouse_input(int mouse_fd, DIRECTION direction, int value);

#endif //MOUSE_EVENT