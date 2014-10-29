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

#include "eoEEP_A506xx.h"

#include "eoChannelEnums.h"
#include <string.h>

const uint8_t numOfChan = 3;
const uint8_t numOfProfiles = 0x04;
//Channels have to be in the right order for the getChannel function
const EEP_ITEM listA506xx[numOfProfiles][numOfChan] =
{
// exist,bitoffs,bitsize,rangeMin,rangeMax,scaleMin, scaleMax,type;
//TYPE:00
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 }, },
//TYPE:01
{
{ true, 0, 8, 0, 255, 0, 5.1F, S_VOLTAGE, 0 }, //Voltage
{ true, 8, 8, 0, 255, 300, 30000, S_LUMINANCE, 0 }, //Light
{ true, 16, 8, 0, 255, 600, 60000, S_LUMINANCE, 0 }, //Light

},
//TYPE:02
{
{ true, 0, 8, 0, 255, 0, 5.1F, S_VOLTAGE, 0 }, //Voltage
{ true, 8, 8, 0, 255, 0, 510, S_LUMINANCE, 0 }, //Light
{ true, 16, 8, 0, 255, 0, 1020, S_LUMINANCE, 0 } //Light
},
//TYPE:03
{
{ true, 0, 8, 0, 255, 0, 5.1F, S_VOLTAGE, 0 }, //Voltage
{ true, 8, 10, 0, 1000, 0, 1000, S_LUMINANCE, 0 }, //Light
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 }, }, };

eoEEP_A506xx::eoEEP_A506xx()
{
	channel = new eoEEPChannelInfo[numOfChan];
	channelCount = 0;

	this->rorg = RORG_4BS;
	this->func = 0x06;
}

eoEEP_A506xx::~eoEEP_A506xx()
{
	//Tobi Review: added delete parameter to free memory
	if(channel!=NULL)
		delete[] channel;
	channel=NULL;
}

eoReturn eoEEP_A506xx::SetType(uint8_t type)
{
	uint8_t tmpChannelCount;
	if (type > numOfProfiles)
		return NOT_SUPPORTED;
	for (tmpChannelCount = 0; tmpChannelCount < numOfChan; tmpChannelCount++)
	{
		if (listA506xx[type][tmpChannelCount].exist)
		{
			channel[channelCount].type = listA506xx[type][tmpChannelCount].type;
			channel[channelCount].max = listA506xx[type][tmpChannelCount].scaleMax;
			channel[channelCount].min = listA506xx[type][tmpChannelCount].scaleMin;
			channel[channelCount].eepItem = &listA506xx[type][tmpChannelCount];
			channelCount++;
		}
	}

	if (type == 0 || channelCount == 0)
		return NOT_SUPPORTED;

	this->type = type;
	return EO_OK;
}

eoChannelInfo* eoEEP_A506xx::GetChannel(CHANNEL_TYPE type)
{
	if (type == S_LUMINANCE)
	{
		if ((msg.data[3] & 0x01) || (this->type == 0x03))
			return &channel[1];
		else
			return &channel[2];
	}
	else if (type == S_VOLTAGE)
		return &channel[0];
	return NULL;
}

eoReturn eoEEP_A506xx::SetValue(CHANNEL_TYPE type, float value)
{
	uint32_t rawValue;
	eoEEPChannelInfo* myChan = (eoEEPChannelInfo*) GetChannel(type);
	if (myChan == NULL)
		return NOT_SUPPORTED;

	switch (type)
	{
		case S_LUMINANCE:

			if (myChan->min > value)
				myChan = &channel[1];
			else if (myChan->max < value)
			{
				myChan = &channel[2];
				msg.data[3] |= 0x01;
			}
			if (myChan->min > value || myChan->max < value)
				return OUT_OF_RANGE; // out of range
			break;

		case S_VOLTAGE:
			if (myChan->min > value || myChan->max < value)
				return OUT_OF_RANGE; // out of range
			break;

		default:
			return NOT_SUPPORTED;
			break;
	}

	rawValue = ScaleToRAW(value, myChan->eepItem->rangeMin, myChan->eepItem->rangeMax, myChan->min, myChan->max);
	SetRawValue(msg, rawValue, myChan->eepItem->bitoffs, (uint8_t)myChan->eepItem->bitsize);

	return EO_OK;
}
