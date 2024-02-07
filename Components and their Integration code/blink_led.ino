#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL69tdiFnul"
#define BLYNK_TEMPLATE_NAME "Reema Awal"
#define BLYNK_AUTH_TOKEN "jAKtD3yeNlqfGsz-nzY1zWr_79jPYg-F"



#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Virinchi LAB";
char pass[] = "tech&inovation";

int relay1 = 2;  //D6 pin
BLYNK_WRITE(V1)
{
  int led1 = param.asInt();
  digitalWrite(relay1, led1);
}
void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(relay1,OUTPUT);
  digitalWrite(relay1,LOW);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  Blynk.run();
}
