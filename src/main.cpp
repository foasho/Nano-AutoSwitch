#include <Arduino.h>
#include <Servo.h>

#define BANDRATE 9600
Servo servo;
#define onDegree 40
#define offDegree 0
float val;
bool isOn = false;
int waitCounter = 0;
#define offWaitNum 30

float getValue(int n){
    int val_int = 0;
    for (int i=0; i <= n; i++){
      val_int = val_int + analogRead(A0);
      delay(10);
   }
   return val_int / n;
}

void setup() {
    Serial.begin(BANDRATE);
    servo.attach(6);// D6に繋げる
    pinMode(A0, INPUT);
}

void loop() {
    val = getValue(10);
    Serial.println(val);
    if (val > 700 && !isOn){ // ON
        servo.write(onDegree);
        isOn = true;
        waitCounter = 0;
    }
    else {// OFF
        delay(200);//回転のため0.4秒待つ
        if (isOn && waitCounter < offWaitNum){
            waitCounter++;
        }
        else {
            servo.write(offDegree);
            isOn = false;
        }
    }
    delay(200);
}