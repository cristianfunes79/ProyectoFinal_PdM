#include "pipe.h"
#include "sapi.h"
#include "comm_layer.h"


int pipe_write( struct pipe * self, uint32_t value )
{
    if ( self->is_full == 0 )
    {
        self->pipe_buffer[ self->word_count ] = value;
        self->word_count ++;
        self->is_empty = 0;

        if ( self->word_count >= self->pipe_size )
        {
            self->is_full = 1;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

uint32_t pipe_read( struct pipe * self )
{
    if ( self->is_empty == 0 )
    {
        self->word_count --;
        if ( self->word_count == 0 )
        {
            self->is_empty = 1;
        }
        return self->pipe_buffer[ self->word_count ];
    }

    return 0;
}

int pipe_init( struct pipe * self, uint32_t pipe_size, uint32_t * pipe_buffer )
{
    self->pipe_size = pipe_size;
    self->pipe_buffer = pipe_buffer;
    self->is_full = 0;
    self->is_empty = 1;
    self->word_count = 0;
    self->write = pipe_write;
    self->read = pipe_read;

    return 1;
}

