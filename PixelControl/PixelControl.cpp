#include <Arduino.h>
#include "PixelControl.h"


PixelControl::PixelControl(Adafruit_NeoPixel *pixels, int quantityLeds, byte pinAudio){///Aca le llega el objeto al constructor
    _pinAudio = pinAudio;
    _numPixel = quantityLeds;

    this->pixels = pixels;//Lo definimos como objeto ???

    pinMode(_pinAudio, INPUT);
}

void PixelControl::setDetectionFrequency(int frequency, float sensibilityPeak, int maxValuePeak){
    if(sensibilityPeak >= 0){_sensibilidadPico = sensibilityPeak;}
    if(frequency >= 0){_frecuenciaDeteccion = frequency;}
    if(maxValuePeak >= 0){_valorMaximoPico = maxValuePeak;}
}


void PixelControl::setDetectionSilence(bool value, int readingFrequency, int ruinValue){
    _deteccionMute = value;
    if(readingFrequency >= 0){_frecuenciaDeteccionSilencio = readingFrequency;}
    if(ruinValue >= 0){_valorDeRuido = ruinValue;}
}



void PixelControl::setSpecificColor(byte r, byte g, byte b, int delayValue){

    for(int i=0;i < _numPixel;i++) {
        pixels->setPixelColor(i, r, g, b);
        pixels->show();
        if(delayValue >= 0){delay(delayValue);}
    }
}


bool PixelControl::getStateMute(){
    return _estadoMute;
}












float PixelControl::getAudio(){

    float val;
    float diferencia;

    if((micros() - _timpoDeteccionAudio) >= _frecuenciaDeteccion){

        val = analogRead(_pinAudio);
        diferencia = val - _valorAudioAnterior;
        _valorAudioAnterior = val;
        _timpoDeteccionAudio = millis();

        return max(0, diferencia);
    }

    return 0;
}




float PixelControl::readAudio(){

    float valFinal = getAudio();
    deteccionDeSilencio(valFinal);
    return valFinal;
}




void PixelControl::deteccionDeSilencio(float valFinal){

   if(valFinal >= 1.0){
        _valorMute += valFinal;

        if(_estadoMute == true){
            _estadoMute = false;
        }
    }

    //esto explota en el rollover, mira este: https://youtu.be/hq999kZk3Hg
    if(millis() > _tiempoMute + _frecuenciaDeteccionSilencio){

        if((_valorMute <= _valorDeRuido) && (_estadoMute == false)){
            _estadoMute = true;
        }
        _valorMute = 0.00;
        _tiempoMute = millis();
    }
}