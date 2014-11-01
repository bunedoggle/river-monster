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

#define ADC          'A'
#define TEMP         'T'
#define VERSION      'V'
#define INDICATE     'I'
#define NOOP         unsupportedCmd

void setVersion(void* vui, char* cmd);
void getVersion(void* vui, char* cmd);
void getADC(void* vui, char* cmd);
void getTemp(void* vui, char* cmd);
void getIndicate(void* vui, char* cmd);
void setIndicate(void* vui, char* cmd);
void unsupportedCmd(void* vui, char* cmd);
void registerAllCommands(CSI* ui);

#endif /* COMMANDS_H_ */
