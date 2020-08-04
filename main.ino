#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

/// Motor R1
int motorR1Pin1 = 17; 
int motorR1Pin2 = 16; 
int AtivarR1Pin = 15; 

/// Motor R2
int motorL1Pin1 = 19; 
int motorL1Pin2 = 18; 
int AtivarL1Pin = 21; 

/// Motor L1
int motorR2Pin1 = 27; 
int motorR2Pin2 = 26; 
int AtivarR2Pin = 14; 

// Motor L2
int motorL2Pin1 = 25; 
int motorL2Pin2 = 23; 
int AtivarL2Pin = 32 ; 

int state = 0 ;

// Definido Propriedadess PWM 
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 250;

void setup() {
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  // Definido os pinos como outputs:
    pinMode(motorR1Pin1, OUTPUT);
    pinMode(motorR1Pin2, OUTPUT);
    pinMode(AtivarR1Pin, OUTPUT);
    pinMode(motorR2Pin1, OUTPUT);
    pinMode(motorR2Pin2, OUTPUT);
    pinMode(AtivarR2Pin, OUTPUT);
    pinMode(motorL1Pin1, OUTPUT);
    pinMode(motorL1Pin2, OUTPUT);
    pinMode(AtivarL1Pin, OUTPUT);
    pinMode(motorL2Pin1, OUTPUT);
    pinMode(motorL2Pin2, OUTPUT);
    pinMode(AtivarL2Pin, OUTPUT);
    
  // configura PWM 
    ledcSetup(pwmChannel, freq, resolution);

  // anexar o canal para o GPIO ser controlado
    ledcAttachPin(AtivarR1Pin, pwmChannel);
    ledcAttachPin(AtivarR2Pin, pwmChannel);
    ledcAttachPin(AtivarL1Pin, pwmChannel);
    ledcAttachPin(AtivarL2Pin, pwmChannel);

    Serial.begin(115200);

  //testando
  //Serial.print("Testando DC Motor...");
}

void loop() {

  if (SerialBT.available()) {
      state = SerialBT.read();
      Serial.write(state);
  }

    
if (state == '0'){
  // desliga o motor
    digitalWrite(motorR1Pin1, LOW);
    digitalWrite(motorR1Pin2, LOW);
    
    digitalWrite(motorR2Pin1, LOW);
    digitalWrite(motorR2Pin2, LOW); 
    
    digitalWrite(motorL1Pin1, LOW);
    digitalWrite(motorL1Pin2, LOW);
    
    digitalWrite(motorL2Pin1, LOW);
    digitalWrite(motorL2Pin2, LOW);
    delay(1000);
}
if (state == '3'){
  // vira para esquerda
    digitalWrite(motorR1Pin1, LOW);
    digitalWrite(motorR1Pin2, LOW);
    
    digitalWrite(motorL1Pin1, LOW);
    digitalWrite(motorL1Pin2, HIGH); 
 
    
    digitalWrite(motorR2Pin1, HIGH);
    digitalWrite(motorR2Pin2, LOW);
    
    digitalWrite(motorL2Pin1, HIGH);
    digitalWrite(motorL2Pin2, LOW);
}
if (state == '4'){
  // vira para Direita
    digitalWrite(motorR1Pin1, HIGH);
    digitalWrite(motorR1Pin2, LOW);
    
    digitalWrite(motorL1Pin1, LOW);
    digitalWrite(motorL1Pin2, LOW); 
 
    
    digitalWrite(motorR2Pin1, HIGH);
    digitalWrite(motorR2Pin2, LOW);
    
    digitalWrite(motorL2Pin1, HIGH);
    digitalWrite(motorL2Pin2, LOW);
    
    delay(500);
}
if (state == '1'){
  // Frente
    digitalWrite(motorR1Pin1, HIGH);
    digitalWrite(motorR1Pin2, LOW);
    
    digitalWrite(motorL1Pin1, HIGH);
    digitalWrite(motorL1Pin2, LOW); 
 
    
    digitalWrite(motorR2Pin1, HIGH);
    digitalWrite(motorR2Pin2, LOW);
    
    digitalWrite(motorL2Pin1, HIGH);
    digitalWrite(motorL2Pin2, LOW);
    
    delay(500);
}
if (state == '2'){
  // tras
    digitalWrite(motorR1Pin1, LOW);
    digitalWrite(motorR1Pin2, HIGH);
    
    digitalWrite(motorL1Pin1, LOW);
    digitalWrite(motorL1Pin2, HIGH); 
 
    
    digitalWrite(motorR2Pin1, LOW);
    digitalWrite(motorR2Pin2, HIGH);
    
    digitalWrite(motorL2Pin1, LOW);
    digitalWrite(motorL2Pin2, HIGH);
    while (dutyCycle <= 255){
        ledcWrite(pwmChannel, dutyCycle);   
       //Serial.print("movendo o carro para frente (duty cycle): ");
       //Serial.println(dutyCycle);
        dutyCycle = dutyCycle + 10;
    }
    delay(500);
}
if (state == '10'){
  // move o carro para frente  adicionado velocidade
   
    //digitalWrite(motorR1Pin1, HIGH);
    //digitalWrite(motorR1Pin2, LOW);
   // delay(2000);
    
    //digitalWrite(motorL1Pin1, HIGH);
    //digitalWrite(motorL1Pin2, LOW); 
    //delay(2000);
    
    digitalWrite(motorR2Pin1, LOW);
    digitalWrite(motorR2Pin2, HIGH);
   // delay(2000);
    
    digitalWrite(motorL2Pin1, HIGH);
    digitalWrite(motorL2Pin2, LOW);
   // delay(2000);
    
    while (dutyCycle <= 255){
        ledcWrite(pwmChannel, dutyCycle);   
       //Serial.print("movendo o carro para frente (duty cycle): ");
       //Serial.println(dutyCycle);
       // dutyCycle = dutyCycle + 10;
    }
    //dutyCycle = 200 ;
}
}
