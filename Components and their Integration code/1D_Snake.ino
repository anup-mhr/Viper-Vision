#include <Servo.h>

Servo myServos[10]; //create 10 servos

float pi = 3.14159;
int TotalNumberofServos = 10; //change as required
float Shift = 2 * pi / TotalNumberofServos; // Phase lag between segments
float Wavelengths, rads;
int InteriorAngle, SetpointAngle, MaxAngleDisplacement;

void setup() {
  Serial.begin(9600);
  //The following code can be cleaned up in a single for-loop if you solder the wires in a more continuous pattern than I did
  //Order of servos is such that myServos[0]=tail segment, and myServos[9]=head segment
//  myServos[0].attach(D0, 500, 2400);
//  myServos[1].attach(D1, 500, 2400);
//  myServos[2].attach(D2, 500, 2400);
//  myServos[3].attach(D3, 500, 2400);
//  myServos[4].attach(D4, 500, 2400);
//  myServos[5].attach(D5, 500, 2400);
//  myServos[6].attach(D6, 500, 2400);

   myServos[5].attach(D3, 500, 2400);
  myServos[6].attach(D4, 500, 2400);
  
  myServos[7].attach(D7, 500, 2400);
  myServos[8].attach(D8, 500, 2400);
  myServos[9].attach(A0, 500, 2400);

  //Initialise snake in a straight line
  for (int i = 0; i < 10; i++) {
    myServos[i].write(90);
    delay(15);
  }
  delay(1000);
}

//----------WORKING-------------
void straightline() {
  for (int i = 0; i < 10; i++) {
    myServos[i].write(90);
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
    for (int j = 0; j < 10; j++) {
//      if (j % 2 == 0) {
//        myServos[j].write(90 + offset + Amplitude * sin(Speed * rads + j * Wavelengths * Shift));
//      } else {
//        myServos[j].write(90 - offset - Amplitude * sin(Speed * rads + j * Wavelengths * Shift));
//      }
            myServos[j].write(90+offset+Amplitude*sin(Speed*rads+j*Wavelengths*Shift));
    }
    delay(10);
  }
}

//-------WORKING------------------
void ring() {
  InteriorAngle = 180 - 360 / (TotalNumberofServos + 1); //general formula for a polygon with 3 or more vertices, +1 vertice between tail and head segment
  SetpointAngle = abs(InteriorAngle - 90); //Offset the angle from the initial position of 90 degrees.
  for (int i = 0; i < 10; i++) {
    if (i % 2 == 0) {
      myServos[i].write(SetpointAngle);
    } else {
      myServos[i].write(90 + 90 - SetpointAngle);
    }
    //    myServos[i].write(SetpointAngle);
    delay(100);
  }
}

//------------WORKING: JUST SHOW THE WAVE LIKE POSITION--------------
void staticWave(int offset, int Amplitude, float Wavelengths) {
  MaxAngleDisplacement = abs(offset) + abs(Amplitude); //amount servo can rotate from the SetpointAngle without going out of the [0,180] degree range
  while (MaxAngleDisplacement > 90) { //prevents a setpoint angle outside the rage of[0,180]
    Amplitude = abs(Amplitude) - 1;
    MaxAngleDisplacement = abs(offset) + Amplitude;
  }

  for (int j = 0; j < 10; j++) {
    if (j % 2 == 0) {
      myServos[j].write(90 + offset + Amplitude * sin(j * Wavelengths * Shift));
    } else {
      myServos[j].write(90 - offset - Amplitude * sin(j * Wavelengths * Shift));
    }
    delay(15);
  }
}

//--------FUTURE DEVELOPMENT-------------------
//--------TIP: BETTER TO USE U-SHAPE THAN C-SHAPE


void loop() {
slither(0, 35, 3, 1.5); 
//  slither(0, 35, 10, 1.5);           // forwards slither
  //  slither(10, 35, 10, 1.5);        // turning slither right
  //  slither(-10, 35, 1, 1.5);       // opposite direction turn
  //  ring();                         // make ring like shape
  //  staticWave(0, 35, 2);

}
