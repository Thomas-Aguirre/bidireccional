#ifndef SERVER_H_
#define SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <commons/log.h>
#include </home/utnso/tp0/utils/utils.c>

void iterator(char* value);
//-----------------------------------------------------------------
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>

t_log* iniciar_logger(void);
t_config* iniciar_config(void);
void leer_consola(t_log*);
void paquete(int);
void terminar_programa(int, t_log*, t_config*);

#endif /* SERVER_H_ */
