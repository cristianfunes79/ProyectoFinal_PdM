/*-------------------------------------------------------------------------
 * @name Cristian Funes
 * @email cristianfunes79@gmail.com
 * 
 * @file task_sensor.h
 *
 * ------------------------------------------------------------------------
 *  Descripcion:
 *
 *  Definicion de la tarea encargada de leer el sensor de temperatura.
 *  Contiene la fsm para realizar la lectura del sensor.
 * 
-------------------------------------------------------------------------*/

#ifndef __TASK_SENSOR__
#define __TASK_SENSOR__

#include "task_common.h"
#include <stdint.h>

/* Estados de la fsm -----------------------------------------------------*/
typedef enum
{
    WaitingTimer = 0,
    RequestMessage,
    WaitingResponse,
    ReadMessage,
    SendAck
} sensorFsm_t;


/* Constructor de la tarea -----------------------------------------------*/
struct task_sensor
{
    struct task_common task; 
    sensorFsm_t currentState;
    uint32_t time_count;
    uint32_t temperature_k;
};


int task_sensor_init    ( struct task_sensor * self );

#endif
