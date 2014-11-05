/*
 File: deviceManager_example.cpp

Example Program which creates a DeviceManager, and adds some Devices, modifies a Device and then deletes a Device;

 */
#include "eoLink.h"

#include <stdio.h>

void deviceManagerExample()
{
	printf("Example Program which creates a Device, and queries for it\n");
	eoDeviceManager myDeviceManager = eoDeviceManager();
	eoDevice * myDevice;
	/*
	 * Adding some devices
	 */
	myDeviceManager.Add(0x80C0001);
	myDeviceManager.Add(0x80C0002);
	myDeviceManager.Add(0x80C0003);
	//Add also returns a pointer to the Device
	myDevice = myDeviceManager.Add(0x80C0004);
	//Now we change the value of the Device
	printf("Last inserted id was 0x%08X\n",myDevice->ID);
	printf("Changing the dBm value to 32 and then we try to add the same device again\n");
	myDevice->dBm=32;

	//If we try to add the same Device again, the function returns a pointer to the existing Device
	myDevice = myDeviceManager.Add(0x80C0004);
	//As the Device already existed we get the already changed dBm
	printf("Id is: 0x%08X dBm  %d\n",myDevice->ID,myDevice->dBm);
	myDevice = myDeviceManager.Get(0x80C0002);
	//always check for NULL when using .Get()
	if(myDevice!=NULL)
		printf("ID should be 0x80C0002 and the ID is 0x%08X\n",myDevice->ID);

	//This device does not exist
	myDevice = myDeviceManager.Get(0x80C0005);
	if(myDevice!=NULL)
		printf("This should not happen, as we get a NULL pointer if the device doesn't exist\n");
	else
		printf("The device 0x80C0005 does not exist!\n");

	//Now we remove an existing Device
	myDeviceManager.Remove(0x80C0004);
	myDevice = myDeviceManager.Get(0x80C0004);
	if(myDevice!=NULL)
		printf("And this also does not happen\n");
	else
		printf("The device 0x80C0004 has been deleted!\n");

}
