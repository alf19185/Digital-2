#include <SPI.h>
#include <SD.h>

File root;
File myFile;

int en1;
int en2;
int var1;
int cambio;

void archivos (void);
void Directorio(File dir, int numTabs);
void Imagenes(void);
void  Archivo_Print(int numero_print);
void checkserial (void);


void setup(){
  // Open serial communications and wait for port to open:
  
  Serial.begin(9600);
  SPI.setModule(0);
  Serial.print("Initializing SD card...");
 
  pinMode(10, OUTPUT);
  if (!SD.begin(32)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  en1 = 1;
  en2 = 0;
}

void loop(){
  checkserial(); 
  if (en1 == 1){  
    archivos(); 
  }
  if (en2 == 1){
    Imagenes();
  }
  delay(100);
  en2 = 0; 
  var1 = 0;
}

void Imagenes(void){
  en1 = 1;
  en2 = 0;
  Archivo_Print(var1); 
  
  if (myFile) {        
    Serial.println("el archivo seleccionado fue");
    Serial.print("\t");
    
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    
    myFile.close();
    
  } else {
    
    Serial.println("error opening test.txt");
  }
}

void archivos (void){                                               //Lectura SD
    en1 = 0;
    root = SD.open("/");

    Directorio(root, 0); 
}

void checkserial (void){          
    int check = Serial.read();
    if (check == 49){
      en2 = 1;
      var1 = 1;
    }else if (check == 50){
      en2 = 1;
      var1 = 2;
    }else if (check == 51){
      en2 = 1;
      var1 = 3;
    }
    
    
}


void Directorio(File dir, int numTabs) {                  //Coloca listado de archivos
   Serial.println("Seleccione el archivo:");
 
  
   dir.rewindDirectory();
   while(true) {
     
     File entry =  dir.openNextFile();
     if (! entry) {                                         
                                                            
       break;
     }
    for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
    switch(cambio){                                        
        case 0:
          entry.name();
          cambio = 1;
          break;
        case 1:
          Serial.print(cambio);
          Serial.print(".");
          Serial.print(entry.name());
          cambio = 2;
          break;
        case 2:
          Serial.print(cambio);
          Serial.print(".");
          Serial.print(entry.name());
          cambio = 3;
          break;
        case 3:
          Serial.print(cambio);
          Serial.print(".");
          Serial.print(entry.name());
          cambio = 0;
          break;
       }
     
     if (entry.isDirectory()) { 
     } else {
       
       Serial.print("\t\t"); 
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}

void Archivo_Print(int numero_print){  //Selecciona archivo
    switch(numero_print){
      case 1:
        myFile = SD.open("Piranha.txt");
        break;
      
      case 2:
        myFile = SD.open("Goomba.txt");
        break;
        case 3:
       myFile = SD.open("Coin.txt");
        break;
      
      default:
        myFile = SD.open("Coin.txt");
        break;
    }
}
