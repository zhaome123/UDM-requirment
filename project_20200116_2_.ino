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
int  Mx, mx1, mx2, my1, my2,Area1, Area2, w1, w2, h1, h2, D,countTurn = 0, Di,vector;
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
//  speedControl('G', 0, 0);

//pixy.changeProg("color");
//-----------------------------color

  while (Flag == 0)
  { 
    pixy.ccc.getBlocks();
    voidProject();
    if (pixy.ccc.numBlocks = 1)
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
        speedControl('o', 59, 0); //------------------------------------------
        delay(30);
        countTurn = countTurn + 10;
        
      }
      else
      {
        speedControl('R', 0, 0); //-----------------------------------------------------------
       
        delay(70);
      }
    }

  }





  //-----------------------------color
}
void speedControl(char ControlWord, int Speed1, int Speed2)
{
  switch (ControlWord)
  { case 'G':
       analogWrite(PWMA, 59);
        analogWrite(PWMB, 46);
        break;
      
    case 'L':
       analogWrite(PWMA, 37);
        analogWrite(PWMB, 52);
        break;
      
    case 'R':
      
        analogWrite(PWMA, 63);
        analogWrite(PWMB, 45);
        break;
      
    default:
      
        analogWrite(PWMA, Speed1);
        analogWrite(PWMB, Speed2);
        break;
      
  }
}
void voidProject()//------------------------------------------------------------------------------
{ Di = analogRead(A);
  Serial.println(Di);
  if (Di <= 10)
  {
    speedControl('STOP', 0, 0);
    while (Di <= 10)
    { Di = analogRead (A);
      delay(30);
    }
  }
  else if (Di <= 24 )
  {
    speedControl('Restart', 55, 38); //-----------------------------------------------------------------
  }
}

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
  if (Area1 >= 7000) {

    pixy.changeProg("line");
    speedControl('G', 0, 0);
    Flag = 1;
  }
  else if (Mx <= 105) {
    speedControl('L', 0, 0);
    delay(70);
  }
  else if (Mx >= 210)
  {
    speedControl('R', 0, 0);
    delay(70);
  }
  else {
    speedControl('G', 0, 0);
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
  Serial.println("width height area");
  Serial.println(w1);
  Serial.println(h1);
  Serial.println(Area1);
  w2 = pixy.ccc.blocks[1].m_width;
  h2 = pixy.ccc.blocks[1].m_height;
  Area2 = w2 * h2;
  Serial.println("width height area");
  Serial.println(w2);
  Serial.println(h2);
  Serial.println(Area2);
  D = abs(my2 - my1);
  //compare block position
  if (mx1 > mx2)
  {
     if (D < 10 && Area2 > 400 && Area1 > 400)
    {
      pixy.changeProg("line");
      speedControl('G', 0, 0);
      Flag = 1;
    }
    //--------------------------------------------------------right vichol
    else if (my1 < 81)
    {
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH);
      analogWrite(PWMB, s2);
    }

    else if (my1 > 150)
    {
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      analogWrite(PWMB, s2);
    }
    else analogWrite(PWMB, 0);
    //--------------------------------------------------------left vichol
     if (my2 < 81)
    {
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
      analogWrite(PWMA, s1);
    }

    else if (my1 > 150)
    {
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      analogWrite(PWMA, s1);
    }
    //--------------------------------------------------------go stright
    else analogWrite(PWMA, 0);

    delay (40);
  }
  else
  {
    if (D < 10 && Area2 > 400 && Area1 > 400)
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

    else if (my2 > 150)
    {
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      analogWrite(PWMB, s2);
    }
    else  analogWrite(PWMB, 0);
    //--------------------------------------------------------left vichol
    if (my1 < 81)
    {
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
      analogWrite(PWMA, s1);
    }

    else if (my1 > 150)
    {
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      analogWrite(PWMA, s1);
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
  if ((tana > -1.25 && tana < -0.94) || (tana > 1.45 && tana < 1.8))
  {
    speedControl('G', 0, 0);
    Serial.println("GS");
    delay(300);
  }
  else if ((tana < -0.35 && tana >= -0.96) || (tana < 0.40) && (tana >= -0.04))
  {
    speedControl('R', 0, 0);
    Serial.println("TR");
    delay(300);
  }
  else if ((tana < 1.3 && tana > 1.09) || (tana > 1.8) || (tana > 0.40 && tana < 0.89))
  { speedControl('L', 0, 0);
    Serial.println("TL");
    delay(300);
  }
  else {
    speedControl('G', 0, 0);
    Serial.println("gs");
    delay(300);
  }
}
