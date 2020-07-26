#ifndef PixelControl_h
#define PixelControl_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


class PixelControl {

    public:
        PixelControl(int quantityLeds, byte pinLeds, byte brightness, byte pinAudio);
        float updateStatus();
        void setEfectsDelay(int numberEfects, int delay);
        void setDetectionFrequency(int frequency, float sensibilityPeak, float maxValuePeak);
        void setDetectionSilence(bool value, int readingFrequency, int ruinValue);
        void setStateEfects(bool value);
        void setSpecificColor(byte r, byte g, byte b, int delayValue);
        bool getStateMute();
        
    private:

        Adafruit_NeoPixel *pixels;// Declaracion del objeto pixels
        
        //Funciones internas
        void actualizarEfecto(float valFinal);
        void deteccionDeSilencio(float valFinal);
        float lecturaAudio();

        //Funciones de efectos
        void efectoTransicion(float valFinal);
        void efectoOlas(float valFinal);
        void efectoPuntosDegradables(float valFinal);
        void efectoAvanico(float valFinal);
        void efectoRandom(float valFinal);
        void efectoRebote(float valFinal);
        void efectoChoque(float valFinal);
        void efectoPuntosDesplazables(float valFinal);

        //Pines
        byte _pinAudio;
        byte _pinLeds;

        //Deteccion de audio
        float _valorAudioAnterior;
        float _valorMute = 0.0;
        bool _estadoMute = false;
        bool _deteccionMute = true;
        float _pico;
        float _valorMaximoPico = 30;
        float _sensibilidadPico = 3;
        int _frecuenciaDeteccion = 1650;
        int _frecuenciaDeteccionSilencio = 10000;
        int _valorDeRuido = 10;

        //Leds y Efectos
        int _numPixel;
        int _estadoPixels = true;
        int _tiempoEntreEfectos = 20000;
        int _cantidadEfectos = 8;
        int _efecto = 1;
        float _valorDecrementoEntrePicos = 0.15;

        //Variables de tiempo
        long _tiempoMute = 0;
        long _tiempoNoAudio = 0;
        long _tiempoEfectos = 0;

        long _tiempoEfectoPuntosDesplazables = 0;
        long _tiempoColorPuntosDesplazables = 0;
        long _tiempoEfectoPuntosDegradables = 0;
        long _tiempoColorPuntosDegradables = 0;

        //Variables de Efectos
        bool _direccionEfecto = false;
        int _posicionNoAudio = 0;
        byte r_noAudio;
        byte g_noAudio;
        byte b_noAudio;

        byte r_EfectoRebote = 20;
        byte g_EfectoRebote = 255;
        byte b_EfectoRebote = 40;

        const int _cantidadLedsDesplazables = 250;//CantaLeds / 2
        byte _ledsDesplazables[400];
        byte r_puntosDesplazables;
        byte g_puntosDesplazables;
        byte b_puntosDesplazables; 

        const int _cantidadMaxLeds = 50;//CantLeds / 10
        byte _divLedsEfectoVoz[2][50];
        byte r_efectoVoz;
        byte g_efectoVoz;
        byte b_efectoVoz;
};

#endif