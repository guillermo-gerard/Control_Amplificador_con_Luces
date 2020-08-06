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
};



class WaveEffect : public IEffects{

    public:
        WaveEffect(Adafruit_NeoPixel *pixels, int quantityLeds, int sensibilityPeak, float decrementValue, int delayEffect);
        void run(float value) override;
        
    private:

        Adafruit_NeoPixel* _pixels;

        int _numPixel = 0;
        int _delayEfecto = 8;
        float _pico = 0;
        int _sensibilidadPico = 4;
        float _valorDecrementoEntrePicos = 0.15;
        bool _direccionEfecto = false;
};



class DotsDegradableEffect : public IEffects{

    public:
        DotsDegradableEffect(Adafruit_NeoPixel *pixels, int quantityLeds, int sensibilityPeak, float decrementValue, int delayEffect);
        void run(float value) override;
        
    private:

        Adafruit_NeoPixel* _pixels;

        int _numPixel = 0;
        int _delayEfecto = 8;
        float _pico = 0;
        int _sensibilidadPico = 4;
        float _valorDecrementoEntrePicos = 0.15;
        bool _direccionEfecto = false;

        unsigned long _tiempoColorPuntosDegradables = 0;
        unsigned long _tiempoEfectoPuntosDegradables = 0;

        byte r_efectoVoz;
        byte g_efectoVoz;
        byte b_efectoVoz;

        int _cantidadMaxLeds = 50;//Cantidad de Leds / 10
        byte _divLedsEfectoVoz[2][50];
};



class WormEffect : public IEffects{

    public:
        WormEffect(Adafruit_NeoPixel *pixels, int quantityLeds, int sensibilityPeak, float decrementValue, int delayEffect);
        void run(float value) override;
        
    private:

        Adafruit_NeoPixel* _pixels;

        int _numPixel = 0;
        int _delayEfecto = 8;
        float _pico = 0;
        int _sensibilidadPico = 4;
        float _valorDecrementoEntrePicos = 0.15;
        bool _direccionEfecto = false;

};



class RandomEffect : public IEffects{

    public:
        RandomEffect(Adafruit_NeoPixel *pixels, int quantityLeds, int sensibilityPeak, float decrementValue, int delayEffect);
        void run(float value) override;
        
    private:

        Adafruit_NeoPixel* _pixels;

        int _numPixel = 0;
        int _delayEfecto = 8;
        float _pico = 0;
        int _sensibilidadPico = 4;
        float _valorDecrementoEntrePicos = 0.15;
        bool _direccionEfecto = false;
};



class ReboundEffect : public IEffects{

    public:
        ReboundEffect(Adafruit_NeoPixel *pixels, int quantityLeds, int sensibilityPeak, float decrementValue, int delayEffect);
        void run(float value) override;
        
    private:

        Adafruit_NeoPixel* _pixels;

        int _numPixel = 0;
        int _delayEfecto = 8;
        float _pico = 0;
        int _sensibilidadPico = 4;
        float _valorDecrementoEntrePicos = 0.15;
        bool _direccionEfecto = false;

        byte r_EfectoRebote;
        byte g_EfectoRebote;
        byte b_EfectoRebote;
};



class ShockEffect : public IEffects{

    public:
        ShockEffect(Adafruit_NeoPixel *pixels, int quantityLeds, int sensibilityPeak, float decrementValue, int delayEffect);
        void run(float value) override;
        
    private:

        Adafruit_NeoPixel* _pixels;

        int _numPixel = 0;
        int _delayEfecto = 8;
        float _pico = 0;
        int _sensibilidadPico = 4;
        float _valorDecrementoEntrePicos = 0.15;
        bool _direccionEfecto = false;
};



class ScrollingDotsEffect : public IEffects{

    public:
        ScrollingDotsEffect(Adafruit_NeoPixel *pixels, int quantityLeds, int sensibilityPeak, float decrementValue, int delayEffect);
        void run(float value) override;
        
    private:

        Adafruit_NeoPixel* _pixels;

        int _numPixel = 0;
        int _delayEfecto = 8;
        float _pico = 0;
        int _sensibilidadPico = 4;
        float _valorDecrementoEntrePicos = 0.15;
        bool _direccionEfecto = false;
        
        unsigned long _tiempoColorPuntosDesplazables = 0; 
        unsigned long _tiempoEfectoPuntosDesplazables = 0;

        const int _cantidadLedsDesplazables = 250;//Cantidad de Leds / 2
        int _ledsDesplazables[250];

        byte r_puntosDesplazables;
        byte g_puntosDesplazables;
        byte b_puntosDesplazables;
};

#endif