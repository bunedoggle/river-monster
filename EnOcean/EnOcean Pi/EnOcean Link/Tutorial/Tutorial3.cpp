/**
 * \addtogroup tutorial
 * @{
 * \file tutorial3.cpp
 * \brief Tutorial 3: Profile Translation Gateway
 * \author EnOcean GmbH
 *
 * In this Tutorial we receive Information from an EEP A5-02-05 and translate it to A5-02-20.
 * */
#define SER_PORT "/dev/USB300"//! the Serial Port Device
#define LOAD_CONFIG "./Tutorial2.txt" //! where to store the gateway Configuration

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
	myStore.Load(LOAD_CONFIG);
	printf("Loaded Config \n");
	uint16_t recv;
	//As we send a 4BS Telegram, we need 4 data bytes
	eoMessage myMessage = eoMessage(4);
	//Creates a profile to create 4BS telegrams.
	eoProfile *sendProfile = eoProfileFactory::CreateProfile(0xA5,0x02,0x20);
	if(sendProfile!=NULL)
		sendProfile->CreateTeachIN(myMessage);
	myGateway.Send(myMessage);
	while (1)
	{
		recv = myGateway.Receive();
		//Got a Profile
		if (recv & RECV_PROFILE)
		{
			printf("Device %08X\n", myGateway.device->ID);
			eoProfile *profile = myGateway.device->GetProfile();

			float f;
			//with a Temperature
			if (profile->GetValue( S_TEMP, f) ==EO_OK)
			{
				printf(" %.2f \n", f);
				if(sendProfile==NULL)
					continue;
				//Use the eoProfile to set the temperature value
				if(sendProfile->SetValue(S_TEMP,f)==EO_OK)
				{
					//and send a Temperature Telegram
					if(sendProfile->Create(myMessage)==EO_OK)
						myGateway.Send(myMessage);
				}
			}
		}

	}
	return 0;
}
/** @}*/
