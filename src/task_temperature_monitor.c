#include "task_temperature_monitor.h"
#include "sapi.h"
#include "pipe.h"
#include "comm_layer.h"

extern struct pipe tasks_ipc;

int task_temperature_monitor_run( struct task_temperature_monitor * self )
{
    switch( self->currentState )
    {
        case WaitingMeasure:
            if ( tasks_ipc.is_empty == 0 )
            {
                self->measure = tasks_ipc.read( &tasks_ipc );
                self->currentState = CheckRange;
            }
            break;
        case CheckRange:
            if( (self->measure > 0) && (self->measure < 100) )
            {
                self->range = RANGE_LOW;
            }
            else if( (self->measure >= 100) && (self->measure < 200) )
            {
                self->range = RANGE_NORMAL;
            }
            else if( (self->measure >= 200) && (self->measure < 300) )
            {
                self->range = RANGE_HIGH;
            }
            self->currentState = SetLed;
            break;
        case SetLed:
            switch( self->range )
            {
                case RANGE_NORMAL:
                    gpioWrite(LED1, 0);
                    gpioWrite(LED2, 0);
                    gpioWrite(LED3, 1);
                    break;
                case RANGE_LOW:
                    gpioWrite(LED1, 1);
                    gpioWrite(LED2, 0);
                    gpioWrite(LED3, 0);
                    break;
                case RANGE_HIGH:
                    gpioWrite(LED1, 0);
                    gpioWrite(LED2, 1);
                    gpioWrite(LED3, 0);
                    break;
            }
            self->currentState = WaitingMeasure;
            break;
    }
}

int task_temperature_monitor_stop( struct task_temperature_monitor * self )
{
    return 0;
}

int task_temperature_monitor_restart( struct task_temperature_monitor * self )
{
    return 0;
}

int task_temperature_monitor_init( struct task_temperature_monitor * self )
{
    self->task.run = task_temperature_monitor_run;
    self->task.stop = task_temperature_monitor_stop;
    self->task.restart = task_temperature_monitor_restart;
    self->currentState = WaitingMeasure;
}

