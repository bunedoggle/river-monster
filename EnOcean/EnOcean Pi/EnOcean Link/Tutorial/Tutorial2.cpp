/**
 * \addtogroup tutorial
 * @{
 * \file tutorial2.cpp
 * \brief Tutorial 2: Debug Gateway with repeater function
 * \author EnOcean GmbH
 *
 * In this Tutorial a Gateway which checks the Temperature of an external Sensors, and sends a warning Messages if we reach over 30°C.
 * As we do not want to learn in Devices, we uses a prepared configuration, and load it after Starting UP.
 * */
#define SER_PORT "/dev/USB300"//! the Serial Port Device
#define LOAD_CONFIG "./learned.txt" //! where to store the gateway Configuration

#include "./eoLink.h"
#include <stdio.h>


int main(int argc, const char* argv[]) {
	eoGateway myGateway;

	printf("Opening Connection to USB300 \n");
	if (myGateway.Open(SER_PORT)!=EO_OK)
	{
		printf("Failed to open USB300\n");
		return 0;
	}
	//Loading the prepared Configuartion
	eoStorageManager myStore;
	myStore.addObject("Gateway",&myGateway);
	printf("Prepare to Load Config \n");
	myStore.Load(LOAD_CONFIG);


	uint16_t recv;
	//we use in this example a 1BS Telegram, to send an Alarm Flag, which type of messsage is not specified!
	eoMessage myMessage = eoMessage(1);
	myMessage.RORG=RORG_1BS;
	myMessage.data[0]=0xFF;
	printf("Gateway is running \n");
	while (1)
	{
		recv = myGateway.Receive();
		if (recv & RECV_PROFILE)
		{
			printf("Device %08X\n", myGateway.device->ID);
			eoProfile *profile = myGateway.device->GetProfile();

			float f;

			if (profile->GetValue( S_TEMP, f) ==EO_OK)
			{
				printf(" %.2f \n", f);
				//our value is higher then 30° send the warning message!
				if(f>30.0)
					myGateway.Send(myMessage);
			}
		}

	}

	return 0;
}
/** @}*/
