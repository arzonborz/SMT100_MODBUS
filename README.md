# SMT100_MODBUS

![Version](https://img.shields.io/badge/Version-v1.0.0-green.svg)

***Please Note: This is a personal effort and Trubner GMBH is not related nor responsible for using or supporting this library***

 Library for communicating though RS-485 Modbus with Trubner's soil moisture sensor (SMT100) using the Arduino platform. Supports most devices.

### Features
---
* RS-485 Modbus broadcast functionality
* Communication with several sensors on the same RS-485 Modbus
* Set address ID of SMT100 sensor
* Change address ID of a specific SMT100 sensor on-the-fly (i.e. with multiple sensors connected on the same RS-485 Modbus)
* Address collision protection before setting/changing address ID
* Read the data registers of SMT100, which are:
  * Address ID
  * Temprature
  * Water content
  * Permittivity
  * Counts
* Check if an address ID is present on RS-485 Modbus

### Future changes
---
* TBus mode detection functionality
* Switch to Modbus mode functionality
* Clear protocol functionality

### Commands
---
SMT100_MODBUS(Stream *port);

int ReadAddress();

bool SetAddress(byte newId);

bool CheckAddress(byte id);

bool ChangeAddress(byte oldID , byte newId);

float ReadSMT100(byte id, String reg);

bool RS485_TRANSEIVER(String msgSent , byte numOfSentByte, byte* msgReceived, byte numOfReceivedByte, int receiveTimeout);

### Usage
---
The library is not yet included in the IDE/IO library manager. Alternatively, one can simply clone this library to your working library folder and include "SMT100_MODBUS.h" in his main sketch.

If you are having difficulties, please raise an issue.

### A Bit About this Sensor
---
See extras for the official SMT100 Modbus Guide

### Authors
---
Ghaith alshishani, you can find my contact details below.

### License
---
This project is licensed under Apache 2.0 - see the LICENSE.md file for details

### Acknowledgments
----
Extended thanks to Trubner for providing my team with the SMT100 sensors and loggers troughout our research.

### Feedback
---
For any feedback contact me on my Email: arzonborz@gmail.com
