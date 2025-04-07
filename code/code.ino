#include "sdkconfig.h"
#include <QTRSensors.h>
#include <NewPing.h>

#define motor_ground_1 12
#define motor_power_1 13
#define motor_ground_2 14
#define motor_power_2 15
#define EN_A 16
#define EN_B 17
#define red 27
#define blue 32
#define green 33
#define play_pause 18
#define next 23
#define previous 19

NewPing sonar_1(5, 25, 200);
NewPing sonar_2(4, 26, 200);
QTRSensors qtr;
uint16_t sensors[4];

int ping_1 = 0;
int ping_2 = 0;
int light_flash_time = 0;
int next_stop = 1; // Jester Circle, 21st St, 23rd St, Dean Keeton St, 24th St, 22nd St
int stop_time = 0;
int status = 0;
long audio_time = 0;
bool playing_audio = false;
int current_audio_num = 0;
int audio_change = 0;
int min_black_val = 40;
int max_white_val = 40;
bool super_left = false;
bool super_right = false;
bool repeat_audio = false;
int count = 0;

void stop() {
  digitalWrite(motor_ground_1, LOW);
  digitalWrite(motor_power_1, LOW);
  digitalWrite(motor_ground_2, LOW);
  digitalWrite(motor_power_2, LOW);
}

void drive() {
  // int16_t position = qtr.readLineBlack(sensors);
  // qtr.readLineBlack(sensors); // Get calibrated sensor values returned in the sensors array
  // Serial.print(sensors[0]);
  // Serial.print(" | ");
  // Serial.print(sensors[1]);
  // Serial.print(" | ");
  // Serial.print(sensors[2]);
  // Serial.print(" | ");
  // Serial.print(sensors[3]);
  // Serial.print(" | ");
  // Serial.print("SLeft: ");
  // Serial.print(super_left);
  // Serial.print(" | ");
  // Serial.print("SRight: ");
  // Serial.print(super_right);
  // Serial.print(" | ");
  // Serial.print("liner: ");
  // Serial.println(digitalRead(line_reader));

  if(sensors[0] > min_black_val && !super_right){
    super_left = true;
  }
  if(sensors[3] > min_black_val  && !super_left){
    super_right = true;
  }
  if(super_right || super_left)
  {
    if(super_right){
      analogWrite(EN_A, 96);
      analogWrite(EN_B, 96);
      digitalWrite(motor_ground_1, LOW);
      digitalWrite(motor_power_1, HIGH);
      digitalWrite(motor_ground_2, HIGH);
      digitalWrite(motor_power_2, LOW);
      // if(digitalRead(line_reader) == 1) {
      //   super_right = false;
      // }
      if(super_left){
        analogWrite(EN_A, 96);
        analogWrite(EN_B, 96);
        digitalWrite(motor_ground_1, HIGH);
        digitalWrite(motor_power_1, LOW);
        digitalWrite(motor_ground_2, LOW);
        digitalWrite(motor_power_2, HIGH);
        // if(digitalRead(line_reader) == 1) {
        //   super_left = false;
        // }
      }
    }
    if((sensors[1] < max_white_val && sensors[2] < max_white_val)&&(!super_left && !super_right)){
        analogWrite(EN_A, 96);
        analogWrite(EN_B, 96);
        digitalWrite(motor_ground_1, LOW);
        digitalWrite(motor_power_1, HIGH);
        digitalWrite(motor_ground_2, LOW);
        digitalWrite(motor_power_2, HIGH);
    }
    else if((sensors[1] > min_black_val) && (!super_left && !super_right)){
        analogWrite(EN_A, 96);
        analogWrite(EN_B, 0);
        digitalWrite(motor_ground_1, LOW);
        digitalWrite(motor_power_1, HIGH);
        digitalWrite(motor_ground_2, LOW);
        digitalWrite(motor_power_2, LOW);
    }
    else if((sensors[2] > min_black_val) && (!super_left && !super_right)){
        analogWrite(EN_A, 0);
        analogWrite(EN_B, 96);
        digitalWrite(motor_ground_1, LOW);
        digitalWrite(motor_power_1, LOW);
        digitalWrite(motor_ground_2, LOW);
        digitalWrite(motor_power_2, HIGH);
    }
  }
}

void senseSonar() {
  if (ping_1 < 20 && ping_1 != 0) {
    if (status != 1) {
      playing_audio = false;
    }
    status = 1;
  }
  else if ((status == 2 && stop_time < 10000) || (ping_2 < 20 && ping_2 != 0)) {
    if (status != 2) {
      playing_audio = false;
    }
    status = 2;
  }
  else {
    if (status == 1 || status == 2) {
      Serial.println("pause");
      digitalWrite(play_pause, HIGH);
      delay(100);
      digitalWrite(play_pause, LOW);
    }
    status = 0;
    stop_time = 0;
  }
}

void moveFlash() {
  light_flash_time += 250;
  light_flash_time = light_flash_time % 100000;
  if (light_flash_time / 1000 % 2 == 0) {
    analogWrite(red, 0);
    analogWrite(blue, 255);
    analogWrite(green, 0);
  }
  else {
    analogWrite(red, 255);
    analogWrite(blue, 0);
    analogWrite(green, 165);
  }
}

void changeAudio(int new_audio) {
  audio_change = new_audio - current_audio_num;
  if (audio_change > 0) {
    for (int i = 0; i < audio_change; i++) {
      digitalWrite(next, HIGH);
      delay(100);
      digitalWrite(next, LOW);
      Serial.println("next");
      if (status == 2) {
        stop_time += 100;
      }
    }
  }
  else if (audio_change < 0) {
    for (int i = 0; i < (-1) * audio_change; i++) {
      digitalWrite(previous, HIGH);
      delay(100);
      digitalWrite(previous, LOW);
      Serial.println("previous");
      if (status == 2) {
        stop_time += 100;
      }
    }
  }
  else {
    digitalWrite(play_pause, HIGH);
    delay(100);
    digitalWrite(play_pause, LOW);
    if (status == 2) {
      next_stop++;
      stop_time += 100;
    }
  }
  
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(motor_ground_1, OUTPUT);
  pinMode(motor_power_1, OUTPUT);
  pinMode(motor_ground_2, OUTPUT);
  pinMode(motor_power_2, OUTPUT);
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(play_pause, OUTPUT);
  pinMode(next, OUTPUT);
  pinMode(previous, OUTPUT);
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]) {36, 39, 34, 35}, 4); 
  Serial.begin(115200);
  digitalWrite(play_pause, HIGH);
  delay(100);
  digitalWrite(play_pause, LOW);
  delay(5000);
  analogWrite(EN_A, 96);
  analogWrite(EN_B, 96);
  digitalWrite(motor_ground_1, HIGH);
  digitalWrite(motor_power_1, LOW);
  digitalWrite(motor_ground_2, LOW);
  digitalWrite(motor_power_2, HIGH);
  for (uint8_t i = 0; i < 250; i++) {
    delay(20); 
    Serial.println("calibrating");
    qtr.calibrate();
    // if(digitalRead(line_reader) == 1) {
    //   count++;
    //   if(count % 2 == 0) {
    //     digitalWrite(motor_ground_1, HIGH);
    //     digitalWrite(motor_power_1, LOW);
    //     analogWrite(EN_A, 96);
    //     digitalWrite(motor_ground_2, LOW);
    //     digitalWrite(motor_power_2, HIGH);
    //     analogWrite(EN_B, 96);
    //   }
    //   else {
    //     digitalWrite(motor_ground_1, LOW);
    //     digitalWrite(motor_power_1, HIGH);
    //     analogWrite(EN_A, 96);
    //     digitalWrite(motor_ground_2, HIGH);
    //     digitalWrite(motor_power_2, LOW);
    //     analogWrite(EN_B, 96);
    //   }
    // }
  }
  stop();
}

void loop()
{
  ping_1 = sonar_1.ping_cm();
  ping_2 = sonar_2.ping_cm();
  delayMicroseconds(10);
  Serial.print("ping 1 ");
  Serial.println(ping_1);
  Serial.print("ping 2 ");
  Serial.println(ping_2);
  senseSonar();
  switch (status) {
    case 1:
      Serial.println("blocked");
      stop();
      analogWrite(red, 255);
      analogWrite(blue, 0);
      analogWrite(green, 0);
      if (!playing_audio) {
        audio_time = 0;
        Serial.println("blocked audio playing");
        changeAudio(2);
        current_audio_num = 2;
        playing_audio = true;
      }
      break;
    case 2:
      Serial.println("stopped");
      if (stop_time < 10000) {
        stop();
      }
      else {
        drive();
      }
      analogWrite(red, 0);
      analogWrite(blue, 0);
      analogWrite(green, 255);
      if (!playing_audio) {
        changeAudio(next_stop);
        Serial.println("stopped audio playing");
        current_audio_num = next_stop;
        playing_audio = true;
      }
      stop_time += 250;
      break;
    default:
      drive();
      moveFlash();
      break;
  }
  Serial.println(status);
  Serial.println(stop_time);
  delay(250);
}
