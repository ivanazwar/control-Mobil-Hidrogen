void read_sensor() {


  adc_value = analogRead(ANALOG_IN_PIN);
  adc_voltage  = (adc_value * ref_voltage) / 1024.0;
  in_voltage = adc_voltage*(R1+R2)/R2;

  sensorsds1.requestTemperatures();
  sensorsds2.requestTemperatures();

  V = pzem.voltage();
  A = pzem.current();
  P = pzem.power();
  E = pzem.energy();

  t1 = sensorsds1.getTempCByIndex(0);
  t2 = sensorsds2.getTempCByIndex(0);

  gas1h2 = analogRead(PIN_gas1_h2);
  gas2h2 = analogRead(PIN_gas2_h2);

  if (gas1h2 >= batas_gas) {
    gas1h2 = 1;
  } else {
    gas1h2 = 0;
  }
  if (gas2h2 >= batas_gas) {
    gas2h2 = 1;
  } else {
    gas2h2 = 0;
  }

}

void print_serial() {
  Serial.print("T1: ");
  Serial.print(t1);
  Serial.print("  T2: ");
  Serial.print(t2);
  Serial.print(" || ");
  Serial.print("P:");
  Serial.print(pressure);
  Serial.print(" || ");
  Serial.print("P%:");
  Serial.print(pressurepercent);
  Serial.print(" || ");
  Serial.print(V);
  Serial.print(" || ");
  Serial.print(A);
  Serial.print(" || ");
  Serial.print(P);
  Serial.print(" || ");
  Serial.print(E);
  Serial.print(" || ");
  Serial.println(in_voltage);

}
