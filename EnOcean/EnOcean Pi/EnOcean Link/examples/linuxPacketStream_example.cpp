/*
 File: packetStream_example.cpp

Example Program which opens a Generic Packet Stream and tries to read the Version of the connected Device

 */
#define SER_PORT "/dev/ttyUSB0"

#include "eoLink.h"

#include <stdio.h>
//Testing main.c
void linuxPacketStreamExample()
{
	eoLinuxPacketStream ps = eoLinuxPacketStream();
	//Reserves 128bytes for the PacketBuffer
	eoPacket p;

	printf("Example Program which queries the USB300 SW Version\n");

	if(ps.Open(SER_PORT)!=EO_OK)
	{
		printf("Error Opening the port \n");
		return ;
	}
	else
		printf("Port is Open \n");

	//Compare ESP3 Spec, we ask for the SW_Version
	p.type=PACKET_COMMON_COMMAND;
	p.dataLength=1;
	p.optionalLength=0;
	p.data[0]=3;
	ps.Send(p);
	//Now we wait until we get a package
	while(ps.Receive(&p)!=EO_OK);
	printf("Read Version Ok; Connected to:\n");
	printf("%s V %d.%d.%d.%d \n",&p.data[17],p.data[1],p.data[2],p.data[3],p.data[4]);
}
