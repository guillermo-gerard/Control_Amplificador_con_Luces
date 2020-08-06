#include <Arduino.h>
#include "AudioControl.h"


AudioControl::AudioControl(byte pinAudio){///Aca le llega el objeto al constructor
    _pinAudio = pinAudio;
    pinMode(_pinAudio, INPUT);
}

void AudioControl::setDetectionFrequency(int frequency, float sensibilityPeak, int maxValuePeak){
    if(sensibilityPeak >= 0){_sensibilidadPico = sensibilityPeak;}
    if(frequency >= 0){_frecuenciaDeteccion = frequency;}
    if(maxValuePeak >= 0){_valorMaximoPico = maxValuePeak;}
}


void AudioControl::setDetectionSilence(bool value, int readingFrequency, int ruinValue){
    _deteccionMute = value;
    if(readingFrequency >= 0){_frecuenciaDeteccionSilencio = readingFrequency;}
    if(ruinValue >= 0){_valorDeRuido = ruinValue;}
}


bool AudioControl::getStateMute(){
    return _estadoMute;
}












float AudioControl::getAudio(){

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




float AudioControl::readAudio(){

    float valFinal = getAudio();
    deteccionDeSilencio(valFinal);
    return valFinal;
}




void AudioControl::deteccionDeSilencio(float valFinal){

   if(valFinal >= 1.0){
        _valorMute += valFinal;

        if(_estadoMute == true){
            _estadoMute = false;
        }
    }

    if(millis() > _tiempoMute + _frecuenciaDeteccionSilencio){

        if((_valorMute <= _valorDeRuido) && (_estadoMute == false)){
            _estadoMute = true;
        }
        _valorMute = 0.00;
        _tiempoMute = millis();
    }
}