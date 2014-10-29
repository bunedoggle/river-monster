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

#include "eoEEP_F610xx.h"

#include "eoChannelEnums.h"
#include <string.h>
#include <typeinfo>
const uint8_t numOfChan = 1;
const uint8_t numOfProfiles = 0x01;

//Channels have to be in the right order for the getChannel function

eoEEP_F610xx::eoEEP_F610xx()
{
	channel = new eoEEPChannelInfo[numOfChan];
	channelCount = 0;

	this->rorg = RORG_RPS;
	this->func = 0x10;
}

eoEEP_F610xx::~eoEEP_F610xx()
{
	if(channel!=NULL)
		delete[] channel;
	channel=NULL;
}


eoReturn eoEEP_F610xx::SetType(uint8_t type)
{
	if (type > numOfProfiles)
		return NOT_SUPPORTED;
	channel[0].type = E_WINDOWHANDLE;
	channel[0].min = 0;
	channel[0].max = 255;

	channelCount = 1;

	if (type != 0 || channelCount == 0)
		return NOT_SUPPORTED;

	this->type = type;
	return EO_OK;
}

eoChannelInfo* eoEEP_F610xx::GetChannel(CHANNEL_TYPE type)
{
	eoChannelInfo* myChan = NULL;
	switch (type)
	{
		case E_WINDOWHANDLE:
			myChan = &channel[0];
			break;
		default:
			myChan = NULL;
			break;
	}
	return myChan;
}
eoReturn eoEEP_F610xx::GetValue(CHANNEL_TYPE type, uint8_t &value)
{
	eoReturn ret = EO_OK;
	eoEEPChannelInfo *chan = (eoEEPChannelInfo *) GetChannel(type);
	if (chan == NULL)
		return NOT_SUPPORTED;

	switch (type)
	{
		case E_WINDOWHANDLE:
			if ((msg.data[0] >> 4) == 0x0F)
				value = WINDOW_DOWN;
			else if ((msg.data[0] >> 4) == 0x0E || (msg.data[0] >> 4) == 0x0C)
				value = WINDOW_MIDDLE;
			else if ((msg.data[0] >> 4) == 0x0D)
				value = WINDOW_UP;
			break;
		default:
			ret = NOT_SUPPORTED;
			break;
	}
	return ret;
}

eoReturn eoEEP_F610xx::SetValue(CHANNEL_TYPE type, uint8_t value)
{
	eoReturn ret = EO_OK;
	eoEEPChannelInfo *chan = (eoEEPChannelInfo *) GetChannel(type);
	if (chan == NULL)
		return NOT_SUPPORTED;

	switch (type)
	{
		case E_WINDOWHANDLE:
			if (value == 0x00)
				msg.data[0] = 0xF0;
			else if (value == 0x01)
				msg.data[0] = 0xE0;
			else if (value == 0x02)
				msg.data[0] = 0xD0;
			break;
		default:
			ret = NOT_SUPPORTED;
			break;
	}
	return ret;

}

