/*-------------------------------------------------------------------------
 * @name Cristian Funes
 * @email cristianfunes79@gmail.com
 * 
 * @file task_common.h
 *
 * ------------------------------------------------------------------------
 *  Descripcion:
 *
 *  Definicion de una tarea. El resto de las tasks deben heredar de esta.
 *  Contiene un task state, que puede ser usado para controlar las tareas.
 *  Define la interfaz basica para controlar una task.
 * 
-------------------------------------------------------------------------*/


#ifndef __TASK_COMMON__
#define __TASK_COMMON__

#include "pipe.h"

/* Estados posibles --------------------------------------*/
typedef enum
{
    TASK_NORMAL = 0,
    TASK_ERROR  = 1,
    TASK_STOP   = 2
} taskState_t;


/* Constructor ------------------------------------------*/
struct task_common
{
    int (*run)      ( struct task_common * );
    int (*stop)     ( struct task_common * );
    int (*restart)  ( struct task_common * );
    taskState_t taskStatus;
};

#endif
