/*-------------------------------------------------------------------------
 * @name Cristian Funes
 * @email cristianfunes79@gmail.com
 * 
 * @file task_temperature_monitor.h
 *
 * ------------------------------------------------------------------------
 *  Descripcion:
 *
 *  Definicion de la tarea encargada de determinar si la temperatura esta
 *  dentro de los rangos establecidos.
 *
 * 
-------------------------------------------------------------------------*/

#ifndef __TASK_TEMPERATURE_MONITOR__
#define __TASK_TEMPERATURE_MONITOR__

#include "task_common.h"
#include <stdint.h>

/* Estados de la fsm -----------------------------------------------------*/
typedef enum 
{
    WaitingMeasure = 0,
    CheckRange,
    SetLed
} monitorFsm_t;

/* Rangos de temperatura posibles ----------------------------------------*/
typedef enum 
{
    RANGE_NORMAL = 0,
    RANGE_LOW,
    RANGE_HIGH
} monitorRange_t;

/* Constructor -----------------------------------------------------------*/
struct task_temperature_monitor
{
    struct task_common task;
    uint32_t measure;
    monitorFsm_t currentState;
    monitorRange_t range;
};


int task_temperature_monitor_init( struct task_temperature_monitor * self );

#endif
