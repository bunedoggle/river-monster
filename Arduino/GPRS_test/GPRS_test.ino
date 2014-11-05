/*Note: this code is a demo for how to using gprs shield to send sms message, dial a voice call and 
  send a http request to the website, upload data to pachube.com by TCP connection,
 
  The microcontrollers Digital Pin 7 and hence allow unhindered
  communication with GPRS Shield using SoftSerial Library. 
  IDE: Arduino 1.0 or later
  Replace the following items in the code:
  1.Phone number, don't forget add the country code
  2.Replace the Access Point Name
  3. Replace the Pachube API Key with your personal ones assigned
  to your account at cosm.com
  */
 

#include <SoftwareSerial.h>
#include <String.h>
#include "CSI.h"
#include "commands.h"
 
SoftwareSerial mySerial(7, 8);
CSI ui(&Serial, &mySerial);

void setup()
{
  mySerial.begin(19200);               // the GPRS baud rate   
  Serial.begin(115200);    // the GPRS baud rate 
  registerAllCommands(&ui);
  delay(500);
  Serial.println("Setup complete");
}
 
void loop()
{
  //after start up the program, you can use a terminal to connect the serial of gprs shield,
  //if you input 't' in the terminal, the program will execute SendTextMessage(), it will show how to send a sms message,
  //if input 'd' in the terminal, it will execute DialVoiceCall(), etc.
  ui.serialEventHandler();
  /*
  if (Serial.available())
    switch(Serial.read())
   {
     case 't':
       SendTextMessage("");
       break;
   } 
   */
  if (mySerial.available())
    Serial.write(mySerial.read());
}


