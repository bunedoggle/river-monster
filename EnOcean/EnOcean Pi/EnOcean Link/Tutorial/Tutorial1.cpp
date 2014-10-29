/**
 * \addtogroup tutorial
 * @{
 * \file tutorial1.cpp
 * \brief Tutorial 1: Debug Gateway with repeater function
 * \author EnOcean GmbH
 *
 * In this Tutorial a Debug Gateway with automatic Learn Mode for a period of time, and with screen messages will be created.
 *
 * In the LearnMode only near Field Telegrams will be accepted, and afterwards only learned in Telegrams will be handled.
 *
 * After the learnMode the config will be Saved.
 *
 * You can use this Gateway as base for PC-Testing of specified devices, and can use the generated config then for your endproduct.
*/

#define SER_PORT "/dev/ttyUSB0"//! the Serial Port Device
#define SAVE_CONFIG "./learned.txt" //! where to store the gateway Configuration
#define LEARN_TIME_S 1 //! allows you to set the time the gateway should stay in learnmode

#include "./eoLink.h"

#include <stdio.h>

int main(int argc, const char* argv[]) {
	//First a Gateway and a storageManager will be definied
	eoGateway myGateway;

	printf("Opening Connection to USB300 \n");
	if (myGateway.Open(SER_PORT)!=EO_OK)
	{
		printf("Failed to open USB300\n");
		return 0;
	}
	printf("EnOcean-Link Gateway LearnMode\n");
	//adding a dBm Filter as learnFilter
	eodBmFilter *  learnFilter = new eodBmFilter();
	myGateway.learnFilter = learnFilter;
	learnFilter->maxdBm=-0;
	learnFilter->mindBm=-60;

	//the eoIDFilter will allow our Gateway application to filter all the unwanted Telegrams
	eoIDFilter * myFilter = new eoIDFilter();
	myGateway.filter=myFilter;

	//recv stores the return Value of the Gateway
	uint16_t recv;
	//As RPS Telegrams don't have a teach IN Telegram, we need to set the wished profiled for an automated Teach IN
	myGateway.TeachInModule->SetRPS(0x02,0x01);
	//Set the learnTime and update the time
	uint32_t learnTime=eoTimer::GetTickCount()+LEARN_TIME_S*10000;
	uint32_t time=eoTimer::GetTickCount();
	//Activate LearnMode
	myGateway.LearnMode=true;
	while(learnTime>time)
	{
		//updates the time, using the HAL getTickCount function
		time=eoTimer::GetTickCount();
		//the Gateway::Receive() Functions returns different flags, depending on the Packet we got
		recv = myGateway.Receive();
		//as we're in LearnMode currently we only want to process Teach_IN Telegrams(as specified in EEP)
		if (recv & RECV_TEACHIN)
		{
			//add the Source ID to the Normale Mode Filter
			myFilter->Add(myGateway.telegram.sourceID);
			//Print out the Message to stdout
			eoDebug::Print(myGateway.telegram);
			//If the TeachIN process was successfull and we got a Profile print out the Message!
			eoProfile *profile = myGateway.device->GetProfile();
			if(profile!=NULL)
			{
				printf("Device %08X Learned-In EEP: %02X-%02X-%02X\n", myGateway.device->ID, profile->rorg, profile->func, profile->type );

				for (int i = 0; i<profile->GetChannelCount(); i++)
				{
					printf("%s %.2f ... %.2f %s\n", profile->GetChannel(i)->ToString(NAME), profile->GetChannel(i)->min, profile->GetChannel(i)->max, profile->GetChannel(i)->ToString(UNIT));
				}
			}
		}
	}
	//After the Teach IN Process we want to store the configuration of the Gateway, so you could use the learned in Devices for the
	//next Project
	//Deactivate LearnMode
	myGateway.LearnMode=false;
	eoStorageManager myStore;
	//adding our Gateway to the StorageManager allows the storage Manager to save it

	myStore.addObject("Gateway",&myGateway);
	printf("Storing the Config\n");
	myStore.Save(SAVE_CONFIG);
	printf("EnOcean-Link Gateway FilterdMode\n");

	while (1)
	{
		recv = myGateway.Receive();
		if (recv & RECV_MESSAGE)
		{
			//Resend received telegrams
			myGateway.Send(myGateway.message);
			eoDebug::Print(myGateway.telegram);
		}
		//If we got a valid Profile Telegram which is not a Learn IN we print the received Values
		if (recv & RECV_PROFILE)
		{
			printf("Device %08X\n", myGateway.device->ID);
			eoProfile *profile = myGateway.device->GetProfile();

			float f;
			uint8_t t;
			for (int i = 0; i<profile->GetChannelCount(); i++)
			{
				//get the channel value if it is a float
				if (profile->GetValue( profile->GetChannel(i)->type, f) ==EO_OK)
					printf("%s %.2f %s\n", profile->GetChannel(i)->ToString(NAME),f,profile->GetChannel(i)->ToString(UNIT));
				//get the channel value if it is an uint
				if (profile->GetValue( profile->GetChannel(i)->type, t) ==EO_OK)
					printf("%s %u \n", profile->GetChannel(i)->ToString(NAME),t);
			}
		}

	}
	return 0;
}
/** @}*/
