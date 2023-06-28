/**************************************************************************************/
//#define BQ2084_ADDRESS 0x0B // B1011  //b'00010110'  bq2084, posun v pravo lebo 0bit rozhoduje zapis citanie
#include <Wire.h>
//#include <Time.h>
#include "prikazy.h"

int16_t last_ms_char; // milliseconds of last recieved character from Serial port.
int8_t buffer_pos; // next position to recieve character from Serial port.
char buffer[6]; // 0-35K+null
int16_t fn_index=0;

//**************************************************************************************
void setup()
{
 // Serial.begin(115200);
  Serial.begin(57600);
  Wire.setClock(10000);
  Wire.begin();
  pinMode(A4,INPUT_PULLUP);
  pinMode(A5,INPUT_PULLUP);

  while (!Serial) {    
    ; // wait for Serial port to connect.
  }
  Serial.println(F("Serial Initialized"));
  Serial.println(F("I2C Inialized"));

  rData();    //read data from BQ2084 and battery information
  
  help();     //menu for option
  last_ms_char = millis(); // stroke the inter character timeout.
  buffer_pos = 0;         // start the command string at zero length.

 // while(1);
//  scan();  //bypassed but left in for future projects

}
//**************************************************************************************
//------------------------------------------------------------------------------------------------

/*
void scan()  //bypassed but left in for future projects
{
  byte i = 0;
  for ( i= 0; i < 127; i++  )
  {
     int ack =  Wire.beginTransmission(i); 
    if ( ack ) {
          Serial.print("Address: 0x");
    Serial.print(i,HEX);

      Serial.println(": OK");
      Serial.flush();
    }
    else {
   
    }
  Wire.endTransmission();// i2c_stop();
  }
}+*/


//---------------------------------------------------------------------------------------------------


void loop()
{

  char inByte;
  if (Serial.available() > 0) {
    inByte = Serial.read();
    if ((0x20 <= inByte) && (inByte <= 0x126)) { // strip off non-ASCII, such as CR or LF
      if (isDigit(inByte)) { // macro for ((inByte >= '0') && (inByte <= '9'))
        // else if it is a number, add it to the string
        buffer[buffer_pos++] = inByte;
      } else {
        // input char is a letter command
        buffer_pos = 0;
        parse_menu(inByte);
      }
      buffer[buffer_pos] = 0; // update end of line
      last_ms_char = millis(); // stroke the inter character timeout.
    }
  } else if ((millis() - last_ms_char) > 50 && ( buffer_pos > 0 )) {
    // ICT expired and have something
    if (buffer_pos == 1) {
      // look for single byte (non-number) menu commands
      parse_menu(buffer[buffer_pos - 1]);
//***************************************************
} else if (buffer_pos > 5) {
      // dump if entered command is greater then uint16_t
      Serial.println(F("Ignored, Number is Too Big!"));
  //------------------------------------------------------------------------------
    //open directory
    // otherwise its a number, scan through files looking for matching index.  
  //-------------------------------------------------------------------------
    } else {
//9597988
//4401
//0822
      fn_index = atoi(buffer);
      if (fn_index>1)
      {
      Serial.print(F("number is: "));
      Serial.print(fn_index);
      Serial.print(F("  HEX: "));
      Serial.println(fn_index,HEX);
      Serial.print(F("Write to: "));
      //Serial.print(F("Number is: "));
      }
//***************************************************
    }
    //reset buffer to start over
    buffer_pos = 0;
    buffer[buffer_pos] = 0; // delimit
  }

  delay(10);   
}

uint32_t  millis_prv;

//------------------------------------------------------------------------------
/**
 * \brief Decode the Menu.
 *
 * Parses through the characters of the users input
 */

  void parse_menu(byte key_command) {

  uint8_t result; // result code from some function as to be tested at later time.

  Serial.print(F("Received command: "));
  Serial.write(key_command);
  Serial.println(F(" "));

  //ovladanie portov
  if(key_command == 'c') {
    Serial.println(F("Cycle Count set to 0"));
    wCycleCount();

  } else if(key_command == 'r') {
    Serial.println(F("Read Flash and battery data"));
    rData();
    help();     //menu for option
 //9597988
//04400
//0922   
  } else if(key_command == 'd') {
    Serial.println(F("Write Design Capacity"));
    byte hi=highByte(fn_index);
    byte lo=lowByte(fn_index);
    wDesignCapacity(hi,lo);
    Serial.println(hi,DEC);
    Serial.println(lo,DEC);
    Serial.println(hi,HEX);
    Serial.println(lo,HEX);
    Serial.print(F("Press r and check data capacity" ));
//    Serial.print(F("Design Capacity: " ));
//    Serial.println(fetchWord(DESIGN_CAPACITY));

    
  } else if(key_command == 'm') {
    Serial.println(F("Write Manufacture Date"));
    byte month=fn_index/100;
    byte year=(fn_index-month*100)+2000;
    int date=(year-1980)*512+month*32+1;
    byte hi=highByte(date);
    byte lo=lowByte(date);
    wManufactureDate(hi,lo);
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
    
  } else if(key_command == 'a') {
    Serial.println(F("Write Cell Over Voltage 4280mV"));
    wVmaxcell();

  } else if(key_command == 's') {
    Serial.println(F("Write Vmax Charge Voltage)"));
    wVmaxCharge();

  } else if(key_command == 'u') {
    Serial.println(F("Unlock battery"));
    wUnlockBattery();
    Serial.println(F("Reset arduino"));  

  } else if(key_command == 't') {
    Serial.println(F("Write max time to charging"));
    byte hi=highByte(fn_index);
    wMAxchargetime(hi);

    
  } else  if(key_command == 'a') {
    Serial.println(F("Toggle pin B0"));


  } else if(key_command == 's') {
    Serial.println(F("Toggle pin B1"));


  } else if(key_command == 'd') {
    Serial.println(F("Toggle pin B2"));


  } else if(key_command == 'f') {
    Serial.println(F("Toggle pin B3"));


  } else if(key_command == 'g') {
    Serial.println(F("Toggle pin B4"));


  } else if(key_command == 'l') {
    Serial.println(F("Toggle pin B5"));


  } else if(key_command == 'j') {
    Serial.println(F("Toggle pin B6"));


  } else if(key_command == 'k') {
    Serial.println(F("Toggle pin B7"));
 

  } else if(key_command == 'z') {
   
      Serial.println(F("ALL OFF"));

       
  } else if(key_command == 'x') {
   
      Serial.println(F("ALL ON"));

  
     
  } else if(key_command == 'h') {
    help();
  }
//help();
}


void help() {
  Serial.println(F("COMMANDS:"));
    Serial.println(F(" [u] Unlock battery "));
  Serial.println(F(" [c] Cycle Count set to 0 "));
  Serial.println(F(" [r] Read Flash and battery data "));
  Serial.println(F(" [a] Write Cell Over Voltage 4280mV "));
  Serial.println(F(" [s] Vmax Charge Voltage Vmax-4200 Off-4200 On-4100 "));

  Serial.println(F(" !!! WARING set number for write xxxx !!!"));
  Serial.print(F("     number is: "));
  Serial.print(fn_index);
  Serial.print(F("  HEX: "));
  Serial.println(fn_index,HEX);
  Serial.println(F(" [d] Write Design Capacity (04400 is 4400mAh)"));
  Serial.println(F(" [m] Write Manufacture Date (0922 is month 9 and year 2022)"));
  Serial.println(F(" [t] Max time to charging max (36000sec) Vmax-4200 Off-4200 On-4100 "));

  /*
  Serial.print(F(" [u] togle A6 "));
  Serial.println(F(" [i] togle A7"));
  Serial.print(F(" [a] togle B0 "));
  Serial.print(F(" [s] togle B1 "));
  Serial.print(F(" [d] togle B2 "));
  Serial.print(F(" [f] togle B3 "));
  Serial.print(F(" [g] togle B4 "));
  //Serial.print(F(" [h] togle B5 "));
  Serial.print(F(" [j] togle B6 "));
  Serial.println(F(" [k] togle B7"));
  Serial.println(F(" [z] OFF all"));
  Serial.println(F(" [x] ON all"));
  */

  Serial.println(F(" [h] this help"));

  //wVmaxCharge();
  //wVmaxcell();
   //wCYCLE();
  // wcapacity();
  // wcalibracia();
  //wManufactureDate();

//  while(1);
}
