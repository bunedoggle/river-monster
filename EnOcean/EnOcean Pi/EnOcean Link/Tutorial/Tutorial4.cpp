/**
 * \addtogroup tutorial
 * @{
 * \file tutorial4.cpp
 * \brief Tutorial 4: Manual Teach Handling of devices.
 * \details This is just a short "appnote"/Tutorial how to handle Teach Telegrams when you are not in learn mode using
 * the TeachInModule of the gateway. It also automatically unlearns devices after a Second TeachIN
 * \author EnOcean GmbH
 *
 * In this Tutorial
 * */
#define SER_PORT "/dev/USB300"//! the Serial Port Device
#define SAVE_CONFIG "./learned.txt" //! where to Load the gateway Configuration
#define LEARN_TIME_S 1 //! allows you to set the time the gateway should stay in learnmode

#include "./eoLink.h"
#include <stdio.h>


int main(int argc, const char* argv[]) {
	eoGateway myGateway;
	uint16_t recv=0;
	printf("Opening Connection to USB300 \n");
	if (myGateway.Open(SER_PORT)!=EO_OK)
	{
		printf("Failed to open USB300\n");
		return 0;
	}
	myGateway.TeachInModule->SetRPS(0x02,0x01);
	myGateway.TeachInModule->Set1BS(0x00,0x01);
	while (1)
	{
		recv = myGateway.Receive();
		//Got a Profile
		if (recv & RECV_SECTEACHIN)
		{
			myGateway.TeachInModule->TeachOut(myGateway.message.sourceID);
		}
		else if (recv & RECV_TEACHIN)
		{
			myGateway.TeachInModule->TeachIN(myGateway.message);
		}


	}
	return 0;
}
/** @}*/
