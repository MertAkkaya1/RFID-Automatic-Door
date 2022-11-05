
/*
  Bu proje mifare kart kullanarak kapı açma amacıyla yapılmıştır.

  RC522 Connection

  SDA 10
  SCK 13
  MOSI 11
  MISO 12
  RST 9

*/
#include <MFRC522.h>
#include <SPI.h>
//#include<Servo.h>

#define RST_PIN 9
#define SS_PIN 10
//#define ServoPin 3

//Servo servoMotor;
MFRC522 mfrc522(SS_PIN, RST_PIN); 
byte ID1[4] = {0x85, 0x28, 0x34, 0x119};
byte ID2[4] = {0x0A, 0x30, 0x16, 0xCB};

void setup() {
  //servoMotor.attach(ServoPin);
  Serial.begin(9600);
  while (!Serial);
  SPI.begin();
  mfrc522.PCD_Init();
  delay(4);
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    // okutulan karttan baska yeni bir kart gelmediginde yeni kartin okutulmasini bekliyoruz.
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) {
    // Herhangi bir kart okutulmadiginda bekliyoruz.
    //kart okuttugumuzda mfrc522.PICC_ReadCardSerial() 1 olacak bunu tersledigimiz icin bu deger 0 olacak ve if icine girmicek ve bekleme islemini yapmicak
    return;
  }

  if ( (mfrc522.uid.uidByte[0] == ID1[0] &&
        mfrc522.uid.uidByte[1] == ID1[1] &&
        mfrc522.uid.uidByte[2] == ID1[2] &&
        mfrc522.uid.uidByte[3] == ID1[3])||
        mfrc522.uid.uidByte[0] == ID2[0] &&
        mfrc522.uid.uidByte[1] == ID2[1] &&
        mfrc522.uid.uidByte[2] == ID2[2] &&
        mfrc522.uid.uidByte[3] == ID2[3]){
    Serial.println("Kapi Acildi");
    ekranaYazdir();
    /*
      ServoMotor.write(180);
      delay(5000);
      ServoMotor.write(0);
      delay(1000);*/
  }
  else {
    Serial.println("Yetkisiz Kart");
    ekranaYazdir();
  }
  mfrc522.PICC_HaltA();
}

void ekranaYazdir() {
  Serial.print("ID Numarasi: ");

  for (int i = 0; i < 4; i++) {
    Serial.print(mfrc522.uid.uidByte[i]);
    Serial.print(" ");
  }
  Serial.println("");
}
