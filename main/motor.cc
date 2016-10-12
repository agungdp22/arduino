#include <Wire.h>

void gerakMotor(int i, int MSB, int LSB, int rate)
{
        Wire.beginTransmission(0x70);
        Wire.write(0x02); // perintah run servo
        Wire.write(i);
        Wire.write(MSB); 
        Wire.write(LSB);
        Wire.write(rate);
        Wire.endTransmission();
}
void setup()
{
  Wire.begin();
  Serial.begin(9600); 
}

void maju() //gerakan motor sebelah kanan dan kiri berkebalikan
{
        gerakMotor(2, 0x04, 0xB0, 100); //1150 PWM, angkat kaki
        gerakMotor(14, 0x07, 0x08, 100); //1800 PWM, angkat kaki
        gerakMotor(7, 0x04, 0xB0, 100); //1150 PWM, angkat kaki
        delay(150);
        gerakMotor(1, 0x04, 0xB0, 100); //1150 PWM, maju
        gerakMotor(13, 0x07, 0x08, 100); //1800 PWM, maju
        gerakMotor(9, 0x04, 0xB0, 100); //1150 PWM, maju
        delay(150);
        gerakMotor(2, 0x05, 0xDC, 100); //1500 PWM, turun kaki
        gerakMotor(14, 0x05, 0xDC, 100); //1500 PWM, turun kaki
        gerakMotor(7, 0x05, 0xDC, 100); //1500 PWM, turun kaki
        delay(150);
        gerakMotor(1, 0x05, 0xDC, 100); //1500 PWM, 
        gerakMotor(13, 0x05, 0xDC, 100); //1500 PWM,
        gerakMotor(9, 0x05, 0xDC, 100); //1500 PWM, 
        delay(150);
        
        gerakMotor(11, 0x07, 0x08, 100); //1150 PWM, angkat kaki
        gerakMotor(5, 0x04, 0x60, 100); //1800 PWM, angkat kaki
        gerakMotor(17, 0x07, 0x08, 100); //1150 PWM, angkat kaki
        delay(150);
        gerakMotor(10, 0x07, 0x08, 100); //1150 PWM, angkat kaki
        gerakMotor(4, 0x04, 0xB0, 100); //1800 PWM, angkat kaki
        gerakMotor(16, 0x07, 0xB08, 100); //1150 PWM, angkat kaki
        delay(150);
        gerakMotor(11, 0x05, 0xDC, 100); //1150 PWM, turun kaki
        gerakMotor(5, 0x05, 0xDC, 100); //1800 PWM, turun kaki
        gerakMotor(17, 0x05, 0xDC, 100); //1150 PWM, turun kaki
        delay(150);
        gerakMotor(10, 0x05, 0xDC, 100); //1150 PWM, angkat kaki
        gerakMotor(4, 0x05, 0xDC, 100); //1800 PWM, angkat kaki
        gerakMotor(16, 0x05, 0xDC, 100); //1150 PWM, angkat kaki
        delay(150);
}

void diri() //berdiri stabil posisi netral
{
        for(int i = 1; i < 19 ; i++)
         gerakMotor(i, 0x05, 0xDC, 100);
}

void belok_kanan()
{
  //kaki D gerak ke belakang, kaki B maju, kaki F mundur
  //gerak : motor 11 5 17 angkat -> motor 10 ke belakang, motor 4 ke depan, motor 16 ke belakang -> posisi netral
  gerakMotor(11, 0x07, 0x08, 100); //coba 1800 PWM -> 07 08
  gerakMotor(5, 0x04, 0xB0, 100);  //coba 1150 PWM -> 04 B0
  gerakMotor(17, 0x07, 0x08, 100); 
  delay(150);
  gerakMotor(10, 0x02, 0x58, 100); //ke belakang
  gerakMotor(4, 0x02, 0x58, 100); //ke depan
  gerakMotor(16, 0x02, 0x58, 100); //ke belakang
  delay(150);
  //posisi netral, kaki turun
  gerakMotor(11, 0x05, 0xDC, 100); 
  gerakMotor(5, 0x05, 0xDC, 100); 
  gerakMotor(17, 0x05, 0xDC, 100); 
  delay(150);
  //posisi netral, kaki ke posisi awal
  gerakMotor(10, 0x05, 0xDC, 100); 
  gerakMotor(4, 0x05, 0xDC, 100); 
  gerakMotor(16, 0x05, 0xDC, 100); 
  delay(150);
  
  //Kaki A maju, kaki E mundur, kaki C maju
  //gerak : motor 2 14 8 angkat -> motor 1 ke depan, motor 13 ke belakang, motor 7 ke depan -> posisi netral
  gerakMotor(2, 0x04, 0xB0, 100); // angkat
  gerakMotor(14, 0x07, 0x08, 100);  //
  gerakMotor(8, 0x04, 0xB0, 100); 
 delay(150);
  gerakMotor(1, 0x02, 0x58, 100); //ke depan
  gerakMotor(13, 0x02, 0x58, 100); //ke belakang
  gerakMotor(7, 0x02, 0x58, 100); //ke depan
  delay(150);
  
  //kaki turun
  gerakMotor(2, 0x05, 0xDC, 100); 
  gerakMotor(14, 0x05, 0xDC, 100); 
  gerakMotor(8, 0x05, 0xDC, 100); 
  delay(150);
  //ke posisi awal
  gerakMotor(1, 0x05, 0xDC, 100); 
  gerakMotor(13, 0x05, 0xDC, 100); 
  gerakMotor(7, 0x05, 0xDC, 100); 
  delay(150);
}

void belok_kiri()
{
  //kaki A gerak ke belakang, kaki E maju, kaki C mundur
  //gerak : motor 2 14 8 angkat -> motor 1 ke belakang, motor 13 ke depan, motor 7 ke belakang -> posisi netral
  gerakMotor(2, 0x04, 0xB0, 100); //coba 1800 PWM -> 07 08
  gerakMotor(14, 0x07, 0x08, 100);  //coba 1150 PWM -> 04 B0
  gerakMotor(8, 0x04, 0xB0, 100); 
  delay(150);
  
  gerakMotor(1, 0x09, 0x60, 100); //ke belakang
  gerakMotor(13, 0x09, 0x60, 100); //ke depan
  gerakMotor(7, 0x09, 0x60, 100); //ke belakang
  delay(150);
  
  //posisi netral, kaki turun
  gerakMotor(2, 0x05, 0xDC, 100); 
  gerakMotor(14, 0x05, 0xDC, 100); 
  gerakMotor(8, 0x05, 0xDC, 100); 
  delay(150);
  //posisi netral, kaki ke posisi awal
  gerakMotor(1, 0x05, 0xDC, 100); 
  gerakMotor(13, 0x05, 0xDC, 100); 
  gerakMotor(7, 0x05, 0xDC, 100); 
  delay(150);
  
  //Kaki D maju, kaki B mundur, kaki F maju
  //gerak : motor 11 5 17 angkat -> motor 10 ke depan, motor 4 ke belakang, motor 16 ke depan -> posisi netral
  gerakMotor(11, 0x07, 0x08, 100); // angkat
  gerakMotor(5, 0x04, 0xB0, 100);  //
  gerakMotor(7, 0x07, 0x08, 100); 
 delay(150);
  gerakMotor(10, 0x09, 0x60, 100); //ke depan
  gerakMotor(4, 0x09, 0x60, 100); //ke belakang
  gerakMotor(16, 0x09, 0x60, 100); //ke depan
  delay(150);
  
  //kaki turun
  gerakMotor(11, 0x05, 0xDC, 100); 
  gerakMotor(5, 0x05, 0xDC, 100); 
  gerakMotor(7, 0x05, 0xDC, 100); 
  delay(150);
  //ke posisi awal
  gerakMotor(10, 0x05, 0xDC, 100); 
  gerakMotor(4, 0x05, 0xDC, 100); 
  gerakMotor(16, 0x05, 0xDC, 100); 
  delay(150);
}

void loop()
{
        /*Wire.beginTransmission(0x70);
  Wire.write(0x02); // perintah run servo
  Wire.write(2);
        Wire.write(0x02); //lebar pulsa : 1500
  Wire.write(0x58);
        Wire.write(100);
        Wire.endTransmission();
        */
//        diri();
//        delay(1000);
        maju();
        
        //-90 sd -15 kiri
        //15 sd 90 kanan
        //-15 sd 15 maju
        
        /*int sudut = Serial.read();
        if(sudut >= -90 && sudut < -15)
        {
          belok_kiri();
          Serial.println('kiri');
          delay(1000);
        }
        else if(sudut >= -15 && sudut <15)
        {
          maju();
          Serial.println('kiri');
          delay(1000);
        }        
        else if(sudut >=15 && sudut < 90)
        {
          belok_kanan();
          Serial.println('kiri');
          delay(1000);
        }
        */
        
}

int main() {
  init();
	setup();

  while (true) {
    loop();
  }
}
