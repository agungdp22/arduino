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
//pake array
//membership function sensor depan
#define sen_dpn1 0.0
#define sen_dpn2 90.0
#define sen_dpn3 100.0

//membership function sensor kanan
#define sen_kn1 0.0
#define sen_kn2 4.0
#define sen_kn3 8.0
#define sen_kn4 12.0

//membership function output, pwm
#define m1 50.0
#define m2 100.0
#define m3 170.0

NewPing sonar_dpn(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar_kn(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar3(TRIGGER_PIN3, ECHO_PIN3, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

float u[8]={0.0};
float z_kr[8]={0.0};
float z_kn[8]={0.0};
float dpn_dekat, dpn_jauh;
float kn_dekat, kn_sedang, kn_jauh;
int pwm_kn = 0;
int pwm_kr = 0;

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(M1,OUTPUT);
  pinMode(E1,OUTPUT);
  pinMode(M2,OUTPUT);
  pinMode(E2,OUTPUT);

  //output motor kanan
  z_kr[0] = m1;
  z_kr[1] = m1;
  z_kr[2] = m3;
  z_kr[3] = m1;
  z_kr[4] = m2;
  z_kr[5] = m3;
  
  //output motor kiri
  z_kn[0] = m3;
  z_kn[1] = m3;
  z_kn[2] = m1;
  z_kn[3] = m3;
  z_kn[4] = m2;
  z_kn[5] = m2;
  
}

void loop() {
  int dpn = sonar_dpn.ping_cm();
  int kn = sonar_kn.ping_cm();
//  Serial.print("sensor kanan :");
//  Serial.println(kan);
//  Serial.print("sensor depan :");
//  Serial.println(dpn);
if (dpn > 90 && dpn < 100)
  {
    switch(dpn)
    {
      case 91: dpn_dekat = 0.9; dpn_jauh = 0.1; break;
      case 92: dpn_dekat = 0.8; dpn_jauh = 0.2; break;
      case 93: dpn_dekat = 0.7; dpn_jauh = 0.3; break;
      case 94: dpn_dekat = 0.6; dpn_jauh = 0.4; break;
      case 95: dpn_dekat = 0.5; dpn_jauh = 0.5; break;
      case 96: dpn_dekat = 0.4; dpn_jauh = 0.6; break;
      case 97: dpn_dekat = 0.3; dpn_jauh = 0.7; break;
      case 98: dpn_dekat = 0.2; dpn_jauh = 0.8; break;
      case 99: dpn_dekat = 0.1; dpn_jauh = 0.9; break;

    }
  } else 
  {
    //fuzzifikasi depan dekat
    if (dpn <= sen_dpn2) dpn_dekat = 1.0;
    else if (dpn > sen_dpn2 && dpn < sen_dpn3) 
      dpn_dekat = (sen_dpn3 - dpn) / (sen_dpn3 - sen_dpn2);
    else dpn_dekat = 0;
  
    //fuzzifikasi depan jauh
    if (dpn >= sen_dpn3) dpn_jauh = 1.0;
    else if (dpn < sen_dpn3 && dpn > sen_dpn2) 
      dpn_jauh = (dpn - sen_dpn2) / (sen_dpn3 - sen_dpn2);
    else dpn_jauh = 0;
  }

  if (kn > 6 && kn < 14)
  {
    switch(kn)
    {
      case 6: kn_dekat = 1; kn_sedang = 0; kn_jauh = 0; break;
      case 7: kn_dekat = 0.75; kn_sedang = 0.25; kn_jauh = 0; break;
      case 8: kn_dekat = 0.5; kn_sedang = 0.5; kn_jauh = 0; break;
      case 9: kn_dekat = 0.25; kn_sedang = 0.75; kn_jauh = 0; break;
      case 10: kn_dekat = 0; kn_sedang = 1; kn_jauh = 0; break;
      case 11: kn_dekat = 0; kn_sedang = 0.75; kn_jauh = 0.25; break;
      case 12: kn_dekat = 0; kn_sedang = 0.5; kn_jauh = 0.5; break;
      case 13: kn_dekat = 0; kn_sedang = 0.25; kn_jauh = 0.75; break;
      case 14: kn_dekat = 0; kn_sedang = 0; kn_jauh = 1; break;

    }
  } else 
  {
    //fuzzifikasi kanan depan
    if (kn <= sen_kn2) kn_dekat = 1.0;
    else if (kn > sen_kn2 && kn < sen_kn3) 
      kn_dekat = (sen_kn3 - kn) / (sen_kn3 - sen_kn2);
    else kn_dekat = 0;
  
    //fuzzifikasi kanan sedang
    if (kn == sen_kn3) kn_sedang = 1.0;
    else if (kn < sen_kn3 && kn > sen_kn2) kn_sedang = (kn - sen_kn2)/(sen_kn3 - sen_kn2);
    else if (kn > sen_kn3 && kn < sen_kn4) kn_sedang = (sen_kn4 - kn)/(sen_kn4 - sen_kn3);
    else kn_sedang = 0;
  
    //fuzzifikasi kanan jauh
    if (kn >= sen_kn4) kn_jauh = 1.0;
    else if (kn > sen_kn3 && kn < sen_kn4) kn_jauh = (kn - sen_kn3) / (sen_kn4 - sen_kn3);
    else kn_jauh = 0; 
  }
  //cal_sensor_val(dpn, kan);
  u_1();
  //output();
  defuzifikasi();
  maju(pwm_kn, pwm_kr);
//  Serial.print("dpn_dekat :");
//  Serial.println(dpn_dekat);
//  Serial.print("dpn_jauh  :");
//  Serial.println(dpn_jauh);
//  Serial.print("kn_dekat  :");
//  Serial.println(kn_dekat);
//  Serial.print("kn_sedang :");
//  Serial.println(kn_sedang);
//  Serial.print("kn_jauh   :");
//  Serial.println(kn_jauh);
//  delay(0);
}

//fuzzifikasi
void cal_sensor_val(int d, int k)
{
  float dpn = (float) d;
  float kn = (float) k;
  //fuzzifikasi depan dekat
  if (dpn <= sen_dpn2) dpn_dekat = 1.0;
  else if (dpn > sen_dpn2 && dpn < sen_dpn3) 
    dpn_dekat = (sen_dpn3 - dpn) / (sen_dpn3 - sen_dpn2);
  else dpn_dekat = 0;

  //fuzzifikasi depan jauh
  if (dpn >= sen_dpn3) dpn_jauh = 1.0;
  else if (dpn < sen_dpn3 && dpn > sen_dpn2) 
    dpn_jauh = (dpn - sen_dpn2) / (sen_dpn3 - sen_dpn2);
  else dpn_jauh = 0;

  //fuzzifikasi kanan depan
  if (kn <= sen_kn2) kn_dekat = 1.0;
  else if (kn > sen_kn2 && kn < sen_kn3) 
    kn_dekat = (sen_kn3 - kn) / (sen_kn3 - sen_kn2);
  else kn_dekat = 0;

  //fuzzifikasi kanan sedang
  if (kn == sen_kn3) kn_sedang = 1.0;
  else if (kn < sen_kn3 && kn > sen_kn2) kn_sedang = (kn - sen_kn2)/(sen_kn3 - sen_kn2);
  else if (kn > sen_kn3 && kn < sen_kn4) kn_sedang = (sen_kn4 - kn)/(sen_kn4 - sen_kn3);
  else kn_sedang = 0;

  //fuzzifikasi kanan jauh
  if (kn >= sen_kn4) kn_jauh = 1.0;
  else if (kn > sen_kn3 && kn < sen_kn4) kn_jauh = (kn - sen_kn3) / (sen_kn4 - sen_kn3);
  else kn_jauh = 0; 
}

//nilai minimal tiap rule
void u_1()
{  
  u[0] = min(dpn_dekat, kn_dekat);
  u[1] = min(dpn_dekat, kn_sedang);
  u[2] = min(dpn_dekat, kn_jauh);
  u[3] = min(dpn_jauh, kn_dekat);
  u[4] = min(dpn_jauh, kn_sedang);
  u[5] = min(dpn_jauh, kn_jauh);
//  Serial.print("u[0] :");
//  Serial.println(u[0]);
//  Serial.print("u[1] :");
//  Serial.println(u[1]);
//  Serial.print("u[2] :");
//  Serial.println(u[2]);
//  Serial.print("u[3] :");
//  Serial.println(u[3]);
//  Serial.print("u[4] :");
//  Serial.println(u[4]);
//  Serial.print("u[5] :");
//  Serial.println(u[5]);
}

//fungsi maju
void maju(int pwn_m_kn, int pwm_m_kr)
{
  digitalWrite(M1, LOW);
  analogWrite(E1, pwn_m_kn);
  digitalWrite(M2, LOW);
  analogWrite(E2, pwm_m_kr);
//  Serial.print("pwm kanan :");
//  Serial.println(pwn_m_kn);
//  Serial.print("pwm kiri  :");
//  Serial.println(pwm_m_kr);
}

void output()
{
  //output motor kanan
  z_kr[0] = m1;//m_pelan(u[0]);
  z_kr[1] = m1;//m_pelan(u[1]);
  z_kr[2] = m3;//m_cepat(u[2]);
  z_kr[3] = m1;//m_pelan(u[3]);
  z_kr[4] = m2;//m_sedang(1,u[4]);
  z_kr[5] = m2;//m_sedang(2,u[4]);

  z_kn[0] = m3;//m_cepat(u[0]);
  z_kn[1] = m3;//m_cepat(u[1]);
  z_kn[2] = m1;//m_pelan(u[2]);
  z_kn[3] = m3;//m_cepat(u[3]);
  z_kn[4] = m2;//m_sedang(1,u[4]);
  z_kn[5] = m2;//m_sedang(2,u[4]);
}

void defuzifikasi()
{
  float hasil_kn, pembilang_kn = 0.0, penyebut_kn = 0.0;
  float hasil_kr, pembilang_kr = 0.0, penyebut_kr = 0.0;
  int i = 0;
  for (i; i < 6; i++)
  {
    pembilang_kn += z_kn[i] * u[i];
    penyebut_kn += u[i];

    pembilang_kr += z_kr[i] * u[i];
    if(i<7) penyebut_kr += u[i];
  }
  hasil_kn = pembilang_kn / penyebut_kn;
  hasil_kr = pembilang_kr / penyebut_kr;

  pwm_kn = hasil_kn;
  pwm_kr = hasil_kr;
}

