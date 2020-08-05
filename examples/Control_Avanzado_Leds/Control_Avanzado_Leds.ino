#include <Adafruit_NeoPixel.h>
#include "PixelControl.h" //Libreria que controla los leds ws2812b
#include <Arduino.h>

byte pinLeds = 2;
byte pinLecturaAudio = A0;

int cantidadLeds = 50;
byte brilloLeds = 255;

Adafruit_NeoPixel pixels(cantidadLeds, pinLeds, NEO_GRB + NEO_KHZ800);// Instancio un objeto pixels
PixelControl leds(&pixels, cantidadLeds, pinLecturaAudio);//Le paso el objeto pixels

long tiempoAnteriorComprobacion = 0;


void setup() {

    Serial.begin(115200);

    leds.setDetectionSilence(true, 10000, 10);//Activo la deteccion silencio, con un delay entre comprobaciones de 10 segundos y un techo de ruido de 10
    leds.setDetectionFrequency(1000000, 3, 30);//Leer propiedades.txt

    //Inicializo el objeto pixels
    pixels.begin();
    pixels.clear();
    pixels.setBrightness(brilloLeds);
}   


void loop(){

    Serial.println(leds.readAudio());//Actualizo el estado de los leds
    
}