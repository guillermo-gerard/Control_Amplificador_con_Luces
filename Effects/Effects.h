#ifndef Effects_h
#define Effects_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


class IEffects{

    public:
        virtual void run(float value) = 0;
};



class EffectFather : public IEffects{

    public:
        EffectFather();// Contructor necesario ???

    private:  

    protected:
        void run(float value) override;// Funcion heredada de IEffects

        //Variables comunes a todos los efectos
        Adafruit_NeoPixel* _pixels;

        int _numPixel = 0;
        int _delayEfecto = 0;
        float _pico = 0;
        int _sensibilidadPico = 2;
        float _valorDecrementoEntrePicos = 0.10;
        byte _numPixelExtendidos = 18;
        byte _ledsExtendidosPorGrupo = 6;

        byte _r;
        byte _g;
        byte _b;

};



class TransitionEffect : private EffectFather{

    public:
        TransitionEffect(Adafruit_NeoPixel *pixels, int quantityLeds, float sensibilityPeak, float decrementValue, int delayEffect);// Constructor
        void run(float value);// Implementacion de la clase EffectFather 
        
    private:

        //Variables del efecto
        bool _direccionEfecto = false;
        unsigned long _tiempoEfectoTransicion = 0;
        int _posicionLed = 0;
        bool _iniciarSecuencia = false;
};

/*

class WaveEffect : public IEffects{

    public:
        WaveEffect(Adafruit_NeoPixel *pixels, int quantityLeds, int sensibilityPeak, float decrementValue, int delayEffect);
        void run(float value) override;
        
    private:
        Adafruit_NeoPixel* _pixels;

        int _numPixel = 0;
        int _delayEfecto = 15;
        float _pico = 0;
        int _sensibilidadPico = 4;
        float _valorDecrementoEntrePicos = 0.15;

        //Variables del efecto
        unsigned long _tiempoEfectoOlas = 0;
        int _posicionLed = 0;
        int _ledArranque = 0;
        bool _iniciarSecuencia = false;
        bool _topeAscentente = false;
        bool _topeDescentente = false;
        int _varAscendente = 0;
        int _varDescendente = 0;
        byte _r;
        byte _g;
        byte _b;
};



class DotsDegradableEffect : public IEffects{

    public:
        DotsDegradableEffect(Adafruit_NeoPixel *pixels, int quantityLeds, int sensibilityPeak, float decrementValue, int delayEffect);
        void run(float value) override;
        
    private:
        Adafruit_NeoPixel* _pixels;

        int _numPixel = 0;
        int _delayEfecto = 40;
        float _pico = 0;
        int _sensibilidadPico = 4;
        float _valorDecrementoEntrePicos = 0.15;

        //Variables del efecto
        unsigned long _tiempoColorPuntosDegradables = 0;
        unsigned long _tiempoEfectoPuntosDegradables = 0;
        int _posicionLed = 0;
        bool _iniciarSecuencia = false;
        int _cantidadMaxLeds = 50;//Cantidad de Leds / 10
        byte _divLedsEfectoVoz[2][50];
        byte _r;
        byte _g;
        byte _b;
};



class WormEffect : public IEffects{

    public:
        WormEffect(Adafruit_NeoPixel *pixels, int quantityLeds, int sensibilityPeak, float decrementValue, int delayEffect);
        void run(float value) override;
        
    private:
        Adafruit_NeoPixel* _pixels;

        int _numPixel = 0;
        int _delayEfecto = 20;
        float _pico = 0;
        int _sensibilidadPico = 4;
        float _valorDecrementoEntrePicos = 0.15;

        //Variables del efecto
        unsigned long _tiempoEfectoGusano = 0;
        bool _iniciarSecuencia = false;
        int _posicionLed = 0;
        bool _incrementando = true;
        byte _pixel;
        byte _r;
        byte _g;
        byte _b;

};



class RandomEffect : public IEffects{

    public:
        RandomEffect(Adafruit_NeoPixel *pixels, int quantityLeds, int sensibilityPeak, float decrementValue, int delayEffect);
        void run(float value) override;
        
    private:
        Adafruit_NeoPixel* _pixels;

        int _numPixel = 0;
        int _delayEfecto = 5;
        float _pico = 0;
        int _sensibilidadPico = 4;
        float _valorDecrementoEntrePicos = 0.15;

        //Variables del efecto
        unsigned long _tiempoEfectoRandom = 0;
        bool _iniciarSecuencia = false;
        int _pixelElegido = 0;
        int _avance = 0;
        int _i;
        int _a;
        byte _r;
        byte _g;
        byte _b;
};



class ReboundEffect : public IEffects{

    public:
        ReboundEffect(Adafruit_NeoPixel *pixels, int quantityLeds, int sensibilityPeak, float decrementValue, int delayEffect);
        void run(float value) override;
        
    private:
        Adafruit_NeoPixel* _pixels;

        int _numPixel = 0;
        int _delayEfecto = 40;
        float _pico = 0;
        int _sensibilidadPico = 4;
        float _valorDecrementoEntrePicos = 0.15;

        //Variables del efecto
        unsigned long _tiempoEfectoRebote = 0;
        bool _iniciarSecuencia = false;
        int _p = 0;
        int _i = 0;
        int _a = 7;
        byte _r;
        byte _g;
        byte _b;
};



class ShockEffect : public IEffects{

    public:
        ShockEffect(Adafruit_NeoPixel *pixels, int quantityLeds, int sensibilityPeak, float decrementValue, int delayEffect);
        void run(float value) override;
        
    private:
        Adafruit_NeoPixel* _pixels;

        int _numPixel = 0;
        int _delayEfecto = 5;
        float _pico = 0;
        int _sensibilidadPico = 4;
        float _valorDecrementoEntrePicos = 0.15;

        //Variables del efecto
        unsigned long _tiempoEfectoChoque = 0;
        bool _iniciarSecuencia = false;
        bool _incrementando = true;
        int _i = 0;
        byte _r;
        byte _g;
        byte _b;
};



class ScrollingDotsEffect : public IEffects{

    public:
        ScrollingDotsEffect(Adafruit_NeoPixel *pixels, int quantityLeds, int sensibilityPeak, float decrementValue, int delayEffect);
        void run(float value) override;
        
    private:
        Adafruit_NeoPixel* _pixels;

        int _numPixel = 0;
        int _delayEfecto = 35;
        float _pico = 0;
        int _sensibilidadPico = 4;
        float _valorDecrementoEntrePicos = 0.15;
        
        //Variables del efecto
        unsigned long _tiempoColorPuntosDesplazables = 0; 
        unsigned long _tiempoEfectoPuntosDesplazables = 0;
        const int _cantidadLedsDesplazables = 250;//Cantidad de Leds / 2
        int _ledsDesplazables[250];
        byte _r;
        byte _g;
        byte _b;
};

*/

#endif