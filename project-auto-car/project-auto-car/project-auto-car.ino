#include <Pixy2.h>
#include <math.h>
Pixy2 pixy;
#define AIN1 2
#define AIN2 3
#define BIN1 6
#define BIN2 7
#define PWMA 4
#define PWMB 5
#define A A0
int s1 = 59, s2 = 42;
int  Mx, mx1, mx2, my1, my2, Area1, Area2, w1, w2, h1, h2, D, countTurn = 0, Di, vector, Speed1, Speed2, countRefind = 0;
boolean Flag = 0;
void setup()
{
  Serial.begin(115200);
  Serial.print("Starting...\n");
  pixy.init();

  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(A, INPUT);

  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);

  analogWrite(PWMA, 1);
  analogWrite(PWMB, 1);
  //  speedControl('G');

  //pixy.changeProg("color");
  //-----------------------------color

  while (Flag == 0)
  {
    pixy.changeProg("color");//.....................
    findRoad();
  }
  Flag = 0;
  //-----------------------------color
}
void findRoad()
{
  pixy.ccc.getBlocks();
  voidProject();
  if (pixy.ccc.numBlocks == 1)
  {
    Serial.print("one block");
    //---------------------------------------------------when only find one block
    OneBlockFollow();
    //      pixy.changeProg("line");
  }
  else if (pixy.ccc.numBlocks > 1)
  {
    Serial.print("two block");
    TwoBlockFollow();
    //      pixy.changeProg("line");
  }
  else
  {
    if (countTurn < 100) //---------------------------------------------need test turn speed
    {
      Speed1 = 59;
      Speed2 = 0;
      speedControl('o'); //------------------------------------------
      delay(30);
      countTurn = countTurn + 10;

    }
    else
    {
      speedControl('R'); //-----------------------------------------------------------

      delay(70);
    }
  }
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
}





void speedControl(char ControlWord)
{
  switch (ControlWord)
  { case 'G':
      analogWrite(PWMA, 59);
      analogWrite(PWMB, 42);
      break;

    case 'L':
      analogWrite(PWMA, 42);
      analogWrite(PWMB, 46);
      break;
    case 'l':
      analogWrite(PWMA, 0);
      analogWrite(PWMB, 42);
      break;
    case 'R':

      analogWrite(PWMA, 63);
      analogWrite(PWMB, 31);
      break;
    case'r':
      analogWrite(PWMA, 65);
      analogWrite(PWMB, 0);
      break;
    default:

      analogWrite(PWMA, Speed1);
      analogWrite(PWMB, Speed2);
      break;

  }
}
//------------------------------------------------------------------------------void project
void voidProject()
{ Di = analogRead(A);
  Serial.print("void project");
  Serial.println(Di);
  if (Di <= 20)
  { Speed1 = 1;
    Speed2 = 1;
    speedControl('S');//-----------------stop
    while (Di <= 23)
    { Di = analogRead (A);
      delay(30);
    }
  }
  else if (Di <= 30 )
  { Speed1 = 55;
    Speed2 = 38;
    speedControl('C'); //-----------------continue
  }
}
//-----------------------------------------------------------------------------
void OneBlockFollow()
{
  voidProject();
  Mx = pixy.ccc.blocks->m_x;
  Serial.println("only one block");
  Serial.println(Mx);
  w1 = pixy.ccc.blocks->m_width;
  h1 = pixy.ccc.blocks->m_height;
  Area1 = w1 * h1;
  Serial.println("width height area");
  Serial.println(w1);
  Serial.println(h1);
  Serial.println(Area1);
  if (Area1 >= 10000) {

    pixy.changeProg("line");
    speedControl('G');
    Flag = 1;
  }
  else if (Mx <= 105) {
    speedControl('L');
    delay(70);
  }
  else if (Mx >= 210)
  {
    speedControl('R');
    delay(70);
  }
  else {
    speedControl('G');
    delay(70);
  }
}
//----------------------------------------------------------------------------20200128
void TwoBlockFollow()
{
  voidProject();
  mx1 = pixy.ccc.blocks[0].m_x;
  my1 = pixy.ccc.blocks[0].m_y;

  mx2 = pixy.ccc.blocks[1].m_x;
  my2 = pixy.ccc.blocks[1].m_y;


  w1 = pixy.ccc.blocks[0].m_width;
  h1 = pixy.ccc.blocks[0].m_height;
  Area1 = w1 * h1;
  Serial.println("block1: width height area");
  Serial.println(w1);
  Serial.println(h1);
  Serial.println(Area1);
  w2 = pixy.ccc.blocks[1].m_width;
  h2 = pixy.ccc.blocks[1].m_height;
  Area2 = w2 * h2;
  Serial.println("block2: width height area");
  Serial.println(w2);
  Serial.println(h2);
  Serial.println(Area2);
  D = abs(my2 - my1);
  //compare block position
  if (mx1 > mx2)
  {
    if (D < 15 && Area2 > 3600 && Area1 > 3600)
    {
      pixy.changeProg("line");
      speedControl('G');
      Flag = 1;
    }
    //--------------------------------------------------------right vichol
    else if (my1 < 81)
    {
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH);
      analogWrite(PWMB, s2);
    }

    else if (my1 > 138)
    {
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      analogWrite(PWMB, s2);
      delay(100);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH);
    }
    else analogWrite(PWMB, 0);
    //--------------------------------------------------------left vichol
    if (my2 < 81)
    {
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
      analogWrite(PWMA, s1);
    }

    else if (my1 > 138)
    {
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      analogWrite(PWMA, s1);
      delay(100);
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
    }
    //--------------------------------------------------------go stright
    else analogWrite(PWMA, 0);

    delay (40);
  }
  else
  {
    if (D < 15 && Area2 > 3600 && Area1 > 3600)
    {
      pixy.changeProg("line");
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH);
      analogWrite(PWMA, s1);
      analogWrite(PWMB, s2);
      Flag = 1;
    }
    //--------------------------------------------------------right vichol
    else if (my2 < 81)
    {
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH);
      analogWrite(PWMB, s2);
    }

    else if (my2 > 138)
    {
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      analogWrite(PWMB, s2);
      delay(100);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH);
    }
    else  analogWrite(PWMB, 0);
    //--------------------------------------------------------left vichol
    if (my1 < 81)
    {
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
      analogWrite(PWMA, s1);
    }

    else if (my1 > 138)
    {
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      analogWrite(PWMA, s1);
      delay(100);
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
    }
    //---------------------------------------------------------go stright
    else analogWrite(PWMA, 0);
    delay(400);
  }
}
void loop() {
  // put your main code here, to run repeatedly:


  pixy.line.getMainFeatures();
  pixy.line.getAllFeatures();
  if (pixy.line.vectors)
  {
    countRefind = 0;
    voidProject();


    double  m_x0, m_x1, m_y0, m_y1, y, x;
    double tana, angle;

    pixy.line.vectors->print();
    m_x0 = pixy.line.vectors->m_x0;
    m_y0 = pixy.line.vectors->m_y0;
    m_x1 = pixy.line.vectors->m_x1;
    m_y1 = pixy.line.vectors->m_y1;
    Serial.print("x0: "); Serial.print(m_x0);
    Serial.print("y0: "); Serial.print(m_y0);
    Serial.print("x1: "); Serial.print(m_x1);
    Serial.print("y1: "); Serial.println(m_y1);
    tana = (m_y1 - m_y0) / (m_x1 - m_x0);
    y = m_y1 - m_y0;
    x = m_x1 - m_x0;
    angle = atan2(y, x) * 180 / PI;
    Serial.print("k______________ ");
    Serial.println(tana);
    Serial.print("angle______________ ");
    Serial.println(angle);
    if  (tana >= -0.2 && tana < -0.09)
    {
      speedControl('G');
      Serial.println("GS");
      delay(100);
    }
    else if (tana < -0.664 && tana >= -3.5)
    {
      speedControl('R');
      Serial.println("TR1");
      delay(100);
    }
    else if (tana < -0.2 && tana >= -0.664)
    {
      speedControl('r');
      Serial.println("TR2");
      delay(100);
    }
    else if (tana < 3 && tana >= 0.65)
    { speedControl('L');
      Serial.println("TL1");
      delay(100);
    }
    else if (tana >= -0.09 && tana < 0.65)
    {
      speedControl('l');
      Serial.println("TL2");
      delay(100);
    }

    else {
      speedControl('G');
      Serial.println("gs");
      delay(100);
    }
  }
  //------------------------------------------------------------------refindroad
  else
  {
    countRefind++;
    delay(100);
    if (countRefind >= 20)
    {
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      analogWrite(PWMA, 59);
      analogWrite(PWMB, 42);
      delay(2300);
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH);
      analogWrite(PWMA, 1);
      analogWrite(PWMB, 1);
      countRefind = 0;
      while (Flag == 0)
      {
        pixy.changeProg("color");
        findRoad();
      }
      Flag = 0;
    }
  }
}
