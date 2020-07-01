Autor: Facundo Carroz
Fecha: 01/07/2020

Codigo para el control de un amplificador de audio. 

+ Pude controlar leds ws2812/ws2812b (se probo con 40 leds). Cuenta con 8 efectos de luz, todos sincronizados con el audio que se inyecte por el pin de audio.
+ El codigo pude detectar la presencia de audio. Si no lo detecta tiene la opción de poder mutear o poner en stand by el amplificador (si este cuenta con el pin correspondiente).
+ Es capaz de leer un botón. Esta programado para uno con retención, es decir queda precionado.

Control de:
 -mute/stand by
 -ventilador (a través de un transistor)
 -leds ws2812/ws2812b

Medicion de:
 -temperatura (lm35)
 -audio
 -botón touch (puede ser uno normal con retención)