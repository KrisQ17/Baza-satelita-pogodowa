#include <SdFat.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <SPI.h> // SPI connect library
#include <RTClib.h>
#include <Wire.h> // library for I2C
#include <rfm73.h> // RFM75-S - Radio module library
//rmf73 RFM - already added in rfm73 library
#include "DHT.h"

//////////////////////
#define rainAnalog A0
#define DHTPIN 6
#define DHTTYPE DHT11
#define BMP280PIN 9
#define CERADIO 8
#define MISO 12
#define MOSI 11
#define SCK 13
#define SDPIN 7
#define CSNRADIO 10
#define YELLOWLED 2
#define REDLED 3
#define GREENLED 4
#define BLUELED 5
/////////////////////
RTC_DS3231 rtc;
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP280 bmp(9);
SdFile dataFile;
SdFat sd;
Sd2Card card;
SdVolume vol;
/////////////////////
unsigned long actualTime = 0;
unsigned long rememberedTime1 = 0;
unsigned long rememberedTime2 = 0;
int IdSAT;
int IdPackage;
/////////
byte SendArray[15]; /// {id sat, id package, temp, humidity, rain 1byte, rain 2byte, pressure 1byte, pressure 2byte, dht11-error, bmp280-error, time-error, sd-error, rain-error, checksum 1byte, checksum 2byte}
byte TimeArray[6]; //{id sat, id package, hh, mm, ss, checksum}
////////
const String months[13] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
char filename[] = "00000000.CSV";
////////
bool wyb = true;
////////
int rain;        // int for rain 0-100
String rainfall; // 4 types of rain: [5-25, weak rain][26-50, rain][51-75, strong rain][76-100, heavy rain] 
///////
int chk;
float fs = 100;
//////


