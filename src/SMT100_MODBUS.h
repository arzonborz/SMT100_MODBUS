/****************************************************** 
  Arduino library for communicating though RS-485 Modbus with Trubner's soil moisture sensor (SMT100)
  
  Author: Ghaith alshishani arzonborz@gmail.com
  
  Version: 1.0.0
  License: Apache 2.0
 *******************************************************/

#ifndef _SMT100_MODBUS_H
#define _SMT100_MODBUS_H

#include <Arduino.h>

// read/write registers addresses
#define WRITE_REG     "06"
#define READ_REG      "03"

// reading holding registers addresses
#define ADDRESS_REG       "0004"
#define COUNTS_REG        "0003"
#define PERMITTIVITY_REG  "0002"
#define WATER_CONTENT_REG "0001"
#define TEMP_REG          "0000"

// number of registers to read
#define ONE16BITS_REG     "0001"

// general SMT100 ID
#define BROADCAST_ID      0xFD

// timeout
#ifdef ESP32
	#define TIMEOUT_SMT100	  200
#else
	#define TIMEOUT_SMT100	  100
#endif

class SMT100_MODBUS
{
    public:
        SMT100_MODBUS(Stream *port);
		int ReadAddress();
		bool SetAddress(byte newId);
		bool CheckAddress(byte id);
		bool ChangeAddress(byte oldID , byte newId);
		float ReadSMT100(byte id, String reg);
		bool RS485_TRANSEIVER(String msgSent , byte numOfSentByte, byte* msgReceived, byte numOfReceivedByte, int receiveTimeout);
		
    private:
		Stream *_port;
		int available();
		int peek();
		int read();
		size_t write(uint8_t c);
		byte StrtoByte (String str_value);
		String ModRTU_CRC(String raw_msg_data);
};

#endif
