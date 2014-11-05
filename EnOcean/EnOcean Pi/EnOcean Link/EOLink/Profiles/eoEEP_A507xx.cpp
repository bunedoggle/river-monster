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

#include "eoEEP_A507xx.h"

#include "eoChannelEnums.h"
#include <string.h>

const uint8_t numOfChan = 3;
const uint8_t numOfProfiles = 0x04;

const EEP_ITEM listA507xx[numOfProfiles][numOfChan] =
{
// exist	,bitoffs,bitsize,rangeMin,rangeMax,scaleMin, scaleMax,type;
//TYPE:00
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:01
{
{ true, 0, 8, 0, 250, 0, 5.0, S_VOLTAGE, 0 }, //Voltage
{ true, 16, 8, 0, 255, 0, 1, F_OCCUPIED, 0 }, //Occupancy
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 }, },
//TYPE:02
{
{ true, 0, 8, 0, 250, 0, 5.0, S_VOLTAGE, 0 }, //Voltage
{ true, 8, 8, 0, 250, 0, 1000.0, S_LUMINANCE, 0 }, //Luminance
{ true, 16, 8, 0, 255, 0, 1, F_OCCUPIED, 0 }, //Occupancy
},
//TYPE:03
{
{ true, 0, 8, 0, 250, 0, 5.0, S_VOLTAGE, 0 }, //Voltage
{ true, 8, 10, 0, 1000, 0, 1000.0, S_LUMINANCE, 0 }, //Luminance
{ true, 24, 1, 0, 1, 0, 1, F_OCCUPIED, 0 }, //Occupancy
} };

eoEEP_A507xx::eoEEP_A507xx()
{
	channel = new eoEEPChannelInfo[numOfChan];
	channelCount = 0;

	this->rorg = RORG_4BS;
	this->func = 0x07;
}

eoEEP_A507xx::~eoEEP_A507xx()
{
	//Tobi Review: added delete parameter to free memory
	if(channel!=NULL)
		delete[] channel;
	channel=NULL;
}

eoReturn eoEEP_A507xx::SetType(uint8_t type)
{
	uint8_t tmpChannelCount;
	if (type > numOfProfiles)
		return NOT_SUPPORTED;
	for (tmpChannelCount = 0; tmpChannelCount < numOfChan; tmpChannelCount++)
	{
		if (listA507xx[type][tmpChannelCount].exist)
		{
			channel[channelCount].type = listA507xx[type][tmpChannelCount].type;
			channel[channelCount].max = listA507xx[type][tmpChannelCount].scaleMax;
			channel[channelCount].min = listA507xx[type][tmpChannelCount].scaleMin;
			channel[channelCount].eepItem = &listA507xx[type][tmpChannelCount];
			channelCount++;
		}
	}

	if (type == 0 || channelCount == 0)
		return NOT_SUPPORTED;

	this->type = type;
	return EO_OK;
}

eoReturn eoEEP_A507xx::GetValue(CHANNEL_TYPE type, float &value)
{
	if (this->type != 0x03 && type == S_VOLTAGE && (msg.data[3] & 0x01) != 0x01)
		return NOT_SUPPORTED;

	return eoA5EEProfile::GetValue(type, value);
}

eoReturn eoEEP_A507xx::SetValue(CHANNEL_TYPE type, float value)
{
	if (type == S_VOLTAGE)
		msg.data[3] |= 0x01;

	return eoA5EEProfile::SetValue(type, value);
}

eoReturn eoEEP_A507xx::GetValue(CHANNEL_TYPE type, uint8_t &value)
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
		case F_OCCUPIED:
			if (this->type == 0x03)
			{
				if (rawValue == 1)
					value = true;
				else
					value = false;
				break;
			}
			if (rawValue > 127)
				value = true;
			else
				value = false;
			break;
		default:
			return NOT_SUPPORTED;
	}

	return EO_OK;
}

eoReturn eoEEP_A507xx::SetValue(CHANNEL_TYPE type, uint8_t value)
{
	uint32_t rawValue;
	eoEEPChannelInfo* myChan = (eoEEPChannelInfo*) GetChannel(type);
	if (myChan == NULL)
		return NOT_SUPPORTED;

	if (myChan->min > value || myChan->max < value)
		return OUT_OF_RANGE; // out of range

	switch (type)
	{
		case F_OCCUPIED:
			if (this->type == 0x03)
			{
				if (value)
					rawValue = 1;
				else
					rawValue = 0;
				break;
			}
			if (value)
				rawValue = 191;
			else
				rawValue = 64;
			break;

		default:
			return NOT_SUPPORTED;
	}

	SetRawValue(msg, rawValue, myChan->eepItem->bitoffs, (uint8_t)myChan->eepItem->bitsize);
	return EO_OK; //EO_OK;
}
