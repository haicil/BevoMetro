#define previous 23

void setup() {
  // put your setup code here, to run once:
  pinMode(previous, OUTPUT);
  digitalWrite(previous, LOW);
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(previous, HIGH);`
}
