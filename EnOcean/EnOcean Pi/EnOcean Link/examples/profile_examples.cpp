/*
 File: profile_example.cpp

Example Program which creates manually two new Profiles,
one Profile will receive values and the other one will send values
 */
#include "eoLink.h"

#include <stdio.h>

void profileExamples()
{
	//Simulated msg with EEP-A5-02-05 Telegram
	//Temperature: 26.67° and DataTelegram
	float tmpValue;
	eoMessage myMessage = eoMessage(4);
	myMessage.SetDataLength(4);
	myMessage.data[0]=0x00;
	myMessage.data[0]=0x00;
	myMessage.data[0]=0x55;//26.67°
	myMessage.data[0]=0x08;//DataTelegram

	//This is the Profile to handle the received Data
	eoProfile *recProf = eoProfileFactory::CreateProfile(0xA5,0x02,0x05);

	if(recProf==NULL)
		return;
	//And this profile will generate msg to send
	eoProfile *sendProf = eoProfileFactory::CreateProfile(0xA5,0x02,0x30);
	if(sendProf==NULL)
		return;
	//Parse our Message
	recProf->Parse(myMessage);
	//get the Temperature
	if(recProf->GetValue(S_TEMP,tmpValue)!=EO_OK)
		return;
	//Now we set the same Temperature in our sendProfile
	//sendProf->Clear() ?
	sendProf->SetValue(S_TEMP,tmpValue);
	//myMessage contains now an EEP-A5-02-30 data with the temperature 26.67°
	sendProf->Create(myMessage);
}
