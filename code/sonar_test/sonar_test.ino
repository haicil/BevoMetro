#include <NewPing.h>

NewPing sonar_1(5, 25, 200);
NewPing sonar_2(4, 26, 200);

long ping_1 = 0;
long ping_2 = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  ping_1 = sonar_1.ping_cm();
  ping_2 = sonar_2.ping_cm();
  delayMicroseconds(10);
  Serial.println(ping_1);
  Serial.println(ping_2);
  if (ping_1 < 4) {
    Serial.println("bruh");
  }
  if (ping_2 < 4) {
    Serial.println("bruh x2");
  }
}

