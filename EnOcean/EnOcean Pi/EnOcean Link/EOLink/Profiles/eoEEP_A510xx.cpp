/******************************************************************************
 DISCLAIMER

 THIS SOFTWARE PRODUCT ("SOFTWARE") IS PROPRIETARY TO ENOCEAN GMBH, OBERHACHING, 
 GERMANY (THE "OWNER") AND IS PROTECTED BY COPYRIGHT AND INTERNATIONAL TREATIES OR 
 PROTECTED AS TRADE SECRET OR AS OTHER INTELLECTUAL PROPERTY RIGHT. ALL RIGHTS, TITLE AND
 INTEREST IN AND TO THE SOFTWARE, INCLUDING ANY COPYRIGHT, TRADE SECRET OR ANY OTHER 
 INTELLECTUAL PROPERTY EMBODIED IN THE SOFTWARE, AND ANY RIGHTS TO REPRODUCE, 
 DISTRIBUTE, MODIFY, DISPLAY OR OTHERWISE USE THE SOFTWARE SHALL EXCLUSIVELY VEST IN THE
 OWNER. ANY UNAUTHORIZED REPRODUCTION, DISTRIBUTION, MODIFICATION, DISPLAY OR OTHER
 USE OF THE SOFTWARE WITHOUT THE EXPLICIT PERMISSION OF OWNER IS PROHIBITED AND WILL 
 CONSTITUTE AN INFRINGEMENT OF THE OWNER'S RIGHT AND MAY BE SUBJECT TO CIVIL OR 
 CRIMINAL SANCTION.

 THIS SOFTWARE IS PROVIDED BY THE OWNER "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
 FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN PARTICULAR, THE OWNER DOES NOT WARRANT 
 THAT THE SOFTWARE SHALL BE ERROR FREE AND WORKS WITHOUT INTERRUPTION.

 IN NO EVENT SHALL THE OWNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

#include "eoEEP_A510xx.h"

#include "eoChannelEnums.h"
#include <string.h>

const uint8_t numOfChan = 5;
const uint8_t numOfProfiles = 0x20;

const EEP_ITEM listA510xx[numOfProfiles][numOfChan] =
{
// exist	,bitoffs,bitsize,rangeMin,rangeMax,scaleMin, scaleMax,type;
//TYPE:00
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:01
{
{ true, 0, 8, 0, 255, 0, 4, E_FANSPEED, 0 }, //Fan speed
{ true, 8, 8, 0, 255, 0, 255, S_SETPOINT, 0 }, //Setpoint
{ true, 16, 8, 255, 0, 0, 40, S_TEMP, 0 }, //Temperature
{ true, 31, 1, 0, 1, 0, 1, F_BTN_PRESS, 0 }, //Occupied
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:02
{
{ true, 0, 8, 0, 255, 0, 4, E_FANSPEED, 0 }, //Fan speed
{ true, 8, 8, 0, 255, 0, 255, S_SETPOINT, 0 }, //Setpoint
{ true, 16, 8, 255, 0, 0, 40, S_TEMP, 0 }, //Temperature
{ true, 31, 1, 0, 1, 0, 1, F_DAY_NIGHT, 0 }, //Day/Night switch
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:03
{
{ true, 8, 8, 0, 255, 0, 255, S_SETPOINT, 0 }, //Setpoint
{ true, 16, 8, 255, 0, 0, 40, S_TEMP, 0 }, //Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:04
{
{ true, 0, 8, 0, 255, 0, 4, E_FANSPEED, 0 }, //Fan speed
{ true, 8, 8, 0, 255, 0, 255, S_SETPOINT, 0 }, //Setpoint
{ true, 16, 8, 255, 0, 0, 40, S_TEMP, 0 }, //Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:05
{
{ true, 8, 8, 0, 255, 0, 255, S_SETPOINT, 0 }, //Setpoint
{ true, 16, 8, 255, 0, 0, 40, S_TEMP, 0 }, //Temperature
{ true, 31, 1, 0, 1, 0, 1, F_BTN_PRESS, 0 }, //Occupied
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:06
{
{ true, 8, 8, 0, 255, 0, 255, S_SETPOINT, 0 }, //Setpoint
{ true, 16, 8, 255, 0, 0, 40, S_TEMP, 0 }, //Temperature
{ true, 31, 1, 0, 1, 0, 1, F_DAY_NIGHT, 0 }, //Day/Night switch
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:07
{
{ true, 0, 8, 0, 255, 0, 4, E_FANSPEED, 0 }, //Fan speed
{ true, 16, 8, 255, 0, 0, 40, S_TEMP, 0 }, //Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:08
{
{ true, 0, 8, 0, 255, 0, 4, E_FANSPEED, 0 }, //Fan speed
{ true, 16, 8, 255, 0, 0, 40, S_TEMP, 0 }, //Temperature
{ true, 31, 1, 0, 1, 0, 1, F_BTN_PRESS, 0 }, //Occupied
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:09
{
{ true, 0, 8, 0, 255, 0, 4, E_FANSPEED, 0 }, //Fan speed
{ true, 16, 8, 255, 0, 0, 40, S_TEMP, 0 }, //Temperature
{ true, 31, 1, 0, 1, 0, 1, F_DAY_NIGHT, 0 }, //Day/Night switch
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:0A
{
{ true, 8, 8, 0, 255, 0, 255, S_SETPOINT, 0 }, //Setpoint
{ true, 16, 8, 255, 0, 0, 40, S_TEMP, 0 }, //Temperature
{ true, 31, 1, 0, 1, 0, 1, F_OPEN_CLOSED, 0 }, //Contact state
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:0B
{
{ true, 16, 8, 255, 0, 0, 40, S_TEMP, 0 }, //Temperature
{ true, 31, 1, 0, 1, 0, 1, F_OPEN_CLOSED, 0 }, //Contact state
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:0C
{
{ true, 16, 8, 255, 0, 0, 40, S_TEMP, 0 }, //Temperature
{ true, 31, 1, 0, 1, 0, 1, F_BTN_PRESS, 0 }, //Occupied
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:0D
{
{ true, 16, 8, 255, 0, 0, 40, S_TEMP, 0 }, //Temperature
{ true, 31, 1, 0, 1, 0, 1, F_DAY_NIGHT, 0 }, //Day/Night switch
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:0E
{
{ false, 16, 8, 255, 0, 0, 40, S_TEMP, 0 }, //Temperature
{ false, 31, 1, 0, 1, 0, 1, F_DAY_NIGHT, 0 }, //Day/Night switch
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:0F
{
{ false, 16, 8, 255, 0, 0, 40, S_TEMP, 0 }, //Temperature
{ false, 31, 1, 0, 1, 0, 1, F_DAY_NIGHT, 0 }, //Day/Night switch
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:10
{
{ true, 0, 8, 0, 255, 0, 255, S_SETPOINT, 0 }, //Setpoint
{ true, 16, 8, 0, 250, 0, 40, S_TEMP, 0 }, //Temperature
{ true, 31, 1, 0, 1, 0, 1, F_BTN_PRESS, 0 }, //Occupied
{ true, 8, 8, 0, 250, 0, 100, S_RELHUM, 0 }, //Humidity
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:11
{
{ true, 0, 8, 0, 255, 0, 255, S_SETPOINT, 0 }, //Setpoint
{ true, 16, 8, 0, 250, 0, 40, S_TEMP, 0 }, //Temperature
{ true, 31, 1, 0, 1, 0, 1, F_DAY_NIGHT, 0 }, //Day/Night switch
{ true, 8, 8, 0, 250, 0, 100, S_RELHUM, 0 }, //Humidity
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:12
{
{ true, 0, 8, 0, 255, 0, 255, S_SETPOINT, 0 }, //Setpoint
{ true, 16, 8, 0, 250, 0, 40, S_TEMP, 0 }, //Temperature
{ true, 8, 8, 0, 250, 0, 100, S_RELHUM, 0}, //Humidity
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:13
{
{ true, 16, 8, 0, 250, 0, 40, S_TEMP, 0 }, //Temperature
{ true, 31, 1, 0, 1, 0, 1, F_BTN_PRESS, 0 }, //Occupied
{ true, 8, 8, 0, 250, 0, 100, S_RELHUM, 0 }, //Humidity
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:14
{
{ true, 16, 8, 0, 250, 0, 40, S_TEMP, 0 }, //Temperature
{ true, 31, 1, 0, 1, 0, 1, F_DAY_NIGHT, 0 }, //Day/Night switch
{ true, 8, 8, 0, 250, 0, 100, S_RELHUM, 0 }, //Humidity
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:15
{
{ true, 8, 6, 0, 63, 0, 63, S_SETPOINT, 0 }, //Setpoint
{ true, 14, 10, 1023, 0, -10, 41.2F, S_TEMP, 0 }, //Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:16
{
{ true, 8, 6, 0, 63, 0, 63, S_SETPOINT, 0 }, //Setpoint
{ true, 14, 10, 0, 1023, -10, 41.2F, S_TEMP, 0 }, //Temperature
{ true, 31, 1, 0, 1, 0, 1, F_BTN_PRESS, 0 }, //Occupied
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:17
{
{ true, 14, 10, 1023, 0, -10, 41.2F, S_TEMP, 0 }, //Temperature
{ true, 31, 1, 0, 1, 0, 1, F_BTN_PRESS, 0 }, //Occupied
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:18
{
{ true, 25, 3, 0, 7, 0, 7, E_FANSPEED, 0 }, //Fan speed NOTE: different settings!
{ true, 0, 8, 0, 250, 0, 1000, S_LUMINANCE, 0 }, //Light
{ true, 8, 8, 250, 0, 0, 40, S_TEMP_ABS, 0 }, //Set point for temperature
{ true, 16, 8, 250, 0, 0, 40, S_TEMP, 0 }, //Temperature
{ true, 31, 1, 0, 1, 0, 1, F_BTN_PRESS, 0 } //Occupied
},
//TYPE:19
{
{ true, 25, 3, 0, 7, 0, 7, E_FANSPEED, 0 }, //Fan speed
{ true, 0, 8, 0, 250, 0, 100, S_RELHUM, 0 }, //Humidity
{ true, 8, 8, 250, 0, 0, 40, S_TEMP_ABS, 0 }, //Temperature Set Point
{ true, 16, 8, 250, 0, 0, 40, S_TEMP, 0 }, //Temperature
{ true, 30, 1, 0, 1, 0, 1, F_BTN_PRESS, 0 } //Occupied
},
//TYPE:1A
{
{ true, 25, 3, 0, 7, 0, 7, E_FANSPEED, 0 }, //Fan speed
{ true, 0, 8, 0, 250, 0, 5, S_VOLTAGE, 0 }, //Voltage
{ true, 8, 8, 250, 0, 0, 40, S_TEMP_ABS, 0 }, //Temperature Set Point
{ true, 16, 8, 250, 0, 0, 40, S_TEMP, 0 }, //Temperature
{ true, 31, 1, 0, 1, 0, 1, F_BTN_PRESS, 0 } //Occupied
},
//TYPE:1B
{
{ true, 25, 3, 0, 7, 0, 7, E_FANSPEED, 0 }, //Fan speed
{ true, 8, 8, 0, 250, 0, 1000, S_LUMINANCE, 0 }, //Light
{ true, 0, 8, 0, 250, 0, 5, S_VOLTAGE, 0 }, //Voltage
{ true, 16, 8, 250, 0, 0, 40, S_TEMP, 0 }, //Temperature
{ true, 31, 1, 0, 1, 0, 1, F_BTN_PRESS, 0 } //Occupied
},
//TYPE:1C
{
{ true, 25, 3, 0, 7, 0, 7, E_FANSPEED, 0 }, //Fan speed
{ true, 0, 8, 0, 250, 0, 1000, S_LUMINANCE, 0 }, //Light
{ true, 8, 8, 0, 250, 0, 1000, S_LUMINANCE_ABS, 0 }, //Illumination Set Point
{ true, 16, 8, 250, 0, 0, 40, S_TEMP, 0 }, //Temperature
{ true, 31, 1, 0, 1, 0, 1, F_BTN_PRESS, 0 } //Occupied
},
//TYPE:1D
{
{ true, 25, 3, 0, 7, 0, 7, E_FANSPEED, 0 }, //Fan speed
{ true, 0, 8, 0, 0, 250, 100, S_RELHUM, 0 }, //Humidity
{ true, 8, 8, 0, 0, 250, 100, S_RELHUM_ABS, 0 }, //Humidity Set Point
{ true, 16, 8, 250, 0, 0, 40, S_TEMP, 0 }, //Temperature
{ true, 31, 1, 0, 1, 0, 1, F_BTN_PRESS, 0 } //Occupied
},
//TYPE:1E
{
{ true, 25, 3, 0, 7, 0, 7, E_FANSPEED, 0 }, //Fan speed
{ true, 8, 8, 0, 250, 0, 1000, S_LUMINANCE, 0 }, //Light
{ true, 0, 8, 0, 250, 0, 5, S_VOLTAGE, 0 }, //Voltage
{ true, 16, 8, 250, 0, 0, 40, S_TEMP, 0 }, //Temperature
{ true, 31, 1, 0, 1, 0, 1, F_BTN_PRESS, 0 } //Occupied
},
//TYPE:1F
{
{ true, 0, 8, 0, 255, 0, 4, E_FANSPEED, 0 }, //Fan speed
{ true, 8, 8, 0, 255, 0, 255, S_SETPOINT, 0 }, //Setpoint
{ true, 16, 8, 255, 0, 0, 40, S_TEMP, 0 }, //Temperature
{ true, 31, 1, 0, 1, 0, 1, F_BTN_PRESS, OCCUPANCY }, //Occupied
{ true, 30, 1, 0, 1, 0, 1, F_BTN_PRESS, UNOCCUPANCY }  //Unoccupied
} };

eoEEP_A510xx::eoEEP_A510xx()
{
	channel = new eoEEPChannelInfo[numOfChan];
	channelCount = 0;

	this->rorg = RORG_4BS;
	this->func = 0x10;

}

eoEEP_A510xx::~eoEEP_A510xx()
{
	if(channel!=NULL)
		delete[] channel;
	channel=NULL;
}

eoReturn eoEEP_A510xx::SetType(uint8_t type)
{
	uint8_t tmpChannelCount;
	if (type > numOfProfiles)
		return NOT_SUPPORTED;
	for (tmpChannelCount = 0; tmpChannelCount < numOfChan; tmpChannelCount++)
	{
		if (listA510xx[type][tmpChannelCount].exist)
		{
			channel[channelCount].type = listA510xx[type][tmpChannelCount].type;
			channel[channelCount].max = listA510xx[type][tmpChannelCount].scaleMax;
			channel[channelCount].min = listA510xx[type][tmpChannelCount].scaleMin;
			channel[channelCount].eepItem = &listA510xx[type][tmpChannelCount];
			channelCount++;
		}
	}

	if (type == 0 || channelCount == 0)
		return NOT_SUPPORTED;

	this->type = type;
	return EO_OK;
}

eoReturn eoEEP_A510xx::SetValue(CHANNEL_TYPE type, float value)
{
	uint32_t rawValue;
	eoEEPChannelInfo* myChan = (eoEEPChannelInfo*) GetChannel(type);
	if (myChan == NULL)
		return NOT_SUPPORTED;

	if (myChan->min > value || myChan->max < value)
		return OUT_OF_RANGE; // out of range

	switch (type)
	{
		case S_SETPOINT:
			if (this->type == 0x1F)
				msg.data[3] |= 0x20;
			rawValue = (uint32_t)value;
			break;
		case S_TEMP:
			if (this->type == 0x1F)
				msg.data[3] |= 0x40;
			rawValue = ScaleToRAW(value, myChan->eepItem->rangeMin, myChan->eepItem->rangeMax, myChan->min, myChan->max);
			break;
		case S_VOLTAGE:
		case S_RELHUM_ABS:
		case S_LUMINANCE_ABS:
		case S_TEMP_ABS:
		case S_LUMINANCE:
		case S_RELHUM:
			rawValue = ScaleToRAW(value, myChan->eepItem->rangeMin, myChan->eepItem->rangeMax, myChan->min, myChan->max);
			break;

		default:
			return NOT_SUPPORTED;
			break;
	}

	SetRawValue(msg, rawValue, myChan->eepItem->bitoffs, (uint8_t)myChan->eepItem->bitsize);

	return EO_OK;
}

eoReturn eoEEP_A510xx::GetValue(CHANNEL_TYPE type, float &value)
{
	uint32_t rawValue;
	eoEEPChannelInfo* myChan = (eoEEPChannelInfo*) GetChannel(type);

	if (myChan == NULL)
		return NOT_SUPPORTED;

	if (GetRawValue(msg, rawValue, myChan->eepItem->bitoffs, (uint8_t)myChan->eepItem->bitsize) != EO_OK)
		return NOT_SUPPORTED;
	//General Range check
	if (myChan->eepItem->rangeMin > myChan->eepItem->rangeMax)
	{
		if (myChan->eepItem->rangeMin < rawValue || myChan->eepItem->rangeMax > rawValue)
			return OUT_OF_RANGE;
	}
	else
	{
		if (myChan->eepItem->rangeMin > rawValue || myChan->eepItem->rangeMax < rawValue)
			return OUT_OF_RANGE;
	}

	switch (type)
	{
		case S_SETPOINT:
			if (this->type == 0x1F)
				if ((msg.data[3] & 0x20) != 0x20)
					return NOT_SUPPORTED;
			value = (float)rawValue;
			break;
		case S_TEMP:
			if (this->type == 0x1F)
				if ((msg.data[3] & 0x40) != 0x40)
					return NOT_SUPPORTED;
			value = ScaleFromRAW(rawValue, myChan->eepItem->rangeMin, myChan->eepItem->rangeMax, myChan->min, myChan->max);
			break;
		case S_VOLTAGE:
		case S_RELHUM_ABS:
		case S_LUMINANCE_ABS:
		case S_TEMP_ABS:
		case S_LUMINANCE:
		case S_RELHUM:
			value = ScaleFromRAW(rawValue, myChan->eepItem->rangeMin, myChan->eepItem->rangeMax, myChan->min, myChan->max);
			break;
		default:
			return NOT_SUPPORTED;
	}

	return EO_OK;
}

eoReturn eoEEP_A510xx::SetValue(CHANNEL_TYPE type, uint8_t value)
{
	uint32_t rawValue;
	eoEEPChannelInfo* myChan = (eoEEPChannelInfo*) GetChannel(type);
	if (myChan == NULL)
		return NOT_SUPPORTED;

	if (myChan->min > value || myChan->max < value)
		return OUT_OF_RANGE; // out of range

	switch (type)
	{
		case E_FANSPEED:
			if (channel->max == 4)
			{
				if (this->type == 0x1F)
					msg.data[3] |= 0x10;
				if (value >= 0 && value <= 4)
				{
					int speed[] =
					//3	   2    1    0   Auto stage for fan speed
					{ 72, 155, 177, 199, 232 }; //the values are from the datasheet
					rawValue = speed[(uint32_t) value];
				}
				else
					rawValue = 232;
			}
			else if (channel->max == 7)
			{ //see EEP...
				switch ((int) value)
				{
					case 0:
						rawValue = SPEED_AUTO;
						break;
					case 1:
						rawValue = SPEED_0;
						break;
					case 2:
						rawValue = SPEED_1;
						break;
					case 3:
						rawValue = SPEED_2;
						break;
					case 4:
						rawValue = SPEED_3;
						break;
					case 5:
						rawValue = SPEED_4;
						break;
					case 6:
						rawValue = SPEED_5;
						break;
					default:
						rawValue = SPEED_OFF;
						break;
				}
			}
			break;
		case F_BTN_PRESS:
			if (this->type < 0x18)
			{
				rawValue = value ? 0 : 1;
				break;
			}
			switch (this->type)
			{
				case 0x18:
				case 0x1A:
				case 0x1B:
				case 0x1C:
				case 0x1D:
					msg.data[3] |= 0x02;
					rawValue = value ? 0 : 1;
					break;
				case 0x19:
					msg.data[3] |= 0x01;
					rawValue = value ? 0 : 1;
					break;
				case 0x1F:
					return NOT_SUPPORTED;
			}
			break;
		case F_DAY_NIGHT:
			if (value)
				rawValue = true;
			else
				rawValue = false;
			break;
		case F_OPEN_CLOSED:
			if (value)
				rawValue = true;
			else
				rawValue = false;
			break;
		case F_ON_OFF:
			if (value)
				rawValue = true;
			else
				rawValue = false;
			break;
		default:
			return NOT_SUPPORTED;
			break;
	}

	SetRawValue(msg, rawValue, myChan->eepItem->bitoffs, (uint8_t)myChan->eepItem->bitsize);

	return EO_OK; //EO_OK;
}

eoReturn eoEEP_A510xx::GetValue(CHANNEL_TYPE type, uint8_t &value)
{
	uint32_t rawValue;
	eoEEPChannelInfo* myChan = (eoEEPChannelInfo*) GetChannel(type);

	if (myChan == NULL)
		return NOT_SUPPORTED;

	if (GetRawValue(msg, rawValue, myChan->eepItem->bitoffs, (uint8_t)myChan->eepItem->bitsize) != EO_OK)
		return NOT_SUPPORTED;
	//General Range check
	if (myChan->eepItem->rangeMin > myChan->eepItem->rangeMax)
	{
		if (myChan->eepItem->rangeMin < rawValue || myChan->eepItem->rangeMax > rawValue)
			return OUT_OF_RANGE;
	}
	else
	{
		if (myChan->eepItem->rangeMin > rawValue || myChan->eepItem->rangeMax < rawValue)
			return OUT_OF_RANGE;
	}

	switch (type)
	{
		case E_FANSPEED:
			if (this->type == 0x1F) //check for type 0x1F
				if ((msg.data[3] & 0x10) != 0x10)
					return NOT_SUPPORTED;

			if (channel->max == 4)
			{
				if (rawValue <= 144)
					value = STAGE_3;
				else if (rawValue <= 164)
					value = STAGE_2;
				else if (rawValue <= 189)
					value = STAGE_1;
				else if (rawValue <= 209)
					value = STAGE_0;
				else
					value = STAGE_AUTO;
			}
			else if (channel->max == 7)
				switch (rawValue)
				{
					case 0:
						value = SPEED_AUTO;
						break;
					case 1:
						value = SPEED_0;
						break;
					case 2:
						value = SPEED_1;
						break;
					case 3:
						value = SPEED_2;
						break;
					case 4:
						value = SPEED_3;
						break;
					case 5:
						value = SPEED_4;
						break;
					case 6:
						value = SPEED_5;
						break;
					default:
						value = SPEED_OFF;
						break;
				}
			break;
		case F_BTN_PRESS:
			if (this->type < 0x18)
			{
				value = rawValue ? 0 : 1;
				break;
			}
			switch (this->type)
			{
				case 0x18:
				case 0x1A:
				case 0x1B:
				case 0x1C:
				case 0x1D:
					if (type == F_BTN_PRESS && ((msg.data[3] & 0x02) == 0x02))
						return NOT_SUPPORTED;
					else
					{
						value = rawValue ? 0 : 1;
					}
					break;
				case 0x19:
					if (type == F_BTN_PRESS && ((msg.data[3] & 0x01) == 0x01))
						return NOT_SUPPORTED;
					else
					{
						value = rawValue ? 0 : 1;
					}
					break;
				case 0x1F:
					return NOT_SUPPORTED;
			}
			break;
		case F_DAY_NIGHT:
		case F_OPEN_CLOSED:
		case F_ON_OFF:
			value = rawValue ? 1 : 0;
			break;
		default:
			return NOT_SUPPORTED;
	}

	return EO_OK;
}

eoReturn eoEEP_A510xx::GetValue(CHANNEL_TYPE type, uint8_t &value, uint8_t subFlag)
{
	if (this->type != 0x1F)
		return NOT_SUPPORTED;
	if (type != F_BTN_PRESS)
		return NOT_SUPPORTED;

	uint32_t rawValue;
	eoEEPChannelInfo* myChan;
	switch (subFlag)
	{
		case OCCUPANCY:
			myChan = &channel[3];
			break;
		case UNOCCUPANCY:
			myChan = &channel[4];
			break;
		default:
			return GetValue(type, value);
	}

	if (myChan == NULL)
		return NOT_SUPPORTED;

	if (GetRawValue(msg, rawValue, myChan->eepItem->bitoffs, (uint8_t)myChan->eepItem->bitsize) != EO_OK)
		return NOT_SUPPORTED;

	value = rawValue ? 0 : 1;

	return EO_OK;
}

eoReturn eoEEP_A510xx::SetValue(CHANNEL_TYPE type, uint8_t value, uint8_t subFlag)
{
	if (this->type != 0x1F)
		return NOT_SUPPORTED;
	if (type != F_BTN_PRESS)
		return NOT_SUPPORTED;

	uint32_t rawValue;
	eoEEPChannelInfo* myChan;

	switch (subFlag)
	{
		case OCCUPANCY:
			myChan = &channel[3];
			break;
		case UNOCCUPANCY:
			myChan = &channel[4];
			break;
		default:
			return SetValue(type, value);
	}

	if (myChan == NULL)
		return NOT_SUPPORTED;

	if (myChan->min > value || myChan->max < value)
		return OUT_OF_RANGE; // out of range

	rawValue = value ? 0 : 1;
	SetRawValue(msg, rawValue, myChan->eepItem->bitoffs, (uint8_t)myChan->eepItem->bitsize);

	return EO_OK;
}
