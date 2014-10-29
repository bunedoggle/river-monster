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
 * \file eoGateway.h 
 * \brief eoGateway
 * \author EnOcean GmBH
 */
#if !defined(_EO_GATEWAY_H)
#define _EO_GATEWAY_H

#include "eoHalTypes.h"
#include "eoApiDef.h"
#include "eoISerialize.h"
#include "eoMessage.h"
#include "eoTelegram.h"
#include "eoDevice.h"
#include "eoIFilter.h"
#include "eoPacketStream.h"
#include "eoDeviceManager.h"
#include "eoProfileFactory.h"
#include "eoTeachInModule.h"
#include "eoSerialCommand.h"
#include <queue>

/**
 * \ingroup gateway
 *@{*/
/**
 * Receive Flags from the gateway, to handle the receive events.
 */
typedef enum
{
//!Received Package
	RECV_PACKET = (1 << 0), //!< RECV_PACKET
//!Received Telegram
	RECV_TELEGRAM = (1 << 1), //!< RECV_TELEGRAM
//!Received Message
	RECV_MESSAGE = (1 << 2), //!< RECV_MESSAGE
//!Received Teach in Telegram
	RECV_TEACHIN = (1 << 3), //!< RECV_TEACHIN
//!Received Telegram containing learn_in Profile Information
	RECV_PROFILE = (1 << 4), //!< RECV_PROFILE
//!Received Secured Telegram
	RECV_TELEGRAM_SEC = (1 << 5), //!< RECV_TELEGRAM_SEC
//!Received Error Telegram
	RECV_ERROR = (1 << 6), //!< RECV_ERROR
//!Receiver Device Added
	RECV_DEVICE_ADDED = (1 << 7), //!< RECV_DEVICE_ADDED
//!Receiver got second teachIN
	RECV_SECTEACHIN = (1 << 8), //!< RECV_SECTEACHIN
//!Receiver Remote Management MEssage
	RECV_REMAN = (1 << 9) //!< RECV_REMAN
} RECEIVE_FLAGS;
/**\class eoGateway
 * \brief EnOcean Gateway class, for handling a gateway Module
 * \details The eoGateway class, allows you to easily handle Packages received from an EnOcean Gateway module(USB300,TCM310...).
 * with simple calls you can learn in Devices, add filters, check if you received a Message and send packets.
 * <br>
 * The eoGateway has two different modes the learnMode and the normalMode.
 * After creating the eoGateway the Gateway is in the normalMode, the following steps explain the functionality of the receive function.
 * <ol>
 * <li>Receive packet</li>
 * <li>Is Telegram?</li>
 * <li>Encrypted Telegram-> if Yes decrypt </li>
 * <li>Is the Telegram a part of a chained Message?</li>
 * <li>Telegram gets handled and can be accessed unless it gets filtered.
 * <ol>
 * <li>Learn MODE!<br>
 * Uses the learnFilter (if it is set) to Filter telegrams.
 * Always add the Device to device Manager(flag|=RECV_DEVICE_ADDED), when it is a Security Teach IN, store secure Information.
 * The eoGateway::device is set accordingly.
 *
 * When an EEP Teach IN telegram is received, it is handled by the eoTeachInModule. If the telegram contains the func,type the right eoProfile will be created.
 * As for rps no Teach IN telegram is specified you've to use eoTeachInModule::SetRPS function.
 *
 * If you receive a second Teach IN from a learned IN EEP device the RECV_SECTEACHIN will be set.
 * </li>
 *
 * <li>Normal Mode</li>
 * Uses the filter  (if it is set) to Filter telegrams.
 * If the device is in the deviceManager it is set to the Device, otherwise it returns a dummy device with the ID 0, which is not in the deviceManger.
 * </ol>
 * </li>
 * <li>If we get a EEP TeachIN telegram(4bs or 1bs) set the RECV_TEACHIN flag, so you're application can handle always teachINS</li>
 * <li>If the gateway has a profile saved for the received telegram, parse the data and set RECV_PROFILE</li>
 * </ol>
 * \note
 * deviceManger,stream and TeachInModule will be destroyed in the Destructor, if you need to keep them, set the Pointer to NULL
 *  before calling the Destructor!
 *
 * \example Gateway_example.cpp
 * \example sendTelegram_example.cpp
 * \ref GatewayFiltered_example.cpp

 */
class eoGateway: public eoISerialize
{
public:
	//! Activates Learn Mode
	inline void LearnModeOn()
	{
		LearnMode = true;
	}
	//! Deactivates Learn Mode
	inline void LearnModeOff()
	{
		LearnMode = false;
	}
	//! Pointer to the eoPacketStream Handler
	eoPacketStream *stream;
	//! Pointer to eoTeachInModule
	eoTeachInModule* TeachInModule;
	//! Pointer to the device manager, handling your Devices
	eoDeviceManager *deviceManager;
	/**when this Filter points to a Filter implementation, the received telegram will be filtered while not in learn Mode */
	eoIFilter *filter;
	//! This filter will bes used in learnMod
	eoIFilter *learnFilter;
	//! When true, activates LearnMode until set to False
	bool LearnMode;
	//! contains the last Error Code from the receive function
	uint8_t errorCode;
	//! Pointer to the device, to which the last received Telegram belongs \note could be a NULL Pointer!!!
	eoDevice *device;
	//! received Packet data \note contains the last received data!
	eoPacket packet;

	//! received Telegram \note contains the last received data!
	eoTelegram telegram;
	//! received Message \note contains the last received data!
	eoMessage message;
	//!Common Commands
	eoSerialCommand commands;
	/**
	 * Creates your EnOcean gateway class, with the hardware specific PacketStream Handler and a new DeviceManager
	 */
	eoGateway();
  /**
	 * Creates your EnOcean gateway class, with the hardware specific PacketStream Handler.
	 * @param devManager - createas a Gateway with a specified eoDeviceManager.	 
	 */
	eoGateway(eoDeviceManager *devManager);
  /**
	 * Creates your EnOcean gateway class.
	 * @param str - createas a Gateway with a specified eoPacketStream.	 
	 */
	eoGateway(eoPacketStream *str);
  /**
	 * Creates your EnOcean gateway class.
	 * @param str - createas a Gateway with a specified eoPacketStream.
	 * @param devManager - createas a Gateway with a specified eoDeviceManager.   	 
	 */
	eoGateway(eoPacketStream *str, eoDeviceManager *devManager);
  
  /**
	 * Creates your EnOcean gateway class.
	 * @param str - createas a Gateway with a specified eoPacketStream.
	 * @param devManager - createas a Gateway with a specified eoDeviceManager.
	 * @param normFilter - createas a Gateway with a specified filter for data communication.
	 * @param lrnFilter  - createas a Gateway with a specified filter for learn process.       	 
	 */
	eoGateway(eoPacketStream *str, eoDeviceManager *devManager, eoIFilter * normFilter, eoIFilter * lrnFilter);

	virtual ~eoGateway();
	/**
	 * \brief Handles received Telegrams
	 * \details The receive function handles all incoming Packets.<br>
	 * Depending if we're in LearnMode or not the handling differs. In normal mode:<br><br>
	 * When a packet has been received (RECV_PACKET), it automatically tries to decode as much as possible from the Packet.<br>
	 * If the Packet contains a Telegram the Telegram variable will be filled if it is not filtered from the filter, (RECV_TELEGRAM)<br>
	 * If the Telegram is a chained Message, the message will be filled(RECV_MESSAGE)<br>
	 * If the Telegram is secured and the device is learn_in the telegram will be decrypted (RECV_TELEGRAM_SEC)<br>
	 * If the Telegram is from a learned in EEP or GP Device the profile Information will be set (RECV_PROFILE)<br>
	 * <br>
	 * In <b>LearnMode</b> data will handled as in normal mode but the learnFilter will be used to Filter telegram &
	 * Devices will be learned in as specified in the [EEP] or [GP] document.
	 *
	 * When a second 4BS or 1BS Teach IN telegram from the same devices gets received, the RECV_SECTEACHIN flag will be set.
	 *
	 * If you're in normal mode, a RECV_TEACHIN flag will be set for 4BS and 1BS Teach IN telegrams,
	 * but the device&&profile will not be learned in!
	 * \note the RECV_TEACHIN flag is set, so that the user can implement his own learn IN System
	 * @return ::RECEIVE_FLAGS
	 */
	uint16_t Receive();

	/**
	 * sends Packet to the connected device
	 * \note the Gateway waits for a Response, as defined in the ESP3 for maximal 500ms! In the worst case you need to wait
	 * for such a long time
	 * @param p Packet to send
	 * @return ::eoReturn
	 */
	eoReturn Send(const eoPacket &p);
	/**
	 * sends a Message via the connected device
	 * @param msg Message to send
	 * @return ::eoReturn
	 */
	eoReturn Send(const eoMessage &msg);
	/**
	 * Tries to open a connection to the specified Port
	 * @param port to open; for example "/dev/ttyUSB0"
	 * @return ::eoReturn EO_OK if everything was ok else PORT_ERROR
	 */
	eoReturn Open(const char *port);
	
	/**
	 * Closes the connection.
	 */
	void Close();
	uint8_t Serialize(eoArchive &arch);

private:
	void defaultConstructor();

	uint16_t flags;
	void LearnIN();

	std::deque<eoPacket*> packet_queue;

	eoReturn learnHandler(eoTelegram &recvTelegram); //Handles received telegram in learnMode
	eoReturn secHandler(eoTelegram &recvTelegram); //Handles secure telegram
	eoReturn normalHandler(eoTelegram &recvTelegram); //Handles received telegram in normalMode
};
/**\@}
 */
#endif // !defined(_EO_GATEWAY_H)
