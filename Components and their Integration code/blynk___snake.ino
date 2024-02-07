#define BLYNK_TEMPLATE_ID "TMPL6y9R7jewi"
#define BLYNK_TEMPLATE_NAME "Serpo"
#define BLYNK_AUTH_TOKEN "Hw2njIMfd0AFsp-rZ6pKBmzdPnVYVR6B"


#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//snake libraries
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Virinchi LAB";
char pass[] = "tech&inovation";

//servo driver
Adafruit_PWMServoDriver servoList = Adafruit_PWMServoDriver();
#define SERVOMIN 100
#define SERVOMAX 710

//snake
float pi = 3.14159;
int TotalNumberofServos = 10; //change as required
float Shift = 2 * pi / TotalNumberofServos; // Phase lag between segments
float Wavelengths, rads;
int InteriorAngle, SetpointAngle, MaxAngleDisplacement;

//-------WORKING------------------
void ring() {
  InteriorAngle = 180 - 360 / (TotalNumberofServos + 1); //general formula for a polygon with 3 or more vertices, +1 vertice between tail and head segment
  SetpointAngle = abs(InteriorAngle - 90); //Offset the angle from the initial position of 90 degrees.
  int  pulselength = map(SetpointAngle, 0, 180, SERVOMIN, SERVOMAX); // setting degree with SetpointAngle and getting pulselength
  for (int servo = 0; servo < 8; servo++) {
    if (servo % 2 == 0) {
      servoList.setPWM(servo, 0, pulselength);

    } else {
      int angle = 90 + 90 - SetpointAngle;
      int  pulselength = map(angle, 0, 180, SERVOMIN, SERVOMAX); // setting degree with SetpointAngle and getting pulselength
      servoList.setPWM(servo, 0, pulselength);
      //      continue;

    }
    //    servoList.setPWM(servo, 0, pulselength);
    delay(100);
  }
}

//---------WORKING---------
void slither(int offset, int Amplitude, int Speed, float Wavelengths) {
  MaxAngleDisplacement = abs(offset) + abs(Amplitude); //amount servo can rotate from the SetpointAngle without going out of the [0,180] degree range
  while (MaxAngleDisplacement > 90) { //prevents a setpoint angle outside the rage of[0,180]
    Amplitude = abs(Amplitude) - 1;
    MaxAngleDisplacement = abs(offset) + Amplitude;
  }
  for (int i = 0; i < 360; i++) {
    rads = i * pi / 180.0; //convert from degrees to radians
    for (int servo = 0; servo < 8; servo++) {
      //      if (j % 2 == 0) {
      //        myServos[j].write(90 + offset + Amplitude * sin(Speed * rads + j * Wavelengths * Shift));
      //      } else {
      //        myServos[j].write(90 - offset - Amplitude * sin(Speed * rads + j * Wavelengths * Shift));
      //        //continue;
      //      }
      int angle = 90 + offset + Amplitude * sin(Speed * rads + servo * Wavelengths * Shift);
      int  pulselength = map(angle, 0, 180, SERVOMIN, SERVOMAX);
      servoList.setPWM(servo, 0, pulselength);
    }
    delay(10);
  }
}

//------------WORKING: JUST SHOW THE WAVE LIKE POSITION--------------
void staticWave(int offset, int Amplitude, float Wavelengths) {
  MaxAngleDisplacement = abs(offset) + abs(Amplitude); //amount servo can rotate from the SetpointAngle without going out of the [0,180] degree range
  while (MaxAngleDisplacement > 90) { //prevents a setpoint angle outside the rage of[0,180]
    Amplitude = abs(Amplitude) - 1;
    MaxAngleDisplacement = abs(offset) + Amplitude;
  }

  for (int servo = 0; servo < 8; servo++) {
    if (servo % 2 == 0) {
      int angle = 90 + offset + Amplitude * sin(servo * Wavelengths * Shift);
      int  pulselength = map(angle, 0, 180, SERVOMIN, SERVOMAX);
      servoList.setPWM(servo, 0, pulselength);
      //      myServos[j].write(90 + offset + Amplitude * sin(j * Wavelengths * Shift));
    } else {
      int angle = 90 - offset - Amplitude * sin(servo * Wavelengths * Shift);
      int  pulselength = map(angle, 0, 180, SERVOMIN, SERVOMAX);
      servoList.setPWM(servo, 0, pulselength);
      //      myServos[j].write(90 - offset - Amplitude * sin(j * Wavelengths * Shift));
    }
    delay(15);
  }
}

//----------WORKING-------------
void straightline() {
  int  pulselength = map(90, 0, 180, SERVOMIN, SERVOMAX); // setting 90 degree
  //initializing snake to 90 degree
  for (int servo = 0; servo < 8; servo++) {
    servoList.setPWM(servo, 0, pulselength);
    delay(100);
  }
}

int initial_value = 0;

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

  //snake setup
  servoList.begin();
  servoList.setPWMFreq(60);  // This is the maximum PWM frequency
  int  pulselength = map(90, 0, 180, SERVOMIN, SERVOMAX); // setting 90 degree
  //initializing snake to 90 degree
  for (int servo = 0; servo < 8; servo++) {
    servoList.setPWM(servo, 0, pulselength);
    delay(15);
  }
  delay(1000);
}

void loop()
{
  Blynk.run();
  switch (initial_value) {
    case 0:
      break;
    case 1:
      slither(0, 35, 3, 2);
      break;
    case 2:
      slither(10, 35, 4, 2);
      break;
    case 3:
      slither(-10, 35, 4, 2);
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
