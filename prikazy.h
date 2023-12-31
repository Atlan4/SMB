/*****************************************
This is a library for the BQ2084
*******************************************/

/*
#define IODIRA 0x00   
#define IODIRB 0x01   
#define IOCONA 0x0A 
*/  
#define BQ2084_ADDRESS 0x0B // B1011  //b'00010110'  bq2084, posun v pravo lebo 0bit rozhoduje zapis citanie
#include <Wire.h>
#include <Arduino.h>


// Standard and common non-standard Smart Battery commands
#define BATTERY_MODE             0x03
#define TEMPERATURE              0x08
#define VOLTAGE                  0x09
#define CURRENT                  0x0A
#define RELATIVE_SOC             0x0D
#define ABSOLUTE_SOC             0x0E
#define REMAINING_CAPACITY       0x0F
#define FULL_CHARGE_CAPACITY     0x10
#define TIME_TO_FULL             0x13
#define CHARGING_CURRENT         0x14
#define CHARGING_VOLTAGE         0x15
#define BATTERY_STATUS           0x16
#define CYCLE_COUNT              0x17
#define DESIGN_CAPACITY          0x18
#define DESIGN_VOLTAGE           0x19
#define SPEC_INFO                0x1A
#define MFG_DATE                 0x1B
#define SERIAL_NUM               0x1C
#define MFG_NAME                 0x20   // String
#define DEV_NAME                 0x21   // String
#define CELL_CHEM                0x22   // String
#define MFG_DATA                 0x23   // String
#define CELL4_VOLTAGE            0x3C   // Indidual cell voltages don't work on Lenovo and Dell Packs
#define CELL3_VOLTAGE            0x3D
#define CELL2_VOLTAGE            0x3E
#define CELL1_VOLTAGE            0x3F
#define STATE_OF_HEALTH          0x4F

                        // string UTF8 end zero 


//*********************************************************************************************************************
unsigned int fetchWord(byte func);
uint8_t i2c_smbus_read_block ( uint8_t command, uint8_t* blockBuffer, uint8_t blockBufferLen );
char nibble_to_hex (uint8_t nibble);

void wDesignCapacity(byte hi, byte lo);
void wCycleCount(void);
void wManufactureDate(byte hi, byte lo); // hi-mesiac 1-12 and lo-year 00-99 etc 2000-2099
void wcalibracia(void);
void wVmaxcell(void);
void wVmaxCharge(void);
void wUnlockBattery(void);
void wMAxchargetime(byte hi);

void rData(void);
