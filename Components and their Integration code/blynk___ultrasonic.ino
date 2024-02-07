#define BLYNK_TEMPLATE_ID "TMPL6y9R7jewi"
#define BLYNK_TEMPLATE_NAME "Serpo"
#define BLYNK_AUTH_TOKEN "Hw2njIMfd0AFsp-rZ6pKBmzdPnVYVR6B"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Virinchi LAB";
char pass[] = "tech&inovation";

//ultrasonic's variables
const int trigPin = 14;    //D5
const int echoPin = 12;     //D6
long duration;
int distance;


int initial_value = 0;
BLYNK_WRITE(V3)
{
  int s0 = param.asInt();
  Serial.println(s0);
  initial_value = s0;
  Blynk.virtualWrite(V2, s0);
}

void setup() {
  Serial.begin(9600);
  //blynk setup
  Blynk.begin(auth, ssid, pass);//Splash screen delay

  //ultrasonic
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  delay(1000);
}

void loop() {
  Blynk.run();
  if (initial_value == 1) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    Serial.print("Distance: ");
    Serial.println(distance);
  }
}
