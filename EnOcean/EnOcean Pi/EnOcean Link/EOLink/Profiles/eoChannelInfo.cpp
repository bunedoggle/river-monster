#include "eoChannelInfo.h"

const char* eoChannelInfo::ToString(uint8_t strType)
{
	if (strType == UNIT)
	{
		if (type < T_FLAG && (type & 0x00FF)<NUM_SIGNAL_STRINGS )
			return signalStrings[type & 0x00FF][1];
	}
	else
	{
		if (type < T_FLAG && (type & 0x00FF)<NUM_SIGNAL_STRINGS)
			return signalStrings[type & 0x00FF][0];
		if (type < T_ENUM && (type & 0x00FF)<NUM_FLAG_STRINGS)
			return flagStrings[type & 0x00FF];
		if((type & 0x00FF)<NUM_ENUMS_STRINGS)
			return enumStrings[type & 0x00FF];
	}
	return signalStrings[0][0];
}
