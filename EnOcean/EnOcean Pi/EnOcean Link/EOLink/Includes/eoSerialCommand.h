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

/**
 * \file eoSerialCommand.h
 * \brief eoSerialCommand
 * \author EnOcean GmBH
 */

#ifndef EOSERIALCOMMAND_H_
#define EOSERIALCOMMAND_H_
#include "eoHalTypes.h"
#include "eoApiDef.h"
class eoGateway;
class eoPacket;

/**
 * \typedef COMMON_COMMAND_TYPE
 * \brief The most common commands for ESP3
 */
typedef enum
{
	//! Order to enter in energy saving mode
	CO_WR_SLEEP = 1,
	//! Order to reset the device
	CO_WR_RESET = 2,
	//! Read the device (SW) version / (HW) version, chip ID etc.
	CO_RD_VERSION = 3,
	//! Read system log from device databank
	CO_RD_SYS_LOG = 4,
	//! Reset System log from device databank
	CO_WR_SYS_LOG = 5,
	//! Perform Flash BIST operation
	CO_WR_BIST = 6,
	//! Write ID range base number
	CO_WR_IDBASE = 7,
	//! Read ID range base number
	CO_RD_IDBASE = 8,
	//! Write Repeater Level off,1,2
	CO_WR_REPEATER = 9,
	//! Read Repeater Level off,1,2
	CO_RD_REPEATER = 10,
	//! Add filter to filter list
	CO_WR_FILTER_ADD = 11,
	//! Delete filter from filter list
	CO_WR_FILTER_DEL = 12,
	//! Delete filters
	CO_WR_FILTER_DEL_ALL = 13,
	//! Enable/Disable supplied filters
	CO_WR_FILTER_ENABLE = 14,
	//! Read supplied filters
	CO_RD_FILTER = 15,
	//! Waiting till end of maturity time before received radio telegrams will transmitted
	CO_WR_WAIT_MATURITY = 16,
	//! Enable/Disable transmitting additional subtelegram info
	CO_WR_SUBTEL = 17,
	//! Write x bytes of the Flash, XRAM, RAM0 ….
	CO_WR_MEM = 18,
	//! Read x bytes of the Flash, XRAM, RAM0 ….
	CO_RD_MEM = 19,
	//! Feedback about the used address and length of the config area and the Smart Ack Table
	CO_RD_MEM_ADDRESS = 20,
	//! Read security informations (level, keys)
	CO_RD_SECURITY = 21,
	//! Write security informations (level, keys)
	CO_WR_SECURITY = 22,
} COMMON_COMMAND_TYPE;

//! Filter kinds.
typedef enum
{
	//! Blocking filter
	BLOCK = 0x00,
	//! Applying filter
	APPLY = 0x80
} FILTER_KIND;

//! Filter types.
typedef enum
{
	//! ID filter
	ID = 0,
	//! Choice filter
	CHOICE = 1,
	//! dBm filter
	DBM = 2
} FILTER_TYPE;

//! Filter operator.
typedef enum
{
	//! OR composition of filters
	OR = 0,
	//! AND composition of filters
	AND = 1
} FILTER_OPERATOR;

//! Read version response
typedef struct
{
	//! Application version
	uint8_t appVersion[4]; //Application versions 
	//! Application description
	char appDescription[16]; //Applications description  
	//! API version
	uint8_t apiVersion[4]; //API version   
	//! Chip ID
	uint32_t chipID; //Unique ID  
	//! Chip version (reserved for internal use)
	uint32_t chipVersion; //Reserved for internal use
} CO_RD_VERSION_RESPONSE;

//! Read base ID response
typedef struct
{
	//! Base ID
	uint32_t baseID; //Base ID
	//! Remaining write cycles for base ID
	uint8_t remainingWrites; //Remaining write cycles for Base ID
} CO_RD_IDBASE_RESPONSE;

//! Read repeater response
typedef struct
{
	//! Repeater enabled
	bool repEnable; //Repeater enable
	//! Repeater level
	uint8_t repLevel; //Repeater level
} CO_RD_REPEATER_RESPONSE;

//! Read filter response
typedef struct
{
	//! Filter type
	FILTER_TYPE filterType; //Filter type       
	//! Filter value
	uint32_t filterValue; //Filter value
} CO_RD_FILTER_RESPONSE;

//! Common command enum
typedef enum
{
	//! Informs the backbone of a Smart Ack Client to not successful reclaim.           
	SA_RECLAIM_NOT_SUCCESSFUL = 1,
	//! Used for SMACK to confirm/discard learn in/out
	SA_CONFIRM_LEARN = 2,
	//! Inform backbone about result of learn request
	SA_LEARN_ACK = 3,
	//! Inform backbone about about the readiness for operation
	SA_READY = 4,
} SA_EVENT_TYPE;

//! Confirm code enum
typedef enum
{   //! Learn IN
	SA_LEARN_IN = 0x00,
	//! Discard Learn IN, EEP not accepted  
	SA_EEP_NOT_ACCEPTED = 0x11,
	//! Discard Learn IN, PM has no place for further mailbox
	SA_PM_FULL = 0x12,
	//! Discard Learn IN, Controller has no place for new sensor
	SA_CONTROLLER_FULL = 0x13,
	//! Discard Learn IN, RSSI was not good enough
	SA_RSSI_NOT_GOOD = 0x14,
	//! Learn OUT
	SA_LEARN_OUT = 0x20,
	//! Function not supported
	SA_NOT_SUPPORTED = 0xFF
} SA_CONFIRM_CODE;

//! Reset caouse according ESP 3
typedef enum
{
	//! Voltage supply drop or indicates that VDD > VON
	EC_VOLTAGE_DROP = 0x00,
	//! Reset caused by usage of the reset pin
	EC_RESET_PIN = 0x01,
	//! Watchdog timer counter reached the time period
	EC_WATCHDOG_TIMER = 0x02,
	//! Flywheel timer counter reached the time period
	EC_FLYWHEEL_TIMER = 0x03,
	//! Parity error
	EC_PARITY_ERROR = 0x04,
	//! HW Parity error in internal or external memory
	EC_PARITY_MEM_ERROR = 0x05,
	//! CPU memory request does not correspond to valid memory location
	EC_MEM_ERRPR = 0x06,
	//! Wake-up pint 0 activated 
	EC_WAKE_PIN_0 = 0x07,
	//! Wake-up pint 1 activated
	EC_WAKE_PIN_1 = 0x08,
	//! Unknown reset source
	EC_UNKNOWN = 0x09
} EC_RESET_CAUSE;

//! Confirm Learn response
typedef struct
{
	//! Already post master	0b xxxx 1xxx/Place for mailbox	0b xxxx x1xx/Good RSSI	0b xxxx xx1x/Local	0b xxxx xxx1
	uint8_t priPostmaster;
	//! Manufacturer ID 
	uint32_t manufacturerID;
	//! Code of used EEP profile
	uint8_t eep[3];
	//! Signal strength; Send case: FF/Receive case: actual RSSI
	uint8_t rssi;
	//! Device ID of the Post master candidate
	uint32_t postmasterID;
	//! This sensor would be Learn IN
	uint32_t smartAckID;
	//! Numbers of repeater hop
	uint8_t hopCount;
} SA_CONFIRM_LEARN_REQUEST;

//! Learn SmartAck response
typedef struct
{
	//! Response time for Smart Ack Client in ms in which the controller can prepare the data and send it to the postmaster. Only actual if learn return code is Learn IN
	uint16_t responseTime;
	//! Confirmation Code 
	SA_CONFIRM_CODE confirmCode;
} SA_LEARN_ACK_RESPONSE;

//! Ready response
typedef struct
{
	//! Cause of reset
	EC_RESET_CAUSE resetCause;
} CO_READY_RESPONSE;

//! SmartAck command enum
typedef enum
{
	//! Set/Reset Smart Ack learn mode
	SA_WR_LEARNMODE = 1,
	//! Get Smart Ack learn mode state
	SA_RD_LEARNMODE = 2,
	//! Used for Smart Ack to add or delete a mailbox of a client
	SA_WR_LEARNCONFIRM = 3,
	//! Send Smart Ack Learn request (Client)
	SA_WR_CLIENTLEARNRQ = 4,
	//! Send reset command to every SA sensor
	SA_WR_RESET = 5,
	//! Get Smart Ack learned sensors / mailboxes
	SA_RD_LEARNEDCLIENTS = 6,
	//! Set number of reclaim attempts
	SA_WR_RECLAIMS = 7,
	//! Activate/Deactivate Post master functionality
	SA_WR_POSTMASTER = 8,
} SA_COMMAND_TYPE;

//! SmartAck confirm code enum send to gateway in serial command
typedef enum
{
	//! Learn IN
	SA_CC_LEARNIN = 0X00,
	//! Learn OUT
	SA_CC_LEARNOUT = 0X20,
} SMARTACK_CONFIRM_CODE;

//! SmartAck extended learnmode enum
typedef enum
{
	//! Simple Learnmode
	SA_EL_SIMPLE = 0X00,
	//! Advanced Learnmode
	SA_EL_ADVANCE = 0X01,
	//! Advanced Learnmode select Rep.
	SA_EL_ADVANCE_REP = 0X02,
} SA_EXTENDED_LEARNMODE;

//! SmartAck read learnmode response enum
typedef struct
{
	//! Learnmode not active = 0/Learnmode active = 1
	bool enabled;
	//! Simple Learnmode = 0/Advance Learnmode = 1/Advance Learnmode select Rep. = 2
	SA_EXTENDED_LEARNMODE extended;
} SA_RD_LEARNMODE_RESPONSE;

//! SmartAck learned clients response enum
typedef struct
{
	//! Device ID of the Smart Ack Client
	uint32_t clientID;
	//! Postmaster ID dedicated Smart Ack Client
	uint32_t postmasterID;
	//! Internal counter of Post master (0x00 ... 0x0E)
	uint8_t mailboxIndex;

} SA_RD_LEARNEDCLIENTS_RESPONSE;


/**\class eoSerialCommand
 * \brief EnOcean Common Commands class, enables an easy interface for the most common commands
 * \details The eoCommonCommand class, allows you to easily integrate the most common ESP commands into your program.
 * \example commands_example.cpp
 */
class eoSerialCommand
{

public:
  /**
   *Contructor
   *@param gateway Gateway to be used for serial command.
   */        
	eoSerialCommand(eoGateway *gateway);
	virtual ~eoSerialCommand();
	/**
	 *Order to enter the energy saving mode.
	 *@param sleepPeriod The value of deep sleep period in 10 ms units
	 *@return EO_OK or NOT_SUPPORTED
	 */
	eoReturn Sleep(const uint32_t sleepPeriod);
	/**
	 *Order to reset the Device
	 *@return EO_OK or NOT_SUPPORTED
	 */
	eoReturn Reset();
	/**
	 *Read the device SW version / HW version, chip-ID, etc.
	 *@param[out] version Pointer to the CO_RD_VERSION_RESPONSE structure
	 *@return EO_OK or NOT_SUPPORTED
	 */
	eoReturn ReadVersion(CO_RD_VERSION_RESPONSE &version);
	/**
	 *Read System Log from device databank.
	 *@return EO_OK or NOT_SUPPORTED
	 */
	eoReturn BIST();
	/**
	 *Write ID range base number.
	 *@param baseID Base ID
	 *@return EO_OK or NOT_SUPPORTED
	 */
	eoReturn WriteIDBase(const uint32_t baseID);
	/**
	 *READ ID range base number.
	 *@param[out] response Pointer to CO_RD_IDBASE_RESPONSE structure
	 *@return EO_OK or NOT_SUPPORTED
	 */
	eoReturn ReadIDBase(CO_RD_IDBASE_RESPONSE &response);
	/**
	 *Write Repeater Level OFF, 1, 2.
	 *@param repEnable Repeater Enable
	 *@param repLevel Repeater Level
	 *@return EO_OK or NOT_SUPPORTED or WRONG_PARAM
	 */
	eoReturn WriteRepeater(bool repEnable, const uint8_t repLevel);
	/**
	 *Read Repeater Level OFF, 1, 2.
	 *@param[out] response Pointer to the CO_RD_REPEATER_RESPONSE structure
	 *@return EO_OK or NOT_SUPPORTED
	 */
	eoReturn ReadRepeater(CO_RD_REPEATER_RESPONSE &response);
	/**
	 *Add filter to filter list.
	 *@param filterType Type of filter
	 *@param filterValue Value of filter function compare
	 *@param filterKind Blocking/Applying filter
	 *@return EO_OK or NOT_SUPPORTED or WRONG_PARAM or memory error
	 */
	eoReturn AddFilter(const FILTER_TYPE filterType, const uint32_t filterValue, const FILTER_KIND filterKind);
	/**
	 *Delete filter from filter list.
	 *@param filterType Type of filter
	 *@param filterValue Value of filter function compare
	 *@return EO_OK or NOT_SUPPORTED or WRONG_PARAM or memory error
	 */
	eoReturn DeleteFilter(const FILTER_TYPE filterType, const uint32_t filterValue);
	/**
	 *Delete all filters from filter list.
	 *@return EO_OK or NOT_SUPPORTED
	 */
	eoReturn DeleteAllFilter();
	/**
	 *Enable/Disable all supplied filters.
	 *@param filterEnabled Filter enable
	 *@param filterOperator Filter operator (AND or OR)
	 *@return EO_OK or NOT_SUPPORTED or WRONG_PARAM
	 */
	eoReturn EnableFilter(const bool filterEnabled, const FILTER_OPERATOR filterOperator);
	/**
	 *Read supplied filters.
	 *@param[out] filter Pointer to the CO_RD_FILTER_RESPONSE structure
	 *@param[out] filterCount Pointer to the variable where the number of filters stored in the devices is stored
	 *@param[in] maxFilterCount The size of the CO_RD_FILTER_RESPONSE array
	 *@return EO_OK or NOT_SUPPORTED
	 */
	eoReturn ReadFilter(CO_RD_FILTER_RESPONSE *filter, uint8_t *filterCount, uint8_t maxFilterCount);
	/**
	 *Waiting till end of maturity time before received radio telegrams will transmit.
	 *@param waitMaturity Bool value
	 *@return EO_OK or NOT_SUPPORTED or WRONG_PARAM
	 */
	eoReturn WaitMaturity(const bool waitMaturity);
	/**
	 *Response from backbone controller how to handle the received learn request.	 
	 *@param[in] responseTime Response time for client in ms
	 *@param[in] confirmCode Confirmation code
	 *@return EO_OK or NOT_SUPPORTED
	 */
	eoReturn SmartAckConfirmLearn(uint16_t responseTime, SA_CONFIRM_CODE confirmCode);
	/**
	 *Parse the last received gateway.packet into LearnAck response structure
	 *@param[out] response Pointer to the SA_LEARN_ACK_RESPONSE structure
	 *@return EO_OK or NOT_SUPPORTED
	 */
	eoReturn SmartAckLearnAck(SA_LEARN_ACK_RESPONSE &response);
	/**
	 *Parse the last received gateway.packet into ready response structure.
	 *@param[out] response Pointer to the CO_READY_RESPONSE structure
	 *@return EO_OK or NOT_SUPPORTED
	 */
	eoReturn Ready(CO_READY_RESPONSE &response);
	/**
	 *Enables or disables learn mode of Smart Ack Controller.
	 *@param enable Start/End Learnmode
	 *@param extended Simple/Advanced Learnmode
	 *@param timeout Time-out of learnmode in ms
	 *@return EO_OK or NOT_SUPPORTED or WRONG_PARAM
	 */
	eoReturn SmartAckWriteLearnMode(bool enable, SA_EXTENDED_LEARNMODE extended, uint32_t timeout);
	/**
	 *Reads the learnmode state of Smart Ack Controller.
	 *@param[out] response Pointer to the learnmode response structure
	 *@return EO_OK or NOT_SUPPORTED
	 */
	eoReturn SmartAckReadLearnMode(SA_RD_LEARNMODE_RESPONSE &response);
	/**
	 *Send smart ack learn answer to modify mailbox at postmaster.
	 *@param responseTime Response time for sensor in ms
	 *@param confirmCode Learn IN/OUT
	 *@param postmasterID Device ID of the used Post master
	 *@param clientID Device ID of the learned IN/OUT client
	 *@return EO_OK or NOT_SUPPORTED or WRONG_PARAM
	 */
	eoReturn SmartAckLearnConfirm(uint16_t responseTime, SMARTACK_CONFIRM_CODE confirmCode, uint32_t postmasterID, uint32_t clientID);
	/**
	 *Sends Smart Ack Learn Request telegram to Smart Ack Controller. This function will only be used in a Smart Ack Client.
	 *@param manufacturerID
	 *@param EEP
	 *@return EO_OK or NOT_SUPPORTED or WRONG_PARAM
	 */
	eoReturn SmartAckSendLearnRequest(uint16_t manufacturerID, uint32_t EEP);
	/**
	 *Send reset command to a Smart Ack Client.
	 *@param clientID Device ID of the client
	 *@return EO_OK or NOT_SUPPORTED or WRONG_PARAM
	 */
	eoReturn SmartAckReset(uint32_t clientID);
	/**
	 *Read mailbox information at the Post Master device, about all learned Smart Ack clients.
	 *@param[out] *clients Pointer to the Learned clients response structure
	 *@param[out] *learnedCount Number of Learned clients
	 *@param[in] maxLearnedCount The size of the Learned clients response array
	 *@return EO_OK or NOT_SUPPORTED or WRONG_PARAM
	 */
	eoReturn SmartAckLearnedClients(SA_RD_LEARNEDCLIENTS_RESPONSE *clients, uint8_t *learnedCount, uint8_t maxLearnedCount);
	/**
	 *Set the amount of reclaim tries in Smart Ack Client.
	 *@param reclaimCount Preseting for the number of required reclaim tries
	 *@return EO_OK or NOT_SUPPORTED or WRONG_PARAM
	 */
	eoReturn SmartAckSetReclaimTries(uint8_t reclaimCount);
	/**
	 *Set the amount of reclaim tries in Smart Ack Client.
	 *@param mailboxCount Amount of mailboxes available
	 *@return EO_OK or NOT_SUPPORTED or WRONG_PARAM
	 */
	eoReturn SmartAckSetPostmaster(uint8_t mailboxCount);
	/**
	 * Parse the SmartACK confirm learn event packet into structure
	 * @param request ::SA_CONFIRM_LEARN_REQUEST structure
	 */
	eoReturn EventSmartAckConfirmLearn (SA_CONFIRM_LEARN_REQUEST &request);
private:
	eoGateway *gateway;
	eoPacket *packet;
	eoReturn initPacket(uint8_t type, uint8_t command, uint8_t length);

};

#endif /* EOSERIALCOMMAND_H_ */
