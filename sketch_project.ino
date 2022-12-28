
#include <LedControl.h>
#include <SoundSensor.h>
#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>
#include <SoftwareSerial.h>

float leg_angle =0; //다리각도 초기화
float foot_angle= 0; //발 각도 초기화



Servo servo_2;
Servo servo_3;
Servo servo_4;
Servo servo_5; //서보 모터 선언 

#define trig A2 //TRIG 핀 설정 (초음파 보내는 핀)
#define echo A3 //ECHO 핀 설정 (초음파 받는 핀)
//LedControl lc = LedControl(10, 12, 11, 1);

float duration;
float distance;
float distance1;
int BuzzerPin= 13; // 사용할 포트 핀번호  
int num = 8; // 몇개의 음을 사용할 것인지  
int tones[] = {261,293,329,349,391,440,493,523}; // 음계별 주파수  

void _delay(float seconds){
  long endTime = millis() + seconds * 1000;
  while(millis() < endTime)_loop();
}//딜레이 함수 

void _loop() {

}



void forward(){
 while(!(leg_angle > 120)){
  _loop();
  servo_2.write(leg_angle);
  servo_3.write(leg_angle);
  leg_angle += 2;
  _delay(0.03);
}

 while(!(foot_angle < 60)){
  _loop();
  servo_4.write(foot_angle);
  servo_5.write(foot_angle);
  foot_angle += -2;
  _delay(0.03);
}

 while(!(leg_angle < 60)){
  _loop();
  servo_2.write(leg_angle);
  servo_3.write(leg_angle);
  leg_angle -= 2;
  _delay(0.03);
}

 while(!(foot_angle > 120)){
  _loop();
  servo_4.write(foot_angle);
  servo_5.write(foot_angle);
  foot_angle += 2;
  _delay(0.03);
 }
}

void Turn_90(){
  foot_angle=90;
  leg_angle=90;  

  for(int i=0; i<5; i++){
    while(!(leg_angle > 110)){
      _loop();
      servo_2.write(leg_angle);
      servo_3.write(leg_angle);
      leg_angle += 2;
      _delay(0.03);
    }
    while(!(foot_angle > 110)){
      _loop();
      servo_4.write(180-foot_angle);
      servo_5.write(foot_angle);
      foot_angle += 2;
      _delay(0.03);
    }
    while(!(leg_angle < 50)){
      _loop();
      servo_2.write(leg_angle);
      servo_3.write(leg_angle);
      leg_angle += -2;
      //riget_angle -= 2;
      _delay(0.03);
  }

    while(!(foot_angle < 90)){
    _loop();
    servo_4.write(180-foot_angle);
    servo_5.write(foot_angle);
    //leg_angle -= 2;
    foot_angle += -2;
    _delay(0.03);
  }
}

}


void Turn_180(){
  foot_angle=90;
  leg_angle=90;

  for(int i=0; i<9; i++){
    while(!(leg_angle < 50)){
      _loop();
      servo_2.write(leg_angle);
      servo_3.write(leg_angle);
      leg_angle += -2;
      _delay(0.03);
    }
    while(!(foot_angle > 110)){
      _loop();
      servo_4.write(180-foot_angle);
      servo_5.write(foot_angle);
      foot_angle += 2;
      _delay(0.03);
    }
    while(!(leg_angle >110)){
      _loop();
      servo_2.write(leg_angle);
      servo_3.write(leg_angle);
      leg_angle += 2;
      //riget_angle -= 2;
      _delay(0.03);
  }

    while(!(foot_angle < 90)){
    _loop();
    servo_4.write(180-foot_angle);
    servo_5.write(foot_angle);
    //leg_angle -= 2;
    foot_angle += -2;
    _delay(0.03);
  }
}
}




float getDistance() {
  // duration =0;
  // distance =0;
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  duration = pulseIn(echo,HIGH);
  distance = ((float)(340 * duration) / 10000) / 2;
  return distance;
}



void setup() {

  // put your setup code here, to run once:
  servo_2.attach(2);
  servo_3.attach(3);
  servo_4.attach(4);
  servo_5.attach(5); //
  leg_angle = 90;
  foot_angle = 90;

  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);

  Serial.begin(9600); 


//   while(1){

//  }
}

void loop() {
     
    distance = getDistance();
    Serial.print("distance: ");    
    Serial.println(distance);    
    if(distance<10){
      Serial.println("turn90");    
      delay(30);  
      tone(BuzzerPin,tones[2],100);  
      Turn_90();

      distance = getDistance();
      if(distance<10){
        Serial.println("turn180");    
        Turn_180();
      }
    }
    else{
      Serial.println("forward");    
      forward();
    }



}
