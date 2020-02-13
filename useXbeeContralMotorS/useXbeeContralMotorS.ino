#define Add 3
#define Reduce 4
int Flag = 0;
void setup() {
  Serial.begin(9600);
  pinMode(Add, INPUT);
  pinMode(Reduce, INPUT);
}

void loop() {

  if (digitalRead(Add))
  {
    delay(300);
    Flag = Flag + 1;
    SendMassage();
  }
  else if (digitalRead(Reduce))
  {
    delay(300);
    if (Flag == 0) ;
    else Flag = Flag - 1;
    SendMassage();
  }

}

void SendMassage()
{
  switch (Flag)
  { case 0: Serial.print('S'); break;
    case 1: Serial.print('1'); break;
    case 2: Serial.print('2'); break;
    case 3: Serial.print('3'); break;
    default: Flag = 3; break;
  }
}
