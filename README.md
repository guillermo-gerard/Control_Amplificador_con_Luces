# Control amplificador con luces
## Autor: Facundo Carroz

### Codigo para el control de un amplificador de audio. Diseñado para Arduino Uno, Mega y otros similares.

- Pude controlar leds ws2812/ws2812b (se probo con 100 leds). Cuenta con 8 efectos de luz, todos sincronizados con el audio que se inyecte por un pin especifico.
- El codigo pude detectar la presencia de audio. Si no lo detecta tiene la opción de poder mutear o poner en stand by el amplificador a travez de la activacion de un pin.
- Es capaz de leer un botón. Esta programado para uno con retención, es decir queda precionado.

## Descripción: ## 

- Control de:
   - mute/stand by (a través de un transistor)
   - ventilador (a través de un transistor)
   - leds ws2812/ws2812b

- Medicion de:
   - temperatura (lm35)
   - audio (pin analogico)
   - botón touch (puede ser uno normal con retención)
