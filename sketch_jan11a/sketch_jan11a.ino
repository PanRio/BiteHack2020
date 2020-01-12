#include <Servo.h>
#include <PID_v1.h>
#include <stdio.h>

//silniki i serwa
  Servo myservoX;
  Servo myservoY;
  Servo silnikL;
  Servo silnikR;

//aktualna pozycja
  int x;
  int y;

  char msg;
  String c = "";
  String x_char = "";
  String y_char = "";
  String header = "";
  char nextChar = 0;

//PID
  double SetpointX, InputX, OutputX;
  PID myPIDx(&InputX, &OutputX, &SetpointX,0.02,0.05,0.001, DIRECT);

void setup() 
{
  // put your setup code here, to run once:
  

  myservoX.attach(3);
  myservoY.attach(5);
  silnikL.attach(6);
  silnikR.attach(9);

//punkt pracy itp
  //InputX = analogRead(0);
  SetpointX = 350;

  myPIDx.SetMode(AUTOMATIC);
  
  
  Serial.begin(115200);

}

void loop() 
{
  // put your main code here, to run repeatedly:

  
  if (Serial.available()) 
  {
    odczyt(Serial.read());
    Serial.print("x= ");
    Serial.print(x);
    Serial.print(" y= ");
    Serial.println(y);
  }

  InputX = x;
  myPIDx.Compute();
  myservoX.write(OutputX);
}



void odczyt(char msg)
{
               // read a byte, then
        Serial.println(msg);
        //Serial.println(c);
        header += msg;
        if(msg=='c'){
         bool startX=false;
         bool startY=false;


          for(int i=0;i<header.length();i++)
          {
             if(header[i]=='a')
             {
                startX=true;
                i++;
             } 
             else if(header[i]=='b')
             {
                startX=false;
                startY=true;
                i++;
             } 
             
              else if(header[i]=='c')
             {
                header="";
                break;
             }  

              if(startX){
                x_char+=header[i];
              }
              else if(startY){
                y_char+=header[i];             
              }
              
                                                                                                     
          }


         x=x_char.toInt();
         y=y_char.toInt();
    
          x_char="";
          y_char="";
           
        }
}
