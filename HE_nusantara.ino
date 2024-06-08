#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <SimpleKalmanFilter.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <PZEM004Tv30.h>

SimpleKalmanFilter kalman_bar(2.0, 2.0, 0.01);
LiquidCrystal_I2C lcd(0x27, 20, 4);

#define ANALOG_IN_PIN A1
#define inverter 26
#define selenoid 24
#define PIN_buzzer 2
#define fan 28
#define SSR1 32
#define SSR2 34
#define SSR3 36
#define SSR4 38
#define SSR5 40
#define SSR6 42
#define SSR7 44
#define SSR8 46
#define PIN_buzzer 2

PZEM004Tv30 pzem(18, 19);

int var = 0;
//tx 19,rx18,pres:a0, a6/t1:d6,a8/t2:d4
float adc_voltage = 0.0;
float in_voltage = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
float ref_voltage = 5.0;
int adc_value = 0;

const int oneWireBus1 = 4;
const int oneWireBus2 = 6;
float pressure, V, A, E, P;
int pressurepress, pressurepercent;
int gas1h2, gas2h2;
int batas_gas = 200;
int adc_tank, cnt;

const int PIN_pressure = A0;
const int PIN_gas1_h2 = A2;
const int PIN_gas2_h2 = A4;
float t1, t2;


OneWire oneWire1(oneWireBus1);
DallasTemperature sensorsds1(&oneWire1);
OneWire oneWire2(oneWireBus2);
DallasTemperature sensorsds2(&oneWire2);





void setup(void)
{
  Serial.begin(115200);
  lcd.begin();
  sensorsds1.begin();
  sensorsds2.begin();
  pinMode(inverter, OUTPUT);
  pinMode(selenoid, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(PIN_buzzer, OUTPUT);
  digitalWrite(inverter, 1);
  digitalWrite(selenoid, 1);
  digitalWrite(fan, 1);
  digitalWrite(PIN_buzzer, 1);

  pinMode(SSR1, OUTPUT);
  pinMode(SSR2, OUTPUT);
  pinMode(SSR3, OUTPUT);
  pinMode(SSR4, OUTPUT);
  pinMode(SSR5, OUTPUT);
  pinMode(SSR6, OUTPUT);
  pinMode(SSR7, OUTPUT);
  pinMode(SSR8, OUTPUT);
  beepstarting();

  lcd.setCursor(0, 0); lcd.print("        HELLO,,,    ");
  lcd.setCursor(0, 1); lcd.print("   H-EV NUSANTARA   ");
  lcd.setCursor(0, 2); lcd.print("ITSxNUSANTARA POWER ");
  lcd.setCursor(0, 3); lcd.print("starting...         ");

  for (int x = 1; x <= 100;  ++x) {
    pressure = analogRead(PIN_pressure);
    pressure = ((pressure - 97.478) / 2.5465);
    pressure = kalman_bar.updateEstimate(pressure);
    delay(50);
  }
  //
  //  digitalWrite(inverter, 1);
  //  digitalWrite(selenoid, 1);
  //  digitalWrite(fan, 1);
  digitalWrite(SSR1, 1);
  digitalWrite(SSR2, 1);
  digitalWrite(SSR3, 1);
  digitalWrite(SSR4, 1);
  digitalWrite(SSR5, 1);
  digitalWrite(SSR6, 1);
  digitalWrite(SSR7, 1);
  digitalWrite(SSR8, 1);
  var=0;
  lcd.clear();
}


void loop(void) {
  pressure = analogRead(PIN_pressure);
  adc_tank = pressure;
  pressure = ((pressure - 93.136) / 3.0837);
  pressure = kalman_bar.updateEstimate(pressure);
  pressurepercent = map(pressure, 0, 150, 0, 100);
  read_sensor();
  komunikasi();
  kontrol();
 // print_serial();

  lcd.setCursor(0, 0); lcd.print("T1:");
  lcd.print(t1, 1);
  lcd.setCursor(10, 0);
  lcd.print("T2:");
  lcd.print(t2, 1);
  lcd.setCursor(0, 1); lcd.print("PRES:"); lcd.print(pressure, 1); lcd.print("Bar"); 
  lcd.setCursor(0, 2); lcd.print("TANK:");lcd.print(pressurepercent); lcd.print("%");
  lcd.setCursor(0, 3); lcd.print("H1:"); lcd.print("SAFE!!"); lcd.setCursor(10, 3); lcd.print("H2:"); lcd.print("SAFE!!");



}

void beepstarting() {
  digitalWrite(PIN_buzzer, LOW);  delay(600);   digitalWrite(PIN_buzzer, HIGH);  delay(90);
  digitalWrite(PIN_buzzer, LOW);  delay(300);   digitalWrite(PIN_buzzer, HIGH);  delay(10);
  digitalWrite(PIN_buzzer, LOW);  delay(200);   digitalWrite(PIN_buzzer, HIGH);  delay(50);
}
void beepp() {
  digitalWrite(PIN_buzzer, LOW);  delay(200);   digitalWrite(PIN_buzzer, HIGH);  delay(50);
}
void beepp2() {
  digitalWrite(PIN_buzzer, LOW);  delay(70);   digitalWrite(PIN_buzzer, HIGH);  delay(50);
}
