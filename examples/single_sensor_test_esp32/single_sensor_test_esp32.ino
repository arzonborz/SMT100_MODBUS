/*
  Single sensor test

  In this example an esp32 is connected to a ttl to RS485 converter module. 
  On the RS485 a Trubner's SMT100 soil moisture sensor is connected. SerialPort(2)
  is used to view .

  The circuit:
  * Pin 10, 11 are connected TX, RX of the FTDI respectively
  * Pin 0(RX),1(TX) are connected to RX and TX of the ttl to RS485 converter
    respectivel

  Created 18/3/2021
  By Ghaith Alshishani

*/

#include "SMT100_MODBUS.h"

#include <HardwareSerial.h>

HardwareSerial SerialPort(2); // use UART2

SMT100_MODBUS smt100(&SerialPort); // create an SMT100_MODBUS on Serial port (i.e: 0(RX),1(TX) pins or hardware Serial1) 

void setup() {
  // initialize serial transmission with even parity
  SerialPort.begin(9600,SERIAL_8E1, 16, 17);
  // initialize serial transmission using softwareSerial
  Serial.begin(115200);
}

void loop() {
  // ReadAddress read and retuns the ID address of the SMT100 sensor on the RS485 MODBUS. There should only be one SMT100 sensor connected to the bus at a time because this function uses the broadcast ID address
  int readaddress = smt100.ReadAddress();
  Serial.print("readaddress=" + String (readaddress));
  delay(10);
  // SetAddress returns a boolean to determine succeful operation. This function Sets the ID address of the SMT100 sensor on the RS485 MODBUS. There should only be one SMT100 sensor connected to the bus at a time because this function uses the broadcast ID address
  bool setaddress = smt100.SetAddress(0);
  Serial.print("  setaddress=" + String (setaddress));
  delay(10);
  // CheckAddress returns a boolean and checks if the Sensor ID is present on RS485 MODBUS
  bool checkaddress = smt100.CheckAddress(0);
  Serial.print("  checkaddress=" + String (checkaddress));
  delay(10);
  // reads the data registers from SMT100 sensors with a specified id. returns (-255) when wrong id is passed (-254) when wrong address is passed (-253 & -252) when no correct bytes were recieved
  int addressID = smt100.ReadSMT100(0x00,ADDRESS_REG);
  Serial.print("  addressID=" + String (addressID));
  delay(10);
  float temp = smt100.ReadSMT100(0x00,TEMP_REG);
  Serial.print("  temp=" + String (temp));
  delay(10);
  float waterContent = smt100.ReadSMT100(0x00,WATER_CONTENT_REG);
  Serial.print("  waterContent=" + String (waterContent));
  delay(10);
  float permittivity = smt100.ReadSMT100(0x00,PERMITTIVITY_REG);
  Serial.print("  permittivity=" + String (permittivity));
  delay(10);
  // ChangeAddress changes the id address of a given SMT100 id address if the new address is not already taken on the RS485 MODBUS
  bool changeaddress = smt100.ChangeAddress(0x00 , 11);
 Serial.print("  changeaddress=" + String (changeaddress));
 delay(10);
  int counts = smt100.ReadSMT100(0x0B,COUNTS_REG);
  Serial.print("  counts=" + String (counts));
  Serial.println("");
  delay(10);
}
