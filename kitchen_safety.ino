#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define DHTPIN 2 
#define DHTTYPE DHT11
#define MQ2pin (0)
float gasSensor;
int enB=7;
int in3=5;
int in4=6;
float mq7;
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);


//pir


void setup() {
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  dht.begin();
  lcd.begin();
  lcd.backlight();
  // put your setup code here, to run once:
}
void loop() {
  // put your main code here, to run repeatedly:
  nofan();
  gasSensor= analogRead(MQ2pin);
  mq7 = analogRead(1);
  float h=dht.readHumidity();
  float t=dht.readTemperature();
  lcd.setCursor(0,0);
  //lcd.print(h);
  //lcd.print("%;");

  if(h<40 || h>65){
    if(h<40){
      lcd.print("dry!");
      }else{
        lcd.print("humid!");
        }
    }else{
      lcd.print(h);
      lcd.print("%;");
      }
  if(t>35){
    lcd.print("too hot!");
    fan();
    }else{
      nofan();
      lcd.print(" t:");
      lcd.print(t);
      lcd.print("'C");
      }
 

  
  lcd.setCursor(0,1);
  //lcd.print("G2:");
  //lcd.print(gasSensor);
  //lcd.print(";G7:");
  //lcd.print(mq7);
  gasSensor=gasSensor-100;
  if(gasSensor<350){
    if(gasSensor>250){
      fan();
      lcd.print("check gas!");
      tone(9, 1000);
      delay(1000);        
      noTone(9);     
      }else if(gasSensor>140){
        lcd.print("               ");
        fan();
        }else{
          lcd.print("               ");
          nofan();
          }
    }else{
      fan();
      lcd.print("Gas leaking!!");
      tone(9, 1500);
      delay(500);        
      noTone(9); 
      lcd.clear();   
      
      }

if(mq7<400){
  if(mq7>95 && mq7<150){
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Toxic CO !");
  tone(9, 200);
  delay(1500);        
  noTone(9); 
  lcd.clear();
  }else{
    noTone(9);
    lcd.print("               ");
    }
  }
  

//pir




      
  //delay(500);
  //lcd.clear();
  //delay(500);
}



void fan(){
  digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }

 void nofan(){
  analogWrite(enB, 255);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
  }

  }

