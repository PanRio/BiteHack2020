#include <Servo.h>

  Servo myservoX;
  Servo myservoY;
  Servo silnikL;
  Servo silnikR;

  int x;
  int y;
  char msg;
  String c = "";
  String x_char = "";
  String y_char = "";
  char nextChar = 0;


void setup() 
{
  // put your setup code here, to run once:
  

  myservoX.attach(2);
  myservoY.attach(3);
  silnikL.attach(4);
  silnikR.attach(5);

  
  
  
  Serial.begin(115200);

}

void loop() 
{
  // put your main code here, to run repeatedly:

  myservoX.write(2137);
  if (Serial.available()) 
  {
    msg = Serial.read();
    
  }

}

void odczyt(char msg)
{
  if(msg != "$" && msg != 0)
  {
    c += msg;
  }
  else
  {
    for(int i = 0; i < c.length(); i++)
    {
      if(c[i] == "@")
      {
        nextChar = "x";
      }
      else if(c[i] == "#")
      {
        nextChar = "y";
      }
      else
      {
        if(nextChar = "x")
        {
          x_char += msg;
          nextChar = 0;
        }
        if(nextChar = "y")
        {
          y_char += msg;
          nextChar = 0;
        }
      }
    }
    x = x_char.toInt();
    y = y_char.toInt();
    c = "";
  }
  return 0;
}
