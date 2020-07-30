/* En este ejemplo basico se controla la temperatura, un ventilador y el pin de mute de un Amplificador
*  En el ejemplo no se usa DELAY, ya que este entorpece la lectura de audio
*
*  Pines utilizados:
*  2(out) -> Pin ventilador
*  3(out) -> Pin mute
*  A0(in) -> Pin de lectuta de temperatura (LM35)
*/

#include "AmplifiedControl.h"
#include <Arduino.h>

byte pinMute = 3;
byte pinVentilador = 2;
byte pinSensorTemp = A0;

AmplifiedControl ampli(pinMute, pinSensorTemp, pinVentilador);

long tiempoAnteriorTemperatura = 0;//Variable donde guardamos el valor de millis para compararlo
int delayLecturaTemperatura = 1000;//Cada 1 segundo

void setup() {

    Serial.begin(115200);
    ampli.setTemperatureRange(35, 45, 80);//Temp minima 35°, temp alta 45°, temp muy alta 80° 
    ampli.mute(false);//El mute esta apagado
}


void loop(){

    if(millis() > tiempoAnteriorTemperatura + delayLecturaTemperatura)
    {
        Serial.println(ampli.readTemperature());//Actualizo el estado de la temperatura

        //Si la temperatura es extremadamente alta entra al IF
        if(ampli.getStateTempVeryHigh() == true){
            ampli.mute(true);//Habilito el mute del amplificador
        }
        else{
            ampli.mute(false);//Deshabilito el mute del amplificador
        }
        
        tiempoAnteriorTemperatura = millis();//Vuelvo a 0 la diferencia de timepo
    }
}