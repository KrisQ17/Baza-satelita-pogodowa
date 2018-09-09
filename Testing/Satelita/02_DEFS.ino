void rainF() {
  rain = map(analogRead(rainAnalog), 1023, 200, 0, 100); // value from rainAnalog
  if (100 >= rain & rain >= 76) {
    rainfall = "heavy rain";
  }
  if (75 >= rain & rain >= 51) {
    rainfall = "strong rain";
  }
  if (50 >= rain & rain >= 26) {
    rainfall = "rain";
  }
  if (25 >= rain & rain >= 5) {
    rainfall = "weak rain";
  }
  if (4 >= rain & rain >= 0) {
    rainfall = "no rain";
  }
  return;
}

void writeline() {
  Serial.println("writeline start...");
  if (!sd.begin(SDPIN, SPI_HALF_SPEED)) {
    return;
  }
  DateTime now = rtc.now();
  //Serial.println("writeline start...");
  filename[0] = (now.year() / 1000) % 10 + '0'; //To get 1st digi1t from year()
  filename[1] = (now.year() / 100) % 10 + '0'; //To get 2nd digit from year()
  filename[2] = (now.year() / 10) % 10 + '0'; //To get 3rd digit from year()
  filename[3] = now.year() % 10 + '0'; //To get 4th digit from year()
  filename[4] = now.month() / 10 + '0'; //To get 1st digit from month()
  filename[5] = now.month() % 10 + '0'; //To get 2nd digit from month()
  filename[6] = now.day() / 10 + '0'; //To get 1st digit from day()
  filename[7] = now.day() % 10 + '0'; //To get 2nd digit from day()
  dataFile.open(filename, O_RDWR | O_CREAT | O_AT_END);
  dataFile.print(now.hour(), DEC);
  dataFile.print(":");
  dataFile.print(now.minute(), DEC);
  dataFile.print(":");
  dataFile.print(now.second(), DEC);
  dataFile.print(";Rain:");
  dataFile.print(rainfall);
  dataFile.print(";Temp:");
  dataFile.print(float(dht.readTemperature()));
  dataFile.print("*C;HUMIDITY:");
  dataFile.print(float(dht.readHumidity()));
  dataFile.print("%;PRESSURE:");
  dataFile.print(float(bmp.readPressure() / 100));
  dataFile.print("hPa \n");
  dataFile.close();
  //Serial.println("Zapisano");
  Serial.println("writeline dziala");
}

void errors() {
  /////// SD MODULE
  if (!sd.begin(SDPIN, SPI_HALF_SPEED)) {
    //Serial.println("Access to sd denied");
    SendArray[11] = byte(1);
    digitalWrite(REDLED, LOW);
    digitalWrite(GREENLED, HIGH);
  }
  else {
    SendArray[11] = byte(0);
    digitalWrite(REDLED, HIGH);
    digitalWrite(GREENLED, LOW);
  }
  /////// END SD MODULE



  /////////// BMP280 MODULE
  if (!bmp.begin()) {
    SendArray[9] = byte(1);
    //Serial.println("bmp problem");
  }
  else {
    SendArray[9] = byte(0);
  }
  /////////// END BMP280 MODULE

  /////////// RTC MODULE
  if (!rtc.begin()) {
    SendArray[10] = byte(1);
    //Serial.println("rtc problem");
    //Serial.println(bmp.readPressure());
  }
  else {
    //Serial.println(bmp.readPressure());
    SendArray[10] = byte(0);
  }
  /////////// END RTC MODULE

  /////////// DHT11 MODULE
  if (isnan(dht.readTemperature()) || isnan(dht.readHumidity())) {
    //Serial.println("Failed to read from DHT sensor!");
    SendArray[8] = byte(1);
  }
  else{
    SendArray[8]= byte(0);
  }
  /////////// END DHT11 MODULE


  /////////// YL-83 MODULE
  rain = analogRead(rainAnalog);
  //Serial.println(rain);
  if (rain <= 100) {
    //Serial.println("yl-83 error");
    SendArray[12] = byte(1);
  }
  else {
    SendArray[12] = byte(0);
  }
  /////////// END YL-83 MODULE
  if(SendArray[9] == byte(1) or SendArray[10] == byte(1) or SendArray[12] == byte(1)){
    digitalWrite(YELLOWLED, LOW);
  }
  else{
    digitalWrite(YELLOWLED, HIGH);
  }
  return;
}


void SendByRadio() {
  SendArray[1] = byte(1);
  SendArray[2] = byte(int(dht.readTemperature()));
  SendArray[3] = byte(int(dht.readHumidity()));
  SendArray[4] = highByte(rain);
  SendArray[5] = lowByte(rain);
  SendArray[6] = highByte(int(bmp.readPressure() / 100));
  SendArray[7] = lowByte(int(bmp.readPressure() / 100));
  SendArray[13] = highByte(2 + SendArray[8]+ SendArray[9]+ SendArray[10]+ SendArray[11]+ SendArray[12]+int(dht.readTemperature()) + int(dht.readHumidity()) + rain + (int(bmp.readPressure() / 100)));
  SendArray[14] = lowByte(2 + SendArray[8]+ SendArray[9]+ SendArray[10]+ SendArray[11]+ SendArray[12]+int(dht.readTemperature()) + int(dht.readHumidity()) + rain + (int(bmp.readPressure() / 100)));
  return;
}

void SendTimeByRadio() {
  TimeArray[1] = byte(2);
  DateTime now = rtc.now();
  TimeArray[2] = byte(now.hour());
  TimeArray[3] = byte(now.minute());
  TimeArray[4] = byte(now.second());
  TimeArray[5] = byte(3 + now.hour() + now.minute() + now.second());
  return;
}




