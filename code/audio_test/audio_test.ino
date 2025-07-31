#define play_pause 18
#define previous 17
#define next 23

int wat = 175;

void setup() {
  // put your setup code here, to run once:
  pinMode(play_pause, OUTPUT);
  pinMode(next, OUTPUT);
  pinMode(previous, OUTPUT);
  Serial.begin(115200);
  }

void loop() {
  // put your main code here, to run repeatedly:

    Serial.println("next");
    digitalWrite(next, LOW);
    delay(100);
    digitalWrite(next, HIGH);
    delay(100);
    digitalWrite(next, LOW);
    delay(10000);
    digitalWrite(next, HIGH);
    Serial.println("previous");
    digitalWrite(previous, LOW);
    delay(10000);
    digitalWrite(next, HIGH);
    delay(1000);

}
