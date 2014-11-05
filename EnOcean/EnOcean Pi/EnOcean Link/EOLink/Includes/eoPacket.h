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
 * \file eoPacket.h
 * \brief
 * \author EnOcean GmBH
 */
#if !defined(EO_PACKET_H)
#define EO_PACKET_H

#include "eoHalTypes.h"

/** \class eoPacket
 *  \brief Class which contains a Packet
 *  \details Packets are used for the communication with the connected EnOcean Device via ESP3.
 * \ref linuxPacketStream_example.cpp
 */
class eoPacket
{

public:
	/**
	 * The base constructor for Packet will allocate 550bytes for the internal dataBuffer.
	 * 550bytes is enough for ESP 3	(1.17), if you need more or less you can always use Packet(uint16_t size);
	 */
	eoPacket();

	/**
	 * This constructor allows the User to set  the dataBuffer Pointer as he wants
	 * The dataBuffer, will not be deleted in this case, in the destructor.
	 * @param dataBuffer Pointer to dataBuffer
	 * @param size size of the buffer
	 */
	eoPacket(uint8_t* dataBuffer, uint16_t size);
	/**
	 * This constructor automatically allocates size bytes as dataBuffer
	 * @param size bytes to allocate
	 */
	eoPacket(uint16_t size);

	/**
	 * This is copy constructor automatically allocates size bytes as dataBuffer
	 * @param packet bytes to allocate
	 */
	eoPacket(eoPacket &packet);

	virtual ~eoPacket();

	/**
	 * Returns the size of the buffer
	 * @return Buffersize
	 */
	uint16_t getBufferSize();

	/**
	 * Copies the content of this eoPacket to packet.
	 * @return EO_OK
	 * @return OUT_OF_RANGE if the packet.bufferSize is smaller than this eoPacket.dataLength+optionalLength
	 */
	uint8_t copyTo(eoPacket &packet);

	/**
	 * Direct access to DataBuffer, can be unsafe only use it if you know what you do!
	 */
	uint8_t* data;

	/**
	 * Sets or get the DataLength of the Packet
	 */
	uint16_t dataLength;

	/**
	 * Sets or get the Optional DataLength of the Packet
	 */
	uint8_t optionalLength;

	/**
	 * The ::PACKET_TYPE
	 */
	uint8_t type;

private:
	uint16_t bufferSize;
	bool externalBuffer;

};
#endif // !defined(EO_PACKET_H)
