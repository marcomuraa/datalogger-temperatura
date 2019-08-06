#include <SPI.h>
#include <SD.h>
#include <OneWire.h>            
#include <DallasTemperature.h>

const int chipSelect = 4;

#define ONE_WIRE_BUS_PIN 3

OneWire oneWire(ONE_WIRE_BUS_PIN);  // Setup oneWire
DallasTemperature sensors(&oneWire);//  oneWire to Dallas Temperature.


// Assign the addresses of your  temp sensors.You must use 1 wire adress finder

DeviceAddress Probe01 = { 0x28, 0xFF, 0x4B, 0xC9, 0x80, 0x17, 0x04, 0xFA }; //inox2
DeviceAddress Probe02 = { 0x28, 0xFF, 0x00, 0x09, 0x81, 0x17, 0x04, 0xF1 }; //Inox1

void setup() {
  // Open serial communications and wait for port to open:
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  
  // Initialize the Temperature measurement library
  sensors.begin();
  
  // set the resolution to 9 bit (Can be 9 to 12 bits .. lower is faster)
  sensors.setResolution(Probe01, 12);
  sensors.setResolution(Probe02, 12);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

void loop() {
  // make a string for assembling the data to log:
  String dataString = "";

    sensors.requestTemperatures();  

    float sensor1 = sensors.getTempCByIndex(0);
    dataString += String(sensor1);
    dataString += " ";

    sensors.requestTemperatures();
    float sensor2 = sensors.getTempCByIndex(1);
    dataString += String(sensor2);


  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);

    digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(700);              // wait for 700 milliseconds
    digitalWrite(2, LOW);
    delay(30000);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}
