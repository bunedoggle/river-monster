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
 * \file eoApiDef.h
 * \brief contains Dolphin API Definitions
 * \author EnOcean GmBH
 */
#ifndef API_DEF_H_
#define API_DEF_H_

/**
 * \typedef eoReturn
 * \brief contains all the return values from different functions
 */
typedef enum
{
	//! Return values are the same as for the ESP3 command response
	//! <b>0x00</b> - Action performed. No problem detected
	EO_OK = 0x00, //!EO_OK ... command is understood and triggered
	//! <b>0x01</b> - Generic Error
	EO_ERROR = 0x01, //!There is an error occurred
	//! <b>0x02</b> - The functionality is not supported by that implementation
	NOT_SUPPORTED = 0x02, //!The functionality is not supported by that implementation
	//! <b>0x03</b> - There was a wrong function parameter
	WRONG_PARAM = 0x03, //!Wrong function parameter
	//! <b>0x04</b> - Operation denied
	OPERATION_DENIED = 0x04, //!Example: memory access denied (code-protected)
	//! <b>0x80</b> - User command
	USER_CMD = 0x80,//!Return codes greater than 0x80 are used for commands with special return information, not commonly useable.

	//! EO-Link specific return codes
	//! <b>0x05</b> - Action couldn't be carried out within a certain time.
	TIME_OUT = 0x05, //!< TIME_OUT
	//! <b>0x06</b> - No byte or telegram received
	NO_RX = 0x06, //!< NO_RX
	//! <b>0x07</b> - The UART receive is ongoing
	ONGOING_RX = 0x07, //!< ONGOING_RX
	//! <b>0x08</b> - A new byte or telegram received
	NEW_RX = 0x08, //!< NEW_RX
	//! <b>0x09</b> - Buffer full, no space in Tx or Rx buffer
	BUFF_FULL = 0x09, //!< BUFF_FULL
	//!	<b>0x0A</b> - Generic out of range return code e.g. address is out of range or the buffer is too small
	OUT_OF_RANGE = 0x0A, //!< OUT_OF_RANGE
	//! <b>0x0B</b> - Error Opening Port
	PORT_ERROR = 0x0B, //!< PORT_ERROR
	//! <b>0xFF</b> - This function is not implemented
	NOT_IMPLEMENTED = 0xFF  //!< NOT_IMPLEMENTED
} eoReturn;

//! Packet type (ESP3)
typedef enum
{
	PACKET_RESERVED = 0x00,	//!Reserved
	PACKET_RADIO = 0x01,	//!Radio telegram
	PACKET_RESPONSE = 0x02,	//!Response to any packet
	PACKET_RADIO_SUB_TEL = 0x03,//!Radio subtelegram (EnOcean internal function�)
	PACKET_EVENT = 0x04,	//!Event message
	PACKET_COMMON_COMMAND = 0x05,	//!Common command
	PACKET_SMART_ACK_COMMAND = 0x06,	//!Smart Ack command
	PACKET_REMOTE_MAN_COMMAND = 0x07,	//!Remote management command
	PACKET_PRODUCTION_COMMAND = 0x08,	//!Production command
	PACKET_RADIO_MESSAGE = 0x09,	///!Radio message (chained radio telegrams)
	PACKET_RADIO_ADVANCED  = 0x0A, //!Advanced protocol radio telegram
	PACKET_RADIO_SET = 0x0E,	//!set radio stuff&answear
	PACKET_DEBUG = 0x0F	//!debug message
} PACKET_TYPE;

//! Telegram choice codes applies to radio telegram only
typedef enum
{
	//! RPS telegram
	RADIO_CHOICE_RPS = 0xF6,
	//! 1BS telegram
	RADIO_CHOICE_1BS = 0xD5,
	//! 4BS telegram
	RADIO_CHOICE_4BS = 0xA5,
	//! HRC telegram
	RADIO_CHOICE_HRC = 0xA3,
	//! SYS telegram
	RADIO_CHOICE_SYS = 0xA4,
	//! SYS_EX telegram
	RADIO_CHOICE_SYS_EX = 0xC5,
	//! Smart Ack Learn Request telegram
	RADIO_CHOICE_SM_LRN_REQ = 0xC6,
	//! Smart Ack Learn Answer telegram
	RADIO_CHOICE_SM_LRN_ANS = 0xC7,
	//! Smart Ack Reclaim telegram
	RADIO_CHOICE_RECLAIM = 0xA7,
	//! Smart Request telegram
	RADIO_CHOICE_SIGNAL = 0xD0,
	//! Encapsulated addressable telegram
	RADIO_CHOICE_ADT = 0xA6,
	//! Variable Length Data
	RADIO_CHOICE_VLD = 0xD2,
	//! Universal Teach In EEP based
	RADIO_CHOICE_UTE = 0xD4,
	//! Manufacturer Specific Communication
	RADIO_CHOICE_MSC = 0xD1,
	//! Single Teach-In Request
	RADIO_CHOICE_GP_SINGLE_TREQ = 0xB0,
	//! Chained Teach-In Request
	RADIO_CHOICE_GP_CHAINED_TREQ = 0xB1,
	//! Single Teach-In Response
	RADIO_CHOICE_GP_SINGLE_TRES = 0xB2,
	//! Chained Teach-In Response
	RADIO_CHOICE_GP_CHAINED_TRES = 0xB3,
	//! Single Data
	RADIO_CHOICE_GP_SINGLE_DATA = 0xB4,
	//! Chained Data
	RADIO_CHOICE_GP_CHAINED_DATA = 0xB5,
	//! Selective data
	RADIO_CHOICE_GP_SELECT_DATA = 0xB6,
	//! Secure telegram
	RADIO_CHOICE_SEC = 0x30,
	//! Secure telegram	with choice encapsulation
	RADIO_CHOICE_SEC_ENCAPS = 0x31,
	//! Non-secure telegram
	RADIO_CHOICE_NON_SEC = 0x32,
	//! Secure teach-in telegram
	RADIO_CHOICE_SEC_TI = 0x35,

} CHOICE_TYPE;
//! RORGS
typedef enum
{
	//! RPS telegram
	RORG_RPS = 0xF6,
	//! 1BS telegram
	RORG_1BS = 0xD5,
	//! 4BS telegram
	RORG_4BS = 0xA5,
	//! HRC telegram
	RORG_HRC = 0xA3,
	//! SYS telegram
	RORG_SYS = 0xA4,
	//! SYS_EX telegram
	RORG_SYS_EX = 0xC5,
	//! Smart Ack Learn Request telegram
	RORG_SM_LRN_REQ = 0xC6,
	//! Smart Ack Learn Answer telegram
	RORG_SM_LRN_ANS = 0xC7,
	//! Smart Ack Reclaim telegram
	RORG_RECLAIM = 0xA7,
	//! Smart Request telegram
	RORG_SIGNAL = 0xD0,
	//! Encapsulated addressable telegram
	RORG_ADT = 0xA6,
	//! Teach-in request
	GP_TI = 0xB0,
	//!Teach-in response
	GP_TR = 0xB1,
	//! Complete Data
	GP_CD = 0xB2,
	//!Selective data
	GP_SD = 0xB3,
	//! Variable Length Data
	RORG_VLD = 0xD2,
	//! Universal Teach In EEP based
	RORG_UTE = 0xD4,
	//! Manufacturer Specific Communication
	RORG_MSC = 0xD1,
	//! Chained data message
	RORG_CDM = 0x40,
	//! Secure telegram	without choice encapsulation
	RORG_SEC = 0x30,
	//! Secure telegram	with choice encapsulation
	RORG_SEC_ENCAPS = 0x31,
	//! Secure telegram decrypted
	RORG_SECD = 0x32,
	//! Secure teach-in telegram
	RORG_SEC_TI = 0x35,
} RORG_TYPE;


//!Destination broadcast ID
#define  BROADCAST_ID       0xFFFFFFFF

#endif /* API_DEF_H_ */
