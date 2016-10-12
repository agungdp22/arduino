
const int M1=4, E1=5;
const int M2=7, E2=6;

void setup() {
  // put your setup code here, to run once:
  pinMode(M1,OUTPUT);
  pinMode(E1,OUTPUT);
  pinMode(M2,OUTPUT);
  pinMode(E2,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(M1, LOW);
  analogWrite(E1, 190);
  digitalWrite(M2, LOW);
  analogWrite(E2, 110);
}


