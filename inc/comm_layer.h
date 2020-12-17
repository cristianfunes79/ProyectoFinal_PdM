/*-------------------------------------------------------------------------
 * @name Cristian Funes
 * @email cristianfunes79@gmail.com
 * 
 * @file comm_layer.h
 *
 * ------------------------------------------------------------------------
 *  Descripcion:
 *
 *  Implementa una capa de comunicaciones por UART y parseo de mensages
 * 
-------------------------------------------------------------------------*/

#ifndef __COMM_LAYER__
#define __COMM_LAYER__

#define COMM_BUFFER_SIZE 128

/*--------------------------------------------------------------
 * @fn      init_comm_layer
 * @param   none
 * @brief   Inicializa la capa de comunicaciones por uart 
--------------------------------------------------------------*/
int init_comm_layer( void );

/*--------------------------------------------------------------
 * @fn      send_request
 * @param   none
 * @brief   Envia una peticion al modulo sensor para leer la temperatura 
--------------------------------------------------------------*/
int send_request( void );


/*--------------------------------------------------------------
 * @fn      send_ack
 * @param   none
 * @brief   Envia una confirmacion de recepcion al modulo sensor de temperatura 
--------------------------------------------------------------*/
int send_ack( void );

/*--------------------------------------------------------------
 * @fn      check_response
 * @param   none
 * @brief   Espera un mensaje por parte del modulo sensor de temperatura 
--------------------------------------------------------------*/
int check_response( void );

/*--------------------------------------------------------------
 * @fn      get_temperature
 * @param   none
 * @brief   Retorna el valor de temperatura reportado por el modulo sensor en Kelvin 
--------------------------------------------------------------*/
int get_temperature( void );

/*--------------------------------------------------------------
 * @fn      sendInt
 * @param   data Dato entero que se quiere enviar
 * @brief   Envia un valor entero a traves de la uart 
--------------------------------------------------------------*/
void sendInt( uint32_t data);

/*--------------------------------------------------------------
 * @fn      sendString
 * @param   str Puntero al string que se quiere enviar
 * @brief   Envia un string a traves de la UART 
--------------------------------------------------------------*/
void sendString( const char * str );

#endif
