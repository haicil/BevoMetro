#include "sdkconfig.h"
#include <QTRSensors.h>
#include <NewPing.h>
#include "DFRobotDFPlayerMini.h"

#define motor_ground_1 14
#define motor_power_1 15
#define motor_ground_2 12
#define motor_power_2 13
#define EN_A 18
#define EN_B 19
#define red 27
#define blue 32
#define green 33
#define RXD2 16
#define TXD2 17

NewPing sonar_1(5, 25, 200);
NewPing sonar_2(4, 26, 200);
QTRSensors qtr;
uint16_t sensors[4];
DFRobotDFPlayerMini myDFPlayer;

int ping_1 = 0;
int ping_2 = 0;
int light_flash_time = 0;
// int next_stop = 1; // Jester Circle, 21st St, 23rd St, Dean Keeton St, 24th St, 22nd St
int stop_time = 0;
int status = 0;
bool playing_audio = false;
int current_audio_num = 0;
int min_black_val = 40;
int max_white_val = 40;
bool super_left = false;
bool super_right = false;
int left_turn = 0;
int right_turn = 1;
int count = 0;
int supTurnDelay = 0;
//motor power
int power = 255;
int partialPower = -power;
int superPow = -power;
int buffer = 0;
String line;
char command;
int pause = 0;
int repeat = 0;


void rightMotor(int speed){
    if(speed >= 0){
        if (speed > 255){
        speed = 255;
        }
        digitalWrite(motor_ground_1, LOW);
        digitalWrite(motor_power_1, HIGH);
    }
    else if(speed < 0){
    speed = speed*(-1);
        if (speed > 255){
        speed = 255;
        }
        digitalWrite(motor_ground_1, HIGH);
        digitalWrite(motor_power_1, LOW);
    }
    analogWrite(EN_A, speed);
    //Serial.print("Right Motor :: ");
    //Serial.println(speed);
}
//ENB
void leftMotor(int speed){
    
    if(speed >= 0){
        if (speed > 255){
        speed = 255;
        }
        digitalWrite(motor_ground_2, LOW);
        digitalWrite(motor_power_2, HIGH);
    }
    else if(speed < 0){
        speed = speed*(-1);
        if (speed > 255){
        speed = 255;
        }
        digitalWrite(motor_ground_2, HIGH);
        digitalWrite(motor_power_2, LOW);
    }
    analogWrite(EN_B, speed);
    //Serial.print("Left Motor :: ");
    //Serial.println(speed);
}
//movement controls
void forward(){
    // Serial.println("Move forward");
    leftMotor((power*10)/10);
    rightMotor((power*10)/10);
}
void leftShift(){
    // Serial.println("Left shift");
    leftMotor(power);
    rightMotor(partialPower);
}
void rightShift(){
    // Serial.println("Right shift");
    leftMotor(partialPower);
    rightMotor(power);
}
void superTurn(int turnSide){
    if(turnSide == left_turn) // left turn
    {
        // Serial.println("Super Left");
        rightMotor((superPow*8)/10);
        leftMotor((power*8)/10);
        delay(supTurnDelay);
        light_flash_time += supTurnDelay;
    }
    if(turnSide == right_turn) // right turn
    {
        Serial.println("Super Right");
        leftMotor((superPow*8)/10);
        rightMotor((power*8)/10);
        delay(supTurnDelay);
        light_flash_time += supTurnDelay;
    }

}

void stop() {
  rightMotor(0);
  leftMotor(0);
}


void drive() {
  int16_t position = qtr.readLineBlack(sensors);
  qtr.readLineBlack(sensors); // Get calibrated sensor values returned in the sensors array
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

  // if(sensors[0] > min_black_val && !super_right){
  //   super_left = true;
  // }
  // if(sensors[3] > min_black_val  && !super_left){
  //   super_right = true;
  // }
  // if(super_right || super_left)
  // {
  //   if(super_right){
  //     superTurn(right_turn);
  //     // if(digitalRead(line_reader) == 1) {
  //     //   super_right = false;
  //     // }
  //     if(super_left){
  //       superTurn(left_turn);
  //       // if(digitalRead(line_reader) == 1) {
  //       //   super_left = false;
  //       // }
  //     }
  //   }

    if(sensors[1] < max_white_val && sensors[2] < max_white_val){
        forward();
    }
    else if(sensors[1] > min_black_val){
        leftShift();
    }
    else if(sensors[2] > min_black_val){
        rightShift();
    }
}

void senseSonar() {
  if (ping_1 < 10 && ping_1 != 0) {
    if (status != 1) {
      playing_audio = false;
    }
    status = 1;
  }
  else if ((status == 2 || (ping_2 < 10 && ping_2 != 0)) && stop_time < 6000) {
    if (status != 2) {
      playing_audio = false;
      current_audio_num = (current_audio_num + 1) % 3;
      if (current_audio_num == 0) {
        current_audio_num++;
      }
    }
    status = 2;
  }
  else {
    else if (status == 2) {
      buffer = true;
    }
    if (stop_time == 8000) {
      stop_time = 0;
      buffer = false;
    }
    if (buffer) {
      stop_time += 10;
    }
    status = 0;
  }
}

void moveFlash() {
  light_flash_time += 10;
  light_flash_time = light_flash_time % 100000;
  if (light_flash_time / 1000 % 2 == 0) {
    analogWrite(red, 0);
    analogWrite(blue, 255);
    analogWrite(green, 0);
  }
  else {
    analogWrite(red, 255);
    analogWrite(blue, 0);
    analogWrite(green, 69);
  }
}

// void changeAudio(int new_audio) {
//   audio_change = new_audio - current_audio_num;
//   if (audio_change > 0) {
//     for (int i = 0; i < audio_change; i++) {
//       digitalWrite(next, HIGH);
//       delay(100);
//       digitalWrite(next, LOW);
//       Serial.println("next");
//       if (status == 2) {
//         stop_time += 100;
//       }
//     }
//   }
//   else if (audio_change < 0) {
//     for (int i = 0; i < (-1) * audio_change; i++) {
//       digitalWrite(previous, HIGH);
//       delay(100);
//       digitalWrite(previous, LOW);
//       Serial.println("previous");
//       if (status == 2) {
//         stop_time += 100;
//       }
//     }
//   }
//   else {
//     digitalWrite(play_pause, HIGH);
//     delay(100);
//     digitalWrite(play_pause, LOW);
//     if (status == 2) {
//       next_stop++;
//       stop_time += 100;
//     }
//   }
  
// }

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
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]) {36, 39, 34, 35}, 4); 
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.begin(115200);
  if (!myDFPlayer.begin(Serial2)) {// Start communication with DFPlayer
  // myDFPlayer.begin(Serial1, true, false); // Start communication with DFPlayer
    Serial.println("ERROR");
  }
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  delay(1000); // Add this to allow player to fully initialise

  myDFPlayer.volume(15);  //Set volume value. From 0 to 30

  Serial.println("setup ended"); // I like this reassurance
  delay(5000);
  analogWrite(red, 255);
  analogWrite(blue, 255);
  analogWrite(green, 255);
  for (uint8_t i = 0; i < 250; i++) {
    delay(20); 
        Serial.println("calibrating");
        qtr.calibrate();
        rightMotor(power);
        leftMotor(-power);
        /*if(digitalRead(lineReader) == 1) {
            count++;
          }
        if(count%2 == 0) {
            superTurn(leftTurn);
        {
          */
}
analogWrite(red, 0);
analogWrite(blue, 0);
analogWrite(green, 255);
stop();
delay(2000);
}

void loop()
{
  ping_1 = sonar_1.ping_cm();
  ping_2 = sonar_2.ping_cm();
  delayMicroseconds(10);
  //Serial.print("ping 1 ");
  //Serial.println(ping_1);
  //Serial.print("ping 2 ");
  //Serial.println(ping_2);
  senseSonar();
  switch (status) {
    case 1:
      //Serial.println("blocked");
      stop();
      analogWrite(red, 255);
      analogWrite(blue, 0);
      analogWrite(green, 0);
      if (!playing_audio) {
        myDFPlayer.play(3);
        myDFPlayer.enableLoop();
        Serial.println("blocked audio playing");
        playing_audio = true;
      }
      delay(500);
      break;
    case 2:
      //Serial.println("stopped");
      //Serial.println(buffer);
      stop();
      analogWrite(red, 0);
      analogWrite(blue, 0);
      analogWrite(green, 255);
      if (!playing_audio) {
        myDFPlayer.play(current_audio_num);
        Serial.println("stopped audio playing");
        playing_audio = true;
      }
      stop_time += 10;
      break;
    default:
      myDFPlayer.pause();
      myDFPlayer.disableLoop();
      drive();
      moveFlash();
      break;
  }
  Serial.println(status);
  Serial.println(stop_time);
}
