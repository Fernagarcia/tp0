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

	logger = log_create("tp0.log", "Log TP0", 1, LOG_LEVEL_INFO);
	
	log_info(logger, "Soy un log");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	config = config_create("/home/utnso/Desktop/Directorio/TP0/tp0/client/cliente.config");
	
	log_info(logger, config_get_string_value(config, "CLAVE"));


	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje

	enviar_mensaje("CLAVE", conexion);

	// Armamos y enviamos el paquete

	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
	
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	while(1)
	{
		leido = readline("> ");

		if (leido) {
            add_history(leido);
        }

        if (!strcmp(leido, "chau")) {
            rl_free(leido);
			break;
        }

		log_info(logger, leido);

		rl_free(leido);
	}
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!

	char* leido;
	
	t_paquete* paquete;

	// Leemos y esta vez agregamos las lineas al paquete

	paquete = crear_paquete();

	agregar_a_paquete(paquete, leido, sizeof(leido));

	enviar_paquete(paquete, conexion);

	eliminar_paquete(paquete);

	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);

	config_destroy(config);

	liberar_conexion(conexion);
}
