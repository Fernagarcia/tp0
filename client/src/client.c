#include "client.h"
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	log_info(logger, "Soy un log");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();
	
	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");
	valor = config_get_string_value(config, "CLAVE");
	
	log_info(logger, ip);
	log_info(logger, puerto);
	log_info(logger, valor);


	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje

	enviar_mensaje(valor, conexion);

	// Armamos y enviamos el paquete

	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
	
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	nuevo_logger = log_create("tp0.log", "Log TP0", 1, LOG_LEVEL_INFO);
	
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	nuevo_config = config_create("/home/utnso/so-commons-library/tp0/client/cliente.config");

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	while (1)
	{
		leido = readline("> ");

		if (leido) {
            add_history(leido);
        }
        if (strncmp(leido, "exit", 4) == 0) {
            free(leido);
            break;
        }
		log_info(logger, leido);

		free(leido);
	}
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!

	char* leido;
	
	t_paquete* paquete;

	paquete = crear_paquete();

	// Leemos y esta vez agregamos las lineas al paquete

	leido = readline("> ");

	while(strcmp(leido, "") != 0)
	{
		agregar_a_paquete(paquete, leido, strlen(leido) + 1);

		free(leido);

		leido = readline("> ");
	}

		enviar_paquete(paquete, conexion);
	
		eliminar_paquete(paquete);

		free(leido);
}

	

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	


void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);

	config_destroy(config);

	liberar_conexion(conexion);
}
