//Bibliotecas
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

//Portas
#define SS_PIN 10
#define RST_PIN 9
#define SERVO 3

//Variáveis
Servo s;
int pos;

MFRC522 rfid(SS_PIN,RST_PIN);
Servo porta;

void setup() {
//Iniciando a comunicação com o chip
  SPI.begin();
  rfid.PCD_Init();
  Serial.begin(9600);

//Inicia o motor da posição zero
  s.attach(SERVO);
  Serial.begin(9600);
  s.write(0); // Inicia motor posição zero
}

void loop() {
//Checando conexão com o chip
  if(!rfid.PICC_IsNewCardPresent()|| !rfid.PICC_ReadCardSerial())
    return;
//Montar o endereço do código
  String strID = "";
  for(byte i = 0 ; i<4;i++){
    strID +=
      (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
      String(rfid.uid.uidByte[i],HEX) +
      (i!=3 ? ":" : "");
  }
  
//Acesso com a tag e cartão
  strID.toUpperCase();
  Serial.println(strID);
  if(strID.indexOf("A3:8E:A2:98") >=0){
    Serial.println("Achei a tag!");
    digitalWrite(4,HIGH);
    s.write(90);
    delay(2500);
    digitalWrite(4,LOW);
    s.write(0);
  }else if(strID.indexOf("A3:E6:E3:AE") >=0){
    Serial.println("Achei o cartão!");
    digitalWrite(4,HIGH);
    s.write(90);
    delay(2500);
    digitalWrite(4,LOW);
    s.write(0);
  }else{
    Serial.println("Acesso negado.");
    digitalWrite(6,HIGH);
    delay(2500);
    digitalWrite(6,LOW);
  }
}
