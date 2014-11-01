/*
 * commands.cpp
 *
 *  Created on: Sep 11, 2014
 *      Author: brianbailey
 */

#include "commands.h"
#include <SoftwareSerial.h>

void unsupportedCmd(void* vui, char* cmd){
	CSI* ui = (CSI*)vui;
	ui->cmdPort->print("Bad Command");
	ui->cmdPort->print("?");
}

void getVersion(void* vui, char* cmd){
	CSI* ui = (CSI*)vui;
	ui->cmdPort->print("RiverMonster v1.0");
}

void setDataPoint(void* vui, char* cmd){//aka send text for now
        struct ARGS{
          String message;
        };
        CSI* ui = (CSI*)vui;
        struct ARGS args;
        if (ui->getStringParams(cmd, (String*)&args, sizeof(ARGS)/sizeof(String))){
          ui->cmdPort->print(args.message);
          SendTextMessage(args.message, ui->mySerial);
        } 
}

void registerAllCommands(CSI* ui){

	ui->registerCommand(VERSION, getVersion,  NOOP);
        ui->registerCommand(DATAPOINT, NOOP, setDataPoint);

}

bool powerUpOrDown()
{
  static bool on = 0;
  
  pinMode(9, OUTPUT); 
  digitalWrite(9,LOW);
  delay(1000);
  digitalWrite(9,HIGH);
  delay(2000);
  digitalWrite(9,LOW);
  delay(3000);

  on = !on;
  return on;
}
 
///SendTextMessage()
///this function is to send a sms message
void SendTextMessage(String message, SoftwareSerial* mySerial)
{
  mySerial->print("AT+CMGF=1\r");//because we want to send the SMS in text mode
  delay(100);
  mySerial->println("AT + CMGS = \"19787986086\"");//send sms message, be careful need to add a country code before the cellphone number
  delay(100);
  mySerial->println(message);//the content of the message
  delay(100);
  mySerial->println((char)26);//the ASCII code of the ctrl+z is 26
  delay(100);
  mySerial->println();
}
 //19787986086
void ShowSerialData(SoftwareSerial* mySerial)
{
  while(mySerial->available()!=0)
    Serial.write(mySerial->read());
}
