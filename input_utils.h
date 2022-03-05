#ifndef KEYBOARD_UTILS_H
#define KEYBOARD_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>

#define SEND_EVENT_REPORT(fd, value) send_input_event(fd, EV_SYN, SYN_REPORT, value);
#define SEND_EVENT_MSC(fd) send_input_event(fd, EV_MSC, MSC_SCAN, 0x7000a); // ! Valeur 0x7000a au hasard !

#define CHECK_WRITE_RETURN_VALUE(value) if(value < 0) return value;

int send_input_event(int fd, int type, int code, int value);

#endif //KEYBOARD_UTILS_H