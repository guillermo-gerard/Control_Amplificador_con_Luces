#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#include "AudioControl.h" // Libreria que controla el audio
#include "Efects.h" //Libreria que controla los efectos
#include "IEfects.h" //Interfaz de los efectos

byte pinLeds = 2;
byte pinLecturaAudio = A0;

int cantidadLeds = 50;
byte brilloLeds = 255;

Adafruit_NeoPixel pixels(cantidadLeds, pinLeds, NEO_GRB + NEO_KHZ800);// Instancio un objeto pixels
AudioControl audio(pinLecturaAudio);// Instancio el controlador de audio
EfectTransition efect_1(&pixels, cantidadLeds, 4, 0.15);// Inizializo el efecto 1

IEfects* efectos[] = {&efect_1};// Creo un array de efectos

long tiempoAnteriorComprobacion = 0;
int efectoActual = 0;


void setup() {

    Serial.begin(115200);

    audio.setDetectionSilence(true, 10000, 10);//Activo la deteccion silencio, con un delay entre comprobaciones de 10 segundos y un techo de ruido de 10
    audio.setDetectionFrequency(3750, 5, 30);//Leer propiedades.txt

    //Inicializo el objeto pixels
    pixels.begin();
    pixels.clear();
    pixels.setBrightness(brilloLeds);
}   


void loop(){

    efectos[efectoActual]->run(audio.readAudio());//Actualizo el estado de los leds
    
}