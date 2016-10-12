#include <arduino/Arduino.h>
  
int led[5] = {11,10,9,8,7};
int i=0,j,k;

void setup() {                
  for(i=0;i<5;i++){
    pinMode(led[i],OUTPUT);
  }  
}

void loop() {
    for(i=0;i<4;i++){
      digitalWrite(led[i],1);
      delay(100);
      digitalWrite(led[i],LOW);
      delay(100);
    }
    for(i=4;i>0;i--){
      digitalWrite(led[i],1);
      delay(100);
      digitalWrite(led[i],LOW);
      delay(100);
    }
}

int main() {
	init();
	setup();

	while (true) {
		loop();
  	}
}