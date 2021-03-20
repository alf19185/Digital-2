/*
  Blink
  The basic Energia example.
  Turns on an LED on for one second, then off for one second, repeatedly.
  Change the LED define to blink other LEDs.
  
  Hardware Required:
  * LaunchPad with an LED
  
  This example code is in the public domain.
*/

// most launchpads have a red LED
#define LEDR PF_1
#define LEDB PF_2
#define LEDG PF_3
#define PUSH_INICIO PF_4

// *****Variables******
int buttonState = 0; 
  
// *****Setup******
void setup() {                
  // initialize the digital pin as an output.
  pinMode(LEDR, OUTPUT);    
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  
  semaforo(); 
}



// *****Loop*****
void loop() {
  
  INICIO = digitalRead(PUSH_INICIO);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);  
  } 
  else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
  semaforo(); 
  }
}

void semaforo (void){
  
  digitalWrite(LEDR, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(LEDG, LOW);
  delay(1000);               // wait for a second
  digitalWrite(LEDG, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(LEDR, HIGH);
  delay(1000);               // wait for a second
  digitalWrite(LEDG, HIGH);    // turn the LED off by making the voltage LOW
  digitalWrite(LEDR, LOW);
  delay(1000); 
  digitalWrite(LEDG, LOW);    // turn the LED off by making the voltage LOW
  delay(2000); 
  
  }
