#include <NewPing.h>

#define TRIGGER_PIN  12  
#define ECHO_PIN     11  
#define MAX_DISTANCE 200 


NewPing sonar_dpn(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
//NewPing sonar_kn(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


void setup() {
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.

}

void loop() {
  int dpn = sonar_dpn.ping_cm();
  Serial.print("sensor depan :");
  Serial.println(dpn);
  
  delay(1000);
}

