/*
 * \file eoEEProfile.h
 *
 *  Created on: 22.11.2012
 *      Author: tobi
 */

#ifndef EO_EEPROFILE_H_
#define EO_EEPROFILE_H_

#include "eoProfile.h"

/**
 * \ingroup eepProfiles 
 * @{
 */
/**
 * \class eoEEProfile
 * \brief base class for EEProfile parsing
 * \details This class is the base class for all eoEEProfiles.
 * \example profile_examples.cpp
 */
class eoEEProfile: public eoProfile
{
public:
	/**
	 * Constructor
	 * @param size Default size of the expected message.
	 */
	eoEEProfile(uint16_t size = 4);
	virtual ~eoEEProfile();

	//virtual bool operator==(const eoProfile &othProfile) const;
	//virtual bool operator!=(const eoProfile &othProfile) const;
	/**
	 virtual eoReturn Create(eoMessage &m);
	 virtual eoReturn CreateTeachIN(eoMessage &m);

	 virtual eoReturn  Parse(const eoMessage &msg);

	 virtual eoReturn GetValue(CHANNEL_TYPE type, float &value);
	 virtual eoReturn GetValue(CHANNEL_TYPE type, float &value, uint8_t subFlag);
	 virtual eoReturn GetValue(CHANNEL_TYPE type, uint8_t &value);
	 virtual eoReturn GetValue(CHANNEL_TYPE type, uint8_t &value, uint8_t subFlag);

	 virtual eoReturn SetValue(CHANNEL_TYPE type,float value, uint8_t subFlag);
	 virtual eoReturn SetValue(CHANNEL_TYPE type,uint8_t value, uint8_t subFlag);

	 virtual eoReturn SetValue(CHANNEL_TYPE type, float value);
	 virtual eoReturn SetValue(CHANNEL_TYPE type, const uint8_t value);
	 **/
	virtual eoChannelInfo* GetChannel(CHANNEL_TYPE type, uint8_t subType);
	virtual eoChannelInfo* GetChannel(CHANNEL_TYPE type);
	virtual eoChannelInfo* GetChannel(uint8_t channelNumber);

	//virtual eoReturn SetType(uint8_t type);

	virtual uint8_t GetChannelCount() const;

protected:
	//! ChannelInfo list for direct Access to channels
	eoEEPChannelInfo* channel;
	//! Number of channels
	uint8_t channelCount;

};
/**
 * @}
 */

#endif /* EOEEPROFILE_H_ */
