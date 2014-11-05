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

#include "eoProfile.h"
#include "eoManufacturer.h"

const uint8_t eoProfile::maskArray[8] = { 0xFF, 0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01 };

eoProfile::eoProfile(uint16_t size) :
		msg(size)
{
	manufacturer = MULTI_USER_MANUFACTURER;
	rorg = 0;
	type = 0;
	func = 0;
}

bool eoProfile::operator==(const eoProfile &othProfile) const
{
	return (this->rorg == othProfile.rorg && this->type == othProfile.type && this->func == othProfile.func);
}

/**
 * Returns true if rorg,func and type are different.
 * @param othProfile
 * @return true or false
 */
bool eoProfile::operator!=(const eoProfile &othProfile) const
{
	return (this->rorg != othProfile.rorg || this->type != othProfile.type || this->func != othProfile.func);
}

eoProfile::~eoProfile()
{

}
void eoProfile::ClearValues()
{
	msg.Clear();
}

eoReturn eoProfile::Create(eoMessage &m)
{
	return msg.copyTo(m);
}

eoReturn eoProfile::CreateTeachIN(eoMessage &m)
{
	//some checks...
	return NOT_SUPPORTED;
}

eoReturn eoProfile::Parse(const eoMessage &m)
{
	//logic check
	if (rorg == 0 && rorg != m.RORG)
		return NOT_SUPPORTED;

	return m.copyTo(msg);
}

eoReturn eoProfile::GetValue(CHANNEL_TYPE type, float &value)
{
	return NOT_IMPLEMENTED;
}

eoReturn eoProfile::GetValue(CHANNEL_TYPE type, uint8_t &value)
{
	return NOT_IMPLEMENTED;
}

eoReturn eoProfile::GetValue(CHANNEL_TYPE type, float &value, uint8_t subFlag)
{
	return NOT_IMPLEMENTED;
}

eoReturn eoProfile::GetValue(CHANNEL_TYPE type, uint8_t &value, uint8_t subFlag)
{
	return NOT_IMPLEMENTED;
}

eoReturn eoProfile::SetValue(CHANNEL_TYPE type, uint8_t value, uint8_t subFlag)
{
	return NOT_IMPLEMENTED;
}

eoReturn eoProfile::SetValue(CHANNEL_TYPE type, float value, uint8_t subFlag)
{
	return NOT_IMPLEMENTED;
}

eoReturn eoProfile::SetValue(CHANNEL_TYPE type, float value)
{
	return NOT_IMPLEMENTED;
}

eoReturn eoProfile::SetValue(CHANNEL_TYPE type, uint8_t value)
{
	return NOT_IMPLEMENTED;
}

eoReturn eoProfile::SetType(uint8_t type)
{
	return NOT_IMPLEMENTED; //FALLback
}
eoChannelInfo* eoProfile::GetChannel(CHANNEL_TYPE type, uint8_t subType)
{
	return NULL;
}
eoChannelInfo* eoProfile::GetChannel(CHANNEL_TYPE type)
{
	return NULL;
}

eoReturn eoProfile::SetManufacturer (uint16_t manufacturerID = 0x7FF)
{
	if (manufacturerID > 0x7FF)
		return NOT_SUPPORTED;
	manufacturer = manufacturerID;
	return EO_OK;
}

uint16_t eoProfile::BitIdxToByte(const uint16_t &bitIdx)
{
	if ((bitIdx % 8) == 0)
		return bitIdx / 8;
	return (bitIdx + (8 - (bitIdx % 8))) / 8;
}

eoReturn eoProfile::GetRawValue(const eoMessage &msg, uint32_t &value, uint16_t offset, uint8_t size)
{
	if (offset < 0 || size < 0)
		return OUT_OF_RANGE;

	uint16_t idx = (uint16_t)(offset / 8);
	uint16_t idxe = BitIdxToByte(offset + size);
	uint16_t len = idxe - idx;

	uint8_t bits = (offset % 8);
	uint8_t bite = 0;
	if (((offset + size) % 8) != 0)
		bite = (8 - ((offset + size) % 8));

	uint8_t mask = maskArray[bits];

	if (idx + len > msg.GetMaxLength())
		return OUT_OF_RANGE;
	uint8_t * data = msg.data;
	switch (len)
	{
		case 1:
			value = (data[idx] & mask);
			break;
		case 2:
			value = (data[idx] & mask) << 8 | data[idx + 1];
			break;
		case 3:
			value = (data[idx] & mask) << 16 | data[idx + 1] << 8 | data[idx + 2];
			break;
		case 4:
			value = (data[idx] & mask) << 24 | data[idx + 1] << 16 | data[idx + 2] << 8 | data[idx + 3];
			break;
			//case 5: value = ((long)(data[idx] & mask)) << 32 | ((long)(data[idx + 1])) << 24 | (long)data[idx + 2] << 16 | (long)data[idx + 3] << 8 | (long)data[idx + 4]; break;
	}

	value >>= bite;

	return EO_OK;
}

eoReturn eoProfile::SetRawValue(eoMessage &msg, uint32_t &value, uint16_t offset, uint8_t size)
{
	if (offset < 0 || size < 0)
		return OUT_OF_RANGE;
	uint8_t idx = (uint8_t)(offset / 8);
	uint8_t idxe = BitIdxToByte((uint8_t)(offset + size));
	uint8_t len = idxe - idx;

	uint8_t bits = (offset % 8);
	uint8_t bite = 0;
	if (((offset + size) % 8) != 0)
		bite = (8 - ((offset + size) % 8));

	uint8_t mask = maskArray[bits];

	if (idx + len > msg.GetMaxLength())
		return OUT_OF_RANGE;
	uint8_t * data = msg.data;
	//left shift the not used btis are zero
	value <<= bite;
	switch (len)
	{
		case 1:
		{
			//first set to zero
			data[idx] &= ~(mask & (0xFF << bite));
			data[idx] |= (value & mask);
			break;
		}
		case 2:
		{
			data[idx] &= ~mask;
			data[idx] |= (value >> 8) & mask;
			data[idx + 1] &= ~(0xFF << bite);
			data[idx + 1] |= value;
			break;
		}
		case 3:
		{
			data[idx] &= ~mask;
			data[idx] |= (value >> 16) & mask;
			data[idx + 1] = 0;
			data[idx + 1] |= value >> 8;
			data[idx + 2] &= ~(0xFF << bite);
			data[idx + 2] |= value;
			break;
		}
		case 4:
		{
			data[idx] &= ~mask;
			data[idx] |= (value & mask) >> 24;
			data[idx + 1] = 0;
			data[idx + 1] |= value >> 16;
			data[idx + 2] = 0;
			data[idx + 2] |= value >> 8;
			data[idx + 3] &= ~(0xFF << bite);
			data[idx + 3] |= value;
			break;
		}
	}
	return EO_OK;
}

float eoProfile::ScaleFromRAW(uint32_t rawValue, uint32_t rangeMin, uint32_t rangeMax, float scaleMin, float scaleMax)
{
	float q = (scaleMax - scaleMin) / ((float) rangeMax - (float) rangeMin);
	float outValue = q * ((float) rawValue - (float) rangeMin) + scaleMin;
	return outValue;
}

uint32_t eoProfile::ScaleToRAW(float value, uint32_t rangeMin, uint32_t rangeMax, float scaleMin, float scaleMax)
{
	//uint32_t bitSize;
	uint32_t retValue;
	float q = (value - scaleMin) / (scaleMax - scaleMin);
	if (rangeMax > rangeMin)
		retValue = (uint32_t)((rangeMax - rangeMin) * q);
	else
		retValue = (uint32_t)(rangeMin - (rangeMin - rangeMax) * q);
	return retValue;
}

uint8_t eoProfile::GetChannelCount() const
{
	return 0;
}
eoChannelInfo* eoProfile::GetChannel(uint8_t channelNumber)
{
	return NULL;
}
uint8_t eoProfile::Serialize(eoArchive &a)
{
	a & "rorg" & rorg;
	a & "func" & func;
	a & "type" & type;
	a & "manufacturer" & manufacturer;
	return EO_OK;
}
