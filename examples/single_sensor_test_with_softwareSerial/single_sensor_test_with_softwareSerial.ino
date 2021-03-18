/*
  Single sensor test with softwareSerial

  In this example the arduino is connected to a ttl to RS485 converter module. 
  On the RS485 a Trubner's SMT100 soil moisture sensor is connected. A ttl to 
  usb FTDI converter is used to view the date using softwareSerial.

  The circuit:
  * Pin 10, 11 are connected TX, RX of the FTDI respectively
  * Pin 0(RX),1(TX) are connected to RX and TX of the ttl to RS485 converter
    respectively

  Created 18/3/2021
  By Ghaith Alshishani

*/

#include "SMT100_MODBUS.h"

SMT100_MODBUS smt100(&Serial); // create an SMT100_MODBUS on Serial port (i.e: 0(RX),1(TX) pins or hardware Serial1) 

#include <SoftwareSerial.h> 
SoftwareSerial mySerial(10, 11); // RX, TX


void setup() {
  // initialize serial transmission with even parity
  Serial.begin(9600,SERIAL_8E1);
  // initialize serial transmission using softwareSerial
  mySerial.begin(9600);
}

void loop() {
  // ReadAddress read and retuns the ID address of the SMT100 sensor on the RS485 MODBUS. There should only be one SMT100 sensor connected to the bus at a time because this function uses the broadcast ID address
  int readaddress = mySensor.ReadAddress();
  mySerial.print("readaddress=" + String (readaddress));
  // SetAddress returns a boolean to determine succeful operation. This function Sets the ID address of the SMT100 sensor on the RS485 MODBUS. There should only be one SMT100 sensor connected to the bus at a time because this function uses the broadcast ID address
  bool setaddress = mySensor.SetAddress(0);
  mySerial.print("  setaddress=" + String (setaddress));
  // CheckAddress returns a boolean and checks if the Sensor ID is present on RS485 MODBUS
  bool checkaddress = mySensor.CheckAddress(0);
  mySerial.print("  checkaddress=" + String (checkaddress));
  // reads the data registers from SMT100 sensors with a specified id. returns (-255) when wrong id is passed (-254) when wrong address is passed (-253 & -252) when no correct bytes were recieved
  int addressID = mySensor.ReadSMT100(0x00,ADDRESS_REG);
  mySerial.print("  addressID=" + String (addressID));
  float temp = mySensor.ReadSMT100(0x00,TEMP_REG);
  mySerial.print("  temp=" + String (temp));
  float waterContent = mySensor.ReadSMT100(0x00,WATER_CONTENT_REG);
  mySerial.print("  waterContent=" + String (waterContent));
  float permittivity = mySensor.ReadSMT100(0x00,PERMITTIVITY_REG);
  mySerial.print("  permittivity=" + String (permittivity));
  // ChangeAddress changes the id address of a given SMT100 id address if the new address is not already taken on the RS485 MODBUS
  bool changeaddress = mySensor.ChangeAddress(0x00 , 11);
  mySerial.print("  changeaddress=" + String (changeaddress));
  int counts = mySensor.ReadSMT100(0x0B,COUNTS_REG);
  mySerial.println("  counts=" + String (counts));
}
