#include <SoftwareSerial.h>
#include "Akeru.h"

Akeru_ akeru;

struct coord {
  float latitude;
  float longitude;
};

// Example NEMA frame
char nema[] = "$GPRMC,194509.000,A,4042.6142,N,07400.4168,W,2.03,221.11,160412,,,A*77";

void setup() {
  // LED 13 is used to "debug" sigfox operations
  pinMode(13, OUTPUT);

  // Initialize sigfox modem
  akeru.begin();
  
  // Start serial communication, because everyone needs to !
  Serial.begin(9600);
}

void loop() {
  // Get coordinates from NEMA frames
  coord coordinates = extractCoordinates(nema);
  
  // TODO : check for NULL/NULL coordinates
  
  // Send data to Sigfox network
  digitalWrite(13, HIGH);
  akeru.send(&coordinates, sizeof(coord));
  digitalWrite(13, LOW);

  // Wait for 10 minutes and 1 second
  delay(10*60*1000 + 1);
}


// Extract coordinates from NEMA data
struct coord extractCoordinates(char data[]) {
  char *frame_type;
  char *timestamp;
  char *state;
  char *latitude;
  char *latitude_direction;
  char *longitude;
  char *logitude_direction;
  
  char *brkb;
  
  frame_type = strtok_r(data, "," ,&brkb);
  timestamp = strtok_r(NULL, "," ,&brkb);
  state = strtok_r(NULL, "," ,&brkb);
  latitude = strtok_r(NULL, "," ,&brkb);
  latitude_direction = strtok_r(NULL, "," ,&brkb);
  longitude = strtok_r(NULL, "," ,&brkb);
  logitude_direction = strtok_r(NULL, "," ,&brkb);

  if (strcmp(frame_type, "$GPRMC") == 0) {
    // Got the correct frame type
    if (strcmp(state, "A") == 0) {
      // GPS locked
      
      // Get latitude and logitude (DDMM.MMMM style ; DD = degrees; MM = minutes)
      float lat = atof(latitude);
      float lon = atof(longitude);
      if (strcmp(latitude_direction, "S") == 0) {
        // If southern coordinates => negative values
        lat = 0 - lat;
      }
      if (strcmp(logitude_direction, "W") == 0) {
        // If western coordinates => positive values
        lon = 0 - lon;
      }
      
      // Convert latitude and longitude to decimal degrees
      float dlat = calculateCurrentLocation(lat);
      float dlon = calculateCurrentLocation(lon);

      coord result = {dlat, dlon};
      return result;
    }
  }

  coord result = {NULL, NULL};
  return result;
}

// Convert coordinates from GPS to decimal degrees
float calculateCurrentLocation(float coordinate){

  float minutesLat; 
  float minuteLong;
  float degreesLat; 
  float degreesLong; 
  float secondsLat; 
  float millisecondsLat; 

  degreesLat = trunc(coordinate/100);
  minutesLat = coordinate - (degreesLat*100);
  secondsLat = (minutesLat - trunc(minutesLat)) * 60;
  millisecondsLat = (secondsLat - trunc(secondsLat)) * 1000;
  
  minutesLat = trunc(minutesLat);
  secondsLat = trunc(secondsLat);

  return degreesLat + minutesLat/60 + secondsLat/3600 + millisecondsLat/3600000; 
}
