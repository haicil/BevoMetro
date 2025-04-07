#include <QTRSensors.h>

QTRSensors qtr;
uint16_t sensors[4];

void setup() {
  // put your setup code here, to run once:
  qtr.setTypeAnalog();
  qtr.setSensorPins((const uint8_t[]) {36, 39, 34, 35}, 4);
  qtr.calibrate();
  Serial.begin(115200);
  }

void loop() {
  // put your main code here, to run repeatedly:
  int16_t position = qtr.readLineBlack(sensors);
  qtr.readLineBlack(sensors); // Get calibrated sensor values returned in the sensors array
  Serial.print(sensors[0]);
  Serial.print(" | ");
  Serial.print(sensors[1]);
  Serial.print(" | ");
  Serial.print(sensors[2]);
  Serial.print(" | ");
  Serial.println(sensors[3]);
}