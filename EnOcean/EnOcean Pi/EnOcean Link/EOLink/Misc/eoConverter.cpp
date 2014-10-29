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
#include "eoConverter.h"
#include <string.h>
#define MULTIPLIER 37

const char numToHex[0x10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

const char* eoConverter::NumToHex(uint8_t num)
{
	return &numToHex[num & 0xF];
}

eoReturn eoConverter::packetToRadio(const eoPacket &packet, eoTelegram &tel)
{
	if (packet.type == PACKET_RADIO_ADVANCED)
		return advancedPacketToRadio(packet, tel);

	if (packet.type != PACKET_RADIO && packet.type != PACKET_RADIO_SUB_TEL)
		return WRONG_PARAM;

	if (packet.dataLength > tel.GetMaxLength() + 6)
		return WRONG_PARAM;

	// Copy RORG
	tel.RORG = packet.data[0];

	// Copy DATA
	tel.SetDataLength(packet.dataLength - 6);
	memcpy(tel.data, &packet.data[1], tel.GetDataLength());

	// Copy SourceID
	uint16_t i = packet.dataLength - 5;
	tel.sourceID = (packet.data[i + 0] << 24) + (packet.data[i + 1] << 16) + (packet.data[i + 2] << 8) + (packet.data[i + 3]);
	tel.status = (packet.data[i + 4]);
	// Copy SubtelegramCount
	i = packet.dataLength;
	if (packet.optionalLength >= 1)
	{
		tel.subtelCount = packet.data[i];
		i += 1;
	}

	// Copy DestinationID
	if (packet.optionalLength >= 5)
	{
		tel.destinationID = (packet.data[i + 0] << 24) + (packet.data[i + 1] << 16) + (packet.data[i + 2] << 8) + (packet.data[i + 3]);
		i += 4;
	}

	// Copy dBm
	if (packet.optionalLength >= 6)
	{
		tel.dBm = -packet.data[i];
	}

	return EO_OK;
}

eoReturn eoConverter::advancedPacketToRadio(const eoPacket &packet, eoTelegram &tel)
{
	const uint8_t AdvancedRORG [] =
	{
			RORG_RPS,
			RORG_1BS,
			RORG_4BS,
			RORG_SIGNAL,
			RORG_VLD,
			RORG_UTE,
			RORG_MSC,
			RORG_SEC,
			RORG_SEC_ENCAPS,
			RORG_SEC_TI,
			GP_SD,
			0xFF,
			0xFF,
			0xFF,
			0xFF,
			0xFF
	};

	const uint8_t AdvancedExtRORG [] =
	{
			RORG_SYS_EX,
			RORG_SM_LRN_REQ,
			RORG_SM_LRN_ANS,
			RORG_CDM,
			RORG_SECD,
			GP_TI,
			GP_TR,
			GP_CD
	};

	const uint8_t SourceIDLength [] =
	{
			3,
			4,
			4,
			0,
			0,
			0,
			0
	};

	const uint8_t DestinationIDLength [] =
	{
			0,
			0,
			4,
			6,
			0,
			0,
			0
	};

	uint8_t * data = &packet.data[0];
	uint8_t addrControl = (*data & 0xE0) >> 5;
	uint8_t sourceLength = SourceIDLength[addrControl];
	uint8_t destLength = DestinationIDLength[addrControl];
	uint8_t optLength = 0;
	bool extHeader = (*data & 0x10) != 0;
	bool extTelType = (*data & 0x0F) == 0x0F;

	if (extTelType == false)
		tel.RORG = AdvancedRORG[*(data++) & 0x0F];
	else
	{
		if (extHeader)
		{
		    if ((*(data + 2)) > sizeof(AdvancedExtRORG))
		        tel.RORG = *(data + 2);
		    else
		        tel.RORG = AdvancedExtRORG[*(data+2) & 0x0F];
		}
		else
		{
		    if ((*(data + 2)) > sizeof(AdvancedExtRORG))
		        tel.RORG = *(data + 1);
		    else
		        tel.RORG = AdvancedExtRORG[*(data+1) & 0x0F];
		}
		data++;
	}

	if (extHeader)
	{
		tel.status = (*(data) & 0xF0) >> 4;
		optLength = *data++ & 0x0F;
	}

	if (extTelType)
		data++;

	switch (sourceLength)
	{
		case 0x03:
			tel.sourceID  = *(data++) << 16;
			tel.sourceID |= *(data++) << 8;
			tel.sourceID |= *(data++);
			break;
		case 0x04:
			tel.sourceID = *(data++) << 24;
			tel.sourceID |= *(data++) << 16;
			tel.sourceID |= *(data++) << 8;
			tel.sourceID |= *(data++);
			break;
		case 0x06:
			data++;
			data++;
			tel.sourceID = *(data++) << 24;
			tel.sourceID |= *(data++) << 16;
			tel.sourceID |= *(data++) << 8;
			tel.sourceID |= *(data++);
			break;
		default:
			return NOT_SUPPORTED;
	}

	tel.destinationID = 0xFFFFFFFF;
	if (destLength)
	{
		tel.destinationID = *(data++) << 24;
		tel.destinationID |= *(data++) << 16;
		tel.destinationID |= *(data++) << 8;
		tel.destinationID |= *(data++);
	}

	uint8_t dataLength = packet.dataLength - optLength - sourceLength - destLength - 2;

	if (extHeader)
		dataLength--;
	if (extTelType)
		dataLength--;

	tel.dataLength = dataLength;
	memcpy(tel.data, data, dataLength);

	if (packet.optionalLength >= 2)
	{
		tel.dBm = packet.data[packet.dataLength + 1];
		tel.subtelCount = packet.data[packet.dataLength + 2];
	}

	return EO_OK;
}

eoReturn eoConverter::radioToPacket(const eoMessage &msg, eoPacket &packet)
{
	//checks Buffer Size before returning dataLength
	if (packet.getBufferSize() < (msg.GetDataLength() + 6 + 5))
		return OUT_OF_RANGE;
	if (msg.GetDataLength() > 14)
		return WRONG_PARAM;
	packet.type = PACKET_RADIO;

	packet.dataLength = msg.GetDataLength()+ 6;

	// Copy RORG
	packet.data[0] = msg.RORG;

	// Copy DATA
	memcpy(&packet.data[1], msg.data, msg.GetDataLength());

	// Copy SourceID
	uint16_t i = msg.GetDataLength() + 1;
	packet.data[i + 0] = (uint8_t)(msg.sourceID >> 24);
	packet.data[i + 1] = (uint8_t)(msg.sourceID >> 16);
	packet.data[i + 2] = (uint8_t)(msg.sourceID >> 8);
	packet.data[i + 3] = (uint8_t)(msg.sourceID);

	packet.data[i + 4] = msg.status;

	packet.optionalLength = 6;
	i = packet.dataLength;
	packet.data[i + 0] = 3; // subtelegram count
	packet.data[i + 1] = (uint8_t)(msg.destinationID >> 24);
	packet.data[i + 2] =(uint8_t)( msg.destinationID >> 16);
	packet.data[i + 3] = (uint8_t)(msg.destinationID >> 8);
	packet.data[i + 4] = (uint8_t)msg.destinationID;
	packet.data[i + 5] = 0xFF;
	return EO_OK;
}

eoReturn eoConverter::radioToPacket(const eoTelegram &tel, eoPacket &packet)
{
	//checks Buffer Size before returning dataLength
	if (packet.getBufferSize() < (tel.GetDataLength() + 6 + 5))
		return OUT_OF_RANGE;
	packet.type = PACKET_RADIO;

	packet.dataLength = tel.GetDataLength() + 6;

	// Copy RORG
	packet.data[0] = tel.RORG;

	// Copy DATA
	memcpy(&packet.data[1], tel.data, tel.GetDataLength());

	// Copy SourceID
	uint16_t i = tel.GetDataLength() + 1;
	packet.data[i + 0] = (uint8_t)(tel.sourceID >> 24);
	packet.data[i + 1] = (uint8_t)(tel.sourceID >> 16);
	packet.data[i + 2] = (uint8_t)(tel.sourceID >> 8);
	packet.data[i + 3] = (uint8_t)tel.sourceID;

	packet.data[i + 4] = tel.status;

	packet.optionalLength = 5;
	i = packet.dataLength;
	packet.data[i++] = 3; // subtelegram count

	packet.data[i + 0] = (uint8_t)(tel.destinationID >> 24);
	packet.data[i + 1] = (uint8_t)(tel.destinationID >> 16);
	packet.data[i + 2] = (uint8_t)(tel.destinationID >> 8);
	packet.data[i + 3] = (uint8_t)tel.destinationID;
	return EO_OK;
}
uint8_t eoConverter::TigrisToRPS(eoTelegram &inTel, eoTelegram &outTel)
{
	const uint8_t secToRps[16] =	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 0x70, 0x37, 0x10, 0x15, 0x35, 0x50, 0x70, 0x10, 0x30, 0x00 };
	const uint8_t secToStat[16] =	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x20, 0x30, 0x20, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x20 };

	if (inTel.RORG == RADIO_CHOICE_NON_SEC && inTel.GetDataLength() == 1)
	{
		outTel.RORG = RADIO_CHOICE_RPS;
		outTel.SetDataLength(1);
		outTel.data[0] = secToRps[inTel.data[0] & 0xF];
		outTel.status = secToStat[inTel.data[0] & 0xF];
		return EO_OK;
	}
	return NOT_SUPPORTED;

}

uint32_t eoConverter::Hash(char const * str)
{
	unsigned int h;
	unsigned char *p;

	h = 0;
	for (p = (unsigned char*) str; *p != '\0'; p++)
		h = MULTIPLIER * h + *p;
	return h; // or, h % ARRAY_SIZE;
}

eoReturn eoConverter::celsiusToFahrenheit(float &value)
{
	value = (value - 32) * (5 / 9);
	return EO_OK;
}

eoReturn eoConverter::fahrenheitToCelsius(float &value)
{
	value = value * (9 / 5) + 32;
	return EO_OK;
}
