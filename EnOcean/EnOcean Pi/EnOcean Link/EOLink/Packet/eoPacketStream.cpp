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

#include "eoPacketStream.h"
#include "eoProc.h"
#include "eoTimer.h"

eoPacketStream::eoPacketStream()
{
	u8CRC = 0;
	u16Count = 0;
	u8State = GET_SYNC_STATE;
	u8TickCount = 0;
}

eoPacketStream::~eoPacketStream()
{

}

eoReturn eoPacketStream::Receive(eoPacket *p)
{
	uint8_t u8RxByte;
	// Data Buffer is used to receiver header...
	uint8_t *u8Raw = (uint8_t*) p->data;
	// Temporal variable
	uint8_t i;

	// Check for timeout between two bytes
	if (((uint8_t) eoTimer::GetTickCount()) - u8TickCount > SER_INTERBYTE_TIME_OUT)
	{
		// Reset state machine to init state
		u8State = GET_SYNC_STATE;
	}

	// State machine goes on when a new byte is received
	while (ReceiveByte(&u8RxByte) == EO_OK)
	{
		// Tick count of last received byte
		u8TickCount = (uint8_t) eoTimer::GetTickCount();

		// State machine to load incoming packet bytes
		switch (u8State)
		{
			// Waiting for packet sync byte 0x55
			case GET_SYNC_STATE:
				if (u8RxByte == SER_SYNCH_CODE)
				{
					u8State = GET_HEADER_STATE;
					u16Count = 0;
					u8CRC = 0;
				}

				break;

				// Read the header bytes
			case GET_HEADER_STATE:
				// Copy received data to buffer
				u8Raw[u16Count++] = u8RxByte;
				u8CRC = eoProc::crc8(u8CRC, u8RxByte);

				// All header bytes received?
				if (u16Count == SER_HEADER_NR_BYTES)
				{
					u8State = CHECK_CRC8H_STATE;
					p->dataLength = ((uint16_t) u8Raw[0] << 8) + u8Raw[1];
					p->optionalLength = u8Raw[2];
					p->type = u8Raw[3];
				}

				break;

				// Check header checksum & try to resynchonise if error happened
			case CHECK_CRC8H_STATE:
				// Header CRC correct?
				if (u8CRC != u8RxByte)
				{
					// No. Check if there is a sync byte (0x55) in the header
					int a = -1;
					for (i = 0; i < SER_HEADER_NR_BYTES; i++)
						if (u8Raw[i] == SER_SYNCH_CODE)
						{
							// indicates the next position to the sync byte found
							a = i + 1;
							break;
						};

					if ((a == -1) && (u8RxByte != SER_SYNCH_CODE))
					{
						// Header and CRC8H does not contain the sync code
						u8State = GET_SYNC_STATE;
						break;
					}
					else if ((a == -1) && (u8RxByte == SER_SYNCH_CODE))
					{
						// Header does not have sync code but CRC8H does. The sync code could be the beginning of a packet
						u8State = GET_HEADER_STATE;
						u16Count = 0;
						u8CRC = 0;
						break;
					}
					// Header has a sync byte.
					//It could be a new telegram. Shift all bytes from the 0x55 code in the buffer. Recalculate CRC8 for those bytes
					u8CRC = 0;
					for (i = 0; i < (SER_HEADER_NR_BYTES - a); i++)
					{
						u8Raw[i] = u8Raw[a + i];
						u8CRC = eoProc::crc8(u8CRC, u8Raw[i]);
					}
					u16Count = (uint16_t)(SER_HEADER_NR_BYTES - a);
					// u16Count = i; // Seems also valid and more intuitive than u16Count -= a;

					// Copy the just received byte to buffer
					u8Raw[u16Count++] = u8RxByte;
					u8CRC = eoProc::crc8(u8CRC, u8RxByte);

					if (u16Count < SER_HEADER_NR_BYTES)
					{
						u8State = GET_HEADER_STATE;
						break;
					}

					break;
				}

				// CRC8H correct. Length fields values valid?
				if ((p->dataLength + p->optionalLength) == 0)
				{
					//No. Sync byte received?
					if ((u8RxByte == SER_SYNCH_CODE))
					{
						//yes
						u8State = GET_HEADER_STATE;
						u16Count = 0;
						u8CRC = 0;
						break;
					}
					// Packet with correct CRC8H but wrong length fields.
					u8State = GET_SYNC_STATE;
					return OUT_OF_RANGE;
				}

				// Correct header CRC8. Go to the reception of data.
				u8State = GET_DATA_STATE;
				u16Count = 0;
				u8CRC = 0;

				break;

				// Copy the information bytes
			case GET_DATA_STATE:
				// Copy byte in the packet buffer only if the received bytes have enough room
				if (u16Count < p->getBufferSize())
				{
					p->data[u16Count] = u8RxByte;
					u8CRC = eoProc::crc8(u8CRC, u8RxByte);
				}

				// When all expected bytes received, go to calculate data checksum
				if (++u16Count == (p->dataLength + p->optionalLength))
				{
					u8State = CHECK_CRC8D_STATE;
				}

				break;

				// Check the data CRC8
			case CHECK_CRC8D_STATE:
				// In all cases the state returns to the first state: waiting for next sync byte
				u8State = GET_SYNC_STATE;

				// Received packet bigger than space to allocate bytes?
				if (u16Count > p->getBufferSize())
					return OUT_OF_RANGE;

				// Enough space to allocate packet. Equals last byte the calculated CRC8?
				if (u8CRC == u8RxByte)
					return EO_OK; // Correct packet received

				// False CRC8. If the received byte equals sync code, then it could be sync byte for next paquet.
				if ((u8RxByte == SER_SYNCH_CODE))
				{
					u8State = GET_HEADER_STATE;
					u16Count = 0;
					u8CRC = 0;
				}

				return EO_ERROR;

			default:

				// Yes. Go to the reception of info.
				u8State = GET_SYNC_STATE;
				break;
		}
	}

	return (u8State == GET_SYNC_STATE) ? ONGOING_RX : NEW_RX;
}

eoReturn eoPacketStream::Send(const eoPacket &p)
{
	uint16_t i;
	uint8_t CRC;

	// When both length fields are 0, then this telegram is not allowed.
	if ((p.dataLength || p.optionalLength) == 0)
	{
		return EO_OK;
	}
	// Sync
	SendByte(0x55);

	// Header
	SendByte((uint8_t) (p.dataLength >> 8));
	SendByte((uint8_t) (p.dataLength));
	SendByte(p.optionalLength);
	SendByte(p.type);

	// Header CRC
	CRC = 0;
	CRC = eoProc::crc8(CRC, (uint8_t) (p.dataLength >> 8));
	CRC = eoProc::crc8(CRC, (uint8_t) (p.dataLength));
	CRC = eoProc::crc8(CRC, p.optionalLength);
	CRC = eoProc::crc8(CRC, p.type);
	SendByte(CRC);

	// Data
	CRC = 0;
	for (i = 0; i < (p.dataLength + p.optionalLength); i++)
	{
		CRC = eoProc::crc8(CRC, p.data[i]);
		SendByte(p.data[i]);
	}

	// Data CRC
	SendByte(CRC);
	return EO_OK;
}
