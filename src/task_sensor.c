#include "task_sensor.h"
#include "comm_layer.h"
#include "sapi.h"
#include "pipe.h"

extern struct pipe tasks_ipc;


int task_sensor_run( struct task_sensor * self )
{
    switch( self->currentState )
    {
        case WaitingTimer:
            if ( self->time_count > 200 )
            {
                self->time_count = 0;
                self->currentState = RequestMessage;
            }
            break;
        case RequestMessage:
            send_request();
            self->currentState = WaitingResponse;
            break;
        case WaitingResponse:
            if (check_response())
            {
                self->currentState = ReadMessage;
            }
            else
            {
                self->currentState = RequestMessage;
            }
            break;
        case ReadMessage:
            self->temperature_k = get_temperature();
            tasks_ipc.write( &tasks_ipc, self->temperature_k );
            self->currentState = SendAck;
            break;
        case SendAck:
            send_ack();
            self->currentState = WaitingTimer;
            break;
    }
}

int task_sensor_stop( struct task_sensor * self )
{
    return 0;
}

int task_sensor_restart( struct task_sensor * self )
{
    return 0;
}


void sensorTickHook( struct task_sensor * self )
{
    self->time_count ++;
}


int task_sensor_init ( struct task_sensor * self )
{
    self->task.run = task_sensor_run;
    self->task.stop = task_sensor_stop;
    self->task.restart = task_sensor_restart;
    self->task.taskStatus = TASK_NORMAL;
    self->currentState = WaitingTimer;
    self->time_count = 0;
    self->temperature_k = 0;

    tickConfig( 50 );
    tickCallbackSet( sensorTickHook, self );

}

