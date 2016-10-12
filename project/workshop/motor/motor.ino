#include <NewPing.h>

#define TRIGGER_PIN  12  
#define ECHO_PIN     11  
#define MAX_DISTANCE 200 

#define TRIGGER_PIN2  10 
#define ECHO_PIN2     9  

#define TRIGGER_PIN3  8  
#define ECHO_PIN3     7 

const int M1=4, E1=5;
const int M2=7, E2=6;


NewPing sonar_dpn(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar_kn(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(M1,OUTPUT);
  pinMode(E1,OUTPUT);
  pinMode(M2,OUTPUT);
  pinMode(E2,OUTPUT);
}

void loop() {
  int dpn = sonar_dpn.ping_cm();
  int kn = sonar_kn.ping_cm();
  maju(pwm_kn, pwm_kr);
  delay(1000);
}

//fungsi maju
void maju()
{
  digitalWrite(M1, LOW);
  analogWrite(E1, 200);
  digitalWrite(M2, LOW);
  analogWrite(E2, 200);
}
