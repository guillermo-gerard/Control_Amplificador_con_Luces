/* En este ejemplo basico se controla la temperatura (lm35) t pin de mute/stand by de un amplificador.
*  Tambien se controlan 50 leds ws2812b al ritmo de la musica (utilizando un filtro pasa bajos externo).
*  En el ejemplo no se usa DELAY, ya que este entorpese la lectura de audio que deve ser rapida 
*
*  Pines utilizados:
*  2(out) -> Pin de Datos de los leds
*  3(out) -> Pin de mute/stand by del amplificador (a travez de un transistor)
*  4(out) -> Pin de control del ventilador (a travez de un transistor)
*  A0(in) -> Pin de lectuta de audio (es recomendable que tenga un filtro pasa bajos)
*  A1(in) -> Pin de lectura de temperatura (se tiene que utilizar un LM35)
*/

// ¡¡¡¡ IMPORTANTE !!!!
// Es necesario tener instalada la libreria: Adafruit_NeoPixel.h

#include "AmplifiedControl.h" //Libreria que controla el amplificador
#include "PixelControl.h"     //Libreria que controla los leds ws2812b
#include <Arduino.h>

byte pinLeds = 2;
byte pinMute = 3;
byte pinVentilador = 4;
byte pinLecturaAudio = A0;
byte pinSensorTemp = A1;

int cantidadLeds = 50;//La cantidad de leds se puede modificar (procure que la cantidad sea par)
byte billoLeds = 255;//Esto determina el brillo de los leds. El minimo es 0 y el maximo 255

AmplifiedControl ampli(pinMute, pinSensorTemp, pinVentilador);
PixelControl leds(cantidadLeds, pinLeds, billoLeds, pinLecturaAudio);

long tiempoAnteriorTemperatura = 0;


void setup() {

    ampli.setTemperatureRange(35, 45, 80);//Temp minima 35°, temp alta 45°, temp muy alta 80° 
    ampli.mute(false);//El mute esta apagado

    leds.setDetectionSilence(true);//Activo la deteccion silencio/no audio
    leds.setStateEfects(true);//Activo los efectos de luz
}


void loop(){

    leds.updateStatus();//Actualizo el estado de los leds
    ampli.readTemperature();//Actualizo el estado de la temperatura
    
    //Cada 1 segundo entro en el IF
    if(millis() > tiempoAnteriorTemperatura + 1000)
    {
        //Si la temperatura es extremadamente alta entra al IF
        if(ampli.getStateTempVeryHigh() == true){
            leds.setSpecificColor(50,0,0,0);//Seteo los leds en rojo
            leds.setStateEfects(false);//Desactivo los efectos de luz
            ampli.mute(true);//Muteo el amplificador
        }
        
        //Si la temperatura NO es extremadamente alta entra al IF
        if(ampli.getStateTempVeryHigh() == false){

            ampli.mute(false);//Apago el mute del amplificador
    
            //Si no detecta audio en la entrada mutea el amplificador
            if(leds.getStateMute() == true){
                leds.setSpecificColor(0,0,0,0);//Apago los leds
                leds.setStateEfects(false);//Apago los efectos
            }
            else{
                leds.setStateEfects(true);//Enciendo los efectos
            }
        }
        tiempoAnteriorTemperatura = millis();//Vuelvo a 0 la diferencia de timepo
    }
}