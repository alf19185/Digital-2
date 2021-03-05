// Adafruit IO Publish Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.

#include "config.h"
#define RX2 16
#define TX2 17

/************************ Example Starts Here *******************************/

// this int will hold the current count for our sketch
int count = 0;
String recibo;
int ex = 1;
int ey = 1;
int ez = 1;
int FLAG = 0;
char READ[8];
char L1;
char L2;

// set up the 'counter' feed
AdafruitIO_Feed *Eje_X = io.feed("Eje_X");
AdafruitIO_Feed *Eje_Y = io.feed("Eje_Y");
AdafruitIO_Feed *Eje_Z = io.feed("Eje_Z");

AdafruitIO_Feed *Luz1 = io.feed("Luz1");
AdafruitIO_Feed *Luz2 = io.feed("Luz2");

void setup() {

  // start the serial connection
  Serial.begin(9600);
  Serial1.begin(9600, SERIAL_8N1, RX2, TX2);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  Luz1->onMessage(handleMessage_LED1); 
  Luz2->onMessage(handleMessage_LED2); 
  
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Luz1->get();
  Luz2->get();
  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {


  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  // save count to the 'counter' feed on Adafruit IO
  Lectura_Correcta ();
  Serial1.print("sending -> ");
  Serial2.println(READ);

   Lectura_Correcta();
 


    Eje_X->save(READ);
   // Eje_Y->save(READ);
   // Eje_Z->save(READ);
 
  
  delay(8000);

   
  /*Serial.print("sending EX -> ");
  Serial.println(ex);
  Eje_X->save(ex); */

  Serial1.print("sending EY -> ");
  Serial1.println(ey);
  Eje_Y->save(ey);

  Serial1.print("sending EZ -> ");
  Serial1.println(ez);
  Eje_Z->save(ez);

  // Adafruit IO is rate limited for publishing, so a delay is required in
  // between feed->save events. In this example, we will wait three seconds
  // (1000 milliseconds == 1 second) during each loop.

}

void Lectura_Correcta (){
  if (READ[3] == ',' && READ[7] == ','&& READ[11] == ','){
     FLAG = 1; 
     }
     else{
      FLAG = 0;  }
}

void handleMessage_LED1(AdafruitIO_Data *data) {
  if (data->toString() == "ON"){
    L1 = 1;
  }else{
    L1 = 0;
  }
  Serial.print("received <- ");
  Serial.println(data->value());

}
void handleMessage_LED2(AdafruitIO_Data *data) {
  if (data->toString() == "ON"){
      L2 = 1;
  }else{
      L2 = 0;
  }
  Serial.print("received <- ");
  Serial.println(data->value());

}
