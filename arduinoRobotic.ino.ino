#include <SoftwareSerial.h>         // Yazılımsal Seri Port kütüphanesi

int RX = 1;                         // Yazılımsal Seri Port'un RX pini
int TX = 0;                         // Yazılımsal Seri Port'un TX pini

SoftwareSerial bluetooth(RX,TX);    // Kütüphanemizi ayarlıyoruz

// Motor pinlerini tanımla
int motor1A = 5; // IN1
int motor1B = 4; // IN2
int motor2A = 3; // IN3
int motor2B = 2; // IN4

char data; // Bluetooth'dan gelen veriyi saklamak için

void setup() {
  // Motor pinlerini çıkış olarak ayarla
  if (bluetooth.available()){       // HC-06'dan gelen veri Seri Port Ekranı'na
    Serial.write(bluetooth.read()); // yazılıyor
  }

  if (Serial.available()){          // Seri Port Ekranı'ndan gelen veri HC-06'ya
    bluetooth.write(Serial.read()); // gönderiliyor
  }
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  bluetooth.begin(9600); 
  // Bluetooth modülünü başlat
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    data = Serial.read(); // Bluetooth üzerinden gelen veriyi oku
    
    // Gelen verilere göre motorları kontrol et
    switch(data){
      case 'F':
        digitalWrite(motor1A, HIGH);
        digitalWrite(motor1B, LOW);
        digitalWrite(motor2A, HIGH);
        digitalWrite(motor2B, LOW);
        break;
        //İLERİ
      case 'B':
        digitalWrite(motor1A, LOW);
        digitalWrite(motor1B, HIGH);
        digitalWrite(motor2A, LOW);
        digitalWrite(motor2B, HIGH);
        break;
        //GERİ
      case 'L':
        digitalWrite(motor1A, LOW);
        digitalWrite(motor1B, HIGH);
        digitalWrite(motor2A, HIGH);
        digitalWrite(motor2B, LOW);
        break;
        //SOLA
      case 'R':
        digitalWrite(motor1A, HIGH);
        digitalWrite(motor1B, LOW);
        digitalWrite(motor2A, LOW);
        digitalWrite(motor2B, HIGH);
        break;
        //SAĞA
      case 'S':
        digitalWrite(motor1A, LOW);
        digitalWrite(motor1B, LOW);
        digitalWrite(motor2A, LOW);
        digitalWrite(motor2B, LOW);
        break;
        //DURDUR
    }  
        
  } else{
    digitalWrite(motor1A, LOW);
    digitalWrite(motor1B, LOW);
    digitalWrite(motor2A, LOW);
    digitalWrite(motor2B, LOW);
  }
  Serial.println(data);
}
