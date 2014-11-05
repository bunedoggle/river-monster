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

#include "eoA5EEProfile.h"

eoA5EEProfile::eoA5EEProfile(uint16_t size) :
		eoEEProfile(size)
{
	msg.RORG = RORG_4BS;
	msg.SetDataLength(4);
}

eoA5EEProfile::~eoA5EEProfile()
{

}

eoReturn eoA5EEProfile::CreateTeachIN(eoMessage &tel)
{
	if (msg.GetMaxLength() < 4)
		return OUT_OF_RANGE;
	tel.RORG = rorg;
	tel.SetDataLength(4);
	tel.destinationID = BROADCAST_ID;
	tel.sourceID = 0;

	tel.data[0] = (func << 2) | (type >> 5);
	tel.data[1] = ((type & 0x1F) << 3);
	tel.data[1] |= (manufacturer & 0x700) >> 8;
	tel.data[2] = manufacturer & 0xFF;
	tel.data[3] = 0x80; //LEARN_IN
	return EO_OK;
}

eoReturn eoA5EEProfile::GetValue(CHANNEL_TYPE type, float &value)
{
	uint32_t rawValue;
	eoEEPChannelInfo* myChan = (eoEEPChannelInfo*) GetChannel(type);

	if (myChan == NULL)
		return NOT_SUPPORTED;

	//if type is enum or digital flag it can not be scaled as a float in this method
	if (((type >= T_FLAG) && (type < SP_ABS)) || (type >= T_ENUM))
		return NOT_SUPPORTED;

	if (GetRawValue(msg, rawValue, myChan->eepItem->bitoffs, (uint8_t)myChan->eepItem->bitsize) != EO_OK)
		return NOT_SUPPORTED;

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

	value = ScaleFromRAW(rawValue, myChan->eepItem->rangeMin, myChan->eepItem->rangeMax, myChan->min, myChan->max);

	return EO_OK;
}

eoReturn eoA5EEProfile::SetValue(CHANNEL_TYPE type, float value)
{
	uint32_t rawValue;
	eoEEPChannelInfo* myChan = (eoEEPChannelInfo*) GetChannel(type);
	if (myChan == NULL)
		return NOT_SUPPORTED;

	//if type is enum or digital flag it can not be scaled as a float in this method
	if (((type >= T_FLAG) && (type < SP_ABS)) || (type >= T_ENUM))
		return NOT_SUPPORTED;

	if (myChan->min > value || myChan->max < value)
		return OUT_OF_RANGE; // out of range

	rawValue = ScaleToRAW(value, myChan->eepItem->rangeMin, myChan->eepItem->rangeMax, myChan->min, myChan->max);
	SetRawValue(msg, rawValue, myChan->eepItem->bitoffs, (uint8_t)myChan->eepItem->bitsize);

	return EO_OK;
}

eoReturn eoA5EEProfile::Parse(const eoMessage &m)
{
	if (Is4BSData(m))
		return eoProfile::Parse(m);

	return NOT_SUPPORTED;
}

bool eoA5EEProfile::Is4BSData(const eoMessage &m)
{
	return (m.RORG == RORG_4BS && m.GetDataLength() == 4 && ((m.data[3] & 0x08) == 0x08));
}

eoReturn eoA5EEProfile::SetValue(CHANNEL_TYPE type, float value, uint8_t index)
{
	return NOT_SUPPORTED;
}

eoReturn eoA5EEProfile::SetValue(CHANNEL_TYPE type, uint8_t value, uint8_t index)
{
	return NOT_SUPPORTED;
}

eoReturn eoA5EEProfile::GetValue(CHANNEL_TYPE type, float &value, uint8_t index)
{
	return NOT_SUPPORTED;
}

eoReturn eoA5EEProfile::GetValue(CHANNEL_TYPE type, uint8_t &value, uint8_t index)
{
	return NOT_SUPPORTED;
}
