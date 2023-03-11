 #include <SoftwareSerial.h>  //Cambiamos RX/TX del bluetooth a los pines 2 y 3
 SoftwareSerial BT(2,3);      //Para que no interfieran en la carga del sketch con el USB
 
int motor11 = 4; // 
int motor12 = 5; // salidas para el L298N
int enable1 = 6; // incluidos los 2 enables
int motor21 = 7; // 
int motor22 = 8; // 
int enable2 = 9; // 
int claxon = 10; //
int estado;
int flag=0;       
int estadoStop=0;
void setup() {
    //Configuramos los pines de salida:
    pinMode(motor11, OUTPUT);
    pinMode(motor12, OUTPUT);
    pinMode(enable1, OUTPUT);
    pinMode(motor21, OUTPUT);
    pinMode(motor22, OUTPUT);
    pinMode(enable2, OUTPUT);
    pinMode(claxon,  OUTPUT);
    // Velocidad de los motores al iniciar
    analogWrite(enable1, 80);
    analogWrite(enable2, 80);
  
    BT.begin(9600);      //Comunicacion serial para el bluetooth
    Serial.begin(9600);  //Comunicacion serial para el monitor serial
}

void loop() {
    //El dato recibido se almacena en la variable estado
    if(BT.available() > 0){     
      estado = BT.read();   
      flag=0;
    }   
    if (estado == '1') {          //Los estados del 1 al 9 es la velocidad 
        analogWrite(enable1,80);  //Siendo 1 la mas lenta y 9 la mas rapida
        analogWrite(enable2,80);
    }
      if (estado == '2') {
        analogWrite(enable1,100);
        analogWrite(enable2,100);
      }
     if (estado == '3') {
      analogWrite(enable1,120);
        analogWrite(enable2,120);
     }
      if (estado == '4') {
      analogWrite(enable1,140);
        analogWrite(enable2,140);
      }
     if (estado == '5') {
      analogWrite(enable1,160);
        analogWrite(enable2,160);
     }
     if (estado == '6') {
      analogWrite(enable1,180);
      analogWrite(enable2,180);
     }
     if (estado == '7') {
      analogWrite(enable1,200);
      analogWrite(enable2,200);
     }
     if (estado == '8') {
        analogWrite(enable1,220);
        analogWrite(enable2,220);
     }
      if (estado == '9') {
        analogWrite(enable1,240);
        analogWrite(enable2,240);
      }
    // AVANCE:
    if (estado == 'F') {
        digitalWrite(motor11, HIGH);
        digitalWrite(motor12, LOW); 
        digitalWrite(motor21, HIGH);
        digitalWrite(motor22, LOW);
        if(flag == 0){
          Serial.println("Avance!!!");
          flag=1;
        }
    }
    
    // IZQUIERDA
    else if (estado == 'L') {
        digitalWrite(motor11, LOW); 
        digitalWrite(motor12, LOW); 
        digitalWrite(motor21, HIGH);
        digitalWrite(motor22, LOW);
        if(flag == 0){
          Serial.println("Gira Izquierda");
          flag=1;
        }
        //estado=3;
        //estadoStop=1;
    }
    // PARADO
    else if (estado == 'S' || estadoStop == 1) {
        digitalWrite(motor11, LOW); 
        digitalWrite(motor12, LOW); 
        digitalWrite(motor21, LOW);
        digitalWrite(motor22, LOW);
        if(flag == 0){
          Serial.println("STOP!");
          flag=1;
        }
        estadoStop=0;
    }
    // DERECHA
    else if (estado == 'R') {
        digitalWrite(motor11, HIGH); 
        digitalWrite(motor12, LOW); 
        digitalWrite(motor21, LOW);
        digitalWrite(motor22, LOW);
        if(flag == 0){
        Serial.println("Gira Derecha");
          flag=1;
        }
    }
    // REVERSA
    else if (estado == 'B') {
        digitalWrite(motor11, LOW); 
        digitalWrite(motor12, HIGH);
        digitalWrite(motor21, LOW);
        digitalWrite(motor22, HIGH);
        if(flag == 0){
          Serial.println("Reversa!");
          flag=1;
        }
    }
     //AVANCE DERECHA
    else if (estado == 'I') {
        digitalWrite(motor11, HIGH); 
        digitalWrite(motor12, LOW);
        digitalWrite(motor21, LOW);
        digitalWrite(motor22, HIGH);
        if(flag == 0){
          Serial.println("Reversa!");
          flag=1;
        }
    } // AVANCE IZQUIERDA
    else if (estado == 'G') {
        digitalWrite(motor11, LOW); 
        digitalWrite(motor12, HIGH);
        digitalWrite(motor21, HIGH);
        digitalWrite(motor22, LOW);
        if(flag == 0){
          Serial.println("Reversa!");
          flag=1;
        }
    } // REVERSA DERECHA
    else if (estado == 'J') {
        digitalWrite(motor11, LOW); 
        digitalWrite(motor12, HIGH);
        digitalWrite(motor21, HIGH);
        digitalWrite(motor22, LOW);
        if(flag == 0){
          Serial.println("Reversa!");
          flag=1;
        }
    } // REVERSA IZQUIERDA
    else if (estado == 'H') {
        digitalWrite(motor11, HIGH); 
        digitalWrite(motor12, LOW);
        digitalWrite(motor21, LOW);
        digitalWrite(motor22, HIGH);
        if(flag == 0){
          Serial.println("Reversa!");
          flag=1;
        }
    }
    else if (estado =='V'){
    tone (claxon,1000);
    }
    else if (estado =='v'){
      noTone (claxon);
    }
}
