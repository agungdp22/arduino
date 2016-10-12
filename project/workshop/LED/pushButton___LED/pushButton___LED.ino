int pushButton = 2;
int led = 13;
int led2 = 12;
int led3 = 8;

void setup() {
  Serial.begin(9600);
  pinMode(pushButton, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}
void loop() {
  int buttonState = digitalRead(pushButton);
  Serial.println(buttonState);
  if(buttonState==1){
    digitalWrite (led, HIGH);
    digitalWrite (led2, LOW);
    digitalWrite (led3, LOW);
  delay (500);
  digitalWrite (led, LOW);
  digitalWrite (led2, HIGH);
  digitalWrite (led3, LOW);
  delay (500);
  digitalWrite (led, LOW);
  digitalWrite (led2, LOW);
  digitalWrite (led3, HIGH);
  delay (500);
 }
 else{
  digitalWrite (led, HIGH);
  digitalWrite (led2, HIGH);
  digitalWrite (led3, HIGH);
  delay (500);                              
 }
}

