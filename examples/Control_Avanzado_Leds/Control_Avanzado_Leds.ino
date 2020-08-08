#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#include "AudioControl.h" // Libreria que controla el audio
#include "Effects.h" //Libreria que controla los efectos


//------Pines Utilizados ------//
byte pinLeds = 2;
byte pinLecturaAudio = A0;


//---------- Variables del programa ---------//
int cantidadLeds = 50;
byte brilloLeds = 255;

long tiempoAnteriorComprobacion = 0;
int efectoActual = 1;
int cantidadEfectos = 8;


//--------- Instancias de Objetos ---------//
Adafruit_NeoPixel pixels(cantidadLeds, pinLeds, NEO_GRB + NEO_KHZ800);// Instancio un objeto pixels
AudioControl audio(pinLecturaAudio);// Instancio el controlador de audio


//------------ Inicio los efectos ------------//
TransitionEffect efect_1(&pixels, cantidadLeds, 4, 0.15, 8);
WaveEffect efect_2(&pixels, cantidadLeds, 4, 0.15, 15);
DotsDegradableEffect efect_3(&pixels, cantidadLeds, 4, 0.30, 40);// No adaptado a millis
WormEffect efect_4(&pixels, cantidadLeds, 4, 0.15, 20);
RandomEffect efect_5(&pixels, cantidadLeds, 4, 0.15, 5);
ReboundEffect efect_6(&pixels, cantidadLeds, 4, 0.15, 40);
ShockEffect efect_7(&pixels, cantidadLeds, 4, 0.15, 5);
ScrollingDotsEffect efect_8(&pixels, cantidadLeds, 4, 0.15, 35);// No adaptado a millis


//--------- Creo un array de efectos ---------//
IEffects* efectos[] = {&efect_1, &efect_2, &efect_3, &efect_4, &efect_5, &efect_6, &efect_7, &efect_8};


void setup() {

    audio.setDetectionSilence(true, 10000, 10);//Activo la deteccion silencio, con un delay entre comprobaciones de 10 segundos y un techo de ruido de 10
    audio.setDetectionFrequency(5000);//Seteo la frecuencia de deteccion. Leer propiedades.txt

    //Inicializo los leds
    pixels.begin();
    pixels.clear();
    pixels.setBrightness(brilloLeds);
}   


void loop(){

    efectos[efectoActual]->run(audio.readAudio());//Actualizo el estado de los leds

    if((millis() - tiempoAnteriorComprobacion) >= 10000){
        efectoActual++;
        pixels.clear();//Apago los leds

        if(efectoActual >= cantidadEfectos){
            efectoActual = 0;
        }
        tiempoAnteriorComprobacion = millis();
    }
}