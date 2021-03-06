// Adafruit IO Publish & Subscribe Example
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

// Track time of last published messages and limit feed->save events to once
// every IO_LOOP_DELAY milliseconds.
//
// Because this sketch is publishing AND subscribing, we can't use a long
// delay() function call in the main loop since that would prevent io.run()
// from being called often enough to receive all incoming messages.
//
// Instead, we can use the millis() function to get the current time in
// milliseconds and avoid publishing until IO_LOOP_DELAY milliseconds have
// passed.
#define IO_LOOP_DELAY 5000
#define RXD2 16
#define TXD2 17
unsigned long lastUpdate = 0;
int LEDP2 ;
int LEDP1 ;
String acelerometro = "15,40,90";
String Rx_PIC;

// set up the 'counter' feed
AdafruitIO_Feed *Ejes = io.feed("Ejes");
AdafruitIO_Feed *Luz2 = io.feed("Luz2");
AdafruitIO_Feed *Luz1 = io.feed("Luz1");

void setup() {

  // start the serial connection
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  // connect to io.adafruit.com
  
  io.connect();

  // set up a message handler for the count feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  Luz1->onMessage(handleMessage_1);
  Luz2->onMessage(handleMessage_2);
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  
  Luz1->get();
  Luz2->get();
}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
  
  Serial2.write(LEDP1 + 48);
  Serial2.write(',');
  Serial2.write(LEDP2 + 48);
  Serial2.write(10);  
  
  if (Serial2.available()>0){
  Serial.print("*");  
  Rx_PIC = Serial2.readString();
  Serial.print("RX PIC: ");
  Serial.print(Rx_PIC);
  acelerometro = Rx_PIC;
  //    Serial2.write(0X48);
  //  Serial2.write(0X48);
  //  Serial2.write(10);
    }


  if (millis() > (lastUpdate + IO_LOOP_DELAY)) {
    // save count to the 'counter' feed on Adafruit IO
    Serial.print("sending -> ");
    Serial.println(acelerometro);
    Ejes->save(acelerometro);

    // increment the count by 1
    count++;

    // after publishing, store the current time
    lastUpdate = millis();
  }

}


// this function is called whenever a 'counter' message
// is received from Adafruit IO. it was attached to
// the counter feed in the setup() function above.
void handleMessage_1(AdafruitIO_Data *data) {
  String LED1 = data->toString();
  Serial.println("LED1");
  Serial.println(LED1);
  if (LED1 == "ON"){
    LEDP1=1;
    }
 else {
      LEDP1=0;
 }
}

void handleMessage_2(AdafruitIO_Data *data) {
  
 String LED2 = data->toString();
  Serial.println("LED2");
  Serial.println(LED2);
  if (LED2 == "ON"){
    LEDP2=1;
    }
 else {
      LEDP2=0;
 }
}
