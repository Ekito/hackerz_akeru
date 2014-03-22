/*
 * - GPS TX pin is plugged to Akeru pin 0
 * - GPS VCC pin is plugged to Akeru pin 3V3
 * - GPS GND pin is plugged to Akeru pin GND
 */


#include <SoftwareSerial.h>
#include "TinyGPS.h"
#include "Akeru.h"

Akeru_ akeru;
TinyGPS gps;


struct coord {
  float latitude;
  float longitude;
};

void setup() {
  // LED 13 is used to "debug" sigfox operations
  pinMode(13, OUTPUT);

  // Initialize sigfox modem
  akeru.begin();
  
  // Start serial communication, because everyone needs to !
  Serial.begin(115200);

  delay(2000);
}

void loop() {
  // Get NMEA data
  float latitude;
  float longitude;
  unsigned long fix_age = 9999;

  while (fix_age > 1000) {
    while(Serial.available()) {
      if (gps.encode(Serial.read())) {
        gps.f_get_position(&latitude, &longitude, &fix_age);
      }
      Serial.flush();
    }
  }

  // Some debug can't be harmful    
  Serial.println(latitude);
  Serial.println(longitude);
  Serial.println(fix_age);
  
  coord coordinates = {latitude, longitude};
  
  // Send data to Sigfox network
  digitalWrite(13, HIGH);
  akeru.send(&coordinates, sizeof(coord));
  digitalWrite(13, LOW);

  delay(1000);
}
