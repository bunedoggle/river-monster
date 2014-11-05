/*
 File: commands_example.cpp
brief
Example Program which uses eoCommonCommand to set and receive settings from the tcm300 module

 */
#define SER_PORT "/dev/ttyUSB0"//! the Serial Port Device
#define SAVE_CONFIG "./learned.txt" //! where to store the gateway Configuration
#include "./eoLink.h"

#include <stdio.h>

void ptmExample() {
	eoGateway gateway; //= eoGateway();
	uint8_t tmpValue;//Return value

	if (gateway.Open(SER_PORT)!=EO_OK)
	{
		printf("Failed to open USB300\n");
		return ;
	}

	eoMessage myMessage = eoMessage(1);
	myMessage.SetDataLength(1);

	myMessage.data[0] = 0x17;//Simulating AI and B0 pressed button with Energybow pressed

	//Creating the profile
	eoProfile *profile = eoProfileFactory::CreateProfile(0xF6, 0x02, 0x01);
	if (profile == NULL)
		return;

	//Parse the message
	profile->Parse(myMessage);

	//Get the value of Energybow
	if (profile->GetValue(E_ENERGYBOW, tmpValue) != EO_OK)
		return;

	//Get the value of Rocker A
	if (profile->GetValue(E_ROCKER_A, tmpValue) != EO_OK)
		return;

	//Get the value of Rocker A
	if (profile->GetValue(E_ROCKER_B, tmpValue) != EO_OK)
		return;

	//Set the same Energybow value in the profile
	profile->SetValue(E_ENERGYBOW, (uint8_t)1);
	//Set the same Energybow value in the profile
	profile->SetValue(E_ROCKER_A, (uint8_t)0);
	//Set the same Energybow value in the profile
	profile->SetValue(E_ROCKER_B, (uint8_t)1);
	//myMessage contains data with Energybow pressed, AI and B0 pressed
	profile->Create(myMessage);

	//Sending the myMessage
	gateway.Send(myMessage);

	//Simulating other button combinations
	//Reseting the values
	profile->ClearValues();

	//Sending Rocker B pressed with Energybow (pressed button)
	profile->SetValue(E_ROCKER_B, (uint8_t)1);
	profile->SetValue(E_ENERGYBOW, (uint8_t)1);
	profile->Create(myMessage);
	gateway.Send(myMessage);

	//Simulating button release
	profile->ClearValues();
	profile->SetValue(E_ENERGYBOW, (uint8_t)0);
	profile->Create(myMessage);
	gateway.Send(myMessage);

	return;
}

