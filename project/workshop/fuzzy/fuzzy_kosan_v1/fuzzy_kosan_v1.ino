#include <NewPing.h>
 
#define TRIGGER_PIN1 7
#define ECHO_PIN1 6 
#define TRIGGER_PIN2 5 
#define ECHO_PIN2 4  

int motor_forward1 = 12;
int motor_reverse1 = 13;
int pwmpin1 = 11;

int motor_forward2 = 9;
int motor_reverse2 = 8;
int pwmpin2 = 10;

#define MAX_DISTANCE 1000 

//membership function sensor depan
#define sen_dpn1 0.0
#define sen_dpn2 20.0
#define sen_dpn3 40.0

//membership function sensor kanan
#define sen_kn1 0.0
#define sen_kn2 6.0
#define sen_kn3 10.0
#define sen_kn4 14.0

//membership function output, pwm
#define m1 70.0
#define m2 150.0
#define m3 230.0

NewPing sonar_dpn(TRIGGER_PIN2, ECHO_PIN2, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar_kn(TRIGGER_PIN1, ECHO_PIN1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

double u[7]={0.0};
double z_kr[8]={0.0};
double z_kn[8]={0.0};
double dpn_dekat, dpn_jauh;
double kn_dekat, kn_sedang, kn_jauh;
int pwm_kn = 0;
int pwm_kr = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(motor_forward1, OUTPUT);
  pinMode(motor_reverse1, OUTPUT);
  pinMode(pwmpin1, OUTPUT);
  pinMode(motor_forward2, OUTPUT);
  pinMode(motor_reverse2, OUTPUT);
  pinMode(pwmpin2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int dpn = sonar_dpn.ping_cm();
  int kan = sonar_kn.ping_cm();
  cal_sensor_val(dpn, kan);
  u_1();
  output();
  defuzifikasi();
  maju(pwm_kn, pwm_kr);
//  Serial.print("sensor kanan :");
//  Serial.println(kan);
//  Serial.print("sensor depan :");
//  Serial.println(dpn);
//  maju(kan, dpn);
}

void maju(int kn, int kr) {
  digitalWrite(motor_forward1,1); //terminal D1 will be HIGH
  digitalWrite(motor_reverse1,0); //terminal D2 will be LOW
  digitalWrite(motor_forward2,1); //terminal D1 will be HIGH
  digitalWrite(motor_reverse2,0); //terminal D2 will be LOW
  analogWrite(pwmpin1,kn);
  analogWrite(pwmpin2,kr);
}

//fuzzifikasi
void cal_sensor_val(int d, int k)
{
  double dpn = (double) d;
  double kn = (double) k;
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
  double hasil_kn, pembilang_kn = 0.0, penyebut_kn = 0.0;
  double hasil_kr, pembilang_kr = 0.0, penyebut_kr = 0.0;
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

