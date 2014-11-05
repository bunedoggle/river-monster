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
 * \file eoPacketStream.h
 * \brief
 * \author EnOcean GmBH
 */

#if !defined(EO_PACKETSTREAM_H)
#define EO_PACKETSTREAM_H

#include "eoHalTypes.h"
#include "eoApiDef.h"
#include "eoPacket.h"

/****************************Defines******************************/
//!ESP 3 Start of Frame - before header.
#define SER_SYNCH_CODE 			        0x55
//!ESP 3 Header Lenght.
#define SER_HEADER_NR_BYTES             4
//!ESP 3 Timeout between two following bytes. 
#define SER_INTERBYTE_TIME_OUT 			100

/**\class eoPacketStream
 * \brief The base class for all PacketStreams Implementations
 *
 * \details PacketStream is an abstract base class for the Hardware specific xyPacketStream Classes.
 * It contains the Important PacketStream::Receive and PacketStream::Send Functions to receive and send [ESP3]
 * Packets. The specific Hardware classed have to implement at least SendByte and ReceiveByte to get the Bytes.
 *
 * \example packetStream_example.cpp
 */
class eoPacketStream
{
private:
	typedef enum
	{
		//! Waiting for the synchronization byte 0x55
		GET_SYNC_STATE = 0,
		//! Copying the 4 after sync byte: raw data length (2 bytes), optional data length (1), type (1).
		GET_HEADER_STATE,
		//! Checking the header CRC8 checksum. Resynchronization test is also done here
		CHECK_CRC8H_STATE,
		//! Copying the data and optional data bytes to the packet buffer
		GET_DATA_STATE,
		//! Checking the info CRC8 checksum.
		CHECK_CRC8D_STATE

	} STATES_GET_PACKET;

	//! Checksum calculation
	uint8_t u8CRC;
	//! Nr. of bytes received
	uint16_t u16Count;
	//! State machine counter
	STATES_GET_PACKET u8State;
	//! Timeout measurement
	uint8_t u8TickCount;

public:
	/**
	 * Constructor for eoPacketStream, Inits the necessary Hardware and opens the ports
	 */
	eoPacketStream();
	virtual ~eoPacketStream();

	/**
	 * Tries to Open and initialize the specific port for the eoPacketStream
	 * @param port to open; for example "/dev/USB300"
	 * @return ::eoReturn EO_OK if everything was ok else  ::eoReturn PORT_ERROR
	 */
	virtual eoReturn Open(const char *port) = 0;
	/**
	 * Close the Port
	 */
	virtual void Close() = 0;

	/**
	 * This functions will parse all the available bytes in the Stream, and tries to find an ESP3
	 Packet. It will Return EO_OK if we found one, or NEW_RX_BYTE if we've received some bytes but not yet
	 a full Packet.

	 * @param p Pointer to eoPacket to be filled
	 * @return Returns a ::eoReturn
	 */
	virtual eoReturn Receive(eoPacket *p);
	/**
	 *
	 * @param d Pointer where to write the Byte
	 * @return  Returns a ::eoReturn
	 */
	virtual eoReturn ReceiveByte(uint8_t *d) = 0;
	/**
	 *
	 * @param p The eoPacket to send
	 * @return  Returns a ::eoReturn
	 */
	virtual eoReturn Send(const eoPacket &p);
	/**
	 *
	 * @param d The byte to send
	 * @return  Returns a ::eoReturn
	 */
	virtual eoReturn SendByte(uint8_t d) = 0;

};
#endif // !defined(EO_PACKETSTREAM_H)
