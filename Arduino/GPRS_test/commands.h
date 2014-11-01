/*
 * commands.h
 *
 *  Created on: Sep 11, 2014
 *      Author: brianbailey
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include "Arduino.h"
#include "CSI.h"

#define VERSION      'V'
#define DATAPOINT    'D'
#define NOOP         unsupportedCmd

void getVersion(void* vui, char* cmd);
void setDataPoint(void* vui, char* cmd);
void unsupportedCmd(void* vui, char* cmd);
void registerAllCommands(CSI* ui);

bool powerUpOrDown();
void SendTextMessage(String message, SoftwareSerial* mySerial);
void ShowSerialData();

#endif /* COMMANDS_H_ */
