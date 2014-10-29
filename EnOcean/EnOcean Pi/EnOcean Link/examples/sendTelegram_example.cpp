/*
 File: sendTelegram_example.cpp

This example shows, how to build an telegram according to profile F6-02-01, set some values and send it out.

 */
#define SER_PORT "/dev/ttyUSB0"//this has to be changed accordingly to your pc/embedded system

#include "./eoLink.h"
#include <stdio.h>

void sendTelegramExample()
{
	eoGateway gateway;

	//adding eoIDFilter to the gateWay
	eoIDFilter * myFilter = new eoIDFilter();
	gateway.filter=myFilter;

	if (gateway.Open(SER_PORT)!=EO_OK)
	{
		printf("Failed to open USB300\n");
		return ;
	}

	
	eoProfile *sendProf = eoProfileFactory::CreateProfile(0xF6,0x02,0x01);

		//Parse our Message
	eoMessage mytel = eoMessage(1);

		sendProf->SetValue(E_ROCKER_B,(uint8_t)0);
		sendProf->SetValue(E_ROCKER_A,(uint8_t)0);
		sendProf->SetValue(E_ENERGYBOW,(uint8_t)1);
		sendProf->Create(mytel);
		gateway.Send(mytel);


		float f;
		uint8_t t;
		printf("Send telegram with:");
		for (int i = 0; i<sendProf->GetChannelCount(); i++)
		{
			//get the channel value if it is a float
			if (sendProf->GetValue( sendProf->GetChannel(i)->type, f) ==EO_OK)
				printf("%s %.2f %s\n", sendProf->GetChannel(i)->ToString(NAME),f,sendProf->GetChannel(i)->ToString(UNIT));
			//get the channel value if it is an uint
			if (sendProf->GetValue( sendProf->GetChannel(i)->type, t) ==EO_OK)
				printf("%s %u \n", sendProf->GetChannel(i)->ToString(NAME),t);
		}


		sendProf->ClearValues();
}
