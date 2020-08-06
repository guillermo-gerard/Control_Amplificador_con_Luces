#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "Effects.h"



TransitionEffect::TransitionEffect(Adafruit_NeoPixel *pixels, int value, int sensibilityPeak, float decrementValue, int delayEffect){
    _numPixel = value;
    _pixels = pixels;
    if(sensibilityPeak > 0){_sensibilidadPico = sensibilityPeak;}
    if(decrementValue >= 0){_valorDecrementoEntrePicos = decrementValue;}
    if(delayEffect > 0){_delayEfecto = delayEffect;}
}

void TransitionEffect::run(float valPico){

    byte r = 0;
    byte g = 0;
    byte b = 0;
    int espera = _delayEfecto;
    byte mitadLeds = _numPixel/2;
    byte limite = _numPixel-1;

    if(valPico < _sensibilidadPico){return;}
 
    
    if(valPico > _pico)
    {
        _pico = valPico;

        r = random(0,255);
        g = random(0,255);
        b = random(0,255);


        if(_direccionEfecto == false)
        {
            for(int i=0;i < mitadLeds;i++){

                if(i < mitadLeds){_pixels->setPixelColor(i+1, 0, 0, 0);}
                _pixels->setPixelColor(i, r, g, b);
                _pixels->setPixelColor((_numPixel-1)-i, r, g, b);
                if(i < (mitadLeds-1)){_pixels->setPixelColor((_numPixel-2)-i, 0, 0, 0);}

                _pixels->show();
                delay(espera);
            }
            _direccionEfecto = true;
        }
        else
        {
            for(int i=mitadLeds;i >= 0;i--){

                if(i > 0){_pixels->setPixelColor(i-1, 0, 0, 0);}
                if(i < (_numPixel/2)){_pixels->setPixelColor(i, r, g, b);}
                if(i < (_numPixel/2)){_pixels->setPixelColor((_numPixel-1)-i, r, g, b);}
                if(i > 0){_pixels->setPixelColor(_numPixel-i, 0, 0, 0);}

                _pixels->show();
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









WaveEffect::WaveEffect(Adafruit_NeoPixel *pixels, int value, int sensibilityPeak, float decrementValue, int delayEffect){
    _numPixel = value;
    _pixels = pixels;
    if(sensibilityPeak > 0){_sensibilidadPico = sensibilityPeak;}
    if(decrementValue >= 0){_valorDecrementoEntrePicos = decrementValue;}
    if(delayEffect > 0){_delayEfecto = delayEffect;}
}

void WaveEffect::run(float valPico){

    int topeMaximoLeds = _numPixel + 6;
    int posMaximaRandom = _numPixel - 3;
    int posMinimaRandomv = 3;
    int ledArranque = 0;
    int varAscendente = 0;
    int varDescendente = 0;
    bool topeAscentente = false;
    bool topeDescentente = false;
    byte r;
    byte g;
    byte b;


    if(valPico < _sensibilidadPico){return;}


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
            _pixels->setPixelColor(varAscendente, r, g, b);
            if(varAscendente > ledArranque){_pixels->setPixelColor(varAscendente-1, round(r/1.5), round(g/1.5), round(b/1.5));}
            if(varAscendente > (ledArranque+1)){_pixels->setPixelColor(varAscendente-2, round(r/2), round(g/2), round(b/2));}
            if(varAscendente > (ledArranque+2)){_pixels->setPixelColor(varAscendente-3, round(r/3), round(g/3), round(b/3));}
            if(varAscendente > (ledArranque+3)){_pixels->setPixelColor(varAscendente-4, round(r/6), round(g/6), round(b/6));}
            if(varAscendente > (ledArranque+4)){_pixels->setPixelColor(varAscendente-5, round(r/10), round(g/10), round(b/10));}
            if(varAscendente > (ledArranque+5)){_pixels->setPixelColor(varAscendente-6, 0, 0, 0);}

            varAscendente++;
        }
        else{
            topeAscentente = true;
        }

        if(varDescendente >= -6){
            _pixels->setPixelColor(varDescendente, r, g, b);
            if(varDescendente < ledArranque){_pixels->setPixelColor(varDescendente+1, round(r/1.5), round(g/1.5), round(b/1.5));}
            if(varDescendente < (ledArranque-1)){_pixels->setPixelColor(varDescendente+2, round(r/2), round(g/2), round(b/2));}
            if(varDescendente < (ledArranque-2)){_pixels->setPixelColor(varDescendente+3, round(r/3), round(g/3), round(b/3));}
            if(varDescendente < (ledArranque-3)){_pixels->setPixelColor(varDescendente+4, round(r/6), round(g/6), round(b/6));}
            if(varDescendente < (ledArranque-4)){_pixels->setPixelColor(varDescendente+5, round(r/10), round(g/10), round(b/10));}
            if(varDescendente < (ledArranque-5)){_pixels->setPixelColor(varDescendente+6, 0, 0, 0);}
            varDescendente--;
        }
        else{
            topeDescentente = true;
        }


        if((topeAscentente == true) && (topeDescentente == true)){
            break;
        }

        _pixels->show();
        delay(_delayEfecto);
        }

    }
    else {

        if (_pico > 1){
            _pico = _pico - _valorDecrementoEntrePicos;
        }
    }


}








DotsDegradableEffect::DotsDegradableEffect(Adafruit_NeoPixel *pixels, int value, int sensibilityPeak, float decrementValue, int delayEffect){
    _numPixel = value;
    _pixels = pixels;
    if(sensibilityPeak > 0){_sensibilidadPico = sensibilityPeak;}
    if(decrementValue >= 0){_valorDecrementoEntrePicos = decrementValue;}
    if(delayEffect > 0){_delayEfecto = delayEffect;}
}

void DotsDegradableEffect::run(float valPico){

    byte divisorTemporal = 0;
    byte posicionTemporal = 0;
    byte posicion = 0;
    int delayCambioColor = 3000;
    byte valorDeIncremento = 1;


    if(millis() > _tiempoEfectoPuntosDegradables + delayCambioColor){
        
        r_efectoVoz = random(0,255);
        g_efectoVoz = random(0,255);
        b_efectoVoz = random(0,255);
        
        _tiempoEfectoPuntosDegradables = millis();
    }
    

    if(millis() > _tiempoColorPuntosDegradables + _delayEfecto){

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
                _pixels->setPixelColor(posicionTemporal, round(r_efectoVoz/divisorTemporal), round(g_efectoVoz/divisorTemporal), round(b_efectoVoz/divisorTemporal));
                _pixels->setPixelColor(posicionTemporal + 1, round(r_efectoVoz/divisorTemporal+2), round(g_efectoVoz/divisorTemporal+2), round(b_efectoVoz/divisorTemporal+2));
                _pixels->setPixelColor(posicionTemporal - 1, round(r_efectoVoz/divisorTemporal+2), round(g_efectoVoz/divisorTemporal+2), round(b_efectoVoz/divisorTemporal+2));
                _divLedsEfectoVoz[0][i] += valorDeIncremento;
            }

        }
        _pixels->show();
    }


    if(valPico < _sensibilidadPico){return;}

    
    if(valPico > _pico){

        _pico = valPico;

        for(int i=0;i < _cantidadMaxLeds;i++){
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
            _pico = _pico - _valorDecrementoEntrePicos;
        }
    }

}








WormEffect::WormEffect(Adafruit_NeoPixel *pixels, int value, int sensibilityPeak, float decrementValue, int delayEffect){
    _numPixel = value;
    _pixels = pixels;
    if(sensibilityPeak > 0){_sensibilidadPico = sensibilityPeak;}
    if(decrementValue >= 0){_valorDecrementoEntrePicos = decrementValue;}
    if(delayEffect > 0){_delayEfecto = delayEffect;}
}

void WormEffect::run(float valPico){

    byte pixel;
    byte r;
    byte g;
    byte b;

    if(valPico < _sensibilidadPico){return;}


    if (valPico > _pico){

        _pico = valPico;

        pixel = random(0, _numPixel);
        r = random(0, 255);
        g = random(0, 255);
        b = random(0, 255);



        for(int i=0;i < 5;i++){

            _pixels->setPixelColor(pixel, r, g, b);

            if(i > 0){
                _pixels->setPixelColor(pixel+1, round(r/1.5), round(g/1.5), round(b/1.5));
                _pixels->setPixelColor(pixel-1, round(r/1.5), round(g/1.5), round(b/1.5));
            }
            
            if(i > 1){
                _pixels->setPixelColor(pixel+2, round(r/2), round(g/2), round(b/2));
                _pixels->setPixelColor(pixel-2, round(r/2), round(g/2), round(b/2));
            }
            
            if(i > 2){
                _pixels->setPixelColor(pixel+3, round(r/3), round(g/3), round(b/3));
                _pixels->setPixelColor(pixel-3, round(r/3), round(g/3), round(b/3));
            }
            
            if(i > 3){
                _pixels->setPixelColor(pixel+4, round(r/6), round(g/6), round(b/6));
                _pixels->setPixelColor(pixel-4, round(r/6), round(g/6), round(b/6));
            }

            _pixels->show();
            delay(_delayEfecto);
        }


        for(int i=4;i >= 0;i--){

            if(i <= 0){
                _pixels->setPixelColor(pixel, 0, 0, 0);
            }

            if(i <= 1){
                _pixels->setPixelColor(pixel+1, 0, 0, 0);
                _pixels->setPixelColor(pixel-1, 0, 0, 0);
            }
            
            if(i <= 2){
                _pixels->setPixelColor(pixel+2, 0, 0, 0);
                _pixels->setPixelColor(pixel-2, 0, 0, 0);
            }
            
            if(i <= 3){
                _pixels->setPixelColor(pixel+3, 0, 0, 0);
                _pixels->setPixelColor(pixel-3, 0, 0, 0);
            }
            
            if(i <= 4){
                _pixels->setPixelColor(pixel+4, 0, 0, 0);
                _pixels->setPixelColor(pixel-4, 0, 0, 0);
            }

            delay(_delayEfecto * 2);
            _pixels->show();
        }

    }
    else {

        if (_pico > 1){
            _pico = _pico - _valorDecrementoEntrePicos;
        }
    }


}









RandomEffect::RandomEffect(Adafruit_NeoPixel *pixels, int value, int sensibilityPeak, float decrementValue, int delayEffect){
    _numPixel = value;
    _pixels = pixels;
    if(sensibilityPeak > 0){_sensibilidadPico = sensibilityPeak;}
    if(decrementValue >= 0){_valorDecrementoEntrePicos = decrementValue;}
    if(delayEffect > 0){_delayEfecto = delayEffect;}
}

void RandomEffect::run(float valPico){
    
    int pixelElegido = 0;
    int avanceMaximo = round(_numPixel/3);
    int avance = 0;
    int a = 0;
    byte r;
    byte g;
    byte b;


    if(valPico < _sensibilidadPico){return;}

        
    if(valPico > _pico){

        _pico = valPico;

        pixelElegido = random(0,_numPixel);
        avance = random(4,_numPixel);
        r = random(0,255);
        g = random(0,255);
        b = random(0,255);
        a = pixelElegido;


        for(int i=pixelElegido;i < avance;i++){

            if(i < _numPixel){_pixels->setPixelColor(i,r,g,b);}
            if(a >= 0){_pixels->setPixelColor(a,r,g,b);a--;}

            _pixels->show();
            delay(_delayEfecto);
        }

    }
    else {
    
        if(_pico > 1){
            _pico = _pico - _valorDecrementoEntrePicos;
        }
    }
}








ReboundEffect::ReboundEffect(Adafruit_NeoPixel *pixels, int value, int sensibilityPeak, float decrementValue, int delayEffect){
    _numPixel = value;
    _pixels = pixels;
    if(sensibilityPeak > 0){_sensibilidadPico = sensibilityPeak;}
    if(decrementValue >= 0){_valorDecrementoEntrePicos = decrementValue;}
    if(delayEffect > 0){_delayEfecto = delayEffect;}
}

void ReboundEffect::run(float valPico){

    byte a = 7;
    int pixel = 1;


    if(valPico < _sensibilidadPico){return;}


    if (valPico > _pico){

        _pico = valPico;

        for(int i=0;i < 8;i++){

            for(int p=0;p < _numPixel;p=p+8){

                _pixels->setPixelColor(i+p, r_EfectoRebote, g_EfectoRebote, b_EfectoRebote);
                _pixels->setPixelColor(a+p, r_EfectoRebote, g_EfectoRebote, b_EfectoRebote);
                if((i != 4) && (i > 0)){_pixels->setPixelColor((i+p)-1, 0, 0, 0);}
                if((a != 3) && (i > 0)){_pixels->setPixelColor((a+p)+1, 0, 0, 0);}
            }

            delay(_delayEfecto);
            _pixels->show();
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









ShockEffect::ShockEffect(Adafruit_NeoPixel *pixels, int value, int sensibilityPeak, float decrementValue, int delayEffect){
    _numPixel = value;
    _pixels = pixels;
    if(sensibilityPeak > 0){_sensibilidadPico = sensibilityPeak;}
    if(decrementValue >= 0){_valorDecrementoEntrePicos = decrementValue;}
    if(delayEffect > 0){_delayEfecto = delayEffect;}
}

void ShockEffect::run(float valPico){

    int mitadTira = _numPixel/2;
    int delayDeChoque = 20;
    byte r;
    byte g;
    byte b;


    if(valPico < _sensibilidadPico){return;}


    if (valPico > _pico){

        _pico = valPico;

        r = random(0, 255);
        g = random(0, 255);
        b = random(0, 255);

        for(int i=0;i < mitadTira+2;i++){

            if(i < mitadTira){

                _pixels->setPixelColor(i, r, g, b);
                _pixels->setPixelColor((_numPixel-1)-i, r, g, b);

                if(i > 0){_pixels->setPixelColor(i-1, r, g, b); _pixels->setPixelColor(_numPixel-i, r, g, b);}
                if(i > 1){_pixels->setPixelColor(i-2, r, g, b); _pixels->setPixelColor((_numPixel+1)-i, r, g, b);}
                if(i > 2){_pixels->setPixelColor(i-3, r, g, b); _pixels->setPixelColor((_numPixel+2)-i, r, g, b);}
            }

            if(i > 3){_pixels->setPixelColor(i-4, 0, 0, 0); _pixels->setPixelColor((_numPixel+3)-i, 0, 0, 0);}

            if(i > (mitadTira - 3)){
                delay(delayDeChoque);
            }
            else{
                delay(_delayEfecto);
            }

            _pixels->show();
        }


        for(int i=(mitadTira - 1);i >= -4;i--){
        
            if(i > -1){_pixels->setPixelColor(i, r, g, b); _pixels->setPixelColor((_numPixel-1)-i, r, g, b);}
            if((i > -2) && (i < (mitadTira-2))){_pixels->setPixelColor(i+1, r, g, b); _pixels->setPixelColor((_numPixel-2)-i, r, g, b);}
            if((i > -3) && (i < (mitadTira-3))){_pixels->setPixelColor(i+2, r, g, b); _pixels->setPixelColor((_numPixel-3)-i, r, g, b);}
            if((i > -4) && (i < (mitadTira-4))){_pixels->setPixelColor(i+3, r, g, b); _pixels->setPixelColor((_numPixel-4)-i, r, g, b);}

            if((i > -5) && (i < (mitadTira-4))){_pixels->setPixelColor(i+4, 0, 0, 0); _pixels->setPixelColor((_numPixel-5)-i, 0, 0, 0);}

            delay(_delayEfecto);
            _pixels->show();
        }

    }
    else {

        if (_pico > 1){
            _pico = _pico - _valorDecrementoEntrePicos;
        }
    }
}







ScrollingDotsEffect::ScrollingDotsEffect(Adafruit_NeoPixel *pixels, int value, int sensibilityPeak, float decrementValue, int delayEffect){
    _numPixel = value;
    _pixels = pixels;
    if(sensibilityPeak > 0){_sensibilidadPico = sensibilityPeak;}
    if(decrementValue >= 0){_valorDecrementoEntrePicos = decrementValue;}
    if(delayEffect > 0){_delayEfecto = delayEffect;}
}

void ScrollingDotsEffect::run(float valPico){

    byte posMaxima = (_numPixel / 2) + 1;
    int delayCambioColor = 3000;


    if(millis() > _tiempoColorPuntosDesplazables + delayCambioColor){

        _tiempoColorPuntosDesplazables = millis();

        r_puntosDesplazables = random(0, 255);
        g_puntosDesplazables = random(0, 255);
        b_puntosDesplazables = random(0, 255);
    }


    if(millis() > _tiempoEfectoPuntosDesplazables + _delayEfecto){

        _tiempoEfectoPuntosDesplazables = millis();

        for(int i=0;i < _cantidadLedsDesplazables;i++)
        {
            if(_ledsDesplazables[i] > posMaxima){
                _ledsDesplazables[i] = 0;
                _pixels->setPixelColor(_ledsDesplazables[i], 0, 0, 0);
            }
            else if(_ledsDesplazables[i] > 0){
                _pixels->setPixelColor(_ledsDesplazables[i]-1, r_puntosDesplazables, g_puntosDesplazables, b_puntosDesplazables);
                _pixels->setPixelColor((_numPixel - _ledsDesplazables[i]), r_puntosDesplazables, g_puntosDesplazables, b_puntosDesplazables);
                _pixels->setPixelColor(_ledsDesplazables[i]-2, 0, 0, 0);
                _pixels->setPixelColor(((_numPixel + 1) - _ledsDesplazables[i]), 0, 0, 0);
                _ledsDesplazables[i] += 1;
            }
        }
        _pixels->show();
    }


    if (valPico < _sensibilidadPico){return;}


    if (valPico > _pico){

        _pico = valPico;
    
        for(int i=0;i < _cantidadLedsDesplazables;i++){
            if(_ledsDesplazables[i] == 0){
                _ledsDesplazables[i] = 1;
                break;
            }
        }
    }
    else {

        if (_pico > 1){
            _pico = _pico - _valorDecrementoEntrePicos;
        }
    }
}
