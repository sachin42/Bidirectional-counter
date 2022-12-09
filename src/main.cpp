#include <Arduino.h>

void (*resetFunc)(void) = 0; // declaring reset func at address 0
// defining the pins
#define trig2 5
#define echo2 6
#define trig1 7
#define echo1 8
#define entryLight 11
#define exitLight 9
#define GND 10

int d1, d2, distance, i, j, p, q, a = 0;

int lastp=0,lastq = 0;
long int duration;

void Ultrasonic(int trig, int echo)
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = 0.034 * duration / 2;
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(entryLight, OUTPUT);
  pinMode(exitLight, OUTPUT);
  pinMode(GND, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  a++;
  Ultrasonic(trig1, echo1);
  d1 = distance;

  Ultrasonic(trig2, echo2);
  d2 = distance;

  if (d1 <= 20)
  {
    digitalWrite(entryLight, HIGH);
    i++;
    if (i == 1)
      p++;
    else
      p;
  }
  else
  {
    i = 0;
    digitalWrite(entryLight, LOW);
  }

  if (d2 <= 20)
  {                                // if distance is less than or equal to 20
    digitalWrite(exitLight, HIGH); //
    digitalWrite(GND, LOW);
    j++;
    if (j == 1)
      q++;
    else
      q;
  }
  else
  {
    j = 0;
    digitalWrite(exitLight, LOW);
    digitalWrite(GND, LOW);
  }
  // Serial.println(p);
  // Serial.println(q);
  if ((p - q) < 0)
    resetFunc();

  if (a % 20 == 0) // print after every 2 seconds
  {
    if(lastp != p || lastq != q ){
    lastp = p;
    lastq = q;
    Serial.print("Persons Entered = ");
    Serial.print(p);
    Serial.print(", Persons Exit = ");
    Serial.print(q);
    Serial.print(", Total Persons in the Room = ");
    Serial.println(p - q);
    }
    
  }
  delay(100);
}
