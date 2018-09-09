#include <SPI.h> // SPI connect library
#include <rfm73.h> // RFM75-S - Radio module library
//rmf73 RFM - already added in rfm73 library
#include <LiquidCrystal_I2C.h> // library for LCD connected by I2C



/////////////////////////////////////////////////////

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Set initializer for lcd with I2C address 0x3F

/////////////////////////////////////////////////////
unsigned long rememberLED = 0;
unsigned long rememberSend = 0;
unsigned long rememberTime = 0;
unsigned long rememberSAT = 0;
////////////////////////////////////////////////////
bool RecTime = false;
bool RecData = false;
bool TimeStart = false;
bool terror = false;
int count = 0;
byte GetData[2];

int rainy;
String rainfall;

int hours[2] = {0,0};
int minutes[2] = {0,0};
int seconds[2] = {0,0};


