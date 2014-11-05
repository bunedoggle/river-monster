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
#include "eoSerialCommand.h"
#include "eoGateway.h"

eoSerialCommand::eoSerialCommand(eoGateway *gateway)
{
	this->gateway = gateway;
	this->packet = &gateway->packet;
}

eoSerialCommand::~eoSerialCommand()
{

}

eoReturn eoSerialCommand::initPacket(uint8_t type, uint8_t command, uint8_t length)
{
	if (length > packet->getBufferSize())
		return OUT_OF_RANGE;

	packet = &gateway->packet;
	packet->type = type;
	packet->dataLength = length;
	packet->optionalLength = 0;
	packet->data[0] = command;

	return EO_OK;
}

eoReturn eoSerialCommand::Sleep(uint32_t sleepPeriod)
{
	if (sleepPeriod > 0x00FFFFFF)
		return EO_ERROR;
	if (initPacket(PACKET_COMMON_COMMAND, CO_WR_SLEEP, 5) != EO_OK)
		return OUT_OF_RANGE;

	packet->data[1] = (uint8_t)(sleepPeriod >> 24);
	packet->data[2] = (uint8_t)(sleepPeriod >> 16);
	packet->data[3] = (uint8_t)(sleepPeriod >> 8);
	packet->data[4] = (uint8_t)sleepPeriod;

	return gateway->Send(*packet);
}

eoReturn eoSerialCommand::Reset()
{
	if (initPacket(PACKET_COMMON_COMMAND, CO_WR_RESET, 1) != EO_OK)
		return OUT_OF_RANGE;

	return gateway->Send(*packet);
}

eoReturn eoSerialCommand::ReadVersion(CO_RD_VERSION_RESPONSE &response)
{
	if (initPacket(PACKET_COMMON_COMMAND, CO_RD_VERSION, 1) != EO_OK)
		return OUT_OF_RANGE;

	// Send packet
	eoReturn ret;
	if ((ret = gateway->Send(*packet)) != EO_OK)
		return ret;

	//the datalenght is constant, the first bit of the first data byte is the response, no other identifier for this response
	if (gateway->packet.dataLength != 33 && gateway->packet.data[0] != EO_OK && gateway->packet.type != PACKET_RESPONSE)
		return (eoReturn)gateway->packet.data[0];

	// Parse the response
	response.appVersion[0] = gateway->packet.data[1];
	response.appVersion[1] = gateway->packet.data[2];
	response.appVersion[2] = gateway->packet.data[3];
	response.appVersion[3] = gateway->packet.data[4];

	response.apiVersion[0] = gateway->packet.data[5];
	response.apiVersion[1] = gateway->packet.data[6];
	response.apiVersion[2] = gateway->packet.data[7];
	response.apiVersion[3] = gateway->packet.data[8];

	response.chipID = gateway->packet.data[9] << 24 | gateway->packet.data[10] << 16 | gateway->packet.data[11] << 8 | gateway->packet.data[12];

	response.chipVersion = gateway->packet.data[13] << 24 | gateway->packet.data[14] << 16 | gateway->packet.data[15] << 8 | gateway->packet.data[16];

	for (uint8_t i = 0; i < 16; i++)
		response.appDescription[i] = gateway->packet.data[i + 17];
	return EO_OK;
}

eoReturn eoSerialCommand::BIST()
{
	if (initPacket(PACKET_COMMON_COMMAND, CO_WR_BIST, 1) != EO_OK)
		return OUT_OF_RANGE;

	return gateway->Send(*packet);
}

eoReturn eoSerialCommand::WriteIDBase(uint32_t baseID)
{

	if (baseID >= 0xFFFFFF80 || baseID <= 0xFF800000)
		return EO_ERROR;

	if (initPacket(PACKET_COMMON_COMMAND, CO_WR_IDBASE, 5) != EO_OK)
		return OUT_OF_RANGE;

	packet->data[1] = (uint8_t)(baseID >> 24);
	packet->data[2] = (uint8_t)(baseID >> 16);
	packet->data[3] = (uint8_t)(baseID >> 8);
	packet->data[4] = (uint8_t)baseID;

	return gateway->Send(*packet);
}

eoReturn eoSerialCommand::ReadIDBase(CO_RD_IDBASE_RESPONSE &response)
{
	if (initPacket(PACKET_COMMON_COMMAND, CO_RD_IDBASE, 1) != EO_OK)
		return OUT_OF_RANGE;

	// Send packet
	eoReturn ret;
	if ((ret = gateway->Send(*packet)) != EO_OK)
		return ret;

	if (gateway->packet.dataLength != 5 && gateway->packet.optionalLength != 1 && gateway->packet.data[0] != EO_OK && gateway->packet.type != PACKET_RESPONSE)
		return (eoReturn)gateway->packet.data[0];

	// Parse the response
	response.baseID = gateway->packet.data[1] << 24 | gateway->packet.data[2] << 16 | gateway->packet.data[3] << 8 | gateway->packet.data[4];

	response.remainingWrites = gateway->packet.data[5];

	return EO_OK;
}

eoReturn eoSerialCommand::WriteRepeater(bool repEnable, uint8_t repLevel)
{
	if (initPacket(PACKET_COMMON_COMMAND, CO_WR_REPEATER, 3) != EO_OK)
		return OUT_OF_RANGE;

	packet->data[1] = repEnable ? 1 : 0;
	packet->data[2] = repEnable ? repLevel : 0;

	return gateway->Send(*packet);
}

eoReturn eoSerialCommand::ReadRepeater(CO_RD_REPEATER_RESPONSE &response)
{
	if (initPacket(PACKET_COMMON_COMMAND, CO_RD_REPEATER, 1) != EO_OK)
		return OUT_OF_RANGE;

	// Send packet
	eoReturn ret;
	if ((ret = gateway->Send(*packet)) != EO_OK)
		return ret;

	if (gateway->packet.dataLength != 3 && gateway->packet.data[0] != EO_OK && gateway->packet.type != PACKET_RESPONSE)
		return (eoReturn)gateway->packet.data[0];

	// Parse the response
	response.repEnable = gateway->packet.data[1] != 0;
	response.repLevel = gateway->packet.data[2];

	return EO_OK;
}

eoReturn eoSerialCommand::AddFilter(FILTER_TYPE filterType, uint32_t filterValue, FILTER_KIND filterKind)
{

	if (filterKind != 0x80 && filterKind != 0x00)
		return EO_ERROR;

	if (initPacket(PACKET_COMMON_COMMAND, CO_WR_FILTER_ADD, 7) != EO_OK)
		return OUT_OF_RANGE;

	packet->data[1] = (uint8_t)filterType;
	packet->data[2] = (uint8_t)(filterValue >> 24);
	packet->data[3] = (uint8_t)(filterValue >> 16);
	packet->data[4] = (uint8_t)(filterValue >> 8);
	packet->data[5] = (uint8_t)filterValue;
	packet->data[6] = (uint8_t)filterKind;

	// Send packet
	return gateway->Send(*packet);
}

eoReturn eoSerialCommand::DeleteFilter(FILTER_TYPE filterType, uint32_t filterValue)
{
	if (initPacket(PACKET_COMMON_COMMAND, CO_WR_FILTER_DEL, 6) != EO_OK)
		return OUT_OF_RANGE;

	packet->data[1] = (uint8_t)filterType;
	packet->data[2] = (uint8_t)(filterValue >> 24);
	packet->data[3] = (uint8_t)(filterValue >> 16);
	packet->data[4] = (uint8_t)(filterValue >> 8);
	packet->data[5] = (uint8_t)filterValue;

	return gateway->Send(*packet);
}

eoReturn eoSerialCommand::DeleteAllFilter()
{
	if (initPacket(PACKET_COMMON_COMMAND, CO_WR_FILTER_DEL_ALL, 1) != EO_OK)
		return OUT_OF_RANGE;

	return gateway->Send(*packet);
}

eoReturn eoSerialCommand::EnableFilter(bool filterEnabled, FILTER_OPERATOR filterOperator)
{
	if (initPacket(PACKET_COMMON_COMMAND, CO_WR_FILTER_ENABLE, 3) != EO_OK)
		return OUT_OF_RANGE;

	packet->data[1] = filterEnabled ? 1 : 0;
	packet->data[2] = (uint8_t)filterOperator;

	return gateway->Send(*packet);
}

eoReturn eoSerialCommand::ReadFilter(CO_RD_FILTER_RESPONSE *filter, uint8_t *filterCount, uint8_t maxFilterCount)
{
	if (initPacket(PACKET_COMMON_COMMAND, CO_RD_FILTER, 1) != EO_OK)
		return OUT_OF_RANGE;

	// Send packet
	eoReturn ret;
	if ((ret = gateway->Send(*packet)) != EO_OK)
		return ret;

	if ((gateway->packet.dataLength % 5) != 1 && gateway->packet.data[0] != EO_OK && gateway->packet.type != PACKET_RESPONSE)
		return (eoReturn)gateway->packet.data[0];

	// Parse the response
	*filterCount = (uint8_t)(gateway->packet.dataLength - 1) / 5;

	for (uint8_t i = 0; i < *filterCount && i < maxFilterCount; i++)
	{
		filter[i].filterType = (FILTER_TYPE) gateway->packet.data[i * 5 + 1];

		filter[i].filterValue = gateway->packet.data[i * 5 + 2] << 24 | gateway->packet.data[i * 5 + 3] << 16 | gateway->packet.data[i * 5 + 4] << 8 | gateway->packet.data[i * 5 + 5];
	}

	return EO_OK;
}

eoReturn eoSerialCommand::WaitMaturity(bool waitMaturity)
{
	if (initPacket(PACKET_COMMON_COMMAND, CO_WR_WAIT_MATURITY, 2) != EO_OK)
		return OUT_OF_RANGE;

	packet->data[1] = waitMaturity ? 1 : 0;

	return gateway->Send(*packet);
}
eoReturn eoSerialCommand::SmartAckConfirmLearn(uint16_t responseTime, SA_CONFIRM_CODE confirmCode)
{
	if (initPacket(PACKET_RESPONSE, EO_OK, 4) != EO_OK)
		return OUT_OF_RANGE;

	packet->data[0] = EO_OK;
	packet->data[1] = (uint8_t)(responseTime >> 8);
	packet->data[2] = (uint8_t)responseTime;
	packet->data[3] = (uint8_t)confirmCode;

	eoReturn ret;
	if ((ret = gateway->Send(*packet)) != EO_OK)
		return ret;

	return EO_OK;
}

eoReturn eoSerialCommand::SmartAckLearnAck(SA_LEARN_ACK_RESPONSE &response)
{
	if (gateway->packet.type != PACKET_EVENT)
		return NOT_SUPPORTED;

	if (gateway->packet.data[0] != SA_LEARN_ACK)
		return NOT_SUPPORTED;

	if (gateway->packet.dataLength != 4)
		return NOT_SUPPORTED;

	response.responseTime = gateway->packet.data[1] << 8 | gateway->packet.data[2];

	switch (gateway->packet.data[3])
	{
		case SA_LEARN_IN:
		case SA_EEP_NOT_ACCEPTED:
		case SA_PM_FULL:
		case SA_CONTROLLER_FULL:
		case SA_RSSI_NOT_GOOD:
		case SA_LEARN_OUT:
			response.confirmCode = (SA_CONFIRM_CODE) gateway->packet.data[3];
			break;
		default:
			return NOT_SUPPORTED;
			break;
	}
	return EO_OK;
}

eoReturn eoSerialCommand::Ready(CO_READY_RESPONSE &response)
{
	if (gateway->packet.type != PACKET_EVENT)
		return NOT_SUPPORTED;

	if (gateway->packet.data[0] != SA_READY)
		return NOT_SUPPORTED;

	if (gateway->packet.dataLength != 2)
		return NOT_SUPPORTED;

	switch (gateway->packet.data[1])
	{
		case EC_VOLTAGE_DROP:
		case EC_RESET_PIN:
		case EC_WATCHDOG_TIMER:
		case EC_FLYWHEEL_TIMER:
		case EC_PARITY_ERROR:
		case EC_PARITY_MEM_ERROR:
		case EC_MEM_ERRPR:
		case EC_WAKE_PIN_0:
		case EC_WAKE_PIN_1:
		case EC_UNKNOWN:
			response.resetCause = (EC_RESET_CAUSE) gateway->packet.data[1];
			break;
		default:
			return NOT_SUPPORTED;
			break;
	}

	return EO_OK;
}
eoReturn eoSerialCommand::SmartAckWriteLearnMode(bool enable, SA_EXTENDED_LEARNMODE extended, uint32_t timeout)
{
	if (initPacket(PACKET_SMART_ACK_COMMAND, SA_WR_LEARNMODE, 7) != EO_OK)
		return OUT_OF_RANGE;

	packet->data[1] = enable ? 1 : 0;
	packet->data[2] = (uint8_t)extended;
	packet->data[3] = (uint8_t)(timeout >> 24);
	packet->data[4] = (uint8_t)(timeout >> 16);
	packet->data[5] = (uint8_t)(timeout >> 8);
	packet->data[6] = (uint8_t) timeout;

	return gateway->Send(*packet);
}

eoReturn eoSerialCommand::SmartAckReadLearnMode(SA_RD_LEARNMODE_RESPONSE &response)
{
	if (initPacket(PACKET_SMART_ACK_COMMAND, SA_RD_LEARNMODE, 1) != EO_OK)
		return OUT_OF_RANGE;

	eoReturn ret;
	if ((ret = gateway->Send(*packet)) != EO_OK)
		return ret;

	if (gateway->packet.dataLength != 3 && gateway->packet.data[0] != EO_OK && gateway->packet.type != PACKET_RESPONSE)
		return (eoReturn)gateway->packet.data[0];

	response.enabled = gateway->packet.data[1]!=0;
	switch (gateway->packet.data[2])
	{
		case 0x00:
			response.extended = SA_EL_SIMPLE;
			break;
		case 0x01:
			response.extended = SA_EL_ADVANCE;
			break;
		case 0x02:
			response.extended = SA_EL_ADVANCE_REP;
			break;
	}

	return EO_OK;
}

eoReturn eoSerialCommand::SmartAckLearnConfirm(uint16_t responseTime, SMARTACK_CONFIRM_CODE confirmCode, uint32_t postmasterID, uint32_t clientID)
{
	if (initPacket(PACKET_SMART_ACK_COMMAND, SA_WR_LEARNCONFIRM, 12) != EO_OK)
		return OUT_OF_RANGE;

	packet->data[1] = responseTime >> 8;
	packet->data[2] = responseTime & 0xFF;
	packet->data[3] = (uint8_t)confirmCode;
	packet->data[4] = (uint8_t)(postmasterID >> 24);
	packet->data[5] = (uint8_t)(postmasterID >> 16);
	packet->data[6] = (uint8_t)(postmasterID >> 8);
	packet->data[7] = (uint8_t)postmasterID;
	packet->data[8] = (uint8_t)(clientID >> 24);
	packet->data[9] = (uint8_t)(clientID >> 16);
	packet->data[10] = (uint8_t)(clientID >> 8);
	packet->data[11] = (uint8_t)clientID;

	packet->type = PACKET_SMART_ACK_COMMAND;
	packet->dataLength = 12;

	return (gateway->Send(*packet));
}

eoReturn eoSerialCommand::SmartAckSendLearnRequest(uint16_t manufacturerID, uint32_t EEP)
{
	if (initPacket(PACKET_SMART_ACK_COMMAND, SA_WR_CLIENTLEARNRQ, 6) != EO_OK)
		return OUT_OF_RANGE;

	packet->data[1] = 0xF8 | ((manufacturerID >> 8) & 0x07);
	packet->data[2] = manufacturerID & 0xFF;
	packet->data[3] = (uint8_t)(EEP >> 16);
	packet->data[4] = (uint8_t)(EEP >> 8);
	packet->data[5] = (uint8_t)EEP;


	return 	gateway->Send(*packet);
}

eoReturn eoSerialCommand::SmartAckReset(uint32_t clientID)
{
	if (initPacket(PACKET_SMART_ACK_COMMAND, SA_WR_RESET, 5) != EO_OK)
		return OUT_OF_RANGE;

	packet->data[1] = (uint8_t)(clientID >> 24);
	packet->data[2] = (uint8_t)(clientID >> 16);
	packet->data[3] = (uint8_t)(clientID >> 8);
	packet->data[4] = (uint8_t) clientID;


	return 	gateway->Send(*packet);
}

eoReturn eoSerialCommand::SmartAckLearnedClients(SA_RD_LEARNEDCLIENTS_RESPONSE *clients, uint8_t *learnedCount, uint8_t maxLearnedCount)
{
	if (initPacket(PACKET_SMART_ACK_COMMAND, SA_RD_LEARNEDCLIENTS, 1) != EO_OK)
		return OUT_OF_RANGE;

	eoReturn ret;
	if ((ret = gateway->Send(*packet)) != EO_OK)
		return ret;

	if ((gateway->packet.dataLength % 9) != 1 && gateway->packet.data[0] != EO_OK && gateway->packet.type != PACKET_RESPONSE)
		return (eoReturn)gateway->packet.data[0];

	*learnedCount = (uint8_t)(gateway->packet.dataLength - 1) / 9;
	for (uint8_t i = 0; i < *learnedCount && i < maxLearnedCount; i++)
	{
		clients[i].clientID = gateway->packet.data[i * 9 + 1] << 24 | gateway->packet.data[i * 9 + 2] << 16 | gateway->packet.data[i * 9 + 3] << 8 | gateway->packet.data[i * 9 + 4];

		clients[i].postmasterID = gateway->packet.data[i * 9 + 5] << 24 | gateway->packet.data[i * 9 + 6] << 16 | gateway->packet.data[i * 9 + 7] << 8 | gateway->packet.data[i * 9 + 8];

		clients[i].mailboxIndex = gateway->packet.data[i * 9 + 9];
	}

	return EO_OK;
}

eoReturn eoSerialCommand::SmartAckSetReclaimTries(uint8_t reclaimCount)
{
	if (initPacket(PACKET_SMART_ACK_COMMAND, SA_WR_RECLAIMS, 2) != EO_OK)
		return OUT_OF_RANGE;

	packet->data[1] = reclaimCount;


	return gateway->Send(*packet);
}

eoReturn eoSerialCommand::SmartAckSetPostmaster(uint8_t mailboxCount)
{
	if (initPacket(PACKET_SMART_ACK_COMMAND, SA_WR_POSTMASTER, 2) != EO_OK)
		return OUT_OF_RANGE;

	packet->data[1] = mailboxCount;
	return 	gateway->Send(*packet);
}

eoReturn eoSerialCommand::EventSmartAckConfirmLearn (SA_CONFIRM_LEARN_REQUEST &request)
{

	if (gateway->packet.dataLength != 6 && gateway->packet.data[0] != EO_OK && gateway->packet.type != PACKET_EVENT)
		return NOT_SUPPORTED;

	request.priPostmaster = gateway->packet.data[1];
	request.manufacturerID = gateway->packet.data[2] << 8 | gateway->packet.data[3];

	request.eep[0] = gateway->packet.data[4];
	request.eep[1] = gateway->packet.data[5];
	request.eep[2] = gateway->packet.data[6];
	request.rssi = gateway->packet.data[7];

	request.postmasterID = gateway->packet.data[8] << 24 | gateway->packet.data[9] << 16 | gateway->packet.data[10] << 8 | gateway->packet.data[11];

	request.smartAckID = gateway->packet.data[12] << 24 | gateway->packet.data[13] << 16 | gateway->packet.data[14] << 8 | gateway->packet.data[15];

	request.hopCount = gateway->packet.data[16];

	return EO_OK;
}
