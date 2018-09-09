void loop()
{
   unsigned long actualTime = millis();
      if (count >= 2 and actualTime - rememberSAT >= 5000){
        rememberSAT = actualTime;
  ccc();
  }
  RFM.tick(); // Listening to receive data
  delay(10);
  // Display Time
  if (actualTime - rememberLED >= 1000UL and TimeStart == true) {
    rememberLED = actualTime;
    if (seconds[1] <= 9) {
      seconds[1] += 1;
    }
    if (seconds[1] > 9) {
      seconds[0] += 1;
      seconds[1] = 0;
    }
    if (seconds[0] == 6  and seconds[1] == 0) {
      minutes[1] += 1;
      seconds[0] = 0;
    }
    if (minutes[1] > 9) {
      minutes[0] += 1;
      minutes[1] = 0;
    }
    if (minutes[0] == 6 and minutes[1] == 0) {
      hours[1] += 1;
      minutes[0] = 0;
    }
    if (hours[1] > 9) {
      hours[0] += 1;
      hours[1] = 0;
    }
    if (hours[0] == 2 and hours[1] == 4) {
      hours[0] = 0;
      hours[1] = 0;
    }
    lcd.setCursor(11, 0);
    lcd.print(hours[0]);
    lcd.setCursor(12, 0);
    lcd.print(hours[1]);
    lcd.setCursor(13, 0);
    lcd.print(":");
    lcd.setCursor(14, 0);
    lcd.print(minutes[0]);
    lcd.setCursor(15, 0);
    lcd.print(minutes[1]);
    lcd.setCursor(16, 0);
    lcd.print(":");
    lcd.setCursor(17, 0);
    lcd.print(seconds[0]);
    lcd.setCursor(18, 0);
    lcd.print(seconds[1]);

  }
  else if (TimeStart == false) {
    lcd.setCursor(11, 0);
    lcd.print("--:--:--");
  }
  // Display Time End



  // Updating data 20s, and initalize start
  if (actualTime - rememberSend >= 20000 or RecData == false) {
    rememberSend = actualTime;
    RecData = true;
    RFM.setMode(0); // send
    GetData[0] = byte(1);
    GetData[1] = byte(1);
    RFM.send(GetData, 2);
    RFM.flushTxFIFO();
    RFM.setMode(1); // receive
        count++;
  }
delay(100);
  if (actualTime - rememberTime >= 1800000 or (actualTime - rememberTime >= 8000 and RecTime == false) ) {
    rememberTime = actualTime;
    RecTime = true;
    RFM.setMode(0); // send
    GetData[0] = byte(1);
    GetData[1] = byte(2);
    RFM.send(GetData, 2);
    RFM.flushTxFIFO();
    RFM.setMode(1); // receive
        count++;
  }


}

void receiveEvent(void) {
  count = 0;
  int decodedID = RFM.getRcvByte(0);
  if (decodedID == 1) {
    int packageID = RFM.getRcvByte(1);
    Serial.println(packageID);
    
    if (packageID == 1) {
      Serial.println("Test1");
      int packageTEMP = RFM.getRcvByte(2);
      int packageHUM = RFM.getRcvByte(3);
      int packageRAIN = (RFM.getRcvByte(4) << 8) + RFM.getRcvByte(5);
      int packagePRESS = (RFM.getRcvByte(6) << 8) + RFM.getRcvByte(7);
      int DHTerror = RFM.getRcvByte(8);
      int BMPerror = RFM.getRcvByte(9);
      int TIMEerror = RFM.getRcvByte(10);
      int SDerror = RFM.getRcvByte(11);
      int RAINerror = RFM.getRcvByte(12);
      int checksum = (RFM.getRcvByte(13) << 8) + RFM.getRcvByte(14);
      int checksumReceived = packageTEMP + packageHUM + packageRAIN + packagePRESS + DHTerror + BMPerror + TIMEerror + SDerror + RAINerror + 2;
      if (checksum != checksumReceived) {
        lcd.setCursor(16, 2);
        lcd.print("1");
        lcd.setCursor(2, 0);
        lcd.print("       ");
        lcd.setCursor(2, 0);
        lcd.print("----");
        lcd.setCursor(2, 1);
        lcd.print("          ");
        lcd.setCursor(2, 1);
        lcd.print("----");
        lcd.setCursor(2, 2);
        lcd.print("       ");
        lcd.setCursor(2, 2);
        lcd.print("----");
        lcd.setCursor(2, 3);
        lcd.print("            ");
        lcd.setCursor(2, 3);
        lcd.print("----");
        lcd.setCursor(15, 1);
        lcd.print("-");
        lcd.setCursor(16, 1);
        lcd.print("-");
        lcd.setCursor(17, 1);
        lcd.print("-");
        lcd.setCursor(18, 1);
        lcd.print("-");
        lcd.setCursor(19, 1);
        lcd.print("-");
      }
      if (checksum == checksumReceived) {
        lcd.setCursor(16, 2);
        lcd.print("0");

        // Temperature
        if (DHTerror == 1) {
          lcd.setCursor(2, 0);
          lcd.print("       ");
          lcd.setCursor(2, 0);
          lcd.print("----");
          lcd.setCursor(15, 1);
          lcd.print("1");
        }
        else if (DHTerror == 0) {
          lcd.setCursor(2, 0);
          lcd.print("       ");
          lcd.setCursor(2, 0);
          lcd.print(packageTEMP);
          lcd.print(" ");
          lcd.print((char)2); // degree symbol
          lcd.print("C");
          lcd.setCursor(15, 1);
          lcd.print("0");
        }
        // Pressure
        if (BMPerror == 1) {
          lcd.setCursor(2, 1);
          lcd.print("          ");
          lcd.setCursor(2, 1);
          lcd.print("----");
          lcd.setCursor(16, 1);
          lcd.print("1");
        }
        else if (BMPerror == 0) {
          lcd.setCursor(2, 1);
          lcd.print("          ");
          lcd.setCursor(2, 1);
          lcd.print(packagePRESS);
          lcd.print(" hPa");
          lcd.setCursor(16, 1);
          lcd.print("0");
        }
        // Humidity
        if (DHTerror == 1) {
          lcd.setCursor(2, 2);
          lcd.print("       ");
          lcd.setCursor(2, 2);
          lcd.print("----");
          lcd.setCursor(15, 1);
          lcd.print("1");
        }
        else if (DHTerror == 0) {
          lcd.setCursor(2, 2);
          lcd.print("       ");
          lcd.setCursor(2, 2);
          lcd.print(packageHUM);
          lcd.print(" %");
          lcd.setCursor(15, 1);
          lcd.print("0");
        }
        // Rain
        if (RAINerror == 1) {
          lcd.setCursor(2, 3);
          lcd.print("            ");
          lcd.setCursor(2, 3);
          lcd.print("----");
          lcd.setCursor(17, 1);
          lcd.print("1");
        }
        else if (RAINerror == 0) {
          rainF(packageRAIN);
          lcd.setCursor(2, 3);
          lcd.print("            ");
          lcd.setCursor(2, 3);
          lcd.print(rainfall);
          lcd.setCursor(17, 1);
          lcd.print("0");
        }
        if (TIMEerror == 1) {
          lcd.setCursor(18, 1);
          lcd.print("1");
          terror = false;
        }
        else if (TIMEerror == 0) {
          lcd.setCursor(18, 1);
          lcd.print("0");
          terror = true;
        }
        if (SDerror == 1) {
          lcd.setCursor(19, 1);
          lcd.print("1");
          lcd.setCursor(14, 3);
          lcd.print("ERR-SD");
        }
        if (SDerror == 2) {
          lcd.setCursor(19, 1);
          lcd.print("0");
          lcd.setCursor(13, 3);
          lcd.print("FULL-SD");
        }
        else if (SDerror == 0) {
          lcd.setCursor(19, 1);
          lcd.print("0");
          lcd.setCursor(14, 3);
          lcd.print("      ");
        }
      }




      RFM.flushRxFIFO();
      Serial.println("Test1 END");
    }
    if (packageID == 2) {
      //Serial.println("Test2");
      int packageHH = RFM.getRcvByte(2);
      int packageMM = RFM.getRcvByte(3);
      int packageSS = RFM.getRcvByte(4);
      int checksumtime = RFM.getRcvByte(5);
      int checksumReceivedTime = packageHH + packageMM + packageSS + 3;
      if (checksumReceivedTime != checksumtime or checksumReceivedTime > 141) {
        lcd.setCursor(15, 2); // checksum error on lcd
        lcd.print("1");

        lcd.setCursor(11, 0);
        lcd.print("--:--:--");
      }
      if (checksumReceivedTime == checksumtime and terror == true) {
        TimeStart = true;
        lcd.setCursor(15, 2); // checksum error on lcd
        lcd.print("0");
        if (packageHH <= 9) {
          hours[0] = 0;
          hours[1] = packageHH;
        }
        else {
          hours[0] = packageHH / 10;
          hours[1] = packageHH % 10;
        }

        if (packageMM <= 9) {
          minutes[0] = 0;
          minutes[1] = packageMM;
        }
        else {
          minutes[0] = packageMM / 10;
          minutes[1] = packageMM % 10;
        }

        if (packageSS <= 9) {
          seconds[0] = 0;
          seconds[1] = packageSS;
        }
        else {
          seconds[0] = packageSS / 10;
          seconds[1] = packageSS % 10;
        }

      }
      RFM.flushRxFIFO();
    }
    lcd.setCursor(17, 2);
    lcd.print(0);
  }
  else {
    lcd.setCursor(17, 2);
    lcd.print(1);
  }
}



