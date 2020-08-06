#ifndef PixelControl_h
#define PixelControl_h

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


class PixelControl{

    public:
        PixelControl(Adafruit_NeoPixel *pixels, int quantityLeds, byte pinAudio);/// Aca se pasa el objeto al constructor
        float readAudio();
        void setDetectionFrequency(int frequency, float sensibilityPeak, int maxValuePeak);
        void setDetectionSilence(bool value, int readingFrequency, int ruinValue);
        void setSpecificColor(byte r, byte g, byte b, int delayValue);
        bool getStateMute();
        
    private:

        //Adafruit_NeoPixel *pixels; Antigua declaracion del objeto pixels
        
        //Funciones internas
        void deteccionDeSilencio(float valFinal);
        float getAudio();

        //Pines
        byte _pinAudio;

        //Deteccion de audio
        float _valorAudioAnterior;
        float _valorMute = 0.0;
        bool _estadoMute = false;
        bool _deteccionMute = true;
        float _pico;
        int _valorMaximoPico = 30;
        float _sensibilidadPico = 3;
        int _frecuenciaDeteccion = 1650;
        int _frecuenciaDeteccionSilencio = 10000;
        int _valorDeRuido = 10;

        //Leds y Efectos
        int _numPixel;

        //Variables de tiempo
        unsigned long _tiempoMute = 0;
        unsigned long _tiempoNoAudio = 0;
        unsigned long _timpoDeteccionAudio = 0;

};

#endif