#ifndef SEND_INPUT
#define SEND_INPUT

#include <stdlib.h>

/**
 * @brief Simule la frappe d'une touche unique
 * 
 * @param key Identifiant de la touche, définie dans linux/input-event-codes.h
 * @return int 0 si la touche a été envoyée, -1 en cas d'erreur
 */
int send_unique_key(ushort key);

int send_repeat_key(ushort key);

#endif //SEND_INPUT