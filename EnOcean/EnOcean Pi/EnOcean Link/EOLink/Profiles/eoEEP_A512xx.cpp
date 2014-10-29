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

#include "eoEEP_A512xx.h"

#include "eoChannelEnums.h"
#include <string.h>
#include <math.h>

const uint8_t numOfChan = 3;
const uint8_t numOfProfiles = 0x05;

const EEP_ITEM listA512xx[numOfProfiles][numOfChan] =
{
//tobi review: add channel index for all
// exist	,bitoffs,bitsize,rangeMin,rangeMax,scaleMin, scaleMax,type;
//TYPE:00
{
{ true, 0, 24, 0, 16777215, 0, 16777215.0, S_COUNTER, 0 }, //Counter
{ true, 0, 24, 0, 16777215, 0, 16777215.0, S_VOLUME, 0 }, //Counter
{ true, 24, 4, 0, 15, 0, 15, E_TARIFF, 0 }, //Tariff
},
//TYPE:01
{
{ true, 0, 24, 0, 16777215, 0, 16777215.0, S_ENERGY, 0 }, //Counter
{ true, 0, 24, 0, 16777215, 0, 16777215.0, S_POWER, 0 }, //Counter
{ true, 24, 4, 0, 15, 0, 15, E_TARIFF, 0 }, //Tariff
},
//TYPE:02
{
{ true, 0, 24, 0, 16777215, 0, 16777215.0, S_VOLFLOW, 0 }, //Counter
{ true, 0, 24, 0, 16777215, 0, 16777215.0, S_VOLUME, 0 }, //Counter
{ true, 24, 4, 0, 15, 0, 15, E_TARIFF, 0 }, //Tariff
},
//TYPE:03
{
{ true, 0, 24, 0, 16777215, 0, 16777215.0, S_VOLFLOW, 0 }, //Counter
{ true, 0, 24, 0, 16777215, 0, 16777215.0, S_VOLUME, 0 }, //Counter
{ true, 24, 4, 0, 15, 0, 15, E_TARIFF, 0 }, //Tariff
}, };

eoEEP_A512xx::eoEEP_A512xx()
{
	channel = new eoEEPChannelInfo[numOfChan];
	channelCount = 0;

	this->rorg = RORG_4BS;
	this->func = 0x12;
}

eoEEP_A512xx::~eoEEP_A512xx()
{
	if(channel!=NULL)
		delete[] channel;
	channel=NULL;
}

eoReturn eoEEP_A512xx::SetType(uint8_t type)
{
	uint8_t tmpChannelCount;
	if (type > numOfProfiles)
		return NOT_SUPPORTED;
	for (tmpChannelCount = 0; tmpChannelCount < numOfChan; tmpChannelCount++)
	{
		if (listA512xx[type][tmpChannelCount].exist)
		{
			channel[channelCount].type = listA512xx[type][tmpChannelCount].type;
			channel[channelCount].max = listA512xx[type][tmpChannelCount].scaleMax;
			channel[channelCount].min = listA512xx[type][tmpChannelCount].scaleMin;
			channel[channelCount].eepItem = &listA512xx[type][tmpChannelCount];
			channelCount++;
		}
	}

	if (channelCount == 0)
		return NOT_SUPPORTED;

	this->type = type;
	return EO_OK;
}
eoReturn eoEEP_A512xx::GetValue(CHANNEL_TYPE type, float &value)
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
		case E_TARIFF:
			value = (float)rawValue;
			break;
		case S_COUNTER:
		case S_ENERGY:
		case S_VOLFLOW:
			if ((msg.data[3] & 0x04) == 0x04)
				return NOT_SUPPORTED;
			switch (msg.data[3] & 0x03)
			{
				case 0:
					value = (float)rawValue;
					break;
				case 1:
					value = (float)rawValue / 10;
					break;
				case 2:
					value = (float)rawValue / 100;
					break;
				case 3:
					value = (float)rawValue / 1000;
					break;
			}
			break;
		case S_VOLUME:
		case S_POWER:
			if ((msg.data[3] & 0x04) != 0x04)
				return NOT_SUPPORTED;
			switch (msg.data[3] & 0x03)
			{
				case 0:
					value = (float)rawValue;
					break;
				case 1:
					value = (float)rawValue / 10;
					break;
				case 2:
					value = (float)rawValue / 100;
					break;
				case 3:
					value = (float)rawValue / 1000;
					break;
			}
			break;
		default:
			return NOT_SUPPORTED;
	}

	SetRawValue(msg, rawValue, myChan->eepItem->bitoffs, (uint8_t)myChan->eepItem->bitsize);

	return EO_OK;
}

eoReturn eoEEP_A512xx::SetValue(CHANNEL_TYPE type, float value)
{
	uint32_t rawValue;
	eoEEPChannelInfo* myChan = (eoEEPChannelInfo*) GetChannel(type);
	if (myChan == NULL)
		return NOT_SUPPORTED;

	if (myChan->min > value || myChan->max < value)
		return OUT_OF_RANGE; // out of range

	switch (type)
	{
		case E_TARIFF:
			rawValue = (uint32_t)value;
			break;
		case S_COUNTER:
		case S_ENERGY:
		case S_VOLUME:
		case S_VOLFLOW:
		case S_POWER:
			if (type == S_VOLUME || type == S_POWER)
				msg.data[3] |= 0x04;
			if (fabs(value - (int) value) < 0.001) //if there is no decimal number, do not convert it
			{
				rawValue = (uint32_t)value;
			}
			else if (fabs(value * 10 - (int) (value * 10)) < 0.01) //if there is 1 decimal number
			{
				rawValue = (uint32_t)(fabs(value) * 10);
				if (rawValue > myChan->max) //check if the modified number fits into the maximum limit
					return OUT_OF_RANGE;
				msg.data[3] |= 0x01;
			}
			else if (fabs(value * 100 - (int) (value * 100)) < 0.1) //if there is 2 decimal number
			{
				rawValue = (uint32_t)(fabs(value) * 100);
				if (rawValue > myChan->max) //check if the modified number fits into the maximum limit
					return OUT_OF_RANGE;
				msg.data[3] |= 0x02;
			}
			else if (fabs(value * 1000 - (int) (value * 1000)) < 1) //if there is 3 decimal number
			{
				rawValue = (uint32_t)(fabs(value) * 1000);
				if (rawValue > myChan->max) //check if the modified number fits into the maximum limit
					return OUT_OF_RANGE;
				msg.data[3] |= 0x03;
			}
			break;
		default:
			return NOT_SUPPORTED;
			break;
	}

	SetRawValue(msg, rawValue, myChan->eepItem->bitoffs, (uint8_t)myChan->eepItem->bitsize);

	return EO_OK;
}

eoChannelInfo* eoEEP_A512xx::GetChannel(CHANNEL_TYPE type)
{
	switch (this->type)
	{
		case 0x00:
			if (type == S_COUNTER)
				return &channel[0];
			else if (type == S_VOLUME)
				return &channel[1];
			break;
		case 0x01:
			if (type == S_ENERGY)
				return &channel[0];
			else if (type == S_POWER)
				return &channel[1];
			break;
		case 0x02:
		case 0x03:
			if (type == S_VOLFLOW)
				return &channel[0];
			else if (type == S_VOLUME)
				return &channel[1];
			break;
		default:
			return NULL;
			break;
	}
	if (type == E_TARIFF)
		return &channel[2];
	return NULL;
}
