void setup()
{
  lcd.backlight(); // Backlight of display, to turn off -> lcd.noBacklight()
  lcd.begin(20, 4); // Initialize lcd (chars, rows)
  Serial.begin(9600);
  RFM.Begin(8, -1, 10); // Initialize with pinout (CE, IRQ, CSN(SS))
  RFM.onReceive(receiveEvent);
  RFM.setChannel(10); // Channel to communicate with other radio-module
  lcd.createChar(0, temperature);
  lcd.createChar(1, pressure);
  lcd.createChar(2, degree);
  lcd.createChar(3, humidity);
  lcd.createChar(4, rain);
  lcd.createChar(5, timee);
  lcd.setCursor(0, 0);
  GUI();
}


