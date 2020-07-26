#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "PixelControl.h"


PixelControl::PixelControl(int quantityLeds, byte pinLeds, byte brightness, byte pinAudio){
    _pinAudio = pinAudio;
    _numPixel = quantityLeds;

    pixels = new Adafruit_NeoPixel(_numPixel, pinLeds, NEO_GRB + NEO_KHZ800);

    pixels->begin();
    pixels->clear();
    pixels->setBrightness(brightness);

    randomSeed(millis());
    pinMode(_pinAudio, INPUT);

    for(int i=0;i < _cantidadMaxLeds;i++){
        _divLedsEfectoVoz[0][i] = 20;
        _divLedsEfectoVoz[1][i] = 0;
    }
}



void PixelControl::setEfectsDelay(int numberEfects, int delay){
    _tiempoEntreEfectos = delay;
    _cantidadEfectos = numberEfects;
}


void PixelControl::setDetectionFrequency(int frequency, float sensibilityPeak, float maxValuePeak){
    _sensibilidadPico = sensibilityPeak;
    _frecuenciaDeteccion = frequency;
    _valorMaximoPico = maxValuePeak;
}


void PixelControl::setDetectionSilence(bool value, int readingFrequency, int ruinValue){
    _deteccionMute = value;
    _frecuenciaDeteccionSilencio = readingFrequency;
    _valorDeRuido = ruinValue;
}


void PixelControl::setStateEfects(bool value){
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


void PixelControl::setSpecificColor(byte r, byte g, byte b, int delayValue){

    for(int i=0;i < _numPixel;i++) {
        pixels->setPixelColor(i, r, g, b);
        pixels->show();
        delay(delayValue);
    }
}


bool PixelControl::getStateMute(){
    return _estadoMute;
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

    if(millis() > _tiempoEfectos + _tiempoEntreEfectos){ 

        _tiempoEfectos = millis();
        _efecto++;
        setSpecificColor(0,0,0,0);
        
        if(_efecto > _cantidadEfectos){
            _efecto = 1;
        }
    }


    if (valFinal > _valorMaximoPico){
        valFinal = _sensibilidadPico;
    }

    if (valFinal < _sensibilidadPico && _efecto != 3 && _efecto != 8){
        return;
    }

   
    switch(_efecto){

        case 1:
            efectoTransicion(valFinal);break;
        case 2:
            efectoOlas(valFinal);break;
        case 3:
            efectoPuntosDegradables(valFinal);break;
        case 4:
            efectoAvanico(valFinal);break;
        case 5:
            efectoRandom(valFinal);break;
        case 6:
            efectoRebote(valFinal);break;
        case 7:
            efectoChoque(valFinal);break;
        case 8:
            efectoPuntosDesplazables(valFinal);break;

        default: 
            _efecto = 1;break;
    }
}




void PixelControl::deteccionDeSilencio(float valFinal){

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











void PixelControl::efectoTransicion(float valPico){
 
    byte r = 0;
    byte g = 0;
    byte b = 0;
    int espera = 8;
    byte mitadLeds = _numPixel/2;
    byte limite = _numPixel-1;
 
    
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
            _pico = _pico - _valorDecrementoEntrePicos;
        }
    }

}






void PixelControl::efectoOlas(float valPico){

    int topeMaximoLeds = _numPixel + 6;
    int posMaximaRandom = _numPixel - 3;
    int posMinimaRandomv = 3;
    int ledArranque = 0;
    int delayEfecto = 15;
    int varAscendente = 0;
    int varDescendente = 0;
    bool topeAscentente = false;
    bool topeDescentente = false;
    byte r;
    byte g;
    byte b;



    if (valPico > _pico){

        _pico = valPico;

        ledArranque = random(posMinimaRandomv, posMaximaRandom);
        r = random(0,255);
        g = random(0,255);
        b = random(0,255);

        varAscendente = ledArranque;
        varDescendente = ledArranque;


        for(int i=0;i < topeMaximoLeds;i++){

        if(varAscendente < topeMaximoLeds){
            pixels->setPixelColor(varAscendente, r, g, b);
            if(varAscendente > ledArranque){pixels->setPixelColor(varAscendente-1, round(r/1.5), round(g/1.5), round(b/1.5));}
            if(varAscendente > (ledArranque+1)){pixels->setPixelColor(varAscendente-2, round(r/2), round(g/2), round(b/2));}
            if(varAscendente > (ledArranque+2)){pixels->setPixelColor(varAscendente-3, round(r/3), round(g/3), round(b/3));}
            if(varAscendente > (ledArranque+3)){pixels->setPixelColor(varAscendente-4, round(r/6), round(g/6), round(b/6));}
            if(varAscendente > (ledArranque+4)){pixels->setPixelColor(varAscendente-5, round(r/10), round(g/10), round(b/10));}
            if(varAscendente > (ledArranque+5)){pixels->setPixelColor(varAscendente-6, 0, 0, 0);}

            varAscendente++;
        }
        else{
            topeAscentente = true;
        }

        if(varDescendente >= -6){
            pixels->setPixelColor(varDescendente, r, g, b);
            if(varDescendente < ledArranque){pixels->setPixelColor(varDescendente+1, round(r/1.5), round(g/1.5), round(b/1.5));}
            if(varDescendente < (ledArranque-1)){pixels->setPixelColor(varDescendente+2, round(r/2), round(g/2), round(b/2));}
            if(varDescendente < (ledArranque-2)){pixels->setPixelColor(varDescendente+3, round(r/3), round(g/3), round(b/3));}
            if(varDescendente < (ledArranque-3)){pixels->setPixelColor(varDescendente+4, round(r/6), round(g/6), round(b/6));}
            if(varDescendente < (ledArranque-4)){pixels->setPixelColor(varDescendente+5, round(r/10), round(g/10), round(b/10));}
            if(varDescendente < (ledArranque-5)){pixels->setPixelColor(varDescendente+6, 0, 0, 0);}
            varDescendente--;
        }
        else{
            topeDescentente = true;
        }


        if((topeAscentente == true) && (topeDescentente == true)){
            break;
        }

        pixels->show();
        delay(delayEfecto);
        }

    }
    else {

        if (_pico > 1){
            _pico = _pico - _valorDecrementoEntrePicos;
        }
    }


}






void PixelControl::efectoPuntosDegradables(float valPico){

    byte divisorTemporal = 0;
    byte posicionTemporal = 0;
    byte posicion = 0;
    int delayCambioColor = 3000;
    int delayDecremento = 40;
    byte valorDeIncremento = 1;


    if(millis() > _tiempoEfectoPuntosDegradables + delayCambioColor){
        
        r_efectoVoz = random(0,255);
        g_efectoVoz = random(0,255);
        b_efectoVoz = random(0,255);
        
        _tiempoEfectoPuntosDegradables = millis();
    }
    

    if(millis() > _tiempoColorPuntosDegradables + delayDecremento){

        _tiempoColorPuntosDegradables = millis();

        for(int i=0;i < _cantidadMaxLeds;i++)
        {
            if(_divLedsEfectoVoz[0][i] >= 20){
            
                _divLedsEfectoVoz[0][i] = 0;
                _divLedsEfectoVoz[1][i] = 0;
            }
            else if(_divLedsEfectoVoz[0][i] > 0){

                divisorTemporal = _divLedsEfectoVoz[0][i];
                posicionTemporal = _divLedsEfectoVoz[1][i];
                pixels->setPixelColor(posicionTemporal, round(r_efectoVoz/divisorTemporal), round(g_efectoVoz/divisorTemporal), round(b_efectoVoz/divisorTemporal));
                pixels->setPixelColor(posicionTemporal + 1, round(r_efectoVoz/divisorTemporal+2), round(g_efectoVoz/divisorTemporal+2), round(b_efectoVoz/divisorTemporal+2));
                pixels->setPixelColor(posicionTemporal - 1, round(r_efectoVoz/divisorTemporal+2), round(g_efectoVoz/divisorTemporal+2), round(b_efectoVoz/divisorTemporal+2));
                _divLedsEfectoVoz[0][i] += valorDeIncremento;
            }

        }
        pixels->show();
    }


    if (valPico < _sensibilidadPico){
        return;
    }


    
    if(valPico > _pico){

        _pico = valPico;

        for(int i=0;i < _cantidadMaxLeds;i++)
        {
            if(_divLedsEfectoVoz[0][i] == 0){

                posicion = random(1, _numPixel);
                _divLedsEfectoVoz[0][i] = 1;
                _divLedsEfectoVoz[1][i] = posicion;
                break;
            }
        }

    }
    else {

        if (_pico > 1){
            _pico = _pico - (_valorDecrementoEntrePicos + 0.20);
        }
    }

}





void PixelControl::efectoAvanico(float valPico){

    byte pixel;
    byte r;
    byte g;
    byte b;


    if (valPico > _pico){

        _pico = valPico;

        pixel = random(0, _numPixel);
        r = random(0, 255);
        g = random(0, 255);
        b = random(0, 255);



        for(int i=0;i < 5;i++){

            pixels->setPixelColor(pixel, r, g, b);

            if(i > 0){
                pixels->setPixelColor(pixel+1, round(r/1.5), round(g/1.5), round(b/1.5));
                pixels->setPixelColor(pixel-1, round(r/1.5), round(g/1.5), round(b/1.5));
            }
            
            if(i > 1){
                pixels->setPixelColor(pixel+2, round(r/2), round(g/2), round(b/2));
                pixels->setPixelColor(pixel-2, round(r/2), round(g/2), round(b/2));
            }
            
            if(i > 2){
                pixels->setPixelColor(pixel+3, round(r/3), round(g/3), round(b/3));
                pixels->setPixelColor(pixel-3, round(r/3), round(g/3), round(b/3));
            }
            
            if(i > 3){
                pixels->setPixelColor(pixel+4, round(r/6), round(g/6), round(b/6));
                pixels->setPixelColor(pixel-4, round(r/6), round(g/6), round(b/6));
            }

            pixels->show();
            delay(25);
        }


        for(int i=4;i >= 0;i--){

            if(i <= 0){
                pixels->setPixelColor(pixel, 0, 0, 0);
            }

            if(i <= 1){
                pixels->setPixelColor(pixel+1, 0, 0, 0);
                pixels->setPixelColor(pixel-1, 0, 0, 0);
            }
            
            if(i <= 2){
                pixels->setPixelColor(pixel+2, 0, 0, 0);
                pixels->setPixelColor(pixel-2, 0, 0, 0);
            }
            
            if(i <= 3){
                pixels->setPixelColor(pixel+3, 0, 0, 0);
                pixels->setPixelColor(pixel-3, 0, 0, 0);
            }
            
            if(i <= 4){
                pixels->setPixelColor(pixel+4, 0, 0, 0);
                pixels->setPixelColor(pixel-4, 0, 0, 0);
            }

            delay(45);
            pixels->show();
        }

    }
    else {

        if (_pico > 1){
            _pico = _pico - _valorDecrementoEntrePicos;
        }
    }


}




void PixelControl::efectoRandom(float valPico){
    
    int velocidad = 5;
    int pixelElegido = 0;
    int avanceMaximo = round(_numPixel/3);
    int avance = 0;
    int a = 0;
    byte r;
    byte g;
    byte b;

        
    if(valPico > _pico){

        _pico = valPico;

        pixelElegido = random(0,_numPixel);
        avance = random(4,_numPixel);
        r = random(0,255);
        g = random(0,255);
        b = random(0,255);
        a = pixelElegido;


        for(int i=pixelElegido;i < avance;i++){

            if(i < _numPixel){pixels->setPixelColor(i,r,g,b);}
            if(a >= 0){pixels->setPixelColor(a,r,g,b);a--;}

            pixels->show();
            delay(velocidad);
        }

    }
    else {
    
        if(_pico > 1){
            _pico = _pico - _valorDecrementoEntrePicos;
        }
    }
}





void PixelControl::efectoRebote(float valPico){

    byte a = 7;
    int delayEfecto = 40;
    int pixel = 1;


    if (valPico > _pico){

        _pico = valPico;

        for(int i=0;i < 8;i++){

            for(int p=0;p < _numPixel;p=p+8){

                pixels->setPixelColor(i+p, r_EfectoRebote, g_EfectoRebote, b_EfectoRebote);
                pixels->setPixelColor(a+p, r_EfectoRebote, g_EfectoRebote, b_EfectoRebote);
                if((i != 4) && (i > 0)){pixels->setPixelColor((i+p)-1, 0, 0, 0);}
                if((a != 3) && (i > 0)){pixels->setPixelColor((a+p)+1, 0, 0, 0);}
            }

            delay(delayEfecto);
            pixels->show();
            a--;

            if(i == 3){
                r_EfectoRebote = random(0, 255);
                g_EfectoRebote = random(0, 255);
                b_EfectoRebote = random(0, 255);
            }
        }

    }
    else {

        if (_pico > 1){
            _pico = _pico - _valorDecrementoEntrePicos;
        }
    }
}





void PixelControl::efectoChoque(float valPico){

    int mitadTira = _numPixel/2;
    int delayEfecto = 5;
    int delayDeChoque = 20;
    byte r;
    byte g;
    byte b;


    if (valPico > _pico){

        _pico = valPico;

        r = random(0, 255);
        g = random(0, 255);
        b = random(0, 255);

        for(int i=0;i < mitadTira+2;i++){

            if(i < mitadTira){

                pixels->setPixelColor(i, r, g, b);
                pixels->setPixelColor((_numPixel-1)-i, r, g, b);

                if(i > 0){pixels->setPixelColor(i-1, r, g, b); pixels->setPixelColor(_numPixel-i, r, g, b);}
                if(i > 1){pixels->setPixelColor(i-2, r, g, b); pixels->setPixelColor((_numPixel+1)-i, r, g, b);}
                if(i > 2){pixels->setPixelColor(i-3, r, g, b); pixels->setPixelColor((_numPixel+2)-i, r, g, b);}
            }

            if(i > 3){pixels->setPixelColor(i-4, 0, 0, 0); pixels->setPixelColor((_numPixel+3)-i, 0, 0, 0);}

            if(i > (mitadTira - 3)){
                delay(delayDeChoque);
            }
            else{
                delay(delayEfecto);
            }

            pixels->show();
        }


        for(int i=(mitadTira - 1);i >= -4;i--){
        
            if(i > -1){pixels->setPixelColor(i, r, g, b); pixels->setPixelColor((_numPixel-1)-i, r, g, b);}
            if((i > -2) && (i < (mitadTira-2))){pixels->setPixelColor(i+1, r, g, b); pixels->setPixelColor((_numPixel-2)-i, r, g, b);}
            if((i > -3) && (i < (mitadTira-3))){pixels->setPixelColor(i+2, r, g, b); pixels->setPixelColor((_numPixel-3)-i, r, g, b);}
            if((i > -4) && (i < (mitadTira-4))){pixels->setPixelColor(i+3, r, g, b); pixels->setPixelColor((_numPixel-4)-i, r, g, b);}

            if((i > -5) && (i < (mitadTira-4))){pixels->setPixelColor(i+4, 0, 0, 0); pixels->setPixelColor((_numPixel-5)-i, 0, 0, 0);}

            delay(delayEfecto);
            pixels->show();
        }

    }
    else {

        if (_pico > 1){
            _pico = _pico - _valorDecrementoEntrePicos;
        }
    }
}





void PixelControl::efectoPuntosDesplazables(float valPico){

    const int cantidadLedsDesplazables = 200;
    byte posMaxima = (_numPixel / 2) + 1;
    byte delayEntreDesplazamientos = 35;
    int delayCambioColor = 3000;


    if(millis() > _tiempoColorPuntosDesplazables + delayCambioColor){

        _tiempoColorPuntosDesplazables = millis();

        r_puntosDesplazables = random(0, 255);
        g_puntosDesplazables = random(0, 255);
        b_puntosDesplazables = random(0, 255);
    }


    if(millis() > _tiempoEfectoPuntosDesplazables + delayEntreDesplazamientos){

        _tiempoEfectoPuntosDesplazables = millis();

        for(int i=0;i < cantidadLedsDesplazables;i++)
        {
            if(_ledsDesplazables[i] > posMaxima){
                _ledsDesplazables[i] = 0;
                pixels->setPixelColor(_ledsDesplazables[i], 0, 0, 0);
            }
            else if(_ledsDesplazables[i] > 0){
                pixels->setPixelColor(_ledsDesplazables[i]-1, r_puntosDesplazables, g_puntosDesplazables, b_puntosDesplazables);
                pixels->setPixelColor((_numPixel - _ledsDesplazables[i]), r_puntosDesplazables, g_puntosDesplazables, b_puntosDesplazables);
                pixels->setPixelColor(_ledsDesplazables[i]-2, 0, 0, 0);
                pixels->setPixelColor(((_numPixel + 1) - _ledsDesplazables[i]), 0, 0, 0);
                _ledsDesplazables[i] += 1;
            }
        }
        pixels->show();
    }



    if (valPico < _sensibilidadPico){
        return;
    }



    if (valPico > _pico){

        _pico = valPico;
    
        for(int i=0;i < cantidadLedsDesplazables;i++){
            if(_ledsDesplazables[i] == 0){
                _ledsDesplazables[i] = 1;
                break;
            }
        }

    }
    else {

        if (_pico > 1){
            _pico = _pico - (_valorDecrementoEntrePicos + 0.20);
        }
    }
}