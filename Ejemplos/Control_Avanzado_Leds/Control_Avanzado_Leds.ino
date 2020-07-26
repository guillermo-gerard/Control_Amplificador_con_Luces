/* En este ejemplo avanzado se controlan 50 leds ws2812b al ritmo de la musica (utilizando un filtro pasa bajos externo).
*  En el ejemplo no se usa DELAY, ya que este entorpece la lectura de audio
*
*  Pines utilizados:
*  2(out) -> Pin de Datos de los leds
*  A0(in) -> Pin de lectuta de audio (es recomendable que tenga un filtro pasa bajos)
*/

// ¡¡¡¡ IMPORTANTE !!!!
// Es necesario tener instalada la libreria: Adafruit_NeoPixel.h en la misma carpeta que la PixelControl.h

#include "PixelControl.h" //Libreria que controla los leds ws2812b
#include <Arduino.h>

byte pinLeds = 2;
byte pinLecturaAudio = A0;

int cantidadLeds = 50;//La cantidad de leds se puede modificar (procure que la cantidad sea par)
byte billoLeds = 255;//Determina el brillo de los leds. El minimo es 0 y el maximo 255

PixelControl leds(cantidadLeds, pinLeds, billoLeds, pinLecturaAudio);

long tiempoAnteriorComprobacion = 0;


void setup() {

    leds.setEfectsDelay(8, 20000);//Seteamos la cantidad de efectos y el delay (en milisegundos) entre cada uno
    leds.setDetectionSilence(true, 10000, 10);//Activo la deteccion silencio, con un delay entre comprobaciones de 10 segundos y un techo de ruido de 10
    leds.setStateEfects(true);//Activo los efectos de luz
    leds.setDetectionFrequency(1650, 4, 30);//Leer propiedades.txt
}   


void loop(){

    leds.updateStatus();//Actualizo el estado de los leds
    
    if(millis() > tiempoAnteriorComprobacion + 1000){

        //Si no se detecta audio en la entrada entra al IF
        if(leds.getStateMute() == true){
            leds.setSpecificColor(0,0,0,0);//cada color (r, g, b, delay) puede tomar valores de 0 a 255
            leds.setStateEfects(false);//Apagamos los efectos
        }
        else{
            leds.setStateEfects(true);//Activamos los efectos 
        }
        tiempoAnteriorComprobacion = millis();
    }
}