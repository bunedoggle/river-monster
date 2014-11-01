/*
 * CSI.cpp
 *
 *  Created on: Sep 11, 2014
 *      Author: brianbailey
 */

#include "CSI.h"

CSI::CSI(HardwareSerial* serial_ptr, SoftwareSerial* swserial_ptr) {
        mySerial = swserial_ptr;
	cmdPort = serial_ptr;
	debugPort = '\0';
	passthrough = 0;
	cmdIndex = 0;
	cmdIndexModem = 0;
	totalCmds = 0;
}

CSI::~CSI() {
	// TODO Auto-generated destructor stub
}

void CSI::setDebug(byte level){
  if(debugPort != '\0'){
	debug = level;
  }
}

void CSI::serialEventHandler() {

	  while (cmdPort->available()) {
	    // get the new byte:
	    char inChar = (char)cmdPort->read();

	    if(cmd[0] != START_OF_FRAME && inChar != START_OF_FRAME){
	      return;
	    }

	    // add it to the cmd:
	    cmd[cmdIndex++] = inChar;
		
	    if(debug){
	    	 debugPort->print(inChar);
	     }

	    // if the incoming character is a newline, set a flag
	    // so the main loop can do something about it:
	    if (inChar == END_OF_FRAME || cmdIndex >= CMD_BYTE_LIMIT) {
			handleCmd(cmd);
	    }
	  }
}

void CSI::registerCommand(char cmd, cmdHandler getCmdHandler, cmdHandler setCmdHandler){
	// Malloc enough memory to hold the new command structure
	commandList[totalCmds] = (Command*)malloc(sizeof(Command));

	// Check if we got some memory
	if(commandList[totalCmds] == '\0'){
		return;
	}

	// Fill in new structure
	commandList[totalCmds]->cmd = cmd;
	commandList[totalCmds]->getCmdHandler = getCmdHandler;
	commandList[totalCmds]->setCmdHandler = setCmdHandler;

	// update total command length
	totalCmds++;
}

/* Command handler
<byte> | <byte> | <2 byte max> | <byte> |  <2 byte max>  | <byte> | <2 byte max> |...|  <byte>  |
ACTION | object |     ID       |   ,    |      P1        |   ,    |     p2       |...|    $     |
*/
void CSI::handleCmd(char* cmd){
  int i;

  // Look for START_OF_FRAME
  if(cmd[0] != START_OF_FRAME){
	cmdIndex = 0;
	// Clear Start of frame char
	cmd[0] = ' ';
    return;  // No start of frame
  }

  // Ignore replies
  if(cmd[1] == 'R'){
	cmdIndex = 0;
	// Clear Start of frame char
	cmd[0] = ' ';
    return;
  }

  // Look for END_OF_FRAME
  for(i=0; i<=CMD_BYTE_LIMIT; i++){
    if(cmd[i] == END_OF_FRAME){
      break;
    }
  }
  if(i==CMD_BYTE_LIMIT){
    cmdPort->print("@RNo END_OF_FRAME character detected, command too long?#");
    return;
  }

  // TODO: check the checksum.  Will be important for softserial modem (FSK)

  // Start the reply
  cmdPort->print(START_OF_FRAME);
  cmdPort->print(REPLY);

  // Parse out command
  boolean parsed = false;
  for(int i=0; i<totalCmds;i++){
	//cmdPort->println(commandList[i]->cmd);
    if(cmd[2] == commandList[i]->cmd){
      if(cmd[1] == 'S' || cmd[1] == 's'){
        commandList[i]->setCmdHandler((void*)this, cmd);
        parsed = true;
        break;
      }
      else if(cmd[1] == 'G' || cmd[1] == 'g'){
        commandList[i]->getCmdHandler((void*)this, cmd);
        parsed = true;
        break;
      }
    }
  }

  if(!parsed){
      cmdPort->print("Unknown Command?");
  }
  cmdPort->println(END_OF_FRAME);
  cmdIndex = 0;
  // Clear Start of frame char
  cmd[0] = ' ';
}


char* CSI::getInt(char* cmd, int* data){
  int d=0;
  int i=0;
  int isNeg=0;
  if(cmd[0] == END_OF_FRAME){
    return 0;
  }
  if( cmd[0] == '-' ){
    isNeg = 1;
    cmd++;
  }
  while(cmd[i] != END_OF_FRAME && cmd[i] != DELIMITER){
    d *= 10;
    d = ((cmd[i])-48)+ d;
    i++;
  }
//  CMD_PORT.print("Extracted: ");
//  CMD_PORT.println(d);
  if (isNeg){
    *data = -d;
  }
  else{
    *data = d;
  }
  cmd+=i;
  return cmd;
}

char* CSI::getString(char* cmd, String* data){
  int d=0;
  int i=0;
  String command = "";
  if(cmd[0] == END_OF_FRAME){
    return 0;
  }
  while(cmd[i] != END_OF_FRAME && cmd[i] != DELIMITER){
    //CMD_PORT.print(cmd[i]);CMD_PORT.print('  ');CMD_PORT.println(char(cmd[i]));
    //CMD_PORT.print((cmd[i])-48);CMD_PORT.print(' ');CMD_PORT.println(((cmd[i])-48)*10);
    //CMD_PORT.println(d)
    d = ((cmd[i]));
    //CMD_PORT.print("d");
    //CMD_PORT.print(d);
    command += (char)d;
    i++;
  }
  *data = command;
  cmd+=i;
  return cmd;
}

int CSI::getStringParams(char* cmd, String* stringargs, int maxCnt){
  int i=0;
  cmd++; // Go past first command letter
  cmd++; // Go past second command letter
  while((maxCnt-i) && cmd[0] != END_OF_FRAME){
    if(cmd[0] == DELIMITER){
      cmd++;
    }
    cmd++;//skips past action id ('D')
    cmd = getString(cmd, stringargs);
    //args++;
    i++;
  }
  return i;
}

int CSI::getParams(char* cmd, int* args, int maxCnt){
  int i=0;
  cmd+=3; // Go past first 3 command letters (SOF, <S,G> , <command>)

  while((maxCnt-i) && cmd[0] != END_OF_FRAME){
    if(cmd[0] == DELIMITER){
      cmd++;
      continue;
    }
    cmd = getInt(cmd, args);
    args++;
    i++;
  }
  return i;
}

// Print wrappers to handle print distribution
size_t CSI::print(const String &s)
{
	if (debug){
		debugPort->print(s);
	}
	return cmdPort->print(s);
}

size_t CSI::print(const char str[])
{
	if (debug){
		debugPort->print(str);
	}
	return cmdPort->print(str);
}

size_t CSI::print(char c)
{
	if (debug){
		debugPort->print(c);
	}
	return cmdPort->print(c);
}

size_t CSI::print(unsigned char b, int base)
{
	if (debug){
		debugPort->print(b,base);
	}
	return cmdPort->print(b,base);
}

size_t CSI::print(int n, int base)
{
	if (debug){
		debugPort->print(n,base);
	}
	return cmdPort->print(n,base);
}

size_t CSI::print(unsigned int n, int base)
{
	if (debug){
		debugPort->print(n,base);
	}
	return cmdPort->print(n,base);
}

size_t CSI::print(long n, int base)
{
	if (debug){
		debugPort->print(n,base);
	}
	return cmdPort->print(n,base);
}

size_t CSI::print(unsigned long n, int base)
{
	if (debug){
		debugPort->print(n,base);
	}
	return cmdPort->print(n,base);
}

size_t CSI::print(double n, int digits)
{
	if (debug){
		debugPort->print(n, digits);
	}
	return cmdPort->print(n, digits);
}

size_t CSI::print(const Printable& x)
{
	if (debug){
		debugPort->print(x);
	}
	return cmdPort->print(x);
}

size_t CSI::println(void)
{
	if (debug){
		debugPort->println();
	}
	return cmdPort->println();
}

size_t CSI::println(const String &s)
{
	if (debug){
		debugPort->println(s);
	}
	return cmdPort->println(s);
}

size_t CSI::println(const char c[])
{
	if (debug){
		debugPort->println(c);
	}
	return cmdPort->println(c);
}

size_t CSI::println(char c)
{
	if (debug){
		debugPort->println(c);
	}
	return cmdPort->println(c);
}

size_t CSI::println(unsigned char b, int base)
{
	if (debug){
		debugPort->println(b,base);
	}
	return cmdPort->println(b,base);
}

size_t CSI::println(int num, int base)
{
	if (debug){
		debugPort->println(num,base);
	}
	return cmdPort->println(num,base);
}

size_t CSI::println(unsigned int num, int base)
{
	if (debug){
		debugPort->println(num,base);
	}
	return cmdPort->println(num,base);
}

size_t CSI::println(long num, int base)
{
	if (debug){
		debugPort->println(num,base);
	}
	return cmdPort->println(num,base);
}

size_t CSI::println(unsigned long num, int base)
{
	if (debug){
		debugPort->println(num, base);
	}
	return cmdPort->println(num, base);
}

size_t CSI::println(double num, int digits)
{
	if (debug){
		debugPort->println(num,digits);
	}
	return cmdPort->println(num,digits);
}

size_t CSI::println(const Printable& x)
{
	if (debug){
		debugPort->println(x);
	}
	return cmdPort->println(x);
}
