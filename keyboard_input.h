#ifndef SEND_INPUT
#define SEND_INPUT

#include <pthread.h>

#include "input_utils.h"

#define SEND_EVENT_KEY(fd, key, value) send_input_event(fd, EV_KEY, key, value);

typedef struct InputDescriptor{
	/**
	 * @brief Touche à entrer, définie dans input-event-code.h
	 * 
	 */
	int key;

	/**
	 * @brief Indique si la touche doit etre enfoncée ou non.
	 * 0 si elle est levée, 1 si elle est enfoncée
	 * 
	 */
	int active;

	/**
	 * @brief Thread de la fonction qui envoie la répétition de la touche. Cela permet de l'arrêter
	 * 
	 */
	pthread_t *function_thread;
} InputDescriptor;


/**
 * @brief Utilisé pour le thread
 * 
 */
typedef struct RepeatKeyArguments{

	int fd;

	int key;

} RepeatKeyArguments;

/**
 * @brief Simule la frappe d'une touche unique
 * 
 * @param key Identifiant de la touche, définie dans linux/input-event-codes.h
 * @return int 0 si la touche a été envoyée, -1 en cas d'erreur
 */
int send_unique_key(int key);

/**
 * @brief Appelée pour simuler une touche maintenue enfoncée mais aussi pour la lacher
 * @deprecated
 * @param descriptor Contient la touche, si elle est appuyée ou non et le thread qui envoie la touche au pc
 * @return int -1 en cas d'erreur
 */

void *thread_send_repeat_key(void *args);

int open_keyboard_fd();

int start_repeated_key(int keyboard_fd, int key, pthread_t *thread);

int stop_repeated_key(int keyboard_fd,int key, pthread_t *thread);

#endif //SEND_INPUT