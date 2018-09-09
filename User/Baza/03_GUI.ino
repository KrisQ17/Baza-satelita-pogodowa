void GUI() {
  lcd.setCursor(0, 0);
  lcd.print((char)0); // temperature symbol
  lcd.setCursor(9, 0);
  lcd.print((char)5); // time symbol
  lcd.setCursor(0, 1);
  lcd.print((char)1); // pressure symbol
  lcd.setCursor(0, 2);
  lcd.print((char)3); // humidity symbol
  lcd.setCursor(0, 3);
  lcd.print((char)4); // rain symbol
}


void rainF(int rain) {
  rainy = map(rain, 1023, 200, 0, 100); // value from rainAnalog
  if (100 >= rainy & rainy >= 76) {
    rainfall = "heavy rain";
  }
  if (75 >= rainy & rainy >= 51) {
    rainfall = "strong rain";
  }
  if (50 >= rainy & rainy >= 26) {
    rainfall = "rain";
  }
  if (25 >= rainy & rainy >= 5) {
    rainfall = "weak rain";
  }
  if (4 >= rainy & rainy >= 0) {
    rainfall = "no rain";
  }
  return;
}

void ccc (){
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
        lcd.setCursor(14, 1);
        lcd.print("SAT");
        lcd.setCursor(13, 2);
        lcd.print("ERROR");
}


