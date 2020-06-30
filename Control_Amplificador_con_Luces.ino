#include <Adafruit_NeoPixel.h>

byte numPixel = 40;

//------- Pines de Control -------//
int pinAudio = A0;
int pinTemperatura = A2;
byte pinCooler = 9;
byte pinPausa = 5;
byte pinLuz = 3;
byte botonLed = 4;

Adafruit_NeoPixel pixels(numPixel, pinLuz, NEO_GRB + NEO_KHZ800);

//------- Variables de control de tiempo -------//
long tiempoAnteriorTemperatura = 0;
long tiempoAnteriorEstadoLeds = 0; 
long tiempoAnteriorPausa = 0;
long tiempoAnteriorNoAudio = 0;
long tiempoAnteriorEfectoLuz = 0;

long tiempoAnteriorPuntosDesplazables = 0;
long tiempoColorPuntosDesplazables = 0;
long tiempoEfectoPuntosDegradables = 0;
long tiempoColorPuntosDegradables = 0;


//------- Variables de temperatura -------//
bool temperaturaAlta = false;


//------- Variables de deteccion de audio -------//
float valMicroAnterior;
float valPausa;
bool mute = false;
bool detectarSilencio = true;
float pico;//Utilizado para todos los efectos


//------- Variables de control de Modos -------//
bool estadoBotonModo = false;
bool ledsOn = false;
byte modoParlante = 0;// MODO 1 = con deteccion de audio y luces, MODO 2 = sin deteccion de audio y con luces
byte ultimaTiraEncendida = 0;


//------- Variables de efectos de luces -------//
long tiempoEntreEfectos = 30000;// 30 segundos
byte efecto = 1;
byte cantidadEfectos = 9;// Cantidad de efectos 
byte sensibilidadPico = 4; // Entre 2-6
bool direccionEfecto = false;
byte ultimoColor = 0; 
byte posicionAnterior = 0;
int tira[10];
int posicionNoAudio = 0;
int delayNoAudio = 50;
byte pixelBorrado;


//-------- Variables de color globales --------//
byte r_noAudio;
byte g_noAudio;
byte b_noAudio;

byte r_EfectoRebote = 20;
byte g_EfectoRebote = 255;
byte b_EfectoRebote = 40;

byte ledsDesplazables[10];
byte r_puntosDesplazables;
byte g_puntosDesplazables;
byte b_puntosDesplazables;

byte divLedsEfectoVoz[2][10];// bidimencional [1-2] [divisor/posicion]
byte divisorMinimoBrillo = 30;
float valorDeIncremento = 2;//1
byte cantidadMaxLeds = 10;
byte r_efectoVoz;
byte g_efectoVoz;
byte b_efectoVoz;






void setup() {

//Serial.begin(115200);

pixels.begin();
pixels.clear();

pinMode(pinAudio, INPUT);
pinMode(pinTemperatura, INPUT);
pinMode(pinCooler, OUTPUT);
pinMode(pinPausa, OUTPUT);
pinMode(pinLuz, OUTPUT);
pinMode(botonLed, INPUT);

digitalWrite(pinPausa, LOW);

for(int i=0;i < cantidadMaxLeds;i++){
  divLedsEfectoVoz[0][i] = divisorMinimoBrillo;
  divLedsEfectoVoz[1][i] = 0;
}

inicioLuz();
}





void loop() {

  if(millis() > tiempoAnteriorTemperatura + 5000)
  {
    lecturaTemperatura();
    tiempoAnteriorTemperatura = millis();
  }

  if(millis() > tiempoAnteriorEstadoLeds + 1000 && temperaturaAlta == false){
    controlBotonModo();
  }

  if(temperaturaAlta == false){
    lecturaAudio();
  }

  if(mute == true && ledsOn == true && temperaturaAlta == false)
  {
    noAudio();
  }

//delay(1);
}







void controlBotonModo(){

  if(digitalRead(botonLed) != estadoBotonModo){

    if(digitalRead(botonLed) == true) {
      modoParlante++;
      estadoBotonModo = true;

      if(modoParlante > 2){
        modoParlante = 1;
      }

      if(modoParlante == 2){
        ledsOn = true;
        mute = false;
        detectarSilencio = false;
        digitalWrite(pinPausa, LOW);
        mostrarModo(2);
      }
      else{
        ledsOn = true;
        detectarSilencio = true;
        mostrarModo(1);
      }
    }
    else {
      estadoBotonModo = false;
      ledsOn = false;
      ledsApagados();
    }

  }
}








void inicioLuz()
{
  byte topeLeds = numPixel/2;
  float r = 220;
  float g = 0;
  float b = 0;
  
  
  // Leds 0-5
  for(int i=0;i < 6;i++){
      
    for(int a=0;a < topeLeds;a++){
      pixels.setPixelColor(a, r, g, b);
      pixels.setPixelColor(a-1, 0, 0, 0);

      pixels.setPixelColor(39-a, r, g, b);
      pixels.setPixelColor(40-a, 0, 0, 0);
      pixels.show();
      delay(15);
    }
    
    if(i < 4)
    {
      r = r-36.66;
      g = g+36.66;
    }
    else{
      r = 0;
      g = 220;
    }

    topeLeds--;
  }


  //Leds 6-12
  for(int i=6;i < 13;i++){

    for(int a=0;a < topeLeds;a++){
      pixels.setPixelColor(a, r, g, b);
      pixels.setPixelColor(a-1, 0, 0, 0);

      pixels.setPixelColor(39-a, r, g, b);
      pixels.setPixelColor(40-a, 0, 0, 0);
      pixels.show();
      delay(20);
    }
    
    if(i < 11)
    {
      g = g-31.42;
      b = b+31.42;
    }
    else{
      g = 0;
      b = 220;
    }

    topeLeds--;
  }


  //Leds 13-19
  for(int i=13;i < 20;i++){
      

    for(int a=0;a < topeLeds;a++){
      pixels.setPixelColor(a, r, g, b);
      pixels.setPixelColor(a-1, 0, 0, 0);

      pixels.setPixelColor(39-a, r, g, b);
      pixels.setPixelColor(40-a, 0, 0, 0);
      pixels.show();
      delay(40);
    }
    
    b = b-31.42;
    r = r+31.42;

    topeLeds--;
  }

    
  delay(2000);


  for(int i=19;i >= 0;i--){

    pixels.setPixelColor(i, 0, 0, 0);
    pixels.setPixelColor(39-i, 0, 0, 0);
    pixels.show();
    delay(25);
  }

}









void lecturaTemperatura()
{
  float lectura;
  float temp;

  for(int i=0;i < 3;i++)
  {
   lectura = analogRead(pinTemperatura);
   temp = temp + lectura;
  }
  
  temp = temp / 3;
  temp = (lectura * 5 * 100) / 1024;
  
  if(temp > 80.0) {
    temperaturaAlta = true;
    mute = true;
    ledsOn = false; 
    detectarSilencio = false;
    luzTemperaturaAlta();
    digitalWrite(pinPausa, HIGH);
    digitalWrite(pinCooler, HIGH); 
  }
  else if(temp > 45.0) {
    temperaturaAlta = false;
    digitalWrite(pinCooler, HIGH);
   }
  else if(temp < 40.0) {
    digitalWrite(pinCooler, LOW);
   }
    
}






void lecturaAudio()
{
  float val;
  float valFinal;
  
  //------- Lectura de audio -------//
  delayMicroseconds(2500);// 900 para 1KHz, 1250 para 800hz, 1650 para 600Hz, 2500 para 400hz, 3750 para 266hz, 5000 para 200hz, 10000 para 100hz 
  val = analogRead(pinAudio);


  if(val - valMicroAnterior < 0)
  {
    valFinal = 1;
    valMicroAnterior = val;
  }
  else
  {
    valFinal = val - valMicroAnterior;
    valMicroAnterior = val;
  }


  if(ledsOn == true){
    actualizarEfecto(valFinal);// Actualizamos el efecto de los leds
  }

  if(detectarSilencio == true){
    deteccionDeSilencio(valFinal);
  }
    
}







void actualizarEfecto(float valFinal){

  if((millis() > tiempoAnteriorEfectoLuz + tiempoEntreEfectos) && (mute == false) && (ledsOn == true)) 
  { 

    tiempoAnteriorEfectoLuz = millis();
    efecto++;
    pico = 0;
    ledsApagados();
    transicion();
    
    if(efecto > cantidadEfectos)
    {
      efecto = 1;
    }
  }

    
  if((ledsOn == true) && (mute == false))
  {
   
    switch(efecto){

      case 1:
        efectoTransicion(valFinal);
        break;
      case 2:
        efectoOlas(valFinal);
        break;
      case 3:
        efectoPuntosDegradables(valFinal);
        break;
      case 4:
        efectoAvanico(valFinal);
        break;
      case 5:
        efectoTren(valFinal);
        break;
      case 6:
        efectoRebote(valFinal);
        break;
      case 7:
        efectoChoque(valFinal);
        break;
      case 8:
        efectoPuntosDesplazables(valFinal);
        break;
      case 9:
        efectoVumetro(valFinal);
        break;

      default: 
        efecto = 1;
        break;
    }

  }
}






void deteccionDeSilencio(float valFinal){

  if(valFinal >= 1.0)
  {
    valPausa = valPausa + valFinal;

    if(mute == true){
      digitalWrite(pinPausa, LOW); 
      ledsApagados();
      mute = false;
    }
  }



  if(millis() > tiempoAnteriorPausa + 10000){

    if((valPausa <= 10.00) && (mute == false)){
      digitalWrite(pinPausa, HIGH);
      mute = true;
      ledsApagados();
    }

    valPausa = 0.00;
    tiempoAnteriorPausa = millis();
  }
}







void transicion()
{
  int velocidad = 35;//35

  
  for(int i=0;i < (numPixel+32);i++)
  {
     pixels.setPixelColor(i, 255, 0, 0);
     pixels.setPixelColor((i-1), 220, 0, 0);
     pixels.setPixelColor((i-2), 180, 0, 0);  
     pixels.setPixelColor((i-3), 140, 0, 0);
     pixels.setPixelColor((i-4), 100, 0, 0);  //Rojo
     pixels.setPixelColor((i-5), 60, 0, 0);
     pixels.setPixelColor((i-6), 20, 0, 0);  
     pixels.setPixelColor((i-7), 5, 0, 0);

     pixels.setPixelColor((i-8), 0, 0, 0);
     pixels.setPixelColor((i-9), 0, 0, 0);
     pixels.setPixelColor((i-10), 0, 0, 0);
     pixels.setPixelColor((i-11), 0, 0, 0);

     pixels.setPixelColor((i-12), 0, 255, 0);
     pixels.setPixelColor((i-13), 0, 220, 0);
     pixels.setPixelColor((i-14), 0, 180, 0); 
     pixels.setPixelColor((i-15), 0, 140, 0); //Verde
     pixels.setPixelColor((i-16), 0, 100, 0);
     pixels.setPixelColor((i-17), 0, 60, 0);
     pixels.setPixelColor((i-18), 0, 20, 0);  
     pixels.setPixelColor((i-19), 0, 5, 0);

     pixels.setPixelColor((i-20), 0, 0, 0);
     pixels.setPixelColor((i-21), 0, 0, 0);
     pixels.setPixelColor((i-22), 0, 0, 0);
     pixels.setPixelColor((i-23), 0, 0, 0);

     pixels.setPixelColor((i-24), 0, 0, 255);
     pixels.setPixelColor((i-25), 0, 0, 220);
     pixels.setPixelColor((i-26), 0, 0, 180); 
     pixels.setPixelColor((i-27), 0, 0, 140); //Azul
     pixels.setPixelColor((i-28), 0, 0, 100);
     pixels.setPixelColor((i-29), 0, 0, 60);
     pixels.setPixelColor((i-30), 0, 0, 20);
     pixels.setPixelColor((i-31), 0, 0, 5);

     pixels.setPixelColor((i-32), 0, 0, 0);
     
     pixels.show();
     delay(velocidad);
    }

}









void efectoTransicion(float valPico)
{
 byte r = 0;
 byte g = 0;
 byte b = 0;
 int espera = 10;//15
 byte mitadLeds = numPixel/2;
 byte limite = numPixel-1;



 if(valPico > 30)
  {
    valPico = sensibilidadPico;
  }

 if(valPico < sensibilidadPico)
 {
  return;
  }
 
    
  if(valPico > pico)
  {
    pico = valPico;

    randomSeed(millis());
    r = random(5,255);
    g = random(5,255);
    b = random(5,255);


  if(direccionEfecto == false)
  {
    for(int i=0;i < mitadLeds;i++)
    {
      if(i < mitadLeds){pixels.setPixelColor(i+1, 0, 0, 0);}
      pixels.setPixelColor(i, r, g, b);
      pixels.setPixelColor(39-i, r, g, b);
      if(i < (mitadLeds-1)){pixels.setPixelColor(38-i, 0, 0, 0);}

      pixels.show();
      delay(espera);

      if(i > mitadLeds - 8){
        espera = espera + 8;
      }
     }
     direccionEfecto = true;
     //espera = 10;
  }
  else
  {
    for(int i=mitadLeds;i >= 0;i--)
    {
      if(i > 0){pixels.setPixelColor(i-1, 0, 0, 0);}
      if(i < 20){pixels.setPixelColor(i, r, g, b);}
      if(i < 20){pixels.setPixelColor(39-i, r, g, b);}
      if(i > 0){pixels.setPixelColor(40-i, 0, 0, 0);}

      pixels.show();
      delay(espera);

      if(i < mitadLeds - 12){
        espera = espera + 8;
      }
     }
     direccionEfecto = false;
     //espera = 10;
   }
   
  }
  else {
   
   if(pico > 5)
    {
      pico = pico - 0.15;//15
    }
   }

 
}







void efectoTren(float valPico)
{
 int velocidad = 6;//8
 byte colorTira = 0;
 byte posicionTira = 0;
 byte segmentos = numPixel/4;
 int tiraTemporal[segmentos];



 if(valPico > 30)
  {
    valPico = sensibilidadPico;
  }

 if(valPico < sensibilidadPico)
 {
  return;
  }
 
    
  if(valPico > pico)
  {
    pico = valPico;

    randomSeed(millis());
    tira[0] = random(1,7);


    for(int i=0;i < segmentos;i++)
    {
       colorTira = tira[i];
       
       if(colorTira == 1)
       {
        for(int r=posicionTira;r < (posicionTira + 4);r++)  //Rojo
        {
          pixels.setPixelColor(r, 255, 0, 0);
          pixels.show();
          delay(velocidad);
        }
       }
       else if(colorTira == 2)
       {
        for(int g=posicionTira;g < (posicionTira + 4);g++)  //Verde
        {
          pixels.setPixelColor(g, 0, 255, 0);
          pixels.show();
          delay(velocidad);
        }
       }
       else if(colorTira == 3)
       {
        for(int b=posicionTira;b < (posicionTira + 4);b++)  //Azul
        {
          pixels.setPixelColor(b, 0, 0, 255);
          pixels.show();
          delay(velocidad);
        }
       }
       else if(colorTira == 4)
       {
        for(int b=posicionTira;b < (posicionTira + 4);b++)  //Rosado
        {
          pixels.setPixelColor(b, 255, 0, 255);
          pixels.show();
          delay(velocidad);
        }
       }
       else if(colorTira == 5)
       {
        for(int b=posicionTira;b < (posicionTira + 4);b++)  //Amarillo
        {
          pixels.setPixelColor(b, 255, 255, 0);
          pixels.show();
          delay(velocidad);
        }
       }
       else if(colorTira == 6)
       {
        for(int b=posicionTira;b < (posicionTira + 4);b++)  //Celeste
        {
          pixels.setPixelColor(b, 0, 255, 255);
          pixels.show();
          delay(velocidad);
        }
       }

       posicionTira = posicionTira + 4;
    }





    for(int i=0;i < (segmentos-1);i++)
       {
        tiraTemporal[i+1] = tira[i];
        }
       tiraTemporal[0] = tira[segmentos];

    for(int i=0;i < segmentos;i++)
    {
      tira[i] = tiraTemporal[i];
     }

  }
  else {
   
   if(pico > 5)
    {
      pico = pico - 0.15;//15
    }
   }
}







void efectoAvanico(float valPico)
{
  byte pixel;
  byte r;
  byte g;
  byte b;


  if (valPico > 30)
  {
      valPico = sensibilidadPico;
  }


  if (valPico < sensibilidadPico)
  {
      return;
  }


  if (valPico > pico)
  {
    pico = valPico;



    randomSeed(millis());
    pixel = random(0, numPixel);
    r = random(5, 255);
    g = random(5, 255);
    b = random(5, 255);



    for(int i=0;i < 5;i++){

      pixels.setPixelColor(pixel, r, g, b);

      if(i > 0){
        pixels.setPixelColor(pixel+1, round(r/1.5), round(g/1.5), round(b/1.5));
        pixels.setPixelColor(pixel-1, round(r/1.5), round(g/1.5), round(b/1.5));
      }
      
      if(i > 1){
        pixels.setPixelColor(pixel+2, round(r/2), round(g/2), round(b/2));
        pixels.setPixelColor(pixel-2, round(r/2), round(g/2), round(b/2));
      }
      
      if(i > 2){
        pixels.setPixelColor(pixel+3, round(r/3), round(g/3), round(b/3));
        pixels.setPixelColor(pixel-3, round(r/3), round(g/3), round(b/3));
      }
      
      if(i > 3){
        pixels.setPixelColor(pixel+4, round(r/6), round(g/6), round(b/6));
        pixels.setPixelColor(pixel-4, round(r/6), round(g/6), round(b/6));
      }

      pixels.show();
      delay(25);
    }


    for(int i=4;i >= 0;i--){

      if(i <= 0){
        pixels.setPixelColor(pixel, 0, 0, 0);
      }

      if(i <= 1){
        pixels.setPixelColor(pixel+1, 0, 0, 0);
        pixels.setPixelColor(pixel-1, 0, 0, 0);
      }
      
      if(i <= 2){
        pixels.setPixelColor(pixel+2, 0, 0, 0);
        pixels.setPixelColor(pixel-2, 0, 0, 0);
      }
      
      if(i <= 3){
        pixels.setPixelColor(pixel+3, 0, 0, 0);
        pixels.setPixelColor(pixel-3, 0, 0, 0);
      }
      
      if(i <= 4){
        pixels.setPixelColor(pixel+4, 0, 0, 0);
        pixels.setPixelColor(pixel-4, 0, 0, 0);
      }

      delay(45);
      pixels.show();
    }

  


  }
  else {

    if (pico > 5)
    {
      pico = pico - 0.20;//20

    }
  }

}







void efectoVumetro(float valPico){
    

    if (valPico > 30)
    {
        valPico = sensibilidadPico;
    }


    if (valPico < sensibilidadPico)
    {
        return;
    }


    if (valPico > pico)
    {
        pico = valPico;


        for(int i=0;i < 12;i++){

            if(i < 4){
               
              if(i < 8){
                pixels.setPixelColor(i, 0, 255, 0);
                pixels.setPixelColor(39-i, 0, 255, 0);
              }
              pixels.setPixelColor(i+20, 0, 255, 0);
              pixels.setPixelColor(19-i, 0, 255, 0);
            }
            else if((i >= 4) && (i < 6)){

              if(i < 8){
                pixels.setPixelColor(i, 255, 200, 0);
                pixels.setPixelColor(39-i, 255, 200, 0);
              }
              pixels.setPixelColor(i+20, 255, 200, 0);
              pixels.setPixelColor(19-i, 255, 200, 0);
            }
            else if((i >= 6) && (i < 10)){

              if(i < 8){
                pixels.setPixelColor(i, 255, 0, 0);
                pixels.setPixelColor(39-i, 255, 0, 0);
              }
              pixels.setPixelColor(i+20, 255, 0, 0);
              pixels.setPixelColor(19-i, 255, 0, 0);
            }
            else{
              pixels.setPixelColor(i+20, 0, 0, 255);
              pixels.setPixelColor(19-i, 0, 0, 255);
            }

            pixels.show();
            delay(5);//8
        }


        delay(60);//60


        for(int i=13;i >= 0;i--){
            
            if(i < 8){
            pixels.setPixelColor(i, 0, 0, 0);
            pixels.setPixelColor(39-i, 0, 0, 0);
            }

            pixels.setPixelColor(i+19, 0, 0, 0);
            pixels.setPixelColor(20-i, 0, 0, 0);
            pixels.show();
            delay(15);//15
        }

    }
    else {

      if (pico > 5)
      {
        pico = pico - 0.15;//15
      }
    }

}






void efectoChoque(float valPico){

   byte r;
   byte g;
   byte b;


   if (valPico > 30)
    {
      valPico = sensibilidadPico;
    }


    if (valPico < sensibilidadPico)
    {
      return;
    }


    if (valPico > pico)
    {
      pico = valPico;

 
      randomSeed(millis());
      r = random(5, 255);
      g = random(5, 255);
      b = random(5, 255);



      for(int i=0;i < 24;i++){

        if(i < 20){

          pixels.setPixelColor(i, r, g, b);
          pixels.setPixelColor(39-i, r, g, b);

          if(i > 0){pixels.setPixelColor(i-1, r, g, b); pixels.setPixelColor(40-i, r, g, b);}
          if(i > 1){pixels.setPixelColor(i-2, r, g, b); pixels.setPixelColor(41-i, r, g, b);}
          if(i > 2){pixels.setPixelColor(i-3, r, g, b); pixels.setPixelColor(42-i, r, g, b);}
        }

        if(i > 3){pixels.setPixelColor(i-4, 0, 0, 0); pixels.setPixelColor(43-i, 0, 0, 0);}

        if(i > 17)
        {
          delay(25);//25
        }
        else{
          delay(6);//10
        }
        pixels.show();
      }

    


      for(int i=19;i >= -4;i--){
        
        if(i > -1){pixels.setPixelColor(i, r, g, b); pixels.setPixelColor(39-i, r, g, b);}
        if((i > -2) && (i < 18)){pixels.setPixelColor(i+1, r, g, b); pixels.setPixelColor(38-i, r, g, b);}
        if((i > -3) && (i < 17)){pixels.setPixelColor(i+2, r, g, b); pixels.setPixelColor(37-i, r, g, b);}
        if((i > -4) && (i < 16)){pixels.setPixelColor(i+3, r, g, b); pixels.setPixelColor(36-i, r, g, b);}

        if((i > -5) && (i < 16)){pixels.setPixelColor(i+4, 0, 0, 0); pixels.setPixelColor(35-i, 0, 0, 0);}

        delay(6);//6
        pixels.show();
      }


    }
    else {

      if (pico > 5)
      {
        pico = pico - 0.15;//15
      }
    }
}







void efectoPuntosDesplazables(float valPico){

  byte cantidadLedsDesplazables = 10;
  byte posMaxima = (numPixel / 2) + 1;


  if(millis() > tiempoColorPuntosDesplazables + 3000){

    tiempoColorPuntosDesplazables = millis();

    randomSeed(millis());
    r_puntosDesplazables = random(5, 255);
    g_puntosDesplazables = random(5, 255);
    b_puntosDesplazables = random(5, 255);
  }


  if(millis() > tiempoAnteriorPuntosDesplazables + 40){

    tiempoAnteriorPuntosDesplazables = millis();

    for(int i=0;i < cantidadLedsDesplazables;i++)
    {
      if(ledsDesplazables[i] > posMaxima){
        ledsDesplazables[i] = 0;
        pixels.setPixelColor(ledsDesplazables[i], 0, 0, 0);
      }
      else if(ledsDesplazables[i] > 0){
        pixels.setPixelColor(ledsDesplazables[i]-1, r_puntosDesplazables, g_puntosDesplazables, b_puntosDesplazables);
        pixels.setPixelColor((40 - ledsDesplazables[i]), r_puntosDesplazables, g_puntosDesplazables, b_puntosDesplazables);
        pixels.setPixelColor(ledsDesplazables[i]-2, 0, 0, 0);
        pixels.setPixelColor((41 - ledsDesplazables[i]), 0, 0, 0);
        ledsDesplazables[i] += 1;
      }
    }
    pixels.show();
  }


  if (valPico > 30)
  {
    valPico = sensibilidadPico;
  }

  if (valPico < sensibilidadPico)
  {
    return;
  }



  if (valPico > pico)
  {
    pico = valPico;
  
    for(int i=0;i < cantidadLedsDesplazables;i++)
    {
      if(ledsDesplazables[i] == 0){
        ledsDesplazables[i] = 1;
        break;
      }
    }

  }
  else {

    if (pico > 5)
    {
      pico = pico - 0.60;//60
    }
  }
}







void efectoRebote(float valPico){

  byte a = 7;
  int delayEfecto = 40;//65


  if (valPico > 30)
  {
    valPico = sensibilidadPico;
  }


  if (valPico < sensibilidadPico)
  {
    return;
  }



  if (valPico > pico)
  {
    pico = valPico;

    for(int i=0;i < 8;i++)
      {
        // Tira 1
        pixels.setPixelColor(i, r_EfectoRebote, g_EfectoRebote, b_EfectoRebote);
        pixels.setPixelColor(a, r_EfectoRebote, g_EfectoRebote, b_EfectoRebote);
        if(i != 4){pixels.setPixelColor(i-1, 0, 0, 0);}
        if(a != 3){pixels.setPixelColor(a+1, 0, 0, 0);}


        // Tira 2 
        pixels.setPixelColor(i+8, r_EfectoRebote, g_EfectoRebote, b_EfectoRebote);
        pixels.setPixelColor(a+8, r_EfectoRebote, g_EfectoRebote, b_EfectoRebote);

        if(i != 0){
              if(i != 4){pixels.setPixelColor(i+7, 0, 0, 0);}
              if(a != 3){pixels.setPixelColor(a+9, 0, 0, 0);}
        }


        // Tira 3
        pixels.setPixelColor(i+16, r_EfectoRebote, g_EfectoRebote, b_EfectoRebote);
        pixels.setPixelColor(a+16, r_EfectoRebote, g_EfectoRebote, b_EfectoRebote);
        
        if(i != 0){
              if(i != 4){pixels.setPixelColor(i+15, 0, 0, 0);}
              if(a != 3){pixels.setPixelColor(a+17, 0, 0, 0);}
        }


        // Tira 4
        pixels.setPixelColor(i+24, r_EfectoRebote, g_EfectoRebote, b_EfectoRebote);
        pixels.setPixelColor(a+24, r_EfectoRebote, g_EfectoRebote, b_EfectoRebote);
        
        if(i != 0){
              if(i != 4){pixels.setPixelColor(i+23, 0, 0, 0);}
              if(a != 3){pixels.setPixelColor(a+25, 0, 0, 0);}
        }


        // Tira 5
        pixels.setPixelColor(i+32, r_EfectoRebote, g_EfectoRebote, b_EfectoRebote);
        pixels.setPixelColor(a+32, r_EfectoRebote, g_EfectoRebote, b_EfectoRebote);
        
        if(i != 0){
              if(i != 4){pixels.setPixelColor(i+31, 0, 0, 0);}
              if(a != 3){pixels.setPixelColor(a+33, 0, 0, 0);}
        }
        

        delay(delayEfecto);
        pixels.show();
        a--;

        if(i == 3){
            randomSeed(millis());
            r_EfectoRebote = random(5, 255);
            g_EfectoRebote = random(5, 255);
            b_EfectoRebote = random(5, 255);
        }
      }

  }
  else {

    if (pico > 5)
    {
      pico = pico - 0.15;//15
    }
  }
}






void efectoOlas(float valPico){

  int ledArranque = 0;
  int delayEfecto = 15;//65
  byte r;
  byte g;
  byte b;
  int varAscendente = 0;
  int varDescendente = 0;
  bool topeAscentente = false;
  bool topeDescentente = false;



  if (valPico > 30)
  {
    valPico = sensibilidadPico;
  }


  if (valPico < sensibilidadPico)
  {
    return;
  }



  if (valPico > pico)
  {
    pico = valPico;

    randomSeed(millis());
    ledArranque = random(3,37);
    r = random(5,255);
    g = random(5,255);
    b = random(5,255);

    varAscendente = ledArranque;
    varDescendente = ledArranque;


    for(int i=0;i < 46;i++){

      if(varAscendente < 46){
        pixels.setPixelColor(varAscendente, r, g, b);
        if(varAscendente > ledArranque){pixels.setPixelColor(varAscendente-1, (r/1.5), (g/1.5), (b/1.5));}
        if(varAscendente > (ledArranque+1)){pixels.setPixelColor(varAscendente-2, (r/2), (g/2), (b/2));}
        if(varAscendente > (ledArranque+2)){pixels.setPixelColor(varAscendente-3, (r/3), (g/3), (b/3));}
        if(varAscendente > (ledArranque+3)){pixels.setPixelColor(varAscendente-4, (r/6), (g/6), (b/6));}
        if(varAscendente > (ledArranque+4)){pixels.setPixelColor(varAscendente-5, (r/10), (g/10), (b/10));}
        if(varAscendente > (ledArranque+5)){pixels.setPixelColor(varAscendente-6, 0, 0, 0);}

        varAscendente++;
      }
      else{
        topeAscentente = true;
      }

      if(varDescendente >= -6){
        pixels.setPixelColor(varDescendente, r, g, b);
        if(varDescendente < ledArranque){pixels.setPixelColor(varDescendente+1, (r/1.5), (g/1.5), (b/1.5));}
        if(varDescendente < (ledArranque-1)){pixels.setPixelColor(varDescendente+2, (r/2), (g/2), (b/2));}
        if(varDescendente < (ledArranque-2)){pixels.setPixelColor(varDescendente+3, (r/3), (g/3), (b/3));}
        if(varDescendente < (ledArranque-3)){pixels.setPixelColor(varDescendente+4, (r/6), (g/6), (b/6));}
        if(varDescendente < (ledArranque-4)){pixels.setPixelColor(varDescendente+5, (r/10), (g/10), (b/10));}
        if(varDescendente < (ledArranque-5)){pixels.setPixelColor(varDescendente+6, 0, 0, 0);}
        varDescendente--;
      }
      else{
        topeDescentente = true;
      }


      if((topeAscentente == true) && (topeDescentente == true)){
        break;
      }

      pixels.show();
      delay(delayEfecto);
    }

  }
  else {

    if (pico > 5)
    {
      pico = pico - 0.20;//20
    }
  }
}






void efectoPuntosDegradables(float valPico){

  byte divisorTemporal = 0;
  byte posicionTemporal = 0;
  byte posicion = 0;

  if(millis() > tiempoEfectoPuntosDegradables + 3000){
    
    randomSeed(millis());
    r_efectoVoz = random(30,255);
    g_efectoVoz = random(30,255);
    b_efectoVoz = random(30,255);
    
    tiempoEfectoPuntosDegradables = millis();
  }
  

  if(millis() > tiempoAnteriorPuntosDesplazables + 50){

    tiempoAnteriorPuntosDesplazables = millis();

    for(int i=0;i < cantidadMaxLeds;i++)
    {
      if(divLedsEfectoVoz[0][i] >= divisorMinimoBrillo){
    
        divLedsEfectoVoz[0][i] = 0;
        divLedsEfectoVoz[1][i] = 0;
      }
      else if(divLedsEfectoVoz[0][i] > 0){

        divisorTemporal = divLedsEfectoVoz[0][i];
        posicionTemporal = divLedsEfectoVoz[1][i];
        pixels.setPixelColor(posicionTemporal, round(r_efectoVoz/divisorTemporal), round(g_efectoVoz/divisorTemporal), round(b_efectoVoz/divisorTemporal));
        pixels.setPixelColor(posicionTemporal + 1, round(r_efectoVoz/divisorTemporal+2), round(g_efectoVoz/divisorTemporal+2), round(b_efectoVoz/divisorTemporal+2));
        pixels.setPixelColor(posicionTemporal - 1, round(r_efectoVoz/divisorTemporal+2), round(g_efectoVoz/divisorTemporal+2), round(b_efectoVoz/divisorTemporal+2));
        divLedsEfectoVoz[0][i] += valorDeIncremento;
      }

    }
    pixels.show();
  }




  if(valPico > 30)
  {
    valPico = sensibilidadPico;
  }

  if(valPico < sensibilidadPico)
  {
   return;
  }


 
    
  if(valPico > pico)
  {
    pico = valPico;


    for(int i=0;i < cantidadMaxLeds;i++)
    {
      if(divLedsEfectoVoz[0][i] == 0){

        randomSeed(millis());
        posicion = random(0,40);
        divLedsEfectoVoz[0][i] = 1;
        divLedsEfectoVoz[1][i] = posicion;
        break;
      }
    }

  }
  else {

    if (pico > 5){
      pico = pico - 0.60;//60
    }

  }
}






void noAudio()
{ 

byte r = r_noAudio; 
byte g = g_noAudio;
byte b = b_noAudio;

  
if(millis() > tiempoAnteriorNoAudio + delayNoAudio)
{
 tiempoAnteriorNoAudio = millis();
 
 if(direccionEfecto == false){

   if(posicionNoAudio > (numPixel+4))
   {
    direccionEfecto = !direccionEfecto;

    randomSeed(millis());
    delayNoAudio = random(40, 200);
    r_noAudio = random(5, 255);
    g_noAudio = random(5, 255);
    b_noAudio = random(5, 255);
    return;
    }
  
   posicionNoAudio++;
   pixels.setPixelColor(posicionNoAudio, r, g, b); 
   pixels.setPixelColor((posicionNoAudio-1), round(r/1.5), round(g/1.5), round(b/1.5));
   pixels.setPixelColor((posicionNoAudio-2), round(r/2), round(g/2), round(b/2)); 
   pixels.setPixelColor((posicionNoAudio-3), round(r/3), round(g/3), round(b/3)); 
   pixels.setPixelColor((posicionNoAudio-4), round(r/6), round(g/6), round(b/6)); 
   pixels.setPixelColor((posicionNoAudio-5), round(r/10), round(g/10), round(b/10)); 
   pixels.setPixelColor((posicionNoAudio-6), 0, 0, 0);
   pixels.show();
   return;
 }
 else
 {

   if(posicionNoAudio < -5)
   {
    direccionEfecto = !direccionEfecto;
    
    randomSeed(millis());
    delayNoAudio = random(30, 200);
    r_noAudio = random(5, 255);
    g_noAudio = random(5, 255);
    b_noAudio = random(5, 255);
    return;
    }
  
   posicionNoAudio--;
   pixels.setPixelColor(posicionNoAudio, r, g, b); 
   pixels.setPixelColor((posicionNoAudio+1), round(r/1.5), round(g/1.5), round(b/1.5));
   pixels.setPixelColor((posicionNoAudio+2), round(r/2), round(g/2), round(b/2)); 
   pixels.setPixelColor((posicionNoAudio+3), round(r/3), round(g/3), round(b/3)); 
   pixels.setPixelColor((posicionNoAudio+4), round(r/6), round(g/6), round(b/6)); 
   pixels.setPixelColor((posicionNoAudio+5), round(r/10), round(g/10), round(b/10)); 
   pixels.setPixelColor((posicionNoAudio+6), 0, 0, 0);
   pixels.show();
   return;
  }

 }

}





void ledsApagados(){

  for(int i=0;i < numPixel;i++) {
    
    pixels.setPixelColor(i, 0, 0, 0); // i, R, G, B
    pixels.show();
  }
}





void luzTemperaturaAlta(){

  for(int i=0;i < numPixel;i++) {
    
    pixels.setPixelColor(i, 50, 0, 0); // i, R, G, B
    pixels.show();
  }
}




void mostrarModo(byte modo){

  if(modo == 1){

    for(int i=0;i < (numPixel + 1);i++) {
    
      pixels.setPixelColor(i, 0, 0, 255); // i, R, G, B
      pixels.setPixelColor(i-1, 0, 0, 0); // i, R, G, B
      pixels.show();
      delay(100);
    }
  }
  else if(modo == 2){

    for(int i=0;i < (numPixel + 2);i++) {
    
      pixels.setPixelColor(i, 0, 0, 255); // i, R, G, B
      pixels.setPixelColor(i-1, 0, 0, 255); // i, R, G, B
      pixels.setPixelColor(i-2, 0, 0, 0); // i, R, G, B
      pixels.show();
      delay(100);
    }
  }
}