/*
 File: packetStream_example.cpp

Example Program which opens a Generic Packet Stream and tries to read the Version of the connected Device

 */
#include <stdio.h>
#include "eoLink.h"


void PacketStreamExample()
{
	printf("Example Program to show how a 'Generic Packet Stream' works \n");
	eoLinuxPacketStream ps = eoLinuxPacketStream();
	eoPacket p;

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
