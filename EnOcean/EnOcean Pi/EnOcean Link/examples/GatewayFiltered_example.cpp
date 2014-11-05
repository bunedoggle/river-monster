/*
 File: GatewayFiltered_example.cpp

This example, shows you how to implement a gateway, which is in learnMode in the first 10seconds after Starting Up.
Using the an eodBmFilter as LearnFilter, only near field telegrams are used to learn IN.

For rps we add manually an EEP.

All the learned IN Devices will be added to an eoIDFilter, and used in the normal mode, to filter out other Devices.

 */
#define SER_PORT "/dev/ttyUSB0"//this has to be changed accordingly to your pc/embedded system

#include "./eoLink.h"
#include <stdio.h>

void gatewayFitleredExample()
{
	eoGateway gateway;

	//adding eoIDFilter to the gateWay
	eoIDFilter* myFilter = new eoIDFilter();
	gateway.filter=myFilter;
	uint32_t learnTime;
	uint16_t recv;

	if (gateway.Open(SER_PORT)!=EO_OK)
	{
		printf("Failed to open USB300\n");
		return ;
	}

	printf("EnOcean-Link Gateway LearnMode\n");
	//we set now the automatic RPS-Teach-IN information to RPS-Rocker
	gateway.TeachInModule->SetRPS(0x02,0x01);
	//100sec learnmode
	learnTime=eoTimer::GetTickCount()+1000*10;
	uint32_t time=eoTimer::GetTickCount();
	//adding a dBm Filter as learnFilter
	eodBmFilter*  learnFilter = new eodBmFilter();
	gateway.learnFilter = learnFilter;
	learnFilter->maxdBm=-0;
	learnFilter->mindBm=-60;
	//Activate LearnMode
	gateway.LearnMode=true;
	while(learnTime>time)
	{
		time=eoTimer::GetTickCount();
		recv = gateway.Receive();
		if (recv & RECV_TEACHIN)
		{
			myFilter->Add(gateway.telegram.sourceID);
			eoDebug::Print(gateway.telegram);
			//print teach_in Information
			eoProfile *profile = gateway.device->GetProfile();

			if(profile!=NULL)
			{
				printf("Device %08X Learned-In EEP: %02X-%02X-%02X\n", gateway.device->ID, profile->rorg, profile->func, profile->type );
				for (int i = 0; i<profile->GetChannelCount(); i++)
				{
					printf("%s %.2f ... %.2f %s\n", profile->GetChannel(i)->ToString(NAME), profile->GetChannel(i)->min, profile->GetChannel(i)->max, profile->GetChannel(i)->ToString(UNIT));
				}
			}

		}
	}

	gateway.LearnMode=false;
	printf("EnOcean-Link Gateway FilterdMode\n");

	while (1)
	{
		recv = gateway.Receive();
		if (recv & RECV_PROFILE)
		{
			printf("Device %08X\n", gateway.device->ID);
			eoProfile *profile = gateway.device->GetProfile();

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
		else if (recv & RECV_TELEGRAM)
		{
			eoDebug::Print(gateway.telegram);
		}
	}
}

