void setup() {
  //Serial.begin(9600);
  Wire.begin();
  RFM.Begin(CERADIO, -1, CSNRADIO); // Initialize with pinout (CE, IRQ, CSN(SS))
  RFM.setChannel(10); // Channel to communicate with other radio-module
  RFM.setMode(1); //  receiver
  card.init(SPI_HALF_SPEED, SDPIN);
  vol.init(&card);
  dht.begin();
  RFM.onReceive(receiveEvent);
  pinMode(REDLED, OUTPUT); // zielona
  pinMode(BLUELED, OUTPUT); // czerwona
  pinMode(GREENLED, OUTPUT);
  pinMode(YELLOWLED, OUTPUT);
  digitalWrite(BLUELED, HIGH);
  digitalWrite(GREENLED, HIGH);
  digitalWrite(REDLED, HIGH);
  digitalWrite(YELLOWLED, HIGH);
  SendArray[0] = byte(1);
  TimeArray[0] = byte(1);
}



