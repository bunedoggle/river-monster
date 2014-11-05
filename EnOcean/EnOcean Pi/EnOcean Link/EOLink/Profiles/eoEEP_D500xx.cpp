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

#include "eoEEP_D500xx.h"

#include "eoChannelEnums.h"
#include <string.h>

const uint8_t numOfChan = 1;
const uint8_t numOfProfiles = 0x02;

const EEP_ITEM listD500xx[numOfProfiles][numOfChan] =
{
// exist	,bitoffs,bitsize,rangeMin,rangeMax,scaleMin, scaleMax,type;
//TYPE:00
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 }, },
//TYPE:01
{
{ true, 7, 1, 0, 1, 0, 1, F_OPEN_CLOSED, 0 }, //Occupied
}, };

eoEEP_D500xx::eoEEP_D500xx()
{
	channel = new eoEEPChannelInfo[numOfChan];
	channelCount = 0;

	this->rorg = RORG_1BS;
	this->func = 0x00;
	msg.RORG = RORG_1BS;
	msg.SetDataLength(1);
}

eoEEP_D500xx::~eoEEP_D500xx()
{
	if(channel!=NULL)
		delete[] channel;
	channel=NULL;
}


eoReturn eoEEP_D500xx::SetType(uint8_t type)
{
	uint8_t tmpChannelCount;
	if (type > numOfProfiles)
		return NOT_SUPPORTED;
	for (tmpChannelCount = 0; tmpChannelCount < numOfChan; tmpChannelCount++)
	{
		if (listD500xx[type][tmpChannelCount].exist)
		{
			channel[channelCount].type = listD500xx[type][tmpChannelCount].type;
			channel[channelCount].max = listD500xx[type][tmpChannelCount].scaleMax;
			channel[channelCount].min = listD500xx[type][tmpChannelCount].scaleMin;
			channel[channelCount].eepItem = &listD500xx[type][tmpChannelCount];
			channelCount++;
		}
	}

	if (type == 0 || channelCount == 0)
		return NOT_SUPPORTED;

	this->type = type;
	return EO_OK;
}
eoReturn eoEEP_D500xx::GetValue(CHANNEL_TYPE type, uint8_t &value)
{
	uint32_t rawValue;
	eoEEPChannelInfo* myChan = (eoEEPChannelInfo*) GetChannel(type);
	//Only channel in this profile is the Occupied channel, thats why we only check against NULL
	if (myChan == NULL)
		return NOT_SUPPORTED;

	if (GetRawValue(msg, rawValue, myChan->eepItem->bitoffs, (uint8_t)myChan->eepItem->bitsize) != EO_OK)
		return NOT_SUPPORTED;

	value = rawValue ? 1 : 0;

	return EO_OK;
}

eoReturn eoEEP_D500xx::SetValue(CHANNEL_TYPE type, uint8_t value)
{
	uint32_t rawValue;
	eoEEPChannelInfo* myChan = (eoEEPChannelInfo*) GetChannel(type);
	if (myChan == NULL)
		return NOT_SUPPORTED;

	if (value != 1 && value != 0)
		return OUT_OF_RANGE;

	rawValue = value ? 1 : 0;

	SetRawValue(msg, rawValue, myChan->eepItem->bitoffs, (uint8_t)myChan->eepItem->bitsize);

	return EO_OK; //EO_OK;
}

eoReturn eoEEP_D500xx::Parse(const eoMessage &msg)
{
	if (msg.GetDataLength() != 1 && msg.RORG != RORG_1BS)
		return NOT_SUPPORTED;

	return eoProfile::Parse(msg);
}
