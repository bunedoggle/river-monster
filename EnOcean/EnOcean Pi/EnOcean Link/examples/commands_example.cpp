/*
 File: commands_example.cpp
brief
Example Program which uses eoCommonCommand to set and receive settings from the tcm300 module

 */
#define SER_PORT "/dev/ttyUSB0"//! the Serial Port Device
#define SAVE_CONFIG "./learned.txt" //! where to store the gateway Configuration
#include "./eoLink.h"

#include <stdio.h>

int commands_example() {
	eoGateway gateway; //= eoGateway();

	//adding eoIDFilter to the gateWay
	if (gateway.Open(SER_PORT)!=EO_OK)
	{
		printf("Failed to open USB300\n");
		return -1;
	}

	eoSerialCommand cmd(&gateway);

	//Read Sw and HW version of the device
	CO_RD_VERSION_RESPONSE version;
	if (cmd.ReadVersion(version) == EO_OK)
	{
		printf("%s %i.%i.%i.%i, ID:0x%08X on %s\n",
								   version.appDescription,
								   version.appVersion[0], version.appVersion[1], version.appVersion[2], version.appVersion[3],
								   version.chipID,
								   SER_PORT);
	}
	//Failed to read the version of the device
	else
	{
		printf("Failed to retrieve USB300 version\n");
		return -1;
	}

	//Perform a built in self test
	if (cmd.BIST() == EO_OK)
		printf ("Successful BIST performed!\n");
	//Failed BIST
	else
	{
		printf("Failed to perform BIST\n");
		return -1;
	}

	//Read device ID base
	CO_RD_IDBASE_RESPONSE baseID;
	if (cmd.ReadIDBase(baseID) == EO_OK)
		printf("Base ID: %08X, %i writes left\n", baseID.baseID, baseID.remainingWrites);
	else
	{
		printf("Failed to retrieve USB300 base ID\n");
		return -1;
	}

	//Write repeater
	uint8_t repLevel = 1;
	if (cmd.WriteRepeater(true, repLevel) == EO_OK)
		printf("Repeater added!\n");
	else
	{
		printf("Failed to add repeater\n");
		return -1;
	}

	//Read repeater
	CO_RD_REPEATER_RESPONSE repeater;
	if (cmd.ReadRepeater(repeater) == EO_OK)
		printf("Enabled: %s, Level: %i\n", repeater.repEnable ? "true":"false", repeater.repLevel);
	else
	{
		printf("Failed to read repetear\n");
		return -1;
	}

	//Add filter
	if (cmd.AddFilter(CHOICE,0x11223344, BLOCK) == EO_OK)
		printf("Filter added!\n");
	else
	{
		printf("Failed to add filter\n");
		return -1;
	}

	//Read filter
	CO_RD_FILTER_RESPONSE filter[1];
	uint8_t filterCount;
	if (cmd.ReadFilter(filter, &filterCount, 1) == EO_OK)
		printf("Filter type: %i, Filter value: 0x%08X\n", filter[0].filterType, filter[0].filterValue);
	else
	{
		printf("Failed to read filter\n");
		return -1;
	}

	//Delete filter
	if (cmd.DeleteFilter(CHOICE, 0x11223344) == EO_OK)
		printf("Filter deleted\n");
	else
	{
		printf("Failed to delete filter\n");
		return -1;
	}

	//Enable filter
	if (cmd.EnableFilter(true, OR) == EO_OK)
		printf("Filter enabled\n");
	else
	{
		printf("Failed to enable filter\n");
		return -1;
	}

	//Delete all filter
	if (cmd.DeleteAllFilter() == EO_OK)
		printf("All filter has been deleted!\n");
	else
	{
		printf("Failed to delete all filter\n");
		return -1;
	}

	//Wait maturity time
	if (cmd.WaitMaturity(true) == EO_OK)
		printf("Maturity turned on\n");
	else
	{
		printf("Failed to turn on maturity\n");
		return -1;
	}
	return 0;
}

