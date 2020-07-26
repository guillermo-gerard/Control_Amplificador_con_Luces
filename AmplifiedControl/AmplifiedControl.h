#ifndef AmplifiedControl_h
#define AmplifiedControl_h

#include <Arduino.h>


class AmplifiedControl
{
    public:
        AmplifiedControl(byte pinMute, byte pinSensorTemp, byte pinFan);
        void setTemperatureRange(int tempLow, int tempHigh, int tempVeryHigh);
        void mute(bool value);
        float readTemperature();
        bool getStateTempVeryHigh();

    private:
        byte _pinMute;
        byte _pinFan;
        byte _pinSensorTemp;
        bool _muteState = false;
        bool _stateTempVeryHigh = false;
        int _tempLow;
        int _tempHigh;
        int _tempVeryHigh;
};

#endif