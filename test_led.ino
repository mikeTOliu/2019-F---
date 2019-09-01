

#include <Servo.h>

#include<stdlib.h>
#define FIRE 52
#define CHARGE 50
#define s_8 32
#define s_4 34
#define s_2 36
#define s_1 38
#define start 48
#define start1 46
#define toMV 44
Servo myservo;
Servo myservo1;
int val1 = 0;
int oldval;
int val2 = 0;
int oldval2;
int pos = 83;
int pos1 = 89;
int pos2 = 0;
int pos3 = 60;
void setup() {
  // put your setup code here, to run once:
  setup_led();
  Serial.begin(19200);
  //Serial2.begin(19200);

  myservo.attach(8);
  myservo1.attach(9);//上

  myservo.write(pos1);
  myservo1.write(pos);
  pinMode(FIRE, OUTPUT);
  pinMode(CHARGE, OUTPUT);
  pinMode(toMV, OUTPUT);
  pinMode(s_8, INPUT);
  pinMode(s_4, INPUT);
  pinMode(s_2, INPUT);
  pinMode(s_1, INPUT);
  pinMode(start, INPUT);
  pinMode(start1, INPUT);
  digitalWrite(FIRE, LOW);
  digitalWrite(CHARGE, LOW);
  digitalWrite(toMV, LOW);

}
void jd() {
  if (val1 >= 200 && val1 <= 205) {
    fire(12);
  }
  if (val1 >= 206 && val1 <= 215) {
    fire(13);
  }
  if (val1 >= 216 && val1 <= 225) {
    fire(15);
  }
  if (val1 >= 226 && val1 <= 235) {
    fire(16);
  }
  if (val1 >= 236 && val1 <= 245) {
    fire(18);
  }
  if (val1 >= 246 && val1 <= 255) {
    fire(19);
  }
  if (val1 >= 256 && val1 <= 265) {
    fire(20);
  }
  if (val1 >= 266 && val1 <= 275) {
    fire(23);
  }
  if (val1 >= 276 && val1 <= 285) {
    fire(27);
  }
  if (val1 >= 286 && val1 <= 295) {
    fire(28);
  }
  if (val1 >= 296 && val1 <= 300) {
    fire(30);
  }
}
void d_input() {
  if (digitalRead(s_8) == 0 && digitalRead(s_4) == 0 && digitalRead(s_2) == 0 && digitalRead(s_1) == 1) {
    val1 = 200;  //1
    jd();
    Serial.println(1);
  }
  if (digitalRead(s_8) == 0 && digitalRead(s_4) == 0 && digitalRead(s_2) == 1 && digitalRead(s_1) == 0) {
    val1 = 210;  //2
    jd();
    Serial.println(2);
  }
  if (digitalRead(s_8) == 0 && digitalRead(s_4) == 0 && digitalRead(s_2) == 1 && digitalRead(s_1) == 1) {
    val1 = 220;  //3
    jd();
    Serial.println(3);
  }
  if (digitalRead(s_8) == 0 && digitalRead(s_4) == 1 && digitalRead(s_2) == 0 && digitalRead(s_1) == 0) {
    val1 = 230;  //4
    jd();
    Serial.println(4);
  }
  if (digitalRead(s_8) == 0 && digitalRead(s_4) == 1 && digitalRead(s_2) == 0 && digitalRead(s_1) == 1) {
    val1 = 240;  //5
    jd();
    Serial.println(5);
  }
  if (digitalRead(s_8) == 0 && digitalRead(s_4) == 1 && digitalRead(s_2) == 1 && digitalRead(s_1) == 0) {
    val1 = 250;  //6
    jd();
    Serial.println(6);
  }
  if (digitalRead(s_8) == 0 && digitalRead(s_4) == 1 && digitalRead(s_2) == 1 && digitalRead(s_1) == 1) {
    val1 = 260;  //7
    jd();
    Serial.println(7);
  }
  if (digitalRead(s_8) == 1 && digitalRead(s_4) == 0 && digitalRead(s_2) == 0 && digitalRead(s_1) == 0) {
    val1 = 270;  //8
    jd();
    Serial.println(8);
  }
  if (digitalRead(s_8) == 1 && digitalRead(s_4) == 0 && digitalRead(s_2) == 0 && digitalRead(s_1) == 1) {
    val1 = 280;  //9
    jd();
    Serial.println(9);
  }
  if (digitalRead(s_8) == 1 && digitalRead(s_4) == 0 && digitalRead(s_2) == 1 && digitalRead(s_1) == 0) {
    val1 = 290;  //10
    jd();
    Serial.println(10);
  }
  if (digitalRead(s_8) == 1 && digitalRead(s_4) == 0 && digitalRead(s_2) == 1 && digitalRead(s_1) == 1) {
    val1 = 300;  //11
    jd();
    Serial.println(11);
  }
}
void fire(int yj) {
  myservo1.write(pos - yj);
  delay(300);
  if (val2 >= 60) {
    myservo.write(val2);
    Serial.println(val2);
  }

  // myservo.write(pos1);
  delay(100);
  digitalWrite(CHARGE, HIGH);
  delay(5000);//5000
  digitalWrite(CHARGE, LOW);
  delay(100);
  digitalWrite(FIRE, HIGH);
  delay(100);
  digitalWrite(FIRE, LOW);
}
int n = 0;
int k = 0;
int f = 0;
void loop() {
  if (digitalRead(start) != LOW) {
    delay(100);
    d_input();
  }

  if (digitalRead(start1) != LOW) {
    delay(5);
    pos3 += 1;
    if (digitalRead(s_8) == 1 && digitalRead(s_4) == 1 && digitalRead(s_2) == 1 && digitalRead(s_1) == 1) {
      val2 = pos3;
    }
    myservo.write(pos3);
    delay(20);
    if (pos3 >= 120) {
      pos3 = 60;
      n++;
    }
    if (val2 != 0 && k == 0) {
      digitalWrite(CHARGE, HIGH);/////////////////
      Serial.println(val2);
      delay(10);
      k = 1;
    }

    if (n == 3) {
      // n = 0;
      delay(10);
      if (pos3 == val2 && f == 0) {
        myservo1.write(70);
        delay(200);
        digitalWrite(CHARGE, LOW);////////////////
        delay(100);
        digitalWrite(FIRE, HIGH);
        delay(10);
        //Serial.println(val2);
        digitalWrite(FIRE, LOW);
        f = 1;

      }
    }
  }
  oldval = val1;
  oldval2 = val2;
  loop_led_4(&val1, &val2);

  if (oldval != val1 || oldval2 != val2) {
    Serial.println(val1);
    Serial.println(val2);
  }
  delay(2);
  if (7 == Read_key()) {
    delay(2);
    jd();
  }
}
