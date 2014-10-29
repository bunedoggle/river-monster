/**
 * \addtogroup tutorial
 * @{
 * \file HelloWorld.cpp
 * \brief Hello World : Gateway Receiver with output
 * \author EnOcean GmbH
 *
 * Welcome to the World of eoLink, this Hello World will add an eoLink Gateway and prints out all received telegram to the console.
*/
#define SER_PORT "/dev/USB300"//! the Serial Port Device

#include "./eoLink.h"
#include <stdio.h>

int main(int argc, const char* argv[]) {
	uint16_t recv;
	CO_RD_VERSION_RESPONSE version;
	//First a Gateway will be defined
	eoGateway myGateway;
	//This tries to open an connection to the USB300 or fails otherwise
	printf("Opening Connection to USB300 \n");
	if (myGateway.Open(SER_PORT) != EO_OK)
	{
		printf("Failed to open USB300\n");
		return 0;
	}
	printf("Hello to the world of eoLink\n");

	if(myGateway.commands.ReadVersion(version) == EO_OK)
		printf("%s %i.%i.%i.%i, ID:0x%08X on %s\n",
								   version.appDescription,
								   version.appVersion[0], version.appVersion[1], version.appVersion[2], version.appVersion[3],
								   version.chipID,
								   SER_PORT);
	while(1)
	{
		recv = myGateway.Receive();
		if (recv & RECV_TELEGRAM)
			eoDebug::Print(myGateway.telegram);
	}
	return 0;
}
/** @}*/
