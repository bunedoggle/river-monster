/*
 * commands.cpp
 *
 *  Created on: Sep 11, 2014
 *      Author: brianbailey
 */

#include "commands.h"
#include "hardware.h"
#include "rgb_led.h"

void unsupportedCmd(void* vui, char* cmd){
	CSI* ui = (CSI*)vui;
	ui->cmdPort->print("Bad Command");
	ui->cmdPort->print("?");
}

void getVersion(void* vui, char* cmd){
	CSI* ui = (CSI*)vui;
	ui->cmdPort->print("ThermoJack-2.0");
}

void getTemp(void* vui, char* cmd){
	CSI* ui = (CSI*)vui;
}

void setTemp(void* vui, char* cmd){
	CSI* ui = (CSI*)vui;
}


void getADC(void* vui, char* cmd){
  struct ARGS{
    int id;
  };
  CSI* ui = (CSI*)vui;
  byte data[3];
  int dataint = 0;
  struct ARGS args;
  if(ui->getParams(cmd, (int*)&args, sizeof(ARGS)/sizeof(int))){
    if(args.id <= MAX_ADC_INDEX){
        (CSI*)ui->cmdPort->print("A");
        ui->cmdPort->print(args.id);
        ui->cmdPort->print(",");
        ui->cmdPort->print(analogRead(adc[args.id]));
      }
    else{
      ui->cmdPort->print("Bad ID?");
    }
  }
  else{
    ui->cmdPort->print("getADC?");
  }
}

void getIndicate(void* vui, char* cmd){
	CSI* ui = (CSI*)vui;
}
void setIndicate(void* vui, char* cmd){
  struct ARGS{
    int color;
  };
  CSI* ui = (CSI*)vui;
  struct ARGS args;
  if(ui->getParams(cmd, (int*)&args, sizeof(ARGS)/sizeof(int))){
    pulse(args.color,500);
    ui->cmdPort->print("Indicated:");
    ui->cmdPort->print(args.color);

  }
  else{
	  ui->cmdPort->print("setIndicate?");
  }
}

void registerAllCommands(CSI* ui){

	ui->registerCommand(VERSION, getVersion,  NOOP);
	ui->registerCommand(ADC,     getADC,      NOOP);
	ui->registerCommand(TEMP,    getTemp,     setTemp);
	ui->registerCommand(INDICATE,getIndicate, setIndicate);

}


