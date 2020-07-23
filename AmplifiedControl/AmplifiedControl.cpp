#include <Arduino.h>
#include "AmplifiedControl.h"


AmplifiedControl::AmplifiedControl(byte pinMute, byte pinSensorTemp, byte pinFan){

    _pinMute = pinMute;
    _pinSensorTemp = pinSensorTemp;
    _pinFan = pinFan;

    pinMode(_pinMute, OUTPUT);
    pinMode(_pinFan, OUTPUT);
    pinMode(_pinSensorTemp, INPUT);

    digitalWrite(_pinFan, LOW);
    digitalWrite(_pinMute, LOW);
}


void AmplifiedControl::setTemperatureRange(int tempLow, int tempHigh, int tempVeryHigh){
    _tempLow = tempLow;
    _tempHigh = tempHigh;
    _tempVeryHigh = tempVeryHigh;
}


void AmplifiedControl::mute(bool value){

    if(_muteState == false && value == true){
        digitalWrite(_pinMute, HIGH);
        _muteState = true;
    }
    else if(_muteState == true && value == false && _stateTempVeryHigh == false){
        digitalWrite(_pinMute, LOW);
        _muteState = false;
    }
}


float AmplifiedControl::readTemperature(){

    float reading;
    float temp;

    for(int i=0;i < 2;i++){
        reading = analogRead(_pinSensorTemp);
        temp = temp + reading;
    }
    
    temp = temp / 2;
    temp = (reading * 5 * 100) / 1024;
    
    if(temp > _tempVeryHigh) {
        _stateTempVeryHigh = true;
        _muteState = true; 
        digitalWrite(_pinMute, HIGH);
        digitalWrite(_pinFan, HIGH); 
    }
    else if(temp > _tempHigh) { 
        _stateTempVeryHigh = false;
        digitalWrite(_pinFan, HIGH);
    }
    else if(temp < _tempLow) { 
        _stateTempVeryHigh = false;
        digitalWrite(_pinFan, LOW);
    }
    
    return temp;
}