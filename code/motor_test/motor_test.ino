#define motor_ground_1 12
#define motor_power_1 13
#define motor_ground_2 14
#define motor_power_2 15
#define EN_A 16
#define EN_B 17

void setup() {
  // put your setup code here, to run once:
  pinMode(motor_ground_1, OUTPUT);
  pinMode(motor_power_1, OUTPUT);
  pinMode(motor_ground_2, OUTPUT);
  pinMode(motor_power_2, OUTPUT);
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(EN_A, 96);
  analogWrite(EN_B, 96);
  digitalWrite(motor_ground_1, LOW);
  digitalWrite(motor_power_1, HIGH);
  digitalWrite(motor_ground_2, LOW);
  digitalWrite(motor_power_2, HIGH);
}
