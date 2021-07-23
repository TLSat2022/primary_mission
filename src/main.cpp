// Includes
#include <Arduino.h>
#include <Devices/Devices.h>
#include <DC/Timing.h>
#include <Wire.h>
#include <DC/Transmitter.h>

// Conventions
// Convention motivated by the length of "SerialUSB" name
#define SER SerialUSB

// Macro constants
// SD card Chip Select - pin needed to initialise SD card
#define SD_CS 11
#define DHT_PIN 2
#define DHT_TYPE DHT22

// Utility Macros
#define LOG_ERR(err) SER.print("[ERROR] "); SER.println(err)

// Devices
Magnetometer magnetometer;
DeviceDHT dht(DHT_PIN, DHT_TYPE);
Barometer barometer;
AccGyro acc_gyro;
DeviceSD sd(SD_CS);
Transmitter transmitter(5);

// Device groups
DeviceGroup<3> altimu = { &magnetometer, &barometer, &acc_gyro };
DeviceGroup<1> dht_group = { &dht };

Device* devices[] = { &dht, &barometer, &acc_gyro, &magnetometer, &sd, &transmitter };

// Timing
SAMDTimer ITimer(TIMER_TC3);
SAMD_ISRTimer ISR_TIMER;
ExtendedTimer timer(ISR_TIMER);

// Buffers
char buffer_1[512], buffer_2[512];

// Utility function declarations
[[maybe_unused]] void ReadFileToSerial(const char* filename);
void Printing();
void WriteFile();
void CheckInitialization();

// Callables
UtilityCall write_serial(Printing);
UtilityCall write_file(WriteFile);
UtilityCall check_initialization(CheckInitialization);


// Main Program
void
setup()
{
    // Serial port initialization
    SER.begin(9600);

    // I2C initialization
    Wire.begin();

    CheckInitialization();

    ITimer.attachInterruptInterval(10 * 1000, [](){ ISR_TIMER.run(); });

    timer.SetInterval(500L, &altimu);
    timer.SetInterval(2000L, &dht_group);
    timer.SetInterval(1000L, &write_serial);
    timer.SetInterval(1000L, &write_file);
    timer.SetInterval(5000L, &check_initialization);
}

void
loop()
{
    timer.InLoop();
    transmitter.Transmit(5.0f);
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

void
Printing(){
    for (auto& device : devices) {
        if(device->GetPrettyString(buffer_2) != nullptr) {
            sprintf(buffer_1, "%s: %s", device->GetName().c_str(), buffer_2);
            SER.println(buffer_1);
        }
    }
    SER.println();

}

void
WriteFile() {
    // Open file
    File data_file = SD.open("data.csv", FILE_WRITE);

    // Write formatted data to file
    if(data_file)
    {
        for (auto& device : devices)
            if(device->GetCsvString(buffer_1) != nullptr)
                data_file.print(buffer_1);
        data_file.println();
        data_file.close();
    }
    else { LOG_ERR("Couldn't write to file"); }
}

void
CheckInitialization() {
    for (auto & device : devices)
        if(!device->IsInitialized())
            if(!device->Initialize()) { LOG_ERR(device->GetName() + " couldn't be initialized"); }

}