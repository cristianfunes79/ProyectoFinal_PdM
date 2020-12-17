/* ---------------------------------------------------------------------------
 * Descripcion:
 * 
 * El objetivo del firmware es leer los valores de temperatura de un modulo 
 * sensor que incluye un mcu, la lectura se realiza por puerto serie.
 * Ademas, se verifica que los valores leidos se encuentren detro de 3 rangos
 * preestablecidos: normal y fuera de rango ( por encima y por debajo )
 *
 * Esta implementado de tal forma que cada fsm esta contenida por completo en
 * su modulo de firmware, de forma que agregar tareas resulta mas facil y el
 * codigo resulta mas reutilizable.
 *
 *
*/

/*==================[inclusions]=============================================*/

#include "sapi.h"     
#include "task_sensor.h"
#include "task_temperature_monitor.h"
#include "pipe.h"
#include "comm_layer.h"

/*==================[macros and definitions]=================================*/
#define PIPE_BUFFER_SIZE 100

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/
struct pipe tasks_ipc;
uint32_t pipe_buffer[ PIPE_BUFFER_SIZE ];

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/





// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET.
int main(void){

   // ------------- INICIALIZACIONES -------------

   // Inicializar la placa
   boardConfig();

   // Crear las tareas
   struct task_sensor temperatureTask;
   struct task_temperature_monitor monitorTask;

   // Inicializacion de tasks y capa de comunicaciones
   init_comm_layer();
   task_sensor_init( &temperatureTask );
   task_temperature_monitor_init( &monitorTask );

   // Inicializacion del pipe para comunicar las tasks
   pipe_init( &tasks_ipc, PIPE_BUFFER_SIZE, pipe_buffer );

   // Loop infinito con las tareas
   while(1)
   {
       temperatureTask.task.run( &temperatureTask.task );
       monitorTask.task.run( &monitorTask.task );
   }

   return 0 ;
}

/*==================[end of file]============================================*/
