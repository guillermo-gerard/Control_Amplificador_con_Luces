# Control de amplificador y leds ws2812b
## Autor: Facundo Carroz

### Consta de dos librerias independientes, una para el control de un amplificador y otra para el control de leds ws2812b. Diseñado para Arduino Uno, Mega y otros similares.

## Libreria ControlPixel:
- Pude controlar leds ws2812/ws2812b. Cuenta con 8 efectos de luz, todos sincronizados con el audio detectado
- El codigo pude detectar la presencia de audio
- Permite setear diversos parametros
- Esta configurada para un maximo de 500 leds por instancia

## Libreria AmplifiedControl: 
- Mediante la lectura de temperatura permite la activacion del pin mute/stand by de un amplificador
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
-La libreria ControlPixel depende de **Adafruit_NeoPixel**, la misma tiene que estar insalada en la misma carpeta que ControlPixel
