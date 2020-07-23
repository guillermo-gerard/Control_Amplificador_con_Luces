#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "PixelControl.h"



PixelControl::PixelControl(int quantityLeds, byte pinAudio, byte pinLeds){
    _pinAudio = pinAudio;
    _numPixel = quantityLeds;

    pixels = new Adafruit_NeoPixel(_numPixel, pinLeds, NEO_GRB + NEO_KHZ800);

    pixels->begin();
    pixels->clear();
    pixels->setBrightness(255);

    randomSeed(millis());

    pinMode(_pinAudio, INPUT);


    for(int i=0;i < _cantidadMaxLeds;i++){
        _divLedsEfectoVoz[0][i] = 20;
        _divLedsEfectoVoz[1][i] = 0;
    }


    luzTemperaturaAlta();//Si ejecuto esta funcion que utiliza los leds 
                         //el programa se cuelga
                         //Si no la ejecuto funciona bien
}


void PixelControl::luzTemperaturaAlta(){

  for(int i=0;i < _numPixel;i++) {
    
    pixels->setPixelColor(i, 50, 0, 0); // i, R, G, B
    pixels->show();
  }
}



void PixelControl::setEfectsDelay(int numberEfects, int delay){
    _tiempoEntreEfectos = delay;
    _cantidadEfectos = numberEfects;
}


void PixelControl::setDetectionFrequency(int frequency, float sensibilityPeak){
    _sensibilidadPico = sensibilityPeak;
    _frecuenciaDeteccion = frequency;
}


void PixelControl::detectionSilence(bool value){
    _deteccionMute = value;
}


void PixelControl::pixelState(bool value){
    _estadoPixels = value;
}


float PixelControl::updateStatus(){

    float valFinal = lecturaAudio();

    if(_estadoPixels == true){
        actualizarEfecto(valFinal);
    }

    if(_deteccionMute == true){
        deteccionDeSilencio(valFinal);
    }

    return valFinal;
}












float PixelControl::lecturaAudio(){

    float val;
    float valFinal;
    float diferencia;

    delayMicroseconds(_frecuenciaDeteccion);
    val = analogRead(_pinAudio);

    diferencia = val - _valorAudioAnterior;
    _valorAudioAnterior = val;
    return max(0, diferencia);
}





void PixelControl::actualizarEfecto(float valFinal){

    if(millis() > _tiempoEntreEfectos + _tiempoEntreEfectos) 
    { 

        _tiempoEntreEfectos = millis();
        _efecto++;
        ledsApagados();
        
        if(_efecto > _cantidadEfectos){
            _efecto = 1;
        }
    }

   
    switch(_efecto){

        case 1:
            efectoTransicion(valFinal);break;
        case 2:
            //efectoOlas(valFinal);break;
        case 3:
            //efectoPuntosDegradables(valFinal);break;
        case 4:
            //efectoAvanico(valFinal);break;
        case 5:
            //efectoTren(valFinal);break;
        case 6:
            //efectoRebote(valFinal);break;
        case 7:
            //efectoChoque(valFinal);break;
        case 8:
            //efectoPuntosDesplazables(valFinal);break;

        default: 
            _efecto = 1;break;
    }
}




void PixelControl::deteccionDeSilencio(float valFinal){

  int delayEntreComprobaciones = 10000;
  float valorRuido = 10.00; 

  if(valFinal >= 1.0){
    _valorMute += valFinal;

    if(_estadoMute == true){
      ledsApagados();
      _estadoMute = false;
      pixelState(true);
    }
  }

  if(millis() > _tiempoMute + delayEntreComprobaciones){

    if((_valorMute <= valorRuido) && (_estadoMute == false)){
      pixelState(false);
      _estadoMute = true;
      ledsApagados();
    }

    _valorMute = 0.00;
    _tiempoMute = millis();
  }
}




void PixelControl::ledsApagados(){

  for(int i=0;i < _numPixel;i++) {
    
    pixels->setPixelColor(i, 0, 0, 0); // i, R, G, B
    pixels->show();
  }
}






void PixelControl::efectoTransicion(float valPico){
 
    byte r = 0;
    byte g = 0;
    byte b = 0;
    int espera = 20;// Velocidad de el cambio de color
    byte mitadLeds = _numPixel/2;
    byte limite = _numPixel-1;



    if(valPico > 30){
        valPico = _sensibilidadPico;
    }

    if(valPico < _sensibilidadPico){
        return;
    }
 
    
    if(valPico > _pico)
    {
        _pico = valPico;

        r = random(0,255);
        g = random(0,255);
        b = random(0,255);


        if(_direccionEfecto == false)
        {
            for(int i=0;i < mitadLeds;i++){

                if(i < mitadLeds){pixels->setPixelColor(i+1, 0, 0, 0);}
                pixels->setPixelColor(i, r, g, b);
                pixels->setPixelColor((_numPixel-1)-i, r, g, b);
                if(i < (mitadLeds-1)){pixels->setPixelColor((_numPixel-2)-i, 0, 0, 0);}

                pixels->show();
                delay(espera);
            }
            _direccionEfecto = true;
        }
        else
        {
            for(int i=mitadLeds;i >= 0;i--){

                if(i > 0){pixels->setPixelColor(i-1, 0, 0, 0);}
                if(i < (_numPixel/2)){pixels->setPixelColor(i, r, g, b);}
                if(i < (_numPixel/2)){pixels->setPixelColor((_numPixel-1)-i, r, g, b);}
                if(i > 0){pixels->setPixelColor(_numPixel-i, 0, 0, 0);}

                pixels->show();
                delay(espera);
            }
            _direccionEfecto = false;
        }
    
    }
    else {
    
        if(_pico > 1){
            _pico -= 0.15;
        }
    }

}
