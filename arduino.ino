#include <SoftwareSerial.h>
#include "Akeru.h"

Akeru_ akeru;

struct coord {
  float latitude;
  float longitude;
};

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);

  akeru.begin();
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Begin");
  
  coord coordinates = {43.256663, 1.199009};
  
  
  digitalWrite(13, HIGH);
  akeru.send(&coordinates, sizeof(coord));
  digitalWrite(13, LOW);

  Serial.println("Before delay");

  delay(30*1000);
  
  Serial.println("After delay");
}
