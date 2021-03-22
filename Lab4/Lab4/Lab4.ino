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
#define PUSH_J1 PA_3
#define PUSH_J2 PA_2

#define L10 PD_0
#define L11 PD_1
#define L12 PD_2
#define L13 PD_3
#define L14 PE_1
#define L15 PE_2
#define L16 PE_3
#define L17 PD_7

#define L20 PB_0
#define L21 PB_1
#define L22 PE_4
#define L23 PE_5
#define L24 PB_4
#define L25 PA_5
#define L26 PA_6
#define L27 PA_7

// *****Variables******
int ButtonState = 0; 
int Flag_Carrera =0;
int Contador_J1 = 0;
int Contador_J2 = 0;
int done1 = 0;
int done2 = 0;
    
// *****Setup******
void setup() {        
          
  // Leds del semáforo
  pinMode(LEDR, OUTPUT);    
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  
  // Push buttons
  pinMode(PUSH_INICIO, INPUT_PULLUP);
  pinMode(PUSH_J1, INPUT_PULLUP);
  pinMode(PUSH_J2, INPUT_PULLUP);

  //Puertos para leds de cada jugador
 
  pinMode(L10, OUTPUT);
  pinMode(L11, OUTPUT);
  pinMode(L12, OUTPUT);
  pinMode(L13, OUTPUT);
  pinMode(L14, OUTPUT);
  pinMode(L15, OUTPUT);
  pinMode(L16, OUTPUT);
  pinMode(L17, OUTPUT);
  
  pinMode(L20, OUTPUT);
  pinMode(L21, OUTPUT);
  pinMode(L22, OUTPUT);
  pinMode(L23, OUTPUT);
  pinMode(L24, OUTPUT);
  pinMode(L25, OUTPUT);
  pinMode(L26, OUTPUT);
  pinMode(L27, OUTPUT);

}

// *****Loop*****
void loop() {

//******Semaforo***********  
  ButtonState = digitalRead(PUSH_INICIO);
  
   if (ButtonState == LOW) {   
     semaforo();     
    } 

   else
     {
    digitalWrite(LEDR, LOW);  
    digitalWrite(LEDG, LOW);
    digitalWrite(LEDB, LOW);
  }

//****Carrera**********
  carrera(); 
  Fin(); 
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
  
  Flag_Carrera = 1;          
  Contador_J1 = 0;             //Reinicio valores de contadores
  Contador_J2 = 0;
  
  }

void carrera (void){
    
  if (Flag_Carrera == 1){

   int jugador1_temp = digitalRead(PUSH_J1);
   int jugador2_temp = digitalRead(PUSH_J2);
   
    if (jugador1_temp == LOW){
        Contador_J1++ ;
        contador_Leds1();
    }
  
    else if (jugador2_temp == LOW){
        Contador_J2++ ;
        contador_Leds2();
    }
  
  else{

    digitalWrite(L10, LOW);
    digitalWrite(L11, LOW);
    digitalWrite(L12, LOW);
    digitalWrite(L13, LOW);
    digitalWrite(L14, LOW);
    digitalWrite(L15, LOW);
    digitalWrite(L16, LOW);
    digitalWrite(L17, LOW);
    
    digitalWrite(L20, LOW);
    digitalWrite(L21, LOW);
    digitalWrite(L22, LOW);
    digitalWrite(L23, LOW);
    digitalWrite(L24, LOW);
    digitalWrite(L25, LOW);
    digitalWrite(L26, LOW);
    digitalWrite(L27, LOW);
    
    }  
  }
}

void Fin(void){

  if(done1 == 1 && done2 == 0) {
       digitalWrite(LEDG, HIGH); 
    }
  else if(done1 == 0 && done2 == 1) {
      digitalWrite(LEDB, HIGH); 
    }
   else if(done1 == 1 && done2 == 1) {
      digitalWrite(LEDB, LOW); 
      digitalWrite(LEDB, LOW);
    }
  
}

void contador_Leds1 (void){

if (Contador_J1 == 0){
    digitalWrite(L10, LOW);
    digitalWrite(L11, LOW);
    digitalWrite(L12, LOW);
    digitalWrite(L13, LOW);
    digitalWrite(L14, LOW);
    digitalWrite(L15, LOW);
    digitalWrite(L16, LOW);
    digitalWrite(L17, LOW);
  }
  else if (Contador_J1 == 1){
    digitalWrite(L10, HIGH);
  } 
  else if (Contador_J1 == 2){
    digitalWrite(L11, HIGH);
    digitalWrite(L10, LOW);
  } 
  else if (Contador_J1 == 3){
    digitalWrite(L12, HIGH);
    digitalWrite(L11, LOW);
  }
  else if (Contador_J1 == 4){
    digitalWrite(L13, HIGH);
    digitalWrite(L12, LOW);
  }
  else if (Contador_J1 == 5){
    digitalWrite(L14, HIGH);
    digitalWrite(L13, LOW);
  }
  else if (Contador_J1 == 6){
    digitalWrite(L15, HIGH);
    digitalWrite(L14, LOW);
  }
  else if (Contador_J1 == 7){
    digitalWrite(L16, HIGH);
    digitalWrite(L15, LOW);
  }
  else if (Contador_J1 == 8){
    digitalWrite(L17, HIGH);
    digitalWrite(L16, LOW);
  }
  else if (Contador_J1 == 9){
    digitalWrite(L17, LOW);
    done1 = 1;
  }
}  


void contador_Leds2 (void){
  
if (Contador_J2 == 0){
    digitalWrite(L20, LOW);
    digitalWrite(L21, LOW);
    digitalWrite(L22, LOW);
    digitalWrite(L23, LOW);
    digitalWrite(L24, LOW);
    digitalWrite(L25, LOW);
    digitalWrite(L26, LOW);
    digitalWrite(L27, LOW);
  }
  else if (Contador_J2 == 1){
    digitalWrite(L20, HIGH);
  } 
  else if (Contador_J2 == 2){
    digitalWrite(L21, HIGH);
    digitalWrite(L20, LOW);
  } 
  else if (Contador_J2 == 3){
    digitalWrite(L22, HIGH);
    digitalWrite(L21, LOW);
  }
  else if (Contador_J2 == 4){
    digitalWrite(L23, HIGH);
    digitalWrite(L22, LOW);
  }
  else if (Contador_J2 == 5){
    digitalWrite(L24, HIGH);
    digitalWrite(L23, LOW);
  }
  else if (Contador_J2 == 6){
    digitalWrite(L25, HIGH);
    digitalWrite(L24, LOW);
  }
  else if (Contador_J2 == 7){
    digitalWrite(L26, HIGH);
    digitalWrite(L25, LOW);
  }
  else if (Contador_J2 == 8){
    digitalWrite(L27, HIGH);
    digitalWrite(L26, LOW);
  }
  else if (Contador_J2 == 9){
    digitalWrite(L27, LOW);
    done2 = 1;
  }
}  
