void komunikasi() {

  String data_send = String("gas1h2") + ";" + String("pressure") + ";" +
                     String("pressurepercent") + ";" + String("t1") + ";" +
                     String("t2") + ";" + String("V") + String("A") + ";" +
                     String("P") + ";" + ";" + String("E") + ";";
  Serial.println(data_send);

}
