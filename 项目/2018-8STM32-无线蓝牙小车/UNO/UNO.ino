//宏定义一些引脚
#define LED 13      

#define IN1  2
#define IN2  3
#define IN7  4
#define IN8  5
#define IN4  6
#define IN3  7

#define EN1  9
#define EN2  10

int  command = 0;
char inChar = 0;
String inputString = "";        
boolean stringComplete = false;  

void setup()			
{
  pinMode(LED,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN7,OUTPUT);
  pinMode(IN8,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  Serial.begin(9600);
  Moto_Init();
}
//后循环输出

void loop()				
{
  
 
  switch(inChar)
  {
    case 'g':Go_Straight();break;
    case 's':Stop();break;
    case 'l':Turn_Left();break;
    case 'r':Turn_Right();break;
    case 'b':Go_Back();break;
    case 'w':Water();break;
    case 'd':Donot_Water();break;
  }
  				
}



void Moto_Init()
{
  analogWrite(EN1,255);
  analogWrite(EN2,200);

}

void Go_Straight()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN7,LOW);
  digitalWrite(IN8,HIGH);
}

void Stop()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN7,LOW);
  digitalWrite(IN8,LOW);
}

void Turn_Left()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN7,HIGH);
  digitalWrite(IN8,LOW);
}

void Turn_Right()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN7,LOW);
  digitalWrite(IN8,HIGH);
}

void Go_Back()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN7,HIGH);
  digitalWrite(IN8,LOW);
}
void Water()
{
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void Donot_Water()
{
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}

void serialEvent()
{
  while (Serial.available())
  {
//    inChar = (char)Serial.read();
//    inputString += inChar;
//    if (inChar == '\n') 
//    {
//      stringComplete = true;
//    }
//    
//    if (stringComplete) 
//    {
//      Serial.write(inputString);
//      inputString = "";
//      stringComplete = false;
//    }
      inChar = (char)Serial.read();
      Serial.write(inChar);
  }
}




