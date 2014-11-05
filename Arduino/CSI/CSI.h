/*
 * CSI.h
 *
 *  Created on: Sep 11, 2014
 *      Author: brianbailey
 */
/* Common Serial Interface */

#include "Arduino.h"
#include "Softmodem.h"

#ifndef CSI_H_
#define CSI_H_

#define CMD_BYTE_LIMIT 32
#define MAX_NUM_COMMANDS 26

#define START_OF_FRAME '@'
#define END_OF_FRAME '#'
#define REPLY        'R'
#define SET_CMD      'S'
#define GET_CMD      'G'

typedef void (*cmdHandler)(void* vui, char *cmd);

typedef struct command_t {
        char cmd;
        cmdHandler getCmdHandler;
        cmdHandler setCmdHandler;
} Command;


class CSI {
public:
	CSI(HardwareSerial* serial_ptr);
	CSI(HardwareSerial* serial_ptr, SoftModem* m_ptr);
	CSI(HardwareSerial* serial_ptr, SoftModem* m_ptr, HardwareSerial* debug_ptr);

	virtual ~CSI();
	void serialEventHandler();
	void modemEventHandler();
	void registerCommand(char cmd, cmdHandler getCmdHandler, cmdHandler setCmdHandler);
	void handleCmd(char* cmd);
	int getParams(char* cmd, int* a, int cnt);
	char* getInt(char* cmd, int* data);
	void setDebug(byte level);

	HardwareSerial* cmdPort;
	HardwareSerial* debugPort;
	SoftModem* modem;
	byte totalCmds;
	byte passthrough;
	byte debug;

	// Print wrappers
	size_t print(const String &s);
	size_t print(const char str[]);
	size_t print(char c);
	size_t print(unsigned char b, int base);
	size_t print(int n, int base);
	size_t print(unsigned int n, int base);
	size_t print(long n, int base);
	size_t print(unsigned long n, int base);
	size_t print(double n, int digits);
	size_t print(const Printable& x);
	size_t println(void);
	size_t println(const String &s);
	size_t println(const char c[]);
	size_t println(char c);
	size_t println(unsigned char b, int base);
	size_t println(int num, int base);
	size_t println(unsigned int num, int base);
	size_t println(long num, int base);
	size_t println(unsigned long num, int base);
	size_t println(double num, int digits);
	size_t println(const Printable& x);


private:
// Class Globals
	char cmd[CMD_BYTE_LIMIT];
	char cmdModem[CMD_BYTE_LIMIT];
	Command *commandList[26];
	int cmdIndex, cmdIndexModem;

// Internal Utilities
	int getStringParams(char* cmd, String* stringargs, int maxCnt);
	char* getString(char* cmd, String* data);

};



#endif /* CSI_H_ */
