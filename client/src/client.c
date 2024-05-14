#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_config* config;
	t_list *lista;

	/* ---------------- LOGGING ---------------- */

	logg = iniciar_logger();
	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"
     log_info(logg,"Hola! Soy un log");
	 

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'
     valor=config_get_string_value(config,"CLAVE");
	 ip=config_get_string_value(config,"IP");
	 puerto=config_get_string_value(config,"PUERTO");
	// Loggeamos el valor de config
     /* log_info(logger,"La clave de la config: %s", valor);
	  log_info(logger,"El puerto de la config: %s",puerto);
	  log_info(logger,"La ip de la config: %s",ip);*/

	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	/* ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor
	 esté corriendo para poder conectarnos a él*/
	// Creamos una conexión hacia el servidor
	   conexion = crear_conexion(ip, puerto);
	// Enviamos al servidor el valor de CLAVE como mensaje
	// Armamos y enviamos el paquete
	//paquete(conexion);
    bool flag=true;
	while (flag==true) {

		int cod_op = recibir_operacion(conexion);
		switch (cod_op) {
		case MENSAJE:
		printf("opcion mensaje \n");
			recibir_men(conexion);
			break;
		case PAQUETE:
		printf("opcion paquete \n");
			lista = recibir_paquete(conexion);
			log_info(logg, "Me llegaron los siguientes valores:\n");
			list_iterate(lista, (void*) iterator);
			flag=false;
			break;
		default:
		printf("ninguna opcion \n");
			log_warning(logg,"Operacion desconocida. No quieras meter la pata");
			break;
		}
		
	}
	   enviar_mensaje(valor,conexion);
	terminar_programa(conexion, logg, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;
    nuevo_logger= log_create("tp0.log","codigo",true,LOG_LEVEL_INFO);
	if(nuevo_logger == NULL){
        //si nuevo_logger me devuelve un NULL significa que algo raro paso con el log
		perror("No se pudo encontrar o crear el archivo");
		exit(EXIT_FAILURE);
	};
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;
    nuevo_config=config_create("cliente.config");
	if(nuevo_config == NULL){
        perror("Hubo un error al intentar cargar el config");
		exit(EXIT_FAILURE);
	};
	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;
	// La primera te la dejo de yapa 
	printf("Escribi lo necesario \n");
	leido = readline("> "); //duda, no veo lo que escribo en consola ??????????????
	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	 while(string_is_empty(leido) == false){ //uso de string_is_empty, si ve que la variable leido 
		log_info(logger, ">> %s",leido);     // no es vacio entonces devuelve false
		free(leido);
        leido = readline("> ");
	 };
	// ¡No te olvides de liberar las lineas antes de regresar!
    free(leido);
	
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;
    paquete=crear_paquete();
	// Leemos y esta vez agregamos las lineas al paquete
    leido = readline("> "); 
    while(string_is_empty(leido) == false){ 
		agregar_a_paquete(paquete,leido,strlen(leido)+1);
		free(leido);
        leido = readline("> ");
	};
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	free(leido);
	//ENVIAR PAQUETE	
	enviar_paquete(paquete,conexion);
	//ELIMINAR PAQUETE	
	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	  log_destroy(logger);
	  config_destroy(config);
	  liberar_conexion(conexion);
}
//---------------------------------------------------------------
void iterator(char* value)
{
	log_info(logg, "%s", value);
}