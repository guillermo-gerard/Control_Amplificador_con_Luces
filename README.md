# Control de amplificador y leds ws2812b
## Autor: Facundo Carroz

### Consta de dos librerias independientes, una para el control de un amplificador y otra para el control de leds ws2812b. Diseñado para Arduino Uno, Mega y otros similares.

## Libreria ControlPixel:
- Pude controlar leds ws2812/ws2812b. Cuenta con 8 efectos de luz adaptables a la cantidad de leds, todos sincronizados con el audio
- El codigo pude detectar la presencia de audio
- Permite setear diversos parametros de configuracion
- Esta configurada para un maximo de **500** leds por instancia

## Libreria AmplifiedControl: 
- Pude activar el pin mute/stand by de un amplificador
- Tambien puede controlar un ventilador para el amplificador
- Permite medir temperatura a travez de un sensor LM35
- Permite setear multiples parametros

## Las librerias permiten:

- El control de:
   - mute/stand by
   - ventilador 
   - leds ws2812/ws2812b

- Medicion de:
   - temperatura
   - audio

## Dependencias:
- ControlPixel depende de la libreria **Adafruit_NeoPixel** para el control de los leds, la misma tiene que estar insalada en la misma carpeta que ControlPixel
