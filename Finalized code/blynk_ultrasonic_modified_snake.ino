//---------Including Libraries------------

// Blink
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//snake libraries
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>

//--------Defining Variables-------------

// Blink
#define BLYNK_TEMPLATE_ID "TMPL6y9R7jewi"
#define BLYNK_TEMPLATE_NAME "Serpo"
#define BLYNK_AUTH_TOKEN "Hw2njIMfd0AFsp-rZ6pKBmzdPnVYVR6B"
#define BLYNK_PRINT Serial

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "[wifi SSID]";
char pass[] = "[wifi password]";

int initial_value = 0;


//ultrasonic
const int trigPin = 14;    //D5
const int echoPin = 12;     //D6
long duration;
int distance;

//servo driver
#define SERVOMIN 100
#define SERVOMAX 710

//snake
float pi = 3.14159;
int TotalNumberofServos = 8; //change as required
float Shift = 2 * pi / TotalNumberofServos; // Phase lag between segments
float Wavelengths, rads;
int InteriorAngle, SetpointAngle, MaxAngleDisplacement;

// snake driver
Adafruit_PWMServoDriver servoList = Adafruit_PWMServoDriver();

void ring() {
  InteriorAngle = 180 - 360 / (TotalNumberofServos + 1); //general formula for a polygon with 3 or more vertices, +1 vertice between tail and head segment
  SetpointAngle = abs(InteriorAngle - 90); //Offset the angle from the initial position of 90 degrees.
  for (int servo = 0; servo < TotalNumberofServos; servo++) {
    int angle = SetpointAngle;
    if (servo %2 != 0) {
      angle = 90 + 90 - SetpointAngle;
    }
    int  pulselength = map(angle, 0, 180, SERVOMIN, SERVOMAX); // setting degree with SetpointAngle and getting pulselength
    servoList.setPWM(servo, 0, pulselength);
    delay(100);
  }
}

// todo: Need checking
void slither(int offset, int Amplitude, int Speed, float Wavelengths) {
  MaxAngleDisplacement = abs(offset) + abs(Amplitude); //amount servo can rotate from the SetpointAngle without going out of the [0,180] degree range
  while (MaxAngleDisplacement > 90) { //prevents a setpoint angle outside the rage of[0,180]
    Amplitude = abs(Amplitude) - 1;
    MaxAngleDisplacement = abs(offset) + Amplitude;
  }
  for (int i = 0; i < 360; i++) {
    rads = i * pi / 180.0; //convert from degrees to radians
    for (int servo = 0; servo < TotalNumberofServos; servo++) {

      //use this line of code
      int angle = 90 + offset + Amplitude * sin(Speed * rads + servo * Wavelengths * Shift);
      // if above code don't work use the bloc of code that is commented below
      //the below code wor for alternative server connection i.e. one is faced upward and another is faced downward

      ///******block of code*****
      // int angle;
      // if(servo % 2 == 0) {
      //   angle = 90 + offset + Amplitude * sin(Speed * rads + servo * Wavelengths * Shift);
      // }else{
      //   angle = 90 - offset - Amplitude * sin(Speed * rads + servo * Wavelengths * Shift);
      // }
      ///******block of code end*****

      int  pulselength = map(angle, 0, 180, SERVOMIN, SERVOMAX);
      servoList.setPWM(servo, 0, pulselength);
    }
    delay(10);
  }
}

//todo: need checking
void staticWave(int offset, int Amplitude, float Wavelengths) {
  MaxAngleDisplacement = abs(offset) + abs(Amplitude); //amount servo can rotate from the SetpointAngle without going out of the [0,180] degree range
  while (MaxAngleDisplacement > 90) { //prevents a setpoint angle outside the rage of[0,180]
    Amplitude = abs(Amplitude) - 1;
    MaxAngleDisplacement = abs(offset) + Amplitude;
  }

  for (int servo = 0; servo < TotalNumberofServos; servo++) {
    int angle=0
    if (servo % 2 == 0) {
      angle = 90 + offset + Amplitude * sin(servo * Wavelengths * Shift);
    } else {
      angle = 90 - offset - Amplitude * sin(servo * Wavelengths * Shift);
    }
    int  pulselength = map(angle, 0, 180, SERVOMIN, SERVOMAX);
    servoList.setPWM(servo, 0, pulselength);
    delay(15);
  }
}

void straightline() {
  int  pulselength = map(90, 0, 180, SERVOMIN, SERVOMAX); // getting the value in degree in 90'
  //initializing snake to 90 degree
  for (int servo = 0; servo < TotalNumberofServos; servo++) {
    servoList.setPWM(servo, 0, pulselength);
    delay(50);
  }
}


BLYNK_WRITE(V3)
{
  int s0 = param.asInt();
  Serial.println(s0);
  initial_value = s0;
  Blynk.virtualWrite(V2, s0);
}


void setup()
{
  Serial.begin(9600);
  //blynk setup
  Blynk.begin(auth, ssid, pass);//Splash screen delay

  //ultrasonic setup
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 

  //snake setup
  servoList.begin();
  servoList.setPWMFreq(60);  // This is the maximum PWM frequency

  straightline()
  delay(1000);
}

void loop()
{
  Blynk.run();
  switch (initial_value) {
    case 0:
      break;
    case 1:
      //ultrasonic
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = duration * 0.034 / 2;
      Serial.print("Distance: ");
      Serial.println(distance);

      //detecting the object and turning right
      if (distance < 25) {
        Serial.println("intered zone");
        slither(15, 35, 5, 1.5);    //turning right
      } else {
        Serial.println("outside zone");
        slither(0, 35, 3, 1.5);           // forwards slither
      }
      break;
    case 2:
      slither(15, 35, 4, 2);
      break;
    case 3:
      slither(-20, 35, 4, 2);
      break;
    case 4:
      ring();
      break;
    case 5:
      staticWave(0, 35, 2);
      break;
    default:
      straightline();
  }
}