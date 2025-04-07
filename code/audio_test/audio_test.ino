#define play_pause 18
#define previous 19
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

    delay(3000);
    digitalWrite(previous, HIGH);
    delay(100);
    digitalWrite(previous, LOW); 
    Serial.println("previous");
    delay(3000);
    digitalWrite(previous, HIGH);
    delay(100);
    digitalWrite(previous, LOW); 
    Serial.println("previous");
    delay(3000);
    digitalWrite(previous, HIGH);
    delay(100);
    digitalWrite(previous, LOW); 
    Serial.println("previous");
    delay(3000);
    digitalWrite(next, HIGH);
    delay(100);
    digitalWrite(next, LOW); 
    Serial.println("next");
    delay(3000);
    digitalWrite(next, HIGH);
    delay(100);
    digitalWrite(next, LOW); 
    Serial.println("next");
    delay(3000);
    digitalWrite(next, HIGH);
    delay(100);
    digitalWrite(next, LOW); 
    Serial.println("next");
    delay(3000);
  

}
