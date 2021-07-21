// Includes
#include <Arduino.h>
#include <Wire.h>
#include <LSM6.h>
#include "DHT.h"
#include <SD.h>

// Conventions
// Convention motivated by the length of "SerialUSB" name
#define SER SerialUSB

// Macros
#define SD_CS 11 // SD card Chip Select - pin needed to initialise SD card
#define DHT_PIN 2
#define DHT_TYPE DHT22

// Utility Macros
#define LOG_INIT_FAILED(err) SER.println(err); delay(500)
#define LOG_ERR(err) SER.print("[ERROR] "); SER.println(err)

// Device interfaces
LSM6 imu;
DHT dht(DHT_PIN, DHT_TYPE);

// Files
File data_file;

// Static variables
float h, t;
char output_buffer[512];
char file_buffer[512];

// Utility function declarations
void
ReadFileToSerial(const char* filename);

// Main Program
void
setup()
{
    // Serial port initialization
    SER.begin(9600);

    // I2C initialization
    Wire.begin();

    // Devices Initializations
    while (!imu.init())
    {
        // BE CAREFUL! Macro with parameter - replaces the code with parameter inserted
        LOG_INIT_FAILED("Failed to initialise IMU");
    }
    imu.enableDefault();
    SER.println("Accelerometer and gyroscope initialized successfully!");

    dht.begin();
    SER.println("DHT22 initialized successfully!");

    while(!SD.begin(SD_CS)){
        LOG_INIT_FAILED("Failed to initialise SD card");
    }
    SER.println("SD card initialized successfully!");
}

void
loop()
{
    // Devices read
    imu.read();
    h = dht.readHumidity();
    t = dht.readTemperature();

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)){
        LOG_ERR("Failed to measure from DHT sensor");
    }

    // Write to form making sense for serial port
    sprintf(output_buffer, "Humidity: %s, Temperature: %s °C \n"
                           "A: %6d %6d %6d    G: %6d %6d %6d\n\n",
                           String(h).c_str(), String(t).c_str(),
                           imu.a.x, imu.a.y, imu.a.z,
                           imu.g.x, imu.g.y, imu.g.z);

    SER.println(output_buffer);

    // Write to CSV format
    sprintf(file_buffer, "%s;%s;%d;%d;%d;%d;%d;%d",
            String(h).c_str(), String(t).c_str(),
            imu.a.x, imu.a.y, imu.a.z,
            imu.g.x, imu.g.y, imu.g.z
            );


    // Open file
    data_file = SD.open("data.csv", FILE_WRITE);

    // Write formatted data to file
    if(data_file)
    {
        data_file.println(file_buffer);
        // Needed to write to file
        data_file.close();
    }
    else
    {
        LOG_ERR("Couldn't write to file");
    }

    // !!TEMPORAL!!
    // Wait for the next measurements
    delay(500);
}

// Read the data from SD card (to check if they were written correctly)
void
ReadFileToSerial(const char* filename){
    File datalog = SD.open(filename, FILE_READ);
    char buffer [512];
    while (datalog.readBytesUntil('\n', buffer, 512)){
        SER.println(buffer);
    }
}