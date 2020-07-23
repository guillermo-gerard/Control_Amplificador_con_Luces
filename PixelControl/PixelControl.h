#ifndef PixelControl_h
#define PixelControl_h

#include <Arduino.h>



class PixelControl {

    public:
        PixelControl(int quantityLeds, byte pinAudio, byte pinLeds);
        float updateStatus();
        void setEfectsDelay(int numberEfects, int delay);
        void setDetectionFrequency(int frequency, float sensibilityPeak);
        void detectionSilence(bool value);
        void pixelState(bool value);
        
    private:

        void actualizarEfecto(float valFinal);
        void deteccionDeSilencio(float valFinal);
        float lecturaAudio();
        void ledsApagados();
        void luzTemperaturaAlta();
        void efectoTransicion(float valFinal);


        byte _pinAudio;
        byte _pinLeds;

        //Deteccion de audio
        float _valorAudioAnterior;
        float _valorMute = 0.0;
        bool _estadoMute = false;
        bool _deteccionMute = false;
        float _pico;
        float _sensibilidadPico;
        int _frecuenciaDeteccion = 1650;

        //Leds, Efectos y Modos
        int _numPixel;
        int _estadoPixels = true;
        int _tiempoEntreEfectos = 30000;
        int _cantidadEfectos = 1;
        int _efecto = 1;

        //Variables de tiempo
        long _tiempoMute = 0;
        long _tiempoNoAudio = 0;
        long _tiempoEfectos = 0;

        long _tiempoEfectoPuntosDesplazables = 0;
        long _timepoColorPuntosDesplazables = 0;
        long _tiempoEfectoPuntosDegradables = 0;
        long _tiempoColorPuntosDegradables = 0;


        //Variables de Efectos
        bool _direccionEfecto = false; 

        const int _cantidadMaxLeds = 10;
        byte _divLedsEfectoVoz[2][10];
        byte r_efectoVoz;
        byte g_efectoVoz;
        byte b_efectoVoz;
};

#endif