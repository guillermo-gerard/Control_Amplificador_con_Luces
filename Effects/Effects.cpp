#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "Effects.h"



// Contructor de la clase EffectFather
EffectFather::EffectFather(Adafruit_NeoPixel *pixels, int quantityLeds, float sensibilityPeak, float decrementValue){
    _pixels = pixels;
    if(quantityLeds > 0){_numPixel = quantityLeds;}
    if(sensibilityPeak > 0){_sensibilidadPico = sensibilityPeak;}
    if(decrementValue >= 0){_valorDecrementoEntrePicos = decrementValue;}
}

// Funcion de la clase EffectFather
void EffectFather::run(float value){
    
}





// Contructor de la clase TransitionEffect
TransitionEffect::TransitionEffect(int delayEffect) : EffectFather( // aca le tenes qeu mandar los argumentos al constructor padre, si no no sabe de donde sacarlos
                                                                    ){
    if(delayEffect > 0){_delayEfecto = delayEffect;}
}

// Implementacion de la funcion heredada de EffectFather
void TransitionEffect::run(float valPico){

    byte mitadLeds = _numPixel/2;
    byte limite = _numPixel-1;
    int i = _posicionLed;


    if((millis() - _tiempoEfectoTransicion) >= _delayEfecto && _iniciarSecuencia == true){

        if(_direccionEfecto == false){
    
            if(i < mitadLeds){_pixels->setPixelColor(i+1, 0, 0, 0);}
            _pixels->setPixelColor(i, _r, _g, _b);
            _pixels->setPixelColor((_numPixel-1)-i, _r, _g, _b);
            if(i < (mitadLeds-1)){_pixels->setPixelColor((_numPixel-2)-i, 0, 0, 0);}

            _pixels->show();

            if(_posicionLed == mitadLeds){
                _direccionEfecto = true;
                _iniciarSecuencia = false;
            }

            _posicionLed++;
        }
        else{

            if(i > 0){_pixels->setPixelColor(i-1, 0, 0, 0);}
            if(i < (_numPixel/2)){_pixels->setPixelColor(i, _r, _g, _b);}
            if(i < (_numPixel/2)){_pixels->setPixelColor((_numPixel-1)-i, _r, _g, _b);}
            if(i > 0){_pixels->setPixelColor(_numPixel-i, 0, 0, 0);}

            _pixels->show();

            if(_posicionLed == 0){
                _direccionEfecto = false;
                _iniciarSecuencia = false;
            }

            _posicionLed--;
        }

        _tiempoEfectoTransicion = millis();
    }

    if(valPico < _sensibilidadPico){return;}
 
    
    if(valPico > _pico && _iniciarSecuencia == false){
        _pico = valPico;

        _iniciarSecuencia = true;

        _r = random(0,255);
        _g = random(0,255);
        _b = random(0,255);
    }
    else {
    
        if(_pico > 1){
            _pico = _pico - _valorDecrementoEntrePicos;
        }
    }
}





/*



WaveEffect::WaveEffect(Adafruit_NeoPixel *pixels, int value, int sensibilityPeak, float decrementValue, int delayEffect){
    _pixels = pixels;
    if(value > 0){_numPixel = value;}
    if(sensibilityPeak > 0){_sensibilidadPico = sensibilityPeak;}
    if(decrementValue >= 0){_valorDecrementoEntrePicos = decrementValue;}
    if(delayEffect > 0){_delayEfecto = delayEffect;}
}

void WaveEffect::run(float valPico){

    int topeMaximoLeds = _numPixel + 6;
    int i = _posicionLed;


    if((millis() - _tiempoEfectoOlas) >= _delayEfecto && _iniciarSecuencia == true){

        if(_varAscendente < topeMaximoLeds){
            _pixels->setPixelColor(_varAscendente, _r, _g, _b);
            if(_varAscendente > _ledArranque){_pixels->setPixelColor(_varAscendente-1, round(_r/1.5), round(_g/1.5), round(_b/1.5));}
            if(_varAscendente > (_ledArranque+1)){_pixels->setPixelColor(_varAscendente-2, round(_r/2), round(_g/2), round(_b/2));}
            if(_varAscendente > (_ledArranque+2)){_pixels->setPixelColor(_varAscendente-3, round(_r/3), round(_g/3), round(_b/3));}
            if(_varAscendente > (_ledArranque+3)){_pixels->setPixelColor(_varAscendente-4, round(_r/6), round(_g/6), round(_b/6));}
            if(_varAscendente > (_ledArranque+4)){_pixels->setPixelColor(_varAscendente-5, round(_r/10), round(_g/10), round(_b/10));}
            if(_varAscendente > (_ledArranque+5)){_pixels->setPixelColor(_varAscendente-6, 0, 0, 0);}

            _varAscendente++;
        }
        else{
            _topeAscentente = true;
        }

        if(_varDescendente >= -6){
            _pixels->setPixelColor(_varDescendente, _r, _g, _b);
            if(_varDescendente < _ledArranque){_pixels->setPixelColor(_varDescendente+1, round(_r/1.5), round(_g/1.5), round(_b/1.5));}
            if(_varDescendente < (_ledArranque-1)){_pixels->setPixelColor(_varDescendente+2, round(_r/2), round(_g/2), round(_b/2));}
            if(_varDescendente < (_ledArranque-2)){_pixels->setPixelColor(_varDescendente+3, round(_r/3), round(_g/3), round(_b/3));}
            if(_varDescendente < (_ledArranque-3)){_pixels->setPixelColor(_varDescendente+4, round(_r/6), round(_g/6), round(_b/6));}
            if(_varDescendente < (_ledArranque-4)){_pixels->setPixelColor(_varDescendente+5, round(_r/10), round(_g/10), round(_b/10));}
            if(_varDescendente < (_ledArranque-5)){_pixels->setPixelColor(_varDescendente+6, 0, 0, 0);}
            _varDescendente--;
        }
        else{
            _topeDescentente = true;
        }

        if(_topeAscentente == true && _topeDescentente == true){
            _iniciarSecuencia = false;
            _posicionLed = 0;
            _topeAscentente = false;
            _topeDescentente = false;
            _varAscendente = 0;
            _varDescendente = 0;
        }
        
        _posicionLed++;
        _pixels->show();
        _tiempoEfectoOlas = millis();
    }


    if(valPico < _sensibilidadPico){return;}


    if (valPico > _pico && _iniciarSecuencia == false){

        _pico = valPico;
        _iniciarSecuencia = true;

        _ledArranque = random(3, (_numPixel - 3));
        _r = random(0,255);
        _g = random(0,255);
        _b = random(0,255);

        _varAscendente = _ledArranque;
        _varDescendente = _ledArranque;
    }
    else {

        if (_pico > 1){
            _pico = _pico - _valorDecrementoEntrePicos;
        }
    }


}








DotsDegradableEffect::DotsDegradableEffect(Adafruit_NeoPixel *pixels, int value, int sensibilityPeak, float decrementValue, int delayEffect){
    _pixels = pixels;
    if(value > 0){_numPixel = value;}
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
        
        _r = random(0,255);
        _g = random(0,255);
        _b = random(0,255);
        
        _tiempoEfectoPuntosDegradables = millis();
    }
    

    if(millis() > _tiempoColorPuntosDegradables + _delayEfecto){

        _tiempoColorPuntosDegradables = millis();

        for(int i=0;i < _cantidadMaxLeds;i++){

            if(_divLedsEfectoVoz[0][i] >= 20){
            
                _divLedsEfectoVoz[0][i] = 0;
                _divLedsEfectoVoz[1][i] = 0;
            }
            else if(_divLedsEfectoVoz[0][i] > 0){

                divisorTemporal = _divLedsEfectoVoz[0][i];
                posicionTemporal = _divLedsEfectoVoz[1][i];
                _pixels->setPixelColor(posicionTemporal, round(_r/divisorTemporal), round(_g/divisorTemporal), round(_b/divisorTemporal));
                _pixels->setPixelColor(posicionTemporal + 1, round(_r/divisorTemporal+2), round(_g/divisorTemporal+2), round(_b/divisorTemporal+2));
                _pixels->setPixelColor(posicionTemporal - 1, round(_r/divisorTemporal+2), round(_g/divisorTemporal+2), round(_b/divisorTemporal+2));
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
    _pixels = pixels;
    if(value > 0){_numPixel = value;}
    if(sensibilityPeak > 0){_sensibilidadPico = sensibilityPeak;}
    if(decrementValue >= 0){_valorDecrementoEntrePicos = decrementValue;}
    if(delayEffect > 0){_delayEfecto = delayEffect;}
}

void WormEffect::run(float valPico){

    int i = _posicionLed;

    if((millis() - _tiempoEfectoGusano) >= _delayEfecto && _iniciarSecuencia == true){

        if(_incrementando == true){

            _pixels->setPixelColor(_pixel, _r, _g, _b);

            if(i > 0){
                _pixels->setPixelColor(_pixel+1, round(_r/1.5), round(_g/1.5), round(_b/1.5));
                _pixels->setPixelColor(_pixel-1, round(_r/1.5), round(_g/1.5), round(_b/1.5));
            }
            
            if(i > 1){
                _pixels->setPixelColor(_pixel+2, round(_r/2), round(_g/2), round(_b/2));
                _pixels->setPixelColor(_pixel-2, round(_r/2), round(_g/2), round(_b/2));
            }
            
            if(i > 2){
                _pixels->setPixelColor(_pixel+3, round(_r/3), round(_g/3), round(_b/3));
                _pixels->setPixelColor(_pixel-3, round(_r/3), round(_g/3), round(_b/3));
            }
            
            if(i > 3){
                _pixels->setPixelColor(_pixel+4, round(_r/6), round(_g/6), round(_b/6));
                _pixels->setPixelColor(_pixel-4, round(_r/6), round(_g/6), round(_b/6));
            }
        }
        else{

            if(i <= 0){
                _pixels->setPixelColor(_pixel, 0, 0, 0);
            }

            if(i <= 1){
                _pixels->setPixelColor(_pixel+1, 0, 0, 0);
                _pixels->setPixelColor(_pixel-1, 0, 0, 0);
            }
            
            if(i <= 2){
                _pixels->setPixelColor(_pixel+2, 0, 0, 0);
                _pixels->setPixelColor(_pixel-2, 0, 0, 0);
            }
            
            if(i <= 3){
                _pixels->setPixelColor(_pixel+3, 0, 0, 0);
                _pixels->setPixelColor(_pixel-3, 0, 0, 0);
            }
            
            if(i <= 4){
                _pixels->setPixelColor(_pixel+4, 0, 0, 0);
                _pixels->setPixelColor(_pixel-4, 0, 0, 0);
            }
        }


        if(_incrementando == true){
            _posicionLed++;
        }
        else{
            _posicionLed--;
        }


        if(_posicionLed == 5 && _incrementando == true){
            _incrementando = false;
            _delayEfecto = _delayEfecto * 2;
        }
        else if(_posicionLed == -1 && _incrementando == false){
            _delayEfecto = _delayEfecto / 2;
            _iniciarSecuencia = false;
            _posicionLed = 0;
            _incrementando = true;
        }

        _pixels->show();
        _tiempoEfectoGusano = millis();
    }


    if(valPico < _sensibilidadPico){return;}


    if (valPico > _pico && _iniciarSecuencia == false){

        _pico = valPico;
        _iniciarSecuencia = true;

        _pixel = random(0, _numPixel);
        _r = random(0, 255);
        _g = random(0, 255);
        _b = random(0, 255);
    }
    else {

        if (_pico > 1){
            _pico = _pico - _valorDecrementoEntrePicos;
        }
    }
}









RandomEffect::RandomEffect(Adafruit_NeoPixel *pixels, int value, int sensibilityPeak, float decrementValue, int delayEffect){
    _pixels = pixels;
    if(value > 0){_numPixel = value;}
    if(sensibilityPeak > 0){_sensibilidadPico = sensibilityPeak;}
    if(decrementValue >= 0){_valorDecrementoEntrePicos = decrementValue;}
    if(delayEffect > 0){_delayEfecto = delayEffect;}
}

void RandomEffect::run(float valPico){
    
    int avanceMaximo = round(_numPixel/3);


    if((millis() - _tiempoEfectoRandom) >= _delayEfecto && _iniciarSecuencia == true){

        if(_i < _numPixel){_pixels->setPixelColor(_i,_r,_g,_b);}
        if(_a >= 0){_pixels->setPixelColor(_a,_r,_g,_b);}

        _pixels->show();

        _i++;
        _a--;

        if(_i >= _pixelElegido + _avance){
            _iniciarSecuencia = false;
        }

        _tiempoEfectoRandom = millis();
    }


    if(valPico < _sensibilidadPico){return;}

        
    if(valPico > _pico && _iniciarSecuencia == false){

        _pico = valPico;
        _iniciarSecuencia = true;

        _pixelElegido = random(0,_numPixel);
        _avance = random(4, avanceMaximo);
        _r = random(0,255);
        _g = random(0,255);
        _b = random(0,255);
        _i = _pixelElegido;
        _a = _pixelElegido;
    }
    else {
    
        if(_pico > 1){
            _pico = _pico - _valorDecrementoEntrePicos;
        }
    }
}








ReboundEffect::ReboundEffect(Adafruit_NeoPixel *pixels, int value, int sensibilityPeak, float decrementValue, int delayEffect){
    _pixels = pixels;
    if(value > 0){_numPixel = value;}
    if(sensibilityPeak > 0){_sensibilidadPico = sensibilityPeak;}
    if(decrementValue >= 0){_valorDecrementoEntrePicos = decrementValue;}
    if(delayEffect > 0){_delayEfecto = delayEffect;}
}

void ReboundEffect::run(float valPico){


    if(_iniciarSecuencia == true){

        _pixels->setPixelColor(_i+_p, _r, _g, _b);
        _pixels->setPixelColor(_a+_p, _r, _g, _b);
        if((_i != 4) && (_i > 0)){_pixels->setPixelColor((_i+_p)-1, 0, 0, 0);}
        if((_a != 3) && (_i > 0)){_pixels->setPixelColor((_a+_p)+1, 0, 0, 0);}

        if(_p < _numPixel){
            _p += 8;
        }
        else{
            _p = 0;
        }
    }

    if((millis() - _tiempoEfectoRebote) >= _delayEfecto && _iniciarSecuencia == true){

        _a--;_i++;

        if(_i == 3){
            _r = random(0, 255);
            _g = random(0, 255);
            _b = random(0, 255);
        }
        else if(_i == 8){
            _iniciarSecuencia = false;
            _i = 0;
            _a = 7;
            _p = 0;
        }

        _pixels->show();
        _tiempoEfectoRebote = millis();
    }


    if(valPico < _sensibilidadPico){return;}


    if (valPico > _pico && _iniciarSecuencia == false){

        _pico = valPico;
        _iniciarSecuencia = true;
    }
    else {

        if (_pico > 1){
            _pico = _pico - _valorDecrementoEntrePicos;
        }
    }
}









ShockEffect::ShockEffect(Adafruit_NeoPixel *pixels, int value, int sensibilityPeak, float decrementValue, int delayEffect){
    _pixels = pixels;
    if(value > 0){_numPixel = value;}
    if(sensibilityPeak > 0){_sensibilidadPico = sensibilityPeak;}
    if(decrementValue >= 0){_valorDecrementoEntrePicos = decrementValue;}
    if(delayEffect > 0){_delayEfecto = delayEffect;}
}

void ShockEffect::run(float valPico){

    int mitadTira = _numPixel/2;


    if((millis() - _tiempoEfectoChoque) >= _delayEfecto && _iniciarSecuencia == true){

        if(_incrementando == true){

            if(_i < mitadTira){

                _pixels->setPixelColor(_i, _r, _g, _b);
                _pixels->setPixelColor((_numPixel-1)-_i, _r, _g, _b);

                if(_i > 0){_pixels->setPixelColor(_i-1, _r, _g, _b); _pixels->setPixelColor(_numPixel-_i, _r, _g, _b);}
                if(_i > 1){_pixels->setPixelColor(_i-2, _r, _g, _b); _pixels->setPixelColor((_numPixel+1)-_i, _r, _g, _b);}
                if(_i > 2){_pixels->setPixelColor(_i-3, _r, _g, _b); _pixels->setPixelColor((_numPixel+2)-_i, _r, _g, _b);}
            }

            if(_i > 3){_pixels->setPixelColor(_i-4, 0, 0, 0); _pixels->setPixelColor((_numPixel+3)-_i, 0, 0, 0);}
            _i++;
        }
        else{

            if(_i > -1){_pixels->setPixelColor(_i, _r, _g, _b); _pixels->setPixelColor((_numPixel-1)-_i, _r, _g, _b);}
            if((_i > -2) && (_i < (mitadTira-2))){_pixels->setPixelColor(_i+1, _r, _g, _b); _pixels->setPixelColor((_numPixel-2)-_i, _r, _g, _b);}
            if((_i > -3) && (_i < (mitadTira-3))){_pixels->setPixelColor(_i+2, _r, _g, _b); _pixels->setPixelColor((_numPixel-3)-_i, _r, _g, _b);}
            if((_i > -4) && (_i < (mitadTira-4))){_pixels->setPixelColor(_i+3, _r, _g, _b); _pixels->setPixelColor((_numPixel-4)-_i, _r, _g, _b);}

            if((_i > -5) && (_i < (mitadTira-4))){_pixels->setPixelColor(_i+4, 0, 0, 0); _pixels->setPixelColor((_numPixel-5)-_i, 0, 0, 0);}
            _i--;
        }

        if(_i == (mitadTira - 3) && _incrementando == true){
            _delayEfecto = _delayEfecto * 4;
        }
        else if(_i == mitadTira - 3 && _incrementando == false){
            _delayEfecto = _delayEfecto / 4;
        }

        if(_i >= mitadTira + 2){
            _incrementando = false;
            _i = mitadTira - 2;
        }
        else if(_i <= -5 && _incrementando == false){
            _iniciarSecuencia = false;
            _i = 0; 
            _incrementando = true;
        }
        
        _pixels->show();
        _tiempoEfectoChoque = millis();
    }


    if(valPico < _sensibilidadPico){return;}


    if (valPico > _pico && _iniciarSecuencia == false){

        _pico = valPico;
        _iniciarSecuencia = true;
    
        _r = random(0, 255);
        _g = random(0, 255);
        _b = random(0, 255);
    }
    else {

        if (_pico > 1){
            _pico = _pico - _valorDecrementoEntrePicos;
        }
    }
}







ScrollingDotsEffect::ScrollingDotsEffect(Adafruit_NeoPixel *pixels, int value, int sensibilityPeak, float decrementValue, int delayEffect){
    _pixels = pixels;
    if(value > 0){_numPixel = value;}
    if(sensibilityPeak > 0){_sensibilidadPico = sensibilityPeak;}
    if(decrementValue >= 0){_valorDecrementoEntrePicos = decrementValue;}
    if(delayEffect > 0){_delayEfecto = delayEffect;}

    for(int i=0;i < _cantidadLedsDesplazables;i++){
        _ledsDesplazables[i] = 0;
    }
}

void ScrollingDotsEffect::run(float valPico){

    byte posMaxima = (_numPixel / 2) + 1;
    int delayCambioColor = 3000;


    if(millis() > _tiempoColorPuntosDesplazables + delayCambioColor){

        _tiempoColorPuntosDesplazables = millis();

        _r = random(0, 255);
        _g = random(0, 255);
        _b = random(0, 255);
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
                _pixels->setPixelColor(_ledsDesplazables[i]-1, _r, _g, _b);
                _pixels->setPixelColor((_numPixel - _ledsDesplazables[i]), _r, _g, _b);
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

*/
