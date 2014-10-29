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
 * \file eoLinuxPacketStream.h
 * \brief
 * \author EnOcean GmBH
 */
#ifndef EO_LINUX_PACKET_STREAM_H_
#define EO_LINUX_PACKET_STREAM_H_

#include "eoPacketStream.h"

/**\class eoLinuxPacketStream
 *  \brief PacketStream Implementation for Linux based Systems
 *
 *\details LinuxPacketStream uses a /dev/ttyxx Interface for a direct communication to an EnOcean device via UART [ESP3].
 *
 * \example linuxPacketStream_example.cpp
 */
class eoLinuxPacketStream: public eoPacketStream
{

public:
	eoLinuxPacketStream();
	virtual ~eoLinuxPacketStream();
	/**
	 * Tries to Open and initialize the specific port for the eoLinuxPacketstream
	 * @param port to open; for example "/dev/ttyUSB0"
	 * @return ::eoReturn EO_OK if everything was ok else  ::eoReturn PORT_ERROR
	 */
	eoReturn Open(const char * port);
	/**
	 * Close the Port
	 */
	void Close();

	eoReturn ReceiveByte(uint8_t* u8RxByte);
	eoReturn SendByte(uint8_t u8TxByte);
private:
	int fd;
	static const uint8_t buffSize = 128;
	uint8_t buf[buffSize];
	uint8_t numBytes;
	uint8_t curByte;

};
#endif // !defined(EO_LINUX_PACKET_STREAM_H_)
