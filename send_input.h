#ifndef SEND_INPUT
#define SEND_INPUT

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#define SEND_EVENT_REPORT(fd, value) send_input_event(fd, EV_SYN, SYN_REPORT, value);
#define SEND_EVENT_MSC(fd) send_input_event(fd, EV_MSC, MSC_SCAN, 0x7000a); // ! Valeur 0x7000a au hasard !
#define SEND_EVENT_TYPE(fd, key, value) send_input_event(fd, EV_KEY, key, value);

#define CHECK_WRITE_RETURN_VALUE(bytes_written) if(bytes_written < 0) return bytes_written;

typedef struct InputDescriptor{
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

/**
 * @brief Simule la frappe d'une touche unique
 * 
 * @param key Identifiant de la touche, définie dans linux/input-event-codes.h
 * @return int 0 si la touche a été envoyée, -1 en cas d'erreur
 */
int send_unique_key(ushort key);

int send_repeat_key(InputDescriptor *descriptor);

int send_input_event(int fd, int type, int code, int value);

#endif //SEND_INPUT