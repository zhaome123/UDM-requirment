#define AIN1 3
#define AIN2 4
#define PWMA 5
int Speed;
char receive;
void setup() {
  Serial.begin(9600);
  pinMode(PWMA, OUTPUT);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
}

void loop() {
  while (Serial.available() <= 0) ;
  if (Serial.available() > 0)
  {
    receive = Serial.read();
    switch (receive)
    { case 'S': Speed = 1; break;
      case '1': Speed = 60; break;
      case '2': Speed = 80; break;
      case '3': Speed = 100; break;
      default: Speed = 1; break;
    }
    Serial.println(Speed);
    analogWrite(PWMA, Speed);
    delay(1000);
  }
}
