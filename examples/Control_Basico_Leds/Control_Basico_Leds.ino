/* 
*  En este ejemplo basico se controlan controlan 50 leds ws2812b al ritmo de la musica (utilizando un filtro pasa bajos externo)
*  En el ejemplo no se usa DELAY, ya que este entorpece la lectura de audio
*
*  Pines utilizados:
*  2(out) -> Pin de Datos de los leds
*  A0(in) -> Pin de lectuta de audio (es recomendable que tenga un filtro pasa bajos)
*/

// ¡¡¡¡ IMPORTANTE !!!!
// Es necesario tener instalada la libreria: Adafruit_NeoPixel.h en el mismo directorio que Effects.h


#include <Adafruit_NeoPixel.h>//Libreria necesaria para controlar los leds
#include "AudioControl.h" // Libreria que controla el audio
#include "Effects.h"      //Libreria que controla los efectos
#include <Arduino.h>


//------Pines Utilizados ------//
byte pinLeds = 2;
byte pinLecturaAudio = A0;


//---------- Variables del programa ---------//
int cantidadLeds = 50;//Determina la cantidad de leds a controlar
byte brilloLeds = 255;//Determina el brillo de los leds. El minimo es 0 y el maximo 255

long tiempoAnteriorComprobacion = 0;//Variable donde guardamos el valor de millis para compararlo
byte efectoActual = 0;//Determina el efecto que se esta generando
byte cantidadEfectos = 8;//Cantidad de efectos
bool estadoEfectos = true;//Determina si los efectos estan activos o no


//--------- Instancias de Objetos ---------//
Adafruit_NeoPixel leds(cantidadLeds, pinLeds, NEO_GRB + NEO_KHZ800);
AudioControl audio(pinLecturaAudio);


//-------- Inicializacion de los efectos -----------//
TransitionEffect efect_1(&leds, cantidadLeds, 4, 0.15, 8);
WaveEffect efect_2(&leds, cantidadLeds, 4, 0.15, 15);
DotsDegradableEffect efect_3(&leds, cantidadLeds, 4, 0.30, 40);// No adaptado a millis
WormEffect efect_4(&leds, cantidadLeds, 4, 0.15, 20);
RandomEffect efect_5(&leds, cantidadLeds, 4, 0.15, 5);
ReboundEffect efect_6(&leds, cantidadLeds, 4, 0.15, 40);
ShockEffect efect_7(&leds, cantidadLeds, 4, 0.15, 5);
ScrollingDotsEffect efect_8(&leds, cantidadLeds, 4, 0.15, 35);// No adaptado a millis


//--------- Creo un array con efectos ---------//
IEffects* efectos[] = {&efect_1, &efect_2, &efect_3, &efect_4, &efect_5, &efect_6, &efect_7, &efect_8};


void setup() {

    audio.setDetectionSilence(true, 10000, 10);//Activo la deteccion silencio, con un delay entre comprobaciones de 10 segundos y un techo de ruido de 10
    audio.setDetectionFrequency(5000);//Seteo la frecuencia de deteccion. Leer propiedades.txt

    leds.begin();//Inicializo los leds
    leds.clear();//Apago los leds
    leds.setBrightness(brilloLeds);//Seteo el brillo
}   


void loop(){

    if(estadoEfectos == true){
        efectos[efectoActual]->run(audio.readAudio());//Actualizo el estado de los leds
    }

    if((millis() - tiempoAnteriorComprobacion) >= 10000){
        efectoActual++;//Incremento el efecto
        estadoEfectos = true;//Activo los efectos
        leds.clear();//Apago los leds

        if(audio.getStateMute() == true){
            estadoEfectos = false;//Desactivo los efectos
        }

        if(efectoActual >= cantidadEfectos){
            efectoActual = 0;//Vuelvo a 0 los efectos
        }

        tiempoAnteriorComprobacion = millis();//Vuelvo a 0 la diferencia de timepo
    }
}