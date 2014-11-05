/*
 File: Gateway_example.cpp

Example Program which opens a connection to the connected device, and handles received packages.

 */
#define SER_PORT "/dev/ttyUSB1"

#include "./eoLink.h"

#include <stdio.h>
//Testing main.c
void gatewayExample()
{
	eoGateway gateway;
	uint16_t recv;

	if (gateway.Open(SER_PORT)!=EO_OK)
	{
		printf("Failed to open USB300\n");
		return ;
	}

	printf("EnOcean-Link Gateway\n");

	//we set now the automatic RPS-Teach-IN information
	gateway.TeachInModule->SetRPS(0x02,0x01);
	//Activate LearnMode
	gateway.LearnMode=true;
	while (1)
	{
		//eoGateway is normally in LearnMode, to unset LearnMode, set LearnMode to false
		//gateway.LearnMode=false;
		recv = gateway.Receive();

		if (recv & RECV_TELEGRAM)
		{
			eoDebug::Print(gateway.telegram);
		}
		else
		{
			if (recv & RECV_PACKET)
				eoDebug::Print(gateway.packet);
		}

		if ((recv & RECV_TEACHIN))
		{
			eoProfile *profile = gateway.device->GetProfile();
			printf("Device %08X Learned-In EEP: %02X-%02X-%02X\n", gateway.device->ID, profile->rorg, profile->func, profile->type );

			for (int i = 0; i<profile->GetChannelCount(); i++)
			{
				printf("%s %.2f ... %.2f %s\n", profile->GetChannel(i)->ToString(NAME), profile->GetChannel(i)->min, profile->GetChannel(i)->max, profile->GetChannel(i)->ToString(UNIT));
			}

		}

		if (recv & RECV_PROFILE)
		{
			printf("Device %08X\n", gateway.device->ID);
			eoProfile *profile = gateway.device->GetProfile();

			float f;
			uint8_t t;
			for (int i = 0; i<profile->GetChannelCount(); i++)
			{
				if (profile->GetValue( profile->GetChannel(i)->type, f) ==EO_OK)
					printf("%s %.2f %s\n", profile->GetChannel(i)->ToString(NAME),f,profile->GetChannel(i)->ToString(UNIT));
				if (profile->GetValue( profile->GetChannel(i)->type, t) ==EO_OK)
									printf("%s %u \n", profile->GetChannel(i)->ToString(NAME),t);
			}

		}

	}

}

