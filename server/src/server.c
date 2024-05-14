#include "server.h"

int main(void)
{
	char *valor = "Hola";
	logger = log_create("log.log", "Servidor", 1, LOG_LEVEL_DEBUG);

	int server_fd = iniciar_servidor();
	log_info(logger, "Servidor listo para recibir al cliente");
	int cliente_fd = esperar_cliente(server_fd);
	//-----------------------------------------------------
	
	//------------------------------------------------
	t_list *lista;
	//enviar_mensaje(valor,cliente_fd);
	paquete(cliente_fd);
	while (1)
	{
		int cod_op = recibir_operacion(cliente_fd);
		printf("Esto es: %d \n",cod_op);
		switch (cod_op)
		{
		case MENSAJE:
			recibir_mensaje(cliente_fd);
			break;
		case PAQUETE:
			lista = recibir_paquete(cliente_fd);
			log_info(logger, "Me llegaron los siguientes valores:\n");
			list_iterate(lista, (void *)iterator);
			break;
		case -1:
			log_error(logger, "el cliente se desconecto. Terminando servidor");
			return EXIT_FAILURE;
		default:
			log_warning(logger, "Operacion desconocida. No quieras meter la pata");
			break;
		}
	}
	
	return EXIT_SUCCESS;
}

void iterator(char *value)
{
	log_info(logger, "%s", value);
}


void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;
    paquete=crear_paquete();
	// Leemos y esta vez agregamos las lineas al paquete
	printf("Lee: ");
    leido = readline("> "); 
    while(string_is_empty(leido) == false){ 
		agregar_a_paquete(paquete,leido,strlen(leido)+1);
		free(leido);
		printf("Lee: ");
        leido = readline("> ");
	};
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	free(leido);
	//ENVIAR PAQUETE	
	enviar_paquete(paquete,conexion);
	//ELIMINAR PAQUETE	
	eliminar_paquete(paquete);
}