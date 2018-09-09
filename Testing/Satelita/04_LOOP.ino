void loop() {
  actualTime = millis();
  DateTime now = rtc.now();
  RFM.tick();
  errors();
  delay(1);
  //Serial.println(IdPackage);

  if (fs <= 40) {
    SendArray[11] = byte(2);
    if (actualTime - rememberedTime1 >= 1000) {
      rememberedTime1 = actualTime;
      digitalWrite(BLUELED, HIGH);
    }
    else {
      digitalWrite(BLUELED, LOW);
    }
  }
  else {
    digitalWrite(BLUELED, LOW);
  }


  if (IdSAT == 1 and IdPackage == 1) {
    //Serial.println("Loop 1");
    errors();
    RFM.setMode(0); // send
    SendByRadio();
    RFM.send(SendArray, 15);
    RFM.flushTxFIFO();
    RFM.setMode(1); //receive
    IdSAT = 0;
    IdPackage = 0;
    //Serial.println("Loop 1 eND");
  }

 
  if (IdSAT == 1 and IdPackage == 2) {
    //Serial.println("Loop 3");
    RFM.setMode(0); // send
    SendTimeByRadio();
    RFM.send(TimeArray, 6);
    RFM.flushTxFIFO();
    RFM.setMode(1); //receive
    IdSAT = 0;
    IdPackage = 0;
    //Serial.println("Loop 3 eND");
  }
  if (actualTime - rememberedTime2 >= 1800000) {
    digitalWrite(REDLED, LOW);
    //Serial.println("Loop 2");
    rememberedTime2 = actualTime;
    rainF();
    writeline();
    digitalWrite(REDLED, HIGH);
    uint32_t volFree = vol.freeClusterCount();
    fs = 0.000512 * volFree * vol.blocksPerCluster();
    //Serial.println(fs);
    //Serial.println("Loop 2 eND");
  }


}

void receiveEvent(void) {
  IdSAT = RFM.getRcvByte(0);
  IdPackage = RFM.getRcvByte(1);
  RFM.flushRxFIFO();
}


