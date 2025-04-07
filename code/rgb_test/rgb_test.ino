#define red 27
#define blue 32
#define green 33

long light_flash_time = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  light_flash_time += 250;
  light_flash_time = light_flash_time % 20000;
  if ((light_flash_time / 1000 % 2 == 0) && light_flash_time < 10000) {
    analogWrite(red, 0);
    analogWrite(blue, 255);
    analogWrite(green, 0);
  }
  else {
    analogWrite(red, 255);
    analogWrite(blue, 0);
    analogWrite(green, 255);
  }
  delay(250);
  if (light_flash_time > 10000 && light_flash_time < 15000) {
    analogWrite(red, 255);
    analogWrite(blue, 0);
    analogWrite(green, 0);
    delay(5000);
    light_flash_time += 5000;
  }
  else if (light_flash_time > 15000) {
    analogWrite(red, 0);
    analogWrite(blue, 0);
    analogWrite(green, 255);
    delay(5000);
    light_flash_time += 5000;
  }
}
