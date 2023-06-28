/*****************************************
This is a library for BQ2084
*******************************************/
#include "prikazy.h"

#define bufferLen 32
uint8_t i2cBuffer[bufferLen];
char text_1[11]; 

void wDesignCapacity(byte hi, byte lo)
{
  Wire.beginTransmission(BQ2084_ADDRESS);
  Wire.write(0x50);
  Wire.write(0x32);                             // dizain capacity
  Wire.write(hi);                             //high byte 30 0x1130 4400mA
  Wire.endTransmission();
  delay(100);

  Wire.beginTransmission(BQ2084_ADDRESS);
  Wire.write(0x50);
  Wire.write(0x33); 
  Wire.write(lo);                             //low byte 30 0x09C4 2500mA
  Wire.endTransmission();
  delay(100);
  
  Wire.beginTransmission(BQ2084_ADDRESS);
  Wire.write(0x50);
  Wire.write(0x36);                             //Full Charge Capacity
  Wire.write(hi);                             //high byte 30 0x1130 4400mA
  Wire.endTransmission();
  delay(100);

  Wire.beginTransmission(BQ2084_ADDRESS);
  Wire.write(0x50);
  Wire.write(0x37); 
  Wire.write(lo);                             //low byte 30 0x09C4 2500mA
  Wire.endTransmission();
  delay(100);
}
//----------------------------------------------------------------------------
void wCycleCount(void)
{
  Wire.beginTransmission(BQ2084_ADDRESS);
  Wire.write(0x50);
  Wire.write(0x0c);                       //high bit
  Wire.write(0x00);                             //0x0001 jeden nabijaci cyklus
  Wire.endTransmission();
  delay(100);
  Wire.beginTransmission(BQ2084_ADDRESS);
  Wire.write(0x50);
  Wire.write(0x0d);                       //low bit
  Wire.write(0x00);                             
  Wire.endTransmission();
  delay(100);
}
//**********************************************************************
void wManufactureDate(byte hi, byte lo)
{
  Wire.beginTransmission(BQ2084_ADDRESS);
  Wire.write(0x50);
  Wire.write(0x08);     //high byte
  Wire.write(hi);                             //0x553C 28.9.2022
  Wire.endTransmission();
  delay(100);
  
  Wire.beginTransmission(BQ2084_ADDRESS);
  Wire.write(0x50);
  Wire.write(0x09);     //low byte 
  Wire.write(lo);                            
  Wire.endTransmission();
  delay(100);
}

//***********************************************************************************
void wVmaxCharge(void)
{
  Wire.beginTransmission(BQ2084_ADDRESS);
  Wire.write(0x70);   //0x70 16 bytes Reads/Writes data flash locations 0x0100-0x10f
  Wire.write(0x10);   //write 16 bytes  
  
  Wire.write(0x00);   
  Wire.write(0x00); 
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.write(0x10); //13    1068 is 4200mv    max Charge Voltage
  Wire.write(0x68); //88    1388 is 5000mV
  Wire.write(0x10); //13    1068 is 4200mv    off Charge Voltage
  Wire.write(0x68); //88
  Wire.write(0x10); //13    1004 is 4100mV    Von Charge Voltage
  Wire.write(0x04); //88
  Wire.write(0x01);
  Wire.write(0xE0);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.write(0x8C);
    
  Wire.endTransmission();
  delay(200);
}


//***********************************************************************************
void wUnlockBattery(void)
{
  Wire.beginTransmission(BQ2084_ADDRESS);
  Wire.write(B00000000);  
  Wire.write(B10000100);
  Wire.write(B00100000);
  Wire.write(B00010001);
  Wire.endTransmission(); 
  
  Wire.beginTransmission(BQ2084_ADDRESS);
  Wire.write(B00000000); 
  Wire.write(B01000011); 
  Wire.write(B01111010);
  Wire.write(B00010110);
   
  Wire.endTransmission();
  delay(200);
}
//--------------------------------------------------------------------------
void wMAxchargetime(byte hi) //reset
{
  Wire.beginTransmission(BQ2084_ADDRESS);
  Wire.write(0x70);   //0x70 16 bytes Reads/Writes data flash locations 0x0100-0x10f
  Wire.write(0x10);   //write 16 bytes 
  
  Wire.write(0x00);   
  Wire.write(0x00); 
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.write(0x10); //13    1068 is 4200mv    max Charge Voltage
  Wire.write(0x68); //88    1388 is 5000mV
  Wire.write(0x10); //13    1068 is 4200mv    off Charge Voltage
  Wire.write(0x68); //88
  Wire.write(0x10); //13    1004 is 4100mV    Von Charge Voltage
  Wire.write(0x04); //88
  Wire.write(0x01);
  Wire.write(0xE0);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.write(hi); 
//  Wire.write(0x1C); //8C is 36000s tj 600min; 1c is 7328s tj 122min
    
  Wire.endTransmission();
  delay(200);
}
//-----------------------------------------------------------------------
void wcalibracia(void) //reset
{
  Wire.beginTransmission(BQ2084_ADDRESS);
  Wire.write(0x71);   //0x71 16 bytes Reads/Writes data flash locations 0x0110-0x011f
  Wire.write(0x10);   //write 16 bytes
  
  Wire.write(0xA0);   //1
  Wire.write(0x00); 
  Wire.write(0xA0);
  Wire.write(0x00);
  Wire.write(0x14);
  Wire.write(0xFF);
  Wire.write(0xEC);
  Wire.write(0x10);
  Wire.write(0x68);
  Wire.write(0x10);
  Wire.write(0x36);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.write(0x00);
  Wire.write(0x30);
    
  Wire.endTransmission();
  delay(200);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void wVmaxcell(void)
{
  Wire.beginTransmission(BQ2084_ADDRESS);
  Wire.write(0x50);
  Wire.write(0x64); 
  Wire.write(0xB8);    //0x68 pre 4200mV    0xB8 pre 4280mV

  Wire.endTransmission();
  delay(100);
}

//--------------------------------------------------------------------------------------
//---------------------------------------- read data -----------------------------------
void rData(void)
{
 delay(100);
  uint8_t length_read = 0;
   Serial.print(F("flash  0-0f     "));
   length_read = i2c_smbus_read_block(0x60, i2cBuffer, bufferLen);
   for (uint8_t x=0; x<length_read; x++) {if(i2cBuffer[x]<16)Serial.print('0');Serial.print(i2cBuffer[x], HEX);Serial.print(' ');}
   Serial.println("");
   Serial.print(F("flash 10-1f     "));
   length_read = i2c_smbus_read_block(0x61, i2cBuffer, bufferLen);
   for (uint8_t x=0; x<length_read; x++) {if(i2cBuffer[x]<16)Serial.print('0');Serial.print(i2cBuffer[x], HEX);Serial.print(' ');}
   Serial.println("");
   Serial.print(F("flash 20-2f     "));
   length_read = i2c_smbus_read_block(0x62, i2cBuffer, bufferLen);
   for (uint8_t x=0; x<length_read; x++) {if(i2cBuffer[x]<16)Serial.print('0');Serial.print(i2cBuffer[x], HEX);Serial.print(' ');}
   Serial.println("");  
   Serial.print(F("flash 30-3f     "));
   length_read = i2c_smbus_read_block(0x63, i2cBuffer, bufferLen);
   for (uint8_t x=0; x<length_read; x++) {if(i2cBuffer[x]<16)Serial.print('0');Serial.print(i2cBuffer[x], HEX);Serial.print(' ');}
   Serial.println("");
   Serial.print(F("flash 40-4f     "));
   length_read = i2c_smbus_read_block(0x64, i2cBuffer, bufferLen);
   for (uint8_t x=0; x<length_read; x++) {if(i2cBuffer[x]<16)Serial.print('0');Serial.print(i2cBuffer[x], HEX);Serial.print(' ');}
   Serial.println("");
   Serial.print(F("flash 50-5f     "));
   length_read = i2c_smbus_read_block(0x65, i2cBuffer, bufferLen);
   for (uint8_t x=0; x<length_read; x++) {if(i2cBuffer[x]<16)Serial.print('0');Serial.print(i2cBuffer[x], HEX);Serial.print(' ');}
   Serial.println("");
   Serial.print(F("flash 60-6f     "));
   length_read = i2c_smbus_read_block(0x66, i2cBuffer, bufferLen);
   for (uint8_t x=0; x<length_read; x++) {if(i2cBuffer[x]<16)Serial.print('0');Serial.print(i2cBuffer[x], HEX);Serial.print(' ');}
   Serial.println("");
   Serial.print(F("flash 70-7f     "));
   length_read = i2c_smbus_read_block(0x67, i2cBuffer, bufferLen);
   for (uint8_t x=0; x<length_read; x++) {if(i2cBuffer[x]<16)Serial.print('0');Serial.print(i2cBuffer[x], HEX);Serial.print(' ');}
   Serial.println("");
   Serial.print(F("flash 80-8f     "));
   length_read = i2c_smbus_read_block(0x68, i2cBuffer, bufferLen);
   for (uint8_t x=0; x<length_read; x++) {if(i2cBuffer[x]<16)Serial.print('0');Serial.print(i2cBuffer[x], HEX);Serial.print(' ');}
   Serial.println("");
   Serial.print(F("flash 90-9f     "));
   length_read = i2c_smbus_read_block(0x69, i2cBuffer, bufferLen);
   for (uint8_t x=0; x<length_read; x++) {if(i2cBuffer[x]<16)Serial.print('0');Serial.print(i2cBuffer[x], HEX);Serial.print(' ');}
   Serial.println("");
   Serial.print(F("flash A0-Af     "));
   length_read = i2c_smbus_read_block(0x6A, i2cBuffer, bufferLen);
   for (uint8_t x=0; x<length_read; x++) {if(i2cBuffer[x]<15)Serial.print('0');Serial.print(i2cBuffer[x], HEX);Serial.print(' ');}
   Serial.println("");
   Serial.print(F("flash B0-Bf     "));
   length_read = i2c_smbus_read_block(0x6B, i2cBuffer, bufferLen);
   for (uint8_t x=0; x<length_read; x++) {if(i2cBuffer[x]<16)Serial.print('0');Serial.print(i2cBuffer[x], HEX);Serial.print(' ');}
   Serial.println("");
   Serial.print(F("flash C0-Cf     "));
   length_read = i2c_smbus_read_block(0x6C, i2cBuffer, bufferLen);
   for (uint8_t x=0; x<length_read; x++) {if(i2cBuffer[x]<16)Serial.print('0');Serial.print(i2cBuffer[x], HEX);Serial.print(' ');}
   Serial.println("");
   Serial.print(F("flash D0-Df     "));
   length_read = i2c_smbus_read_block(0x6D, i2cBuffer, bufferLen);
   for (uint8_t x=0; x<length_read; x++) {if(i2cBuffer[x]<16)Serial.print('0');Serial.print(i2cBuffer[x], HEX);Serial.print(' ');}
   Serial.println("");
   Serial.print(F("flash E0-Ef     "));
   length_read = i2c_smbus_read_block(0x6E, i2cBuffer, bufferLen);
   for (uint8_t x=0; x<length_read; x++) {if(i2cBuffer[x]<16)Serial.print('0');Serial.print(i2cBuffer[x], HEX);Serial.print(' ');}
   Serial.println("");   
   Serial.print(F("flash F0-Ff     "));
   length_read = i2c_smbus_read_block(0x6F, i2cBuffer, bufferLen);
   for (uint8_t x=0; x<length_read; x++) {if(i2cBuffer[x]<16)Serial.print('0');Serial.print(i2cBuffer[x], HEX);Serial.print(' ');}
   Serial.println(""); 
   Serial.print(F("flash 100-10f   "));
   length_read = i2c_smbus_read_block(0x70, i2cBuffer, bufferLen);
   for (uint8_t x=0; x<length_read; x++) {if(i2cBuffer[x]<16)Serial.print('0');Serial.print(i2cBuffer[x], HEX);Serial.print(' ');}
   Serial.println("");
   Serial.print(F("flash 110-11f   "));
   length_read = i2c_smbus_read_block(0x71, i2cBuffer, bufferLen);
   for (uint8_t x=0; x<length_read; x++) {if(i2cBuffer[x]<16)Serial.print('0');Serial.print(i2cBuffer[x], HEX);Serial.print(' ');}
   Serial.println("");
   Serial.print(F("flash 120-12f   "));
   length_read = i2c_smbus_read_block(0x72, i2cBuffer, bufferLen);
   for (uint8_t x=0; x<length_read; x++) {if(i2cBuffer[x]<16)Serial.print('0');Serial.print(i2cBuffer[x], HEX);Serial.print(' ');}
   Serial.println("");
   Serial.print(F("flash 130-13F   "));
   length_read = i2c_smbus_read_block(0x73, i2cBuffer, bufferLen);
   for (uint8_t x=0; x<length_read; x++) {if(i2cBuffer[x]<16)Serial.print('0');Serial.print(i2cBuffer[x], HEX);Serial.print(' ');}
   Serial.println("");  
   /* 
   Serial.print("flash 140-14F   ");
   length_read = i2c_smbus_read_block(0x74, i2cBuffer, bufferLen);
   //Serial.write(i2cBuffer, length_read);
   for (uint8_t x=0; x<length_read; x++) {if(i2cBuffer[x]<16)Serial.print('0');Serial.print(i2cBuffer[x], HEX);Serial.print(' ');}
   Serial.println("");
   Serial.print("flash 150-15F   ");
   length_read = i2c_smbus_read_block(0x75, i2cBuffer, bufferLen);
   //Serial.write(i2cBuffer, length_read);
   for (uint8_t x=0; x<length_read; x++) {if(i2cBuffer[x]<16)Serial.print('0');Serial.print(i2cBuffer[x], HEX);Serial.print(' ');}
   Serial.println("");
   Serial.print("flash 160-16F   ");
   length_read = i2c_smbus_read_block(0x76, i2cBuffer, bufferLen);
   //Serial.write(i2cBuffer, length_read);
   for (uint8_t x=0; x<length_read; x++) {if(i2cBuffer[x]<16)Serial.print('0');Serial.print(i2cBuffer[x], HEX);Serial.print(' ');}
   Serial.println("");
   Serial.print("flash 170-17F   ");
   length_read = i2c_smbus_read_block(0x77, i2cBuffer, bufferLen);
   //Serial.write(i2cBuffer, length_read);
   for (uint8_t x=0; x<length_read; x++) {if(i2cBuffer[x]<16)Serial.print('0');Serial.print(i2cBuffer[x], HEX);Serial.print(' ');}
   Serial.println("");      
  */
  Serial.print(F("Manufacturer Name: "));
  length_read = i2c_smbus_read_block(MFG_NAME, i2cBuffer, bufferLen);
  Serial.write(i2cBuffer, length_read);
  Serial.println("");

  Serial.print(F("Device Name: "));
  length_read = i2c_smbus_read_block(DEV_NAME, i2cBuffer, bufferLen);
  Serial.write(i2cBuffer, length_read);
  Serial.println("");

  Serial.print(F("Chemistry "));
  length_read = i2c_smbus_read_block(CELL_CHEM, i2cBuffer, bufferLen);
  Serial.write(i2cBuffer, length_read);
  Serial.println("");

   Serial.print(F("Manufacturer Data "));
   length_read = i2c_smbus_read_block(MFG_DATA, i2cBuffer, bufferLen);
   //Serial.write(i2cBuffer, length_read);
   for (uint8_t x=0; x<length_read; x++) {if(i2cBuffer[x]<15)Serial.print('0');Serial.print(i2cBuffer[x], HEX);Serial.print(' ');}
   Serial.println("");
  
  Serial.print(F("Design Capacity: " ));
  Serial.println(fetchWord(DESIGN_CAPACITY));
  
  Serial.print(F("Design Voltage: " ));
  Serial.println(fetchWord(DESIGN_VOLTAGE));
  
  String formatted_date = "Manufacture Date (Y-M-D): ";
  int mdate = fetchWord(MFG_DATE);
  int mday = B00011111 & mdate;
  int mmonth = mdate>>5 & B00001111;
  int myear = 1980 + (mdate>>9 & B01111111);
  formatted_date += myear;
  formatted_date += "-";
  formatted_date += mmonth;
  formatted_date += "-";
  formatted_date += mday;
  Serial.println(formatted_date);

  Serial.print(F("Serial Number: "));
  Serial.print (fetchWord(SERIAL_NUM),DEC); 
  Serial.print(F("  Hex: "));  
  Serial.println (fetchWord(SERIAL_NUM),HEX); 
  
  Serial.print(F("Specification Info: "));
  Serial.println(fetchWord(SPEC_INFO));
 
  Serial.print(F("Cycle Count: " ));
  Serial.println(fetchWord(CYCLE_COUNT));
  
  Serial.print(F("Voltage: "));
  Serial.println((float)fetchWord(VOLTAGE)/1000);

  Serial.print(F("Full Charge Capacity: " ));
  Serial.println(fetchWord(FULL_CHARGE_CAPACITY));
  
  Serial.print(F("Remaining Capacity: " ));
  Serial.println(fetchWord(REMAINING_CAPACITY));

  Serial.print(F("Relative Charge(%): "));
  Serial.println(fetchWord(RELATIVE_SOC));
  
  Serial.print(F("Absolute Charge(%): "));
  Serial.println(fetchWord(ABSOLUTE_SOC));
  
  Serial.print (F("Minutes remaining for full charge: "));
  Serial.println(fetchWord(TIME_TO_FULL));

  // These aren't part of the standard, but work with some packs.
  // They don't work with the Lenovo and Dell packs we've tested
  Serial.print(F("Cell 1 Voltage: "));
  Serial.println(fetchWord(CELL1_VOLTAGE));
  Serial.print(F("Cell 2 Voltage: "));
  Serial.println(fetchWord(CELL2_VOLTAGE));
  Serial.print(F("Cell 3 Voltage: "));
  Serial.println(fetchWord(CELL3_VOLTAGE));
  Serial.print(F("Cell 4 Voltage: "));
  Serial.println(fetchWord(CELL4_VOLTAGE));
  
  Serial.print(F("State of Health: "));
  Serial.println(fetchWord(STATE_OF_HEALTH));

  Serial.print(F("Battery Mode (BIN): 0b"));
  Serial.println(fetchWord(BATTERY_MODE),BIN);

  Serial.print(F("Battery Status (BIN): 0b"));
  Serial.println(fetchWord(BATTERY_STATUS),BIN);
  
  Serial.print(F("Charging Current: "));
  Serial.println(fetchWord(CHARGING_CURRENT));
  
  Serial.print(F("Charging Voltage: "));
  Serial.println(fetchWord(CHARGING_VOLTAGE));

  Serial.print(F("Temp: "));
  unsigned int tempk = fetchWord(TEMPERATURE);
  Serial.println((float)tempk/10.0-273.15);

  Serial.print(F("Current (mA): " ));
  Serial.println(fetchWord(CURRENT));
  
  Serial.println(F("End batery info"));
  Serial.println(F(""));
}
//****************************************************************************************************************************
unsigned int fetchWord(byte func)
{
  Wire.beginTransmission(BQ2084_ADDRESS);//i2c_start(deviceAddress<<1 | I2C_WRITE);
  Wire.write(func);         //i2c_write(func);
  Wire.endTransmission();
  Wire.requestFrom(BQ2084_ADDRESS,2);//  i2c_rep_start(deviceAddress<<1 | I2C_READ);
  byte b1 = Wire.read();    //byte b1 = i2c_read(false);
  byte b2 = Wire.read();    //byte b2 = i2c_read(true);
  Wire.endTransmission();   //i2c_stop();
  return (int)b1|(((int)b2)<<8);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
uint8_t i2c_smbus_read_block ( uint8_t command, uint8_t* blockBuffer, uint8_t blockBufferLen ) 
{
  uint8_t x, num_bytes;
  Wire.beginTransmission(BQ2084_ADDRESS);//i2c_start((deviceAddress<<1) + I2C_WRITE);
  Wire.write(command);      //i2c_write(command);
  Wire.endTransmission();   // i2c_stop();
  Wire.requestFrom(BQ2084_ADDRESS,32);//i2c_rep_start((deviceAddress<<1) + I2C_READ);  
  num_bytes = Wire.read();  //i2c_read(false); // num of bytes; 1 byte will be index 0
  num_bytes = constrain(num_bytes,0,blockBufferLen-2); // room for null at the end
  for (x=0; x<num_bytes-1; x++) { // -1 because x=num_bytes-1 if x<y; last byte needs to be "nack"'d, x<y-1
       blockBuffer[x] = Wire.read();//i2c_read(false);
  }
  blockBuffer[x++] = Wire.read();//i2c_read(true); // this will nack the last byte and store it in x's num_bytes-1 address.
  blockBuffer[x] = 0;       // and null it at last_byte+1
  Wire.endTransmission();   // i2c_stop();
  return num_bytes;
}
/*
char nibble_to_hex (uint8_t nibble)
{
 //nibble=nibble/16;
nibble &=0xF;
return nibble>9 ? nibble-10+'A':nibble+ '0';
}

int int_to_2int (uint8_t nibble)
{
 //nibble=nibble/16;
nibble &=0xF;
return nibble>9 ? nibble-10+'A':nibble+ '0';
}
*/
