/*-------------------------------------------------------------------------
 * @name Cristian Funes
 * @email cristianfunes79@gmail.com
 * 
 * @file pipe.h
 *
 * ------------------------------------------------------------------------
 *  Descripcion:
 *
 *  Implementa una capa de comunicaciones para ser usada entre tareas.
 * 
-------------------------------------------------------------------------*/

#ifndef __PIPE__
#define __PIPE__

#include <stdint.h>

/* Constructor ------------------------------------------ */
struct pipe
{
    uint32_t * pipe_buffer;
    uint32_t word_count;
    uint32_t pipe_size;
    uint8_t is_full;
    uint8_t is_empty;

    int (*write) (struct pipe * self, uint32_t );
    uint32_t (*read) (struct pipe * self);
};


/*--------------------------------------------------------------
 * @fn      pipe_init
 * @param   self Puntero al pipe a inicializar
 * @param   pipe_size Size del buffer a utilizar
 * @param   pipe_buffer Buffer donde se escriben/leen los mensajes del pipe
 * @brief   Inicializa las funciones relativas al pipe 
--------------------------------------------------------------*/
int pipe_init( struct pipe * self, uint32_t pipe_size, uint32_t * pipe_buffer );

/*--------------------------------------------------------------
 * @fn      pipe_write
 * @param   self Puntero al pipe donde se quiere leer
 * @param   value Valor que se quiere escribir en el pipe
 * @brief   Define la forma en que se escribe el buffer  
--------------------------------------------------------------*/
int pipe_write( struct pipe * self, uint32_t value );


/*--------------------------------------------------------------
 * @fn      pipe_read
 * @param   self Puntero al pipe donde se quiere leer
 * @brief   Define la forma en que se lee el buffer  
--------------------------------------------------------------*/
uint32_t pipe_read( struct pipe * self );

#endif
