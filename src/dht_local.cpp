/*
//// Example testing sketch for various DHT humidity/temperature sensors
//// Written by ladyada, public domain
//
//// REQUIRES the following Arduino libraries:
//// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
//// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
//
#include <Arduino.h>
#include "DHT.h"
#include <SPI.h>
#include <SD.h>
#define SER SerialUSB
#define chipSelect 11

void setup() {
    SER.begin(9600);
    while(!SD.begin(chipSelect)) {
        SER.println("Card couldn't be initialized!");
        delay(500);
    }
}
void loop(){
    File datalog = SD.open("datalog.txt", FILE_READ);
    char buffer [512];
    while (datalog.readBytesUntil('\n', buffer, 512)){
        SER.println(buffer);

    }


    delay(5000);
}

//#define chipSelect 11
//
//#define SER SerialUSB
//
//#define DHTPIN 2     // Digital pin connected to the DHT sensor
//// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
//// Pin 15 can work but DHT must be disconnected during program upload.
//
//// Uncomment whatever type you're using!
////#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
////#define DHTTYPE DHT21   // DHT 21 (AM2301)
//
//// Connect pin 1 (on the left) of the sensor to +5V
//// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
//// to 3.3V instead of 5V!
//// Connect pin 2 of the sensor to whatever your DHTPIN is
//// Connect pin 3 (on the right) of the sensor to GROUND (if your sensor has 3 pins)
//// Connect pin 4 (on the right) of the sensor to GROUND and leave the pin 3 EMPTY (if your sensor has 4 pins)
//// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
//
//// Initialize DHT sensor.
//// Note that older versions of this library took an optional third parameter to
//// tweak the timings for faster processors.  This parameter is no longer needed
//// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    SerialUSB.begin(9600);

    dht.begin();

    while(!SD.begin(chipSelect))
    {
        SER.println("Card couldn't be initialized!");
        delay(500);

    }

}

void loop() {
    // Wait a few seconds between measurements.
    delay(2000);

    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    float t = dht.readTemperature();
    // Read temperature as Fahrenheit (isFahrenheit = true)
    float f = dht.readTemperature(true);

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t) || isnan(f)) {
        SerialUSB.println(F("Failed to read from DHT sensor!"));
        return;
    }

    // Compute heat index in Fahrenheit (the default)
    float hif = dht.computeHeatIndex(f, h);
    // Compute heat index in Celsius (isFahreheit = false)
    float hic = dht.computeHeatIndex(t, h, false);

    SerialUSB.print(F("Humidity: "));
    SerialUSB.print(h);
    SerialUSB.print(F("%  Temperature: "));
    SerialUSB.print(t);
    SerialUSB.print(F("°C "));
    SerialUSB.print(f);
    SerialUSB.print(F("°F  Heat index: "));
    SerialUSB.print(hic);
    SerialUSB.print(F("°C "));
    SerialUSB.print(hif);
    SerialUSB.println(F("°F"));

    String dataString = "";

    dataString += String(h);
    dataString += ", ";
    dataString += String(t);

    File dataFile = SD.open("datalog.txt", FILE_WRITE);

    if(dataFile)
    {
        dataFile.println(dataString);
        dataFile.close();
    }
    else
    {
        SerialUSB.println("Nie udało się otworzyć pliku");
    }
}
*/
