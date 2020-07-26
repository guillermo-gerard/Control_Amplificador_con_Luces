#include "AmplifiedControl.h"
#include "PixelControl.h"
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


AmplifiedControl ampli(5, A2, 9);
PixelControl pix(16, A1, 2);

long tiempoAnteriorTemperatura = 0;


void setup() {

    Serial.begin(115200);
    ampli.setTemperatureRange(40, 45, 80);
    ampli.mute(false);
}


void loop(){

    pix.updateStatus();

    if(millis() > tiempoAnteriorTemperatura + 1000)
    {
        Serial.println(ampli.readTemperature());
        tiempoAnteriorTemperatura = millis();
    }

    delay(1);
}