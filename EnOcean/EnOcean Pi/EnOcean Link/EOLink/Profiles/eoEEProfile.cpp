/*
 * eoEEProfile.cpp
 *
 *  Created on: 22.11.2012
 *      Author: tobi
 */

#include "eoEEProfile.h"

eoEEProfile::eoEEProfile(uint16_t size) :
		eoProfile(size)
{
	channel = NULL;
	channelCount = 0;
}

eoEEProfile::~eoEEProfile()
{
	if (channel != NULL)
		delete[] channel;
	channel = NULL;
}

eoChannelInfo* eoEEProfile::GetChannel(CHANNEL_TYPE type, uint8_t subType)
{
	if (subType == 0)
		return GetChannel(type);
	else
		return NULL;
}
eoChannelInfo* eoEEProfile::GetChannel(CHANNEL_TYPE type)
{
	uint8_t tmpChanCnt;
	for (tmpChanCnt = 0; tmpChanCnt < channelCount; tmpChanCnt++)
	{
		if (channel[tmpChanCnt].type == type)
			return (eoChannelInfo*) &channel[tmpChanCnt];
	}
	return NULL;
}
eoChannelInfo* eoEEProfile::GetChannel(uint8_t channelNumber)
{
	eoChannelInfo* retChannel = NULL;
	if (channelNumber < channelCount)
		retChannel = (eoChannelInfo*) (&channel[channelNumber]);
	return retChannel;
}
uint8_t eoEEProfile::GetChannelCount() const
{
	return channelCount;
}

