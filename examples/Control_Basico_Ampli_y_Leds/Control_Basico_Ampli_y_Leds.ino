/* 
*  En este ejemplo basico se controla la temperatura (lm35) y el pin de mute/stand by de un amplificador
*  Tambien se controlan 50 leds ws2812b al ritmo de la musica (utilizando un filtro pasa bajos externo)
*  En el ejemplo no se usa DELAY, ya que este entorpece la lectura de audio
*
*  Pines utilizados:
*  2(out) -> Pin de Datos de los leds
*  3(out) -> Pin de mute/stand by del amplificador (a travez de un transistor)
*  4(out) -> Pin de control del ventilador (a travez de un transistor)
*  A0(in) -> Pin de lectuta de audio (es recomendable que tenga un filtro pasa bajos)
*  A1(in) -> Pin de lectura de temperatura (se tiene que utilizar un LM35)
*/

// ¡¡¡¡ IMPORTANTE !!!!
// Es necesario tener instalada la libreria: Adafruit_NeoPixel.h en el mismo directorio que Effects.h

#include "AmplifiedControl.h"  //Libreria que controla el amplificador
#include "AudioControl.h"      //Libreria que obtiene el audio
#include "Effects.h"           //Libreria que controla los leds
#include <Adafruit_NeoPixel.h> //Libreria necesaria para controlar los leds
#include <Arduino.h>


//------Pines Utilizados ------//
byte pinLeds = 2;
byte pinMute = 3;
byte pinVentilador = 4;
byte pinLecturaAudio = A0;
byte pinSensorTemp = A1;


//---------- Variables del programa ---------//
int cantidadLeds = 50;//La cantidad de leds se puede modificar (procure que la cantidad sea par)
byte brilloLeds = 255;//Determina el brillo de los leds. El minimo es 0 y el maximo 255
unsigned long tiempoTemperatura = 0;//Variable donde guardamos el valor de millis para compararlo
unsigned long tiempoCambioEfecto = 0;//Variable donde guardamos el valor de millis para compararlo
bool estadoEfectos = true;//Determina si los efectos estan activos o no
byte efectoActual = 0;//Determina el efecto que se esta generando
byte cantidadEfectos = 8;//Cantidad de efectos


//--------- Instancias de Objetos ---------//
AmplifiedControl ampli(pinMute, pinSensorTemp, pinVentilador);
AudioControl audio(pinLecturaAudio);
Adafruit_NeoPixel leds(cantidadLeds, pinLeds, NEO_GRB + NEO_KHZ800);


//-------- Inicializacion de los efectos -----------//
TransitionEffect efect_1(&leds, cantidadLeds, 4, 0.15, 8);
WaveEffect efect_2(&leds, cantidadLeds, 4, 0.15, 15);
DotsDegradableEffect efect_3(&leds, cantidadLeds, 4, 0.30, 40);// No adaptado a millis
WormEffect efect_4(&leds, cantidadLeds, 4, 0.15, 20);
RandomEffect efect_5(&leds, cantidadLeds, 4, 0.15, 5);
ReboundEffect efect_6(&leds, cantidadLeds, 4, 0.15, 40);
ShockEffect efect_7(&leds, cantidadLeds, 4, 0.15, 5);
ScrollingDotsEffect efect_8(&leds, cantidadLeds, 4, 0.15, 35);// No adaptado a millis


//--------- Creo un array con los efectos ---------//
IEffects* efectos[] = {&efect_1, &efect_2, &efect_3, &efect_4, &efect_5, &efect_6, &efect_7, &efect_8};


void setup() {

    Serial.begin(115200);//Inicializo el puerto serial
    ampli.setTemperatureRange(35, 45, 80);//Temp minima 35°, temp alta 45°, temp muy alta 80° 
    ampli.mute(false);//El mute esta apagado

    audio.setDetectionSilence(true, 10000, 10);//Activo la deteccion silencio/no audio
    audio.setDetectionFrequency(5000);//Seteo la frecuencia de deteccion. Leer propiedades.txt

    leds.begin();//Inicializo los leds
    leds.clear();//Apago los leds
    leds.setBrightness(brilloLeds);//Seteo el brillo
}


void loop(){

    if(estadoEfectos == true){
        efectos[efectoActual]->run(audio.readAudio());//Actualizo el estado de los leds
    }
    
    if((millis() - tiempoTemperatura) >= 1000)
    {
        Serial.println(ampli.readTemperature());//Actualizo el estado de la temperatura
        estadoEfectos = true;//Enciendo los efectos

        if(ampli.getStateTempVeryHigh() == true){
            leds.clear();//Apago los leds
            estadoEfectos = false;//Apago los efectos
            ampli.mute(true);//Muteo el amplificador
        }
        else{
            if(audio.getStateMute() == true){
                leds.clear();//Apago los leds
                estadoEfectos = false;//Apago los efectos
                ampli.mute(true);//Activo el mute del amplificador
            }
            else{
                ampli.mute(false);//Desactivo el mute del amplificador
            }
        }
        tiempoTemperatura = millis();//Vuelvo a 0 la diferencia de timepo
    }

    if((millis() - tiempoCambioEfecto) >= 10000){
        efectoActual++;//Incremento el efecto

        if(efectoActual >= cantidadEfectos){
            efectoActual = 0;//Vuelvo a 0 el contador
        }

        tiempoCambioEfecto = millis();//Vuelvo a 0 la diferencia de tiempo
    }
}