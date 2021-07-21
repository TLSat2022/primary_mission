// Includes
#include <Arduino.h>
#include <Devices/DeviceDHT.h>
#include <Devices/Barometer.h>
#include <Devices/AccGyro.h>
#include <Devices/Magnetometer.h>

#include <Wire.h>
#include <LIS3MDL.h>

#include <SD.h>

#include <SAMDTimerInterrupt.h>
#include <SAMD_ISR_Timer.h>

// Conventions
// Convention motivated by the length of "SerialUSB" name
#define SER SerialUSB

// Macro constants
#define SD_CS 11 // SD card Chip Select - pin needed to initialise SD card
#define DHT_PIN 2
#define DHT_TYPE DHT22

// Utility Macros
#define LOG_INIT_FAILED(err) SER.println(err); delay(500)
#define LOG_ERR(err) SER.print("[ERROR] "); SER.println(err)

#define INIT(func) while(!func){ LOG_INIT_FAILED("Couldn't initialize device: func"); } SER.println("Successfully initialized device: func")

// Devices interfaces
Magnetometer magnetometer;
DeviceDHT dht(DHT_PIN, DHT_TYPE);
Barometer barometer;
AccGyro acc_gyro;

Device* devices[4];
char buffers[4][64];

// Files
File data_file;

// Timing
SAMDTimer ITimer(TIMER_TC3);
SAMD_ISRTimer ISR_TIMER;

// Static variables
float h, t, p;
char output_buffer[512];
char file_buffer[512];

// Utility function declarations
[[maybe_unused]]
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

    devices[0] = &acc_gyro; devices[1] = &barometer;
    devices[2] = &magnetometer; devices[3] = &dht;

    // Devices Initializations
    for (auto & device : devices) {
        device->Initialize();
    }

    INIT(SD.begin(SD_CS));
}

void
loop()
{
    // Devices read
    for(auto& device : devices){
        device->Measure();
    }

    for (int i = 0; i < 4; ++i) {
        devices[i]->GetPrettyString(buffers[i]);
    }
    // Write to form making sense for serial port
    sprintf(output_buffer, "%s , %s\n"
                           "%s%s\n\n",
            buffers[0], buffers[1], buffers[2], buffers[3]);

    SER.println(output_buffer);

    for (int i = 0; i < 4; ++i) {
        devices[i]->GetCsvString(buffers[i]);
    }

    // Write to CSV format
    sprintf(file_buffer, "%s%s%s%s",
            buffers[0], buffers[1], buffers[2], buffers[3]);


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
[[maybe_unused]]
void
ReadFileToSerial(const char* filename){
    File datalog = SD.open(filename, FILE_READ);
    char buffer [512];
    while (datalog.readBytesUntil('\n', buffer, 512)){
        SER.println(buffer);
    }
}