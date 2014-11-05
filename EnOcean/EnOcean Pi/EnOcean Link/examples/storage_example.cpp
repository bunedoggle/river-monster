/*
 File: Storage_example.cpp

Example how to add an Gateway to the Storage Manager and Load and Save a File

 */
#define SER_PORT "/dev/ttyUSB1"

#include "eoLink.h"

#include <stdio.h>
//Testing main.c
void storageExample()
{
	eoGateway gateway ;
	eoStorageManager myStore = eoStorageManager();
	//adds the Object Gateway to the storage manager
	myStore.addObject("Gateway",&gateway);
	//now when you load a file, and it contains a Block Gateway, the Gateway will be loaded
	myStore.Load("/root/eoLinkSave.txt");
	/*
	 * main application
	 */
	//every Object which has been added to the storageManager will be saved to the output File
	myStore.Save("/root/eoLinkSave.txt");
}

