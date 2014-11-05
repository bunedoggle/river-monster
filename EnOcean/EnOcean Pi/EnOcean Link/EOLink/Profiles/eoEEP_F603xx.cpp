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

#include "eoEEP_F603xx.h"

#include "eoChannelEnums.h"
#include <string.h>
#include <typeinfo>
const uint8_t numOfChan = 6;
const uint8_t numOfProfiles = 0x02;

//Channels have to be in the right order for the getChannel function

eoEEP_F603xx::eoEEP_F603xx()
{
	channel = new eoEEPChannelInfo[numOfChan];
	channelCount = 0;
	ClearValues();

	this->rorg = RORG_RPS;
	this->func = 0x03;
}

eoEEP_F603xx::~eoEEP_F603xx()
{
	if(channel!=NULL)
		delete[] channel;
	channel=NULL;
}


void eoEEP_F603xx::ClearValues()
{
	eoF6EEProfile::ClearValues();
	rockerA = STATE_NP;
	rockerB = STATE_NP;
	rockerC = STATE_NP;
	rockerD = STATE_NP;
}

eoReturn eoEEP_F603xx::SetType(uint8_t type)
{
	if (type > numOfProfiles)
		return NOT_SUPPORTED;
	channel[0].type = E_ROCKER_A;
	channel[0].min = 0;
	channel[0].max = 3;

	channel[1].type = E_ROCKER_B;
	channel[1].min = 0;
	channel[1].max = 3;

	channel[2].type = E_ROCKER_C;
	channel[2].min = 0;
	channel[2].max = 3;

	channel[3].type = E_ROCKER_D;
	channel[3].min = 0;
	channel[3].max = 3;

	channel[4].type = E_ENERGYBOW;
	channel[4].min = 0;
	channel[4].max = 1;

	channel[5].type = E_MULTIPRESS;
	channel[5].min = 0;
	channel[5].max = 1;

	channelCount = 6;

	if (type == 0 || channelCount == 0)
		return NOT_SUPPORTED;

	this->type = type;
	return EO_OK;
}

eoChannelInfo* eoEEP_F603xx::GetChannel(CHANNEL_TYPE type)
{
	eoEEPChannelInfo* myChan = NULL;
	switch (type)
	{
		case E_ROCKER_A:
			myChan = &channel[0];
			break;
		case E_ROCKER_B:
			myChan = &channel[1];
			break;
		case E_ROCKER_C:
			myChan = &channel[2];
			break;
		case E_ROCKER_D:
			myChan = &channel[3];
			break;
		case E_ENERGYBOW:
			myChan = &channel[4];
			break;
		case E_MULTIPRESS:
			myChan = &channel[5];
			break;
		default:
			myChan = NULL;
			break;
	}
	return myChan;
}
eoReturn eoEEP_F603xx::GetValue(CHANNEL_TYPE type, uint8_t &value)
{
	eoReturn ret = EO_OK;
	eoEEPChannelInfo *chan = (eoEEPChannelInfo *) GetChannel(type);
	if (chan == NULL)
		return NOT_SUPPORTED;

	switch (type)
	{
		case E_ROCKER_A:
			if (RockerHelper() == EO_OK)
				value = rockerA;
			else
				ret = NOT_SUPPORTED;
			break;
		case E_ROCKER_B:
			if (RockerHelper() == EO_OK)
				value = rockerB;
			else
				ret = NOT_SUPPORTED;
			break;
		case E_ROCKER_C:
			if (RockerHelper() == EO_OK)
				value = rockerC;
			else
				ret = NOT_SUPPORTED;
			break;
		case E_ROCKER_D:
			if (RockerHelper() == EO_OK)
				value = rockerD;
			else
				ret = NOT_SUPPORTED;
			break;
		case E_ENERGYBOW:
			value = (msg.data[0] >> 4) & 1;
			break;
		case E_MULTIPRESS:
			if ((msg.status >> 4) == 0x02 && (msg.data[0] >> 5) == 3)
				value = true;
			else
				value = false;
			break;
		default:
			ret = NOT_SUPPORTED;
			break;
	}
	return ret;
}

eoReturn eoEEP_F603xx::SetValue(CHANNEL_TYPE type, uint8_t value)
{
	if (value < 0 || value > 2)
		return OUT_OF_RANGE;

	eoReturn ret = EO_OK;
	eoEEPChannelInfo *chan = (eoEEPChannelInfo *) GetChannel(type);
	if (chan == NULL)
		return NOT_SUPPORTED;
	uint8_t bitoffs = 0;
	uint8_t bitsize = 0;
	uint32_t rawvalue = 0;
	msg.status |= 0x10;
	switch (type)
	{
		case E_ROCKER_A:
			rockerA = value;

			if (value == STATE_I || value == STATE_O)
			{
				bitsize = 3;
				bitoffs = 0;
				if (rockerB != STATE_NP || rockerC != STATE_NP || rockerD != STATE_NP) //second button pressed
				{
					rawvalue = 1;
					SetRawValue(msg, rawvalue, (uint16_t) 7, (uint8_t) 1);
					rawvalue = rockerB + 2;
					SetRawValue(msg, rawvalue, (uint16_t) 4, (uint8_t) 3);
				}

				rawvalue = value;
			}

			else if (value == STATE_IO)
			{
				rawvalue = 1;
				SetRawValue(msg, rawvalue, (uint16_t) 7, (uint8_t) 1);
				rawvalue = 1;
				SetRawValue(msg, rawvalue, (uint16_t) 0, (uint8_t) 3);
				bitoffs = 4;
				bitsize = 3;
				rawvalue = 0;
			}
			break;
		case E_ROCKER_B:
			rockerB = value;
			if (value == STATE_I || value == STATE_O)
			{
				bitsize = 3;
				if (rockerA != STATE_NP || rockerC != STATE_NP || rockerD != STATE_NP)
				{
					bitoffs = 4;
					rawvalue = 1;
					SetRawValue(msg, rawvalue, (uint16_t) 7, (uint8_t) 1);
				}
				else
				{
					bitoffs = 0;
				}
				rawvalue = value + 2; //ButtonB
			}

			else if (value == STATE_IO)
			{
				rawvalue = 1;
				SetRawValue(msg, rawvalue, (uint16_t) 7, (uint8_t) 1);
				rawvalue = 3;
				SetRawValue(msg, rawvalue, (uint16_t) 0, (uint8_t) 3);
				bitoffs = 4;
				bitsize = 3;
				rawvalue = 2;
			}
			break;
		case E_ROCKER_C:
			rockerC = value;
			if (value == STATE_I || value == STATE_O)
			{
				bitsize = 3;
				if (rockerA != STATE_NP || rockerB != STATE_NP || rockerD != STATE_NP)
				{
					bitoffs = 4;
					rawvalue = 1;
					SetRawValue(msg, rawvalue, (uint16_t) 7, (uint8_t) 1);
				}
				else
				{
					bitoffs = 0;
				}
				rawvalue = value + 4; //ButtonC
			}

			else if (value == STATE_IO)
			{
				rawvalue = 1;
				SetRawValue(msg, rawvalue, (uint16_t) 7, (uint8_t) 1);
				rawvalue = 5;
				SetRawValue(msg, rawvalue, (uint16_t) 0, (uint8_t) 3);
				bitoffs = 4;
				bitsize = 3;
				rawvalue = 4;
			}
			break;
		case E_ROCKER_D:
			rockerD = value;
			if (value == STATE_I || value == STATE_O)
			{
				bitsize = 3;
				if (rockerA != STATE_NP || rockerB != STATE_NP || rockerC != STATE_NP)
				{
					bitoffs = 4;
					rawvalue = 1;
					SetRawValue(msg, rawvalue, (uint16_t) 7, (uint8_t) 1);
				}
				else
				{
					bitoffs = 0;
				}
				rawvalue = value + 6; //ButtonD
			}

			else if (value == STATE_IO)
			{
				rawvalue = 1;
				SetRawValue(msg, rawvalue, (uint16_t) 7, (uint8_t) 1);
				rawvalue = 7;
				SetRawValue(msg, rawvalue, (uint16_t) 0, (uint8_t) 3);
				bitoffs = 4;
				bitsize = 3;
				rawvalue = 6;
			}
			break;
		case E_ENERGYBOW:
			bitoffs = 3;
			bitsize = 1;
			rawvalue = value;
			break;
		case E_MULTIPRESS:
			//msg.status&=0x0F;
			if (value)
			{
				rawvalue = 0x3;
				bitoffs = 0;
				bitsize = 3;
			}
			break;
		default:
			ret = NOT_SUPPORTED;
			break;
	}
	//rawvalue=value;
	ret = SetRawValue(msg, rawvalue, (uint16_t)bitoffs, bitsize);
	return ret;
}

eoReturn eoEEP_F603xx::RockerHelper()
{
	eoReturn ret = EO_OK;
	rockerA = STATE_NP;
	rockerB = STATE_NP;
	rockerC = STATE_NP;
	rockerD = STATE_NP;
	switch (msg.data[0])
	{
		case 0x00:
		case 0x10:
			if ((msg.status & 0xF0) == 0x30)
				rockerA = STATE_I;
			break;
		case 0x05:
		case 0x15:
			rockerA = STATE_I;
			rockerB = STATE_I;
			break;
		case 0x07:
		case 0x17:
			rockerA = STATE_I;
			rockerB = STATE_O;
			break;
		case 0x09:
		case 0x19:
			rockerA = STATE_I;
			rockerC = STATE_I;
			break;
		case 0x0B:
		case 0x1B:
			rockerA = STATE_I;
			rockerC = STATE_O;
			break;
		case 0x0D:
		case 0x1D:
			rockerA = STATE_I;
			rockerD = STATE_I;
			break;
		case 0x0F:
		case 0x1F:
			rockerA = STATE_I;
			rockerD = STATE_O;
			break;
			//rockerA=STATE_O
		case 0x20:
		case 0x30:
			rockerA = STATE_O;
			break;
		case 0x21:
		case 0x31:
			rockerA = STATE_IO;
			break;
		case 0x25:
		case 0x35:
			rockerA = STATE_O;
			rockerB = STATE_I;
			break;
		case 0x27:
		case 0x37:
			rockerA = STATE_O;
			rockerB = STATE_O;
			break;
		case 0x29:
		case 0x39:
			rockerA = STATE_O;
			rockerC = STATE_I;
			break;
		case 0x2B:
		case 0x3B:
			rockerA = STATE_O;
			rockerC = STATE_O;
			break;
		case 0x2D:
		case 0x3D:
			rockerA = STATE_O;
			rockerD = STATE_I;
			break;
		case 0x2F:
		case 0x3F:
			rockerA = STATE_O;
			rockerD = STATE_O;
			break;
			//rockerB=STATE_I
		case 0x40:
		case 0x50:
			rockerB = STATE_I;
			break;
		case 0x41:
		case 0x51:
			rockerB = STATE_I;
			rockerA = STATE_I;
			break;
		case 0x43:
		case 0x53:
			rockerB = STATE_I;
			rockerA = STATE_O;
			break;
		case 0x49:
		case 0x59:
			rockerB = STATE_I;
			rockerC = STATE_I;
			break;
		case 0x4B:
		case 0x5B:
			rockerB = STATE_I;
			rockerC = STATE_O;
			break;
		case 0x4D:
		case 0x5D:
			rockerB = STATE_I;
			rockerD = STATE_I;
			break;
		case 0x4F:
		case 0x5F:
			rockerB = STATE_I;
			rockerD = STATE_O;
			break;
			//rockerB=STATE_O
		case 0x60:
		case 0x70:
			rockerB = STATE_O;
			break;
		case 0x61:
		case 0x71:
			rockerB = STATE_O;
			rockerA = STATE_I;
			break;
		case 0x63:
		case 0x73:
			rockerB = STATE_O;
			rockerA = STATE_O;
			break;
		case 0x65:
		case 0x75:
			rockerB = STATE_IO;
			break;
		case 0x69:
		case 0x79:
			rockerB = STATE_O;
			rockerC = STATE_I;
			break;
		case 0x6B:
		case 0x7B:
			rockerB = STATE_O;
			rockerC = STATE_O;
			break;
		case 0x6D:
		case 0x7D:
			rockerB = STATE_O;
			rockerD = STATE_I;
			break;
		case 0x6F:
		case 0x7F:
			rockerB = STATE_O;
			rockerD = STATE_O;
			break;
			//rockerC=STATE_I
		case 0x80:
		case 0x90:
			rockerC = STATE_I;
			break;
		case 0x81:
		case 0x91:
			rockerC = STATE_I;
			rockerA = STATE_I;
			break;
		case 0x83:
		case 0x93:
			rockerC = STATE_I;
			rockerA = STATE_O;
			break;
		case 0x85:
		case 0x95:
			rockerC = STATE_I;
			rockerB = STATE_I;
			break;
		case 0x87:
		case 0x97:
			rockerC = STATE_I;
			rockerB = STATE_O;
			break;
		case 0x8D:
		case 0x9D:
			rockerC = STATE_I;
			rockerD = STATE_I;
			break;
		case 0x8F:
		case 0x9F:
			rockerC = STATE_I;
			rockerD = STATE_O;
			break;
			//rockerC=STATE_O
		case 0xA0:
		case 0xB0:
			rockerC = STATE_O;
			break;
		case 0xA1:
		case 0xB1:
			rockerC = STATE_O;
			rockerA = STATE_I;
			break;
		case 0xA3:
		case 0xB3:
			rockerC = STATE_O;
			rockerA = STATE_O;
			break;
		case 0xA5:
		case 0xB5:
			rockerC = STATE_O;
			rockerB = STATE_I;
			break;
		case 0xA7:
		case 0xB7:
			rockerC = STATE_O;
			rockerB = STATE_O;
			break;
		case 0xA9:
		case 0xB9:
			rockerC = STATE_IO;
			break;
		case 0xAD:
		case 0xBD:
			rockerC = STATE_O;
			rockerD = STATE_I;
			break;
		case 0xAF:
		case 0xBF:
			rockerC = STATE_O;
			rockerD = STATE_O;
			break;
			//rockerD=STATE_I
		case 0xC0:
		case 0xD0:
			rockerD = STATE_I;
			break;
		case 0xC1:
		case 0xD1:
			rockerD = STATE_I;
			rockerA = STATE_I;
			break;
		case 0xC3:
		case 0xD3:
			rockerD = STATE_I;
			rockerA = STATE_O;
			break;
		case 0xC5:
		case 0xD5:
			rockerD = STATE_I;
			rockerB = STATE_I;
			break;
		case 0xC7:
		case 0xD7:
			rockerD = STATE_I;
			rockerB = STATE_O;
			break;
		case 0xC9:
		case 0xD9:
			rockerD = STATE_I;
			rockerC = STATE_I;
			break;
		case 0xCB:
		case 0xDB:
			rockerD = STATE_I;
			rockerC = STATE_O;
			break;
			//rockerD=STATE_O
		case 0xE0:
		case 0xF0:
			rockerD = STATE_O;
			break;
		case 0xE1:
		case 0xF1:
			rockerD = STATE_O;
			rockerA = STATE_I;
			break;
		case 0xE3:
		case 0xF3:
			rockerD = STATE_O;
			rockerA = STATE_O;
			break;
		case 0xE5:
		case 0xF5:
			rockerD = STATE_O;
			rockerB = STATE_I;
			break;
		case 0xE7:
		case 0xF7:
			rockerD = STATE_O;
			rockerB = STATE_O;
			break;
		case 0xE9:
		case 0xF9:
			rockerD = STATE_O;
			rockerC = STATE_I;
			break;
		case 0xEB:
		case 0xFB:
			rockerD = STATE_O;
			rockerC = STATE_O;
			break;
		case 0xED:
		case 0xFD:
			rockerD = STATE_IO;
			break;
		default:
			ret = NOT_SUPPORTED;
			break;
	}
	return ret;
}
