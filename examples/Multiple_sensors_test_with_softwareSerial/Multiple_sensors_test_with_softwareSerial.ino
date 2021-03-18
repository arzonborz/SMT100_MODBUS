/*
  Multiple sensors test with softwareSerial

  In this example the arduino is connected to a ttl to RS485 converter module. 
  On the RS485 two Trubner's SMT100 soil moisture sensors are connected (with 
  id addresses set to 0x00 and 0x01). A ttl to usb FTDI converter is used to 
  view the date using softwareSerial.

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

  // Check if id addresses 0x00 and 0x01 are avilable on the Modbus
  bool checkaddress1 = smt100.CheckAddress(0);
  mySerial.print("  check1=" + String (checkaddress1));
  bool checkaddress2 = smt100.CheckAddress(1);
  mySerial.print("  check2=" + String (checkaddress2));
  if (checkaddress1 && checkaddress2)
  {
    // First sensor readings
    int addressID = smt100.ReadSMT100(0x00,ADDRESS_REG);
    mySerial.print("  ID=" + String (addressID));
    float temp = smt100.ReadSMT100(0x00,TEMP_REG);
    mySerial.print("  T=" + String (temp));
    float waterContent = smt100.ReadSMT100(0x00,WATER_CONTENT_REG);
    mySerial.print("  WC=" + String (waterContent));
    float permittivity = smt100.ReadSMT100(0x00,PERMITTIVITY_REG);
    mySerial.print("  P=" + String (permittivity));
    bool changeaddress = smt100.ChangeAddress(0x00 , 11); // change the id address of SMT100 from 0x00 to 0x0B
    mySerial.print("  CID=" + String (changeaddress));
    int counts = smt100.ReadSMT100(0x0B,COUNTS_REG);
    mySerial.print("  c=" + String (counts));
    changeaddress = smt100.ChangeAddress(11 , 0x00);  // change the id address of SMT100 from 0x0B to 0x00
    mySerial.print("  CID=" + String (changeaddress));

    // Second sensor
    addressID = smt100.ReadSMT100(0x01,ADDRESS_REG);
    mySerial.print("  ID=" + String (addressID));
    temp = smt100.ReadSMT100(0x01,TEMP_REG);
    mySerial.print("  T=" + String (temp));
    waterContent = smt100.ReadSMT100(0x01,WATER_CONTENT_REG);
    mySerial.print("  WC=" + String (waterContent));
    permittivity = smt100.ReadSMT100(0x01,PERMITTIVITY_REG);
    mySerial.print("  P=" + String (permittivity));
    changeaddress = smt100.ChangeAddress(0x01 , 11); // change the id address of SMT100 from 0x01 to 0x0B
    mySerial.print("  CID=" + String (changeaddress));
    counts = smt100.ReadSMT100(0x0B,COUNTS_REG);
    mySerial.print("  c=" + String (counts));
    changeaddress = smt100.ChangeAddress(11 , 0x01);  // change the id address of SMT100 from 0x0B to 0x01
    mySerial.println("  CID=" + String (changeaddress));
  }
  else
  {
    mySerial.println("Check if both sensors are connected correctly on the Modbus");
  }
}
