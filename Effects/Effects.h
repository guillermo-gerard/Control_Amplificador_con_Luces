#ifndef Effects_h
#define Effects_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


class IEffects{

    public:
        virtual void run(float value) = 0;

    private:
};



class TransitionEffect : public IEffects{

    public:
        TransitionEffect(Adafruit_NeoPixel *pixels, int quantityLeds, int sensibilityPeak, float decrementValue, int delayEffect);
        void run(float value) override;
        
    private:
        Adafruit_NeoPixel* _pixels;

        int _numPixel = 0;
        int _delayEfecto = 8;
        float _pico = 0;
        int _sensibilidadPico = 4;
        float _valorDecrementoEntrePicos = 0.15;
        bool _direccionEfecto = false;

        //Variables del efecto
        unsigned long _tiempoEfectoTransicion = 0;
        int _posicionLed = 0;
        bool _iniciarSecuencia = false;
        byte _r;
        byte _g;
        byte _b;
};



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
        bool _direccionEfecto = false;

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
        bool _direccionEfecto = false;

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
        bool _direccionEfecto = false;

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
        bool _direccionEfecto = false;

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
        bool _direccionEfecto = false;

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
        bool _direccionEfecto = false;

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
        bool _direccionEfecto = false;
        
        //Variables del efecto
        unsigned long _tiempoColorPuntosDesplazables = 0; 
        unsigned long _tiempoEfectoPuntosDesplazables = 0;
        const int _cantidadLedsDesplazables = 250;//Cantidad de Leds / 2
        int _ledsDesplazables[250];
        byte _r;
        byte _g;
        byte _b;
};

#endif