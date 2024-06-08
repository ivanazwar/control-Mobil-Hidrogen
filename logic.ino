void kontrol() {

  switch (var) {
    case 0: digitalWrite(selenoid, 0);
            digitalWrite(fan, 0);
            var = 1;
            break;
    case 1: if (in_voltage > 19)var = 2;
            else var = 1;
            break;
    case 2: cnt = 0;
            cnt++;
            if (cnt > 5) var = 3;
            break;
    case 3:
            if (in_voltage <= 19) {
            digitalWrite(inverter, 1);
            var = 1;}
            else digitalWrite(inverter, 0);
               break;

  }

}
