# Descripcion del Proyecto
El objetivo del firmware es poder leer los valores de temperatura de un sensor a traves de una UART y poder mostrar con indicacion led el rango de la misma.
Se implemento de tal forma que cada fsm quede contenida por completo en su propio modulo de firmware, permitiendo una mejor reutilizacion del codigo y mayor flexibilidad a la hora de agregar y/o modificar tareas.

# Protocolo de comunicaciones
Se definio una capa de comunicaciones y parseo de mensajes, la misma maneja 3 tipos de mensajes basicos: request, ack y temperatura.

## Request
<REQ:?>

## ACK
<ACK>

## Temperatura
<TTT> Donde TTT es un numero de 3 digitos que representa la temperatura en Kelvin
