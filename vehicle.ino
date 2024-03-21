#include<Servo.h>
Servo myservo1;
Servo myservo2;

#define BLYNK_TEMPLATE_ID "TMPL3d9hSH9jv"
#define BLYNK_TEMPLATE_NAME "VR"
#define BLYNK_AUTH_TOKEN "LzJlfSfaNLg-O5epFc73XC1C_S4iEy33"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Blynk.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "jarvis";
char pass[] = "backspace";

int vehicleforward;
int vehicleright;
int vehicleleft;
int vehiclebackward;

#define IN1 D8
#define IN2 D7
#define IN3 D6
#define IN4 D5
String incomingByte ;    

void setup() 
{
  Serial.begin(9600);
  myservo1.attach(D0,500,2400);
  myservo2.attach(D1,500,2400);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Blynk.begin(auth, ssid, pass);
}

BLYNK_WRITE(V0)
{
  vehicleforward = param.asInt();
}
 
BLYNK_WRITE(V1)
{
  vehicleleft = param.asInt();
}
 
BLYNK_WRITE(V2)
{
  vehicleright = param.asInt();
}
 
BLYNK_WRITE(V3)
{
  vehiclebackward = param.asInt();
}

void loop() 
{
      if(Serial.available()>0)
  {
   String incomingByte = Serial.readStringUntil('#');
   Serial.println(incomingByte);
   
    if (incomingByte == "b") 
    {
      myservo1.write(90); 
    }
    if (incomingByte == "l") 
    {
      myservo1.write(180); 
    }
    if (incomingByte == "r") 
    {
      myservo1.write(0); 
    }

    if (incomingByte == "a") 
    {
      myservo2.write(130); 
    } 
    if (incomingByte == "u") 
    {
      myservo2.write(100); 
    }
    if (incomingByte == "d") 
    {
      myservo2.write(160); 
    }
  

   Blynk.run();
   iotvehicle();
  }
}

void iotvehicle()
{
  if (vehicleforward == 1)
  {
    forward();
    delay(50);
    Serial.println("vehicleforward");
  }

  else if (vehicleleft == 1)
  {
    left();
    delay(50);
    Serial.println("vehicleleft");
  }
 
  else if (vehicleright == 1)
  {
    right();
    delay(50);
    Serial.println("vehicleright");
  }
  else if (vehiclebackward == 1)
  {
    backward();
    delay(50);
    Serial.println("vehiclebackward");
  }
  else if (vehicleforward == 0 && vehicleleft == 0 && vehicleright == 0 && vehiclebackward == 0)
  {
    STOP();
    delay(50);
    Serial.println("vehiclestop");
  }
}

void forward()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}
void right()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}
void left()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}
void backward()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}
void STOP()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}
