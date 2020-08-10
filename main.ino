#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
//MOTOR INVERIDO
/// Motor R1
int motorR1Pin1 = 19; 
int motorR1Pin2 = 18; 
int AtivarR1Pin = 21;

//SENTIDO CORRETO
/// Motor R2
int motorR2Pin1 = 17; 
int motorR2Pin2 = 16; 
int AtivarR2Pin = 15; 


//MOTOR INVERIDO
/// Motor L1
int motorL1Pin1 = 25; 
int motorL1Pin2 = 33; 
int AtivarL1Pin = 32 ; 


//SENTIDO CORRETO
// Motor L2
int motorL2Pin1 = 27; 
int motorL2Pin2 = 26; 
int AtivarL2Pin = 14; 

int state = 0 ;

// Definido Propriedadess PWM primeiro motor
const int freq_1 = 30000;
const int pwmChannel_1 = 0;
const int resolution_1 = 8;
int dutyCycle_1 = 180;

// Definido Propriedadess PWM Segundo motor
const int freq_2 = 30000;
const int pwmChannel_2 = 1;
const int resolution_2 = 8;
int dutyCycle_2 = 200;

// Definido Propriedadess PWM Terceiro motor
const int freq_3 = 30000;
const int pwmChannel_3 = 2;
const int resolution_3 = 8;
int dutyCycle_3 = 200;


// Definido Propriedadess PWM Quarto motor
const int freq_4 = 30000;
const int pwmChannel_4 = 3;
const int resolution_4 = 8;
int dutyCycle_4 = 200;

   
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
    ledcSetup(pwmChannel_1, freq_1, resolution_1);
 
    ledcSetup(pwmChannel_2, freq_2, resolution_2);

    ledcSetup(pwmChannel_3, freq_3, resolution_3);
 
    ledcSetup(pwmChannel_4, freq_4, resolution_4);

    

  // anexar o canal para o GPIO ser controlado
    ledcAttachPin(AtivarR1Pin, pwmChannel_1);
    ledcAttachPin(AtivarL1Pin, pwmChannel_2);
    ledcAttachPin(AtivarR2Pin, pwmChannel_3);
    ledcAttachPin(AtivarL2Pin, pwmChannel_4);

    Serial.begin(115200);
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
}
if (state == '4'){
  // vira para esquerda
  ledcWrite(pwmChannel_1, 255);
 ledcWrite(pwmChannel_2, 255);
 ledcWrite(pwmChannel_4, 255);
 ledcWrite(pwmChannel_3, 100);
}
if (state == '3'){
  // vira para Direita
    ledcWrite(pwmChannel_1, 255);
    ledcWrite(pwmChannel_2, 255);
    ledcWrite(pwmChannel_3, 255);
    ledcWrite(pwmChannel_4, 150);
    
}
if (state == '2'){
  // Frente
    digitalWrite(motorR1Pin1, LOW);
    digitalWrite(motorR1Pin2, HIGH);
    
    digitalWrite(motorL1Pin1, LOW);
    digitalWrite(motorL1Pin2, HIGH); 
 
    
    digitalWrite(motorR2Pin1, HIGH);
    digitalWrite(motorR2Pin2, LOW);
    
    digitalWrite(motorL2Pin1, LOW);
    digitalWrite(motorL2Pin2, HIGH);

    ledcWrite(pwmChannel_1, 200);
    ledcWrite(pwmChannel_2, 200);
    ledcWrite(pwmChannel_3, 200);
    ledcWrite(pwmChannel_4, 200);
}
if (state == '1'){
  // tras
    digitalWrite(motorR1Pin1, HIGH);
    digitalWrite(motorR1Pin2, LOW);

    digitalWrite(motorL1Pin1, HIGH);
    digitalWrite(motorL1Pin2, LOW); 
 
    
    digitalWrite(motorR2Pin1, LOW);
    digitalWrite(motorR2Pin2, HIGH);
    
    digitalWrite(motorL2Pin1, HIGH);
    digitalWrite(motorL2Pin2, LOW);
    ledcWrite(pwmChannel_1, 180);
    ledcWrite(pwmChannel_2, 180);
    ledcWrite(pwmChannel_3, 180);
    ledcWrite(pwmChannel_4, 180);
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
    
    while (dutyCycle_1 <= 255){
        ledcWrite(pwmChannel_1, dutyCycle_1);   
       //Serial.print("movendo o carro para frente (duty cycle): ");
       //Serial.println(dutyCycle);
       // dutyCycle = dutyCycle + 10;
    }
    //dutyCycle = 200 ;
}
}
