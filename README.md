# Control de audio, amplificador y leds ws2812b
## Autor: Facundo Carroz

### Consta de tres librerias independientes, una para el control de un amplificador, otra para la lectura de audio y otra para el control de leds ws2812b. Diseñado para Arduino Uno, Mega y otros similares.

## Libreria AudioControl
- El codigo se encarga de detectar el audio
- La libreria se adapta automaticamente a cambios en el volumen de audio
- Permite setear diversos parametros de configuracion

## Libreria AmplifiedControl 
- Pude activar el pin mute/stand by de un amplificador
- Tambien puede controlar un ventilador para el amplificador
- Permite medir temperatura a travez de un sensor LM35
- Permite setear multiples parametros

## Libreria Effects
- Pude controlar leds ws2812/ws2812b. Cuenta con 8 efectos de luz adaptables a la cantidad de leds, todos sincronizados con el audio
- Esta configurada para un maximo de **500** leds por instancia
- Permite manipular cada efecto de forma diferente 

## Dependencias
- Effects depende de la libreria **Adafruit_NeoPixel** para el control de los leds, la misma tiene que estar instalada en el equipo

## Algunos efectos de luz
![Imagen de tira led ws2812b](https://github.com/Facundo-prog/Control_Amplificador_con_Luces/blob/master/images/img_1.jpg)
![Imagen de tira led ws2812b](https://github.com/Facundo-prog/Control_Amplificador_con_Luces/blob/master/images/img_2.jpg)
![Imagen de tira led ws2812b](https://github.com/Facundo-prog/Control_Amplificador_con_Luces/blob/master/images/img_3.jpg)
