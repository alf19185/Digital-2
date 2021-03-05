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

/************************ Example Starts Here *******************************/

// this int will hold the current count for our sketch
int count = 0;
int ex = 1;
int ey = 1;
int ez = 1;

// set up the 'counter' feed
AdafruitIO_Feed *Eje_X = io.feed("Eje_X");
AdafruitIO_Feed *Eje_Y = io.feed("Eje_Y");
AdafruitIO_Feed *Eje_Z = io.feed("Eje_Z");
AdafruitIO_Feed *Luz1 = io.feed("Luz1");
AdafruitIO_Feed *Luz2 = io.feed("Luz2");

void setup() {

  // start the serial connection
  Serial.begin(9600);

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  Luz1->onMessage(handleMessage); 
  Luz2->onMessage(handleMessage); 
  
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

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
  Serial.print("sending EX -> ");
  Serial.println(ex);
  Eje_X->save(ex);

  Serial.print("sending EY -> ");
  Serial.println(ey);
  Eje_Y->save(ey);

  Serial.print("sending EZ -> ");
  Serial.println(ez);
  Eje_Z->save(ez);

  // Adafruit IO is rate limited for publishing, so a delay is required in
  // between feed->save events. In this example, we will wait three seconds
  // (1000 milliseconds == 1 second) during each loop.
  delay(8000);

}

void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <- ");
  Serial.println(data->value());
  
}
