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
int s1 = 70, s2 = 60;
int  Mx, mx1, mx2, my1, my2, Area, w, h, i, countTurn = 0;
boolean Flag=0;
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
  analogWrite(PWMA, s1);
  analogWrite(PWMB, s2);

  int  Mx, mx1, mx2, my1, my2, Area, w, h, i, countTurn = 0;
  pixy.changeProg("color");
  pixy.ccc.getBlocks();

  while (1)
  {
    pixy.ccc.getBlocks();
    if (Flag==1) break;
    if (pixy.ccc.numBlocks = 1)
    { 
      Serial.print("one block");
//      Mx = pixy.ccc.blocks->m_x;
//      Serial.println("only one block");
//      Serial.println(Mx);
//      w = pixy.ccc.blocks->m_width;
//      h = pixy.ccc.blocks->m_height;
//      Area = w * h;
//      Serial.println("width height area");
//      Serial.println(w);
//      Serial.println(h);
//      Serial.println(Area);
//      if (Area >= 9000) {
//        //        TR();
//        //        delay(100);
//        pixy.changeProg("line");
//        digitalWrite(AIN1, LOW);
//        digitalWrite(AIN2, HIGH);
//        digitalWrite(BIN1, LOW);
//        digitalWrite(BIN2, HIGH);
//        analogWrite(PWMA, s1);
//        analogWrite(PWMB, s2);
//        break;
//      }
//      else if (Mx <= 105) {
//        TL();
//        delay(70);
//      }
//      else if (Mx >= 210)
//      {
//        TR();
//        delay(70);
//      }
//      else {
//        GS();
//        delay(70);
//      }
      //---------------------------------------------------when only find one block
      OneBlockFollow();
    }
    else if (pixy.ccc.numBlocks > 1)
    {
      Serial.print("two block");
      TwoBlockFollow();
//      mx1 = pixy.ccc.blocks[0].m_x;
//      my1 = pixy.ccc.blocks[0].m_y;
//
//      mx2 = pixy.ccc.blocks[1].m_x;
//      my2 = pixy.ccc.blocks[1].m_y;
//
//
//      //compare block position
//      if (mx1 > mx2)
//      {
//        if ((mx2 < 105) && (mx1 > 210) && (my1 >= 69) && (my1 <= 138) && (my2 >= 69) && (my2 <= 138))
//        {
//          pixy.changeProg("line");
//          digitalWrite(AIN1, LOW);
//          digitalWrite(AIN2, HIGH);
//          digitalWrite(BIN1, LOW);
//          digitalWrite(BIN2, HIGH);
//          analogWrite(PWMA, s1);
//          analogWrite(PWMB, s2);
//          break;
//        }
//        //--------------------------------------------------------right vichol
//        else if (my1 < 69)
//        {
//          digitalWrite(BIN1, LOW);
//          digitalWrite(BIN2, HIGH);
//          analogWrite(PWMB, s2);
//        }
//
//        else if (my1 > 138)
//        {
//          digitalWrite(BIN1, HIGH);
//          digitalWrite(BIN2, LOW);
//          analogWrite(PWMB, s2);
//        }
//        //--------------------------------------------------------left vichol
//        else if (my2 < 69)
//        {
//          digitalWrite(AIN1, LOW);
//          digitalWrite(AIN2, HIGH);
//          analogWrite(PWMA, s1);
//        }
//
//        else if (my1 > 138)
//        {
//          digitalWrite(AIN1, HIGH);
//          digitalWrite(AIN2, LOW);
//          analogWrite(PWMA, s1);
//        }
//        //--------------------------------------------------------go stright
//        else {
//          digitalWrite(AIN1, LOW);
//          digitalWrite(AIN2, HIGH);
//          digitalWrite(BIN1, LOW);
//          digitalWrite(BIN2, HIGH);
//          analogWrite(PWMA, s1);
//          analogWrite(PWMB, s2);
//        }
//
//        delay (40);
//      }
//      else
//      {
//        if ((mx2 < 105) && (mx1 > 210) && (my1 >= 69) && (my1 <= 138) && (my2 >= 69) && (my2 <= 138))
//        {
//          pixy.changeProg("line");
//          digitalWrite(AIN1, LOW);
//          digitalWrite(AIN2, HIGH);
//          digitalWrite(BIN1, LOW);
//          digitalWrite(BIN2, HIGH);
//          analogWrite(PWMA, s1);
//          analogWrite(PWMB, s2);
//          break;
//        }
//        //--------------------------------------------------------right vichol
//        else if (my2 < 69)
//        {
//          digitalWrite(BIN1, LOW);
//          digitalWrite(BIN2, HIGH);
//          analogWrite(PWMB, s2);
//        }
//
//        else if (my2 > 138)
//        {
//          digitalWrite(BIN1, HIGH);
//          digitalWrite(BIN2, LOW);
//          analogWrite(PWMB, s2);
//        }
//        //--------------------------------------------------------left vichol
//        else if (my1 < 69)
//        {
//          digitalWrite(AIN1, LOW);
//          digitalWrite(AIN2, HIGH);
//          analogWrite(PWMA, s1);
//        }
//
//        else if (my1 > 138)
//        {
//          digitalWrite(AIN1, HIGH);
//          digitalWrite(AIN2, LOW);
//          analogWrite(PWMA, s1);
//        }
//        //---------------------------------------------------------go stright
//        else {
//          digitalWrite(AIN1, LOW);
//          digitalWrite(AIN2, HIGH);
//          digitalWrite(BIN1, LOW);
//          digitalWrite(BIN2, HIGH);
//          analogWrite(PWMA, s1);
//          analogWrite(PWMB, s2);
//        }
//        delay(40);
//      }

      //      Mx = pixy.ccc.blocks->m_x;
      //      Serial.println("block");
      //      Serial.println(Mx);
      //      w = pixy.ccc.blocks->m_width;
      //      h = pixy.ccc.blocks->m_height;
      //      Area = w * h;
      //      Serial.println("width height area");
      //      Serial.println(w);
      //      Serial.println(h);
      //      Serial.println(Area);
      //      if (Area >= 25000) {
      //        pixy.changeProg("line");
      //        break;
      //      }
      //      else if (Mx <= 105) {
      //        TL();
      //        delay(70);
      //      }
      //      else if (Mx >= 210)
      //      {
      //        TR();
      //        delay(70);
      //      }
      //      else {
      //        GS();
      //        delay(70);
      //      }

    }
    else
    {
      if (countTurn < 100) //---------------------------------------------need test turn speed
      {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
        digitalWrite(BIN1, HIGH);
        digitalWrite(BIN2, LOW);
        analogWrite(PWMA, s1);
        analogWrite(PWMB, s2);//------------------------------------------
        delay(30);
        countTurn = countTurn + 10; //------------------------------------
      }
      else
      {
        TR();//-----------------------------------------------------------
        delay(70);
      }
    }
  }
}
void TL()
{
  analogWrite(PWMA, s1 - 20);
  analogWrite(PWMB, 0);
}

void TR()
{
  analogWrite(PWMA, 0);
  analogWrite(PWMB, s2 -20);
}
void GS()
{
  analogWrite(PWMA, s1);
  analogWrite(PWMB, s2);
}
void OneBlockFollow()
{
  
  Mx = pixy.ccc.blocks->m_x;
      Serial.println("only one block");
      Serial.println(Mx);
      w = pixy.ccc.blocks->m_width;
      h = pixy.ccc.blocks->m_height;
      Area = w * h;
      Serial.println("width height area");
      Serial.println(w);
      Serial.println(h);
      Serial.println(Area);
      if (Area >= 9000) {
        //        TR();
        //        delay(100);
        pixy.changeProg("line");
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, HIGH);
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, HIGH);
        analogWrite(PWMA, s1);
        analogWrite(PWMB, s2);
        Flag=1;
      }
      else if (Mx <= 105) {
        TL();
        delay(70);
      }
      else if (Mx >= 210)
      {
        TR();
        delay(70);
      }
      else {
        GS();
        delay(70);
      }
  }
  void TwoBlockFollow()
  {
    
     mx1 = pixy.ccc.blocks[0].m_x;
      my1 = pixy.ccc.blocks[0].m_y;

      mx2 = pixy.ccc.blocks[1].m_x;
      my2 = pixy.ccc.blocks[1].m_y;


      //compare block position
      if (mx1 > mx2)
      {
        if ((mx2 < 105) && (mx1 > 210) && (my1 >= 69) && (my1 <= 138) && (my2 >= 69) && (my2 <= 138))
        {
          pixy.changeProg("line");
          digitalWrite(AIN1, LOW);
          digitalWrite(AIN2, HIGH);
          digitalWrite(BIN1, LOW);
          digitalWrite(BIN2, HIGH);
          analogWrite(PWMA, s1);
          analogWrite(PWMB, s2);
          Flag=1;
        }
        //--------------------------------------------------------right vichol
        else if (my1 < 69)
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
        }
        //--------------------------------------------------------left vichol
        else if (my2 < 69)
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
        }
        //--------------------------------------------------------go stright
        else {
          digitalWrite(AIN1, LOW);
          digitalWrite(AIN2, HIGH);
          digitalWrite(BIN1, LOW);
          digitalWrite(BIN2, HIGH);
          analogWrite(PWMA, s1);
          analogWrite(PWMB, s2);
        }

        delay (40);
      }
      else
      {
        if ((mx2 < 105) && (mx1 > 210) && (my1 >= 69) && (my1 <= 138) && (my2 >= 69) && (my2 <= 138))
        {
          pixy.changeProg("line");
          digitalWrite(AIN1, LOW);
          digitalWrite(AIN2, HIGH);
          digitalWrite(BIN1, LOW);
          digitalWrite(BIN2, HIGH);
          analogWrite(PWMA, s1);
          analogWrite(PWMB, s2);
          Flag=1;
        }
        //--------------------------------------------------------right vichol
        else if (my2 < 69)
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
        }
        //--------------------------------------------------------left vichol
        else if (my1 < 69)
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
        }
        //---------------------------------------------------------go stright
        else {
          digitalWrite(AIN1, LOW);
          digitalWrite(AIN2, HIGH);
          digitalWrite(BIN1, LOW);
          digitalWrite(BIN2, HIGH);
          analogWrite(PWMA, s1);
          analogWrite(PWMB, s2);
        }
        delay(400);
      }
    }
void loop() {
  // put your main code here, to run repeatedly:
pixy.line.getMainFeatures();
  pixy.line.getAllFeatures();

  
  
  
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
//  if (tana < -0.5 && tana > -1) //??,
//  { TR();
//    Serial.println("right1");
//    delay(100);
//  }
//  else if (tana >= 1.2)
//  { TL();
//    Serial.println("left1");
//    delay(100);
//  }
//  else {
//    if (angle > -20 && angle < 0)
//    { TR();
//      Serial.println("RIGHT");
//      delay(100);
//    }
//    else if (angle < -147)
//    { TL();
//      Serial.println("LEFT");
//      delay(100);
//    }
//    else
//    {
//      GS();
//      delay(100);
//    }
//  }
if((tana>-1.25&& tana<-0.94)||(tana>1.45&&tana<1.8))
{
  GS();
  Serial.println("GS");
  delay(300);
  }
else if((tana<-0.35&&tana>=-0.96)||(tana<0.40)&&(tana>=-0.04))
{
  TR();
  Serial.println("TR");
  delay(300);
  }
  else if((tana<1.3&& tana>1.09)||(tana>1.8)||(tana>0.40&&tana<0.89))
  {TL();
  Serial.println("TL");
  delay(300);
  }
  else {GS();
  Serial.println("gs");
  delay(300);}
}
