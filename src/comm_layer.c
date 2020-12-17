#include "sapi.h"
#include "comm_layer.h"

// Global variables --------------------------------------------------
volatile char comm_buffer[128];
volatile bool new_message = 0;
volatile uint8_t buffer_index = 0;


// Implementacion de funciones ---------------------------------------

void commRxHandler( void *ptr )
{
   comm_buffer[ buffer_index ] = uartRxRead( UART_USB );
   if ( comm_buffer[ buffer_index ] == '>' )
   {
       new_message = 1;
   }
   buffer_index ++;

   if ( buffer_index >= COMM_BUFFER_SIZE )
   {
       buffer_index = 0;
   }

}


int init_comm_layer( void )
{
    // Inicializar UART_USB a 115200 baudios
    uartConfig( UART_USB, 115200 );
    /* Buffer */
    uartWriteString( UART_USB, "Starting program\r\n" ); // Mensaje inicial 
    // Seteo un callback al evento de recepcion y habilito su interrupcion
    uartCallbackSet(UART_USB, UART_RECEIVE, commRxHandler, NULL);
    // Habilito todas las interrupciones de UART_USB
    uartInterrupt(UART_USB, true);

    int temp_index;
    buffer_index = 0;
    new_message = 0;

    for ( temp_index = 0; temp_index < COMM_BUFFER_SIZE; temp_index ++ )
    {
        comm_buffer[ temp_index ] = 0;
    }
}


int clear_buffer( char * buffer, uint8_t len )
{
    uint8_t index; 

    for ( index = 0; index < len; index ++ )
    {
        buffer[index] = 0;
    }
}

int send_request( void )
{
    uartWriteString( UART_USB, "<REQ:?>\r\n" ); // Enviar un Enter
    return 1;
}

int send_ack( void )
{
    uartWriteString( UART_USB, "<ACK>\r\n" ); // Enviar un Enter
    return 1;
}


void sendInt( uint32_t data )
{
    uartWriteString(UART_USB, "DATA: ");
    printf("DATA: %d",data);
}

void sendString( const char * str )
{
    uartWriteString(UART_USB, str);
}

int check_response( void )
{
    while( new_message == 0  )
    {
    }

    new_message = 0;

    return 1;
}

int get_temperature( void ) // el formato de la respuesta es <TTT> en Kelvin
{
    uint8_t index = 0;
    int res;

    for ( index = 0; index < 128; index ++ )
    {
        if ( (comm_buffer[ index ] == '<') && (comm_buffer[ index+4 ] == '>') )
        {
            res = ( (comm_buffer[ index + 1]-48) * 100 + (comm_buffer[ index + 2]-48) * 10 + (comm_buffer[ index + 3]-48) );
            buffer_index = 0;
            clear_buffer( comm_buffer, COMM_BUFFER_SIZE );

            return res;
        }
    }

    return -1;
}
