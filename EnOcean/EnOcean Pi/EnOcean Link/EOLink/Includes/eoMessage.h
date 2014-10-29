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
 * \file eoMessage.h
 * \brief
 * \author EnOcean GmBH
 */
#ifndef EO_MESSAGE_H_
#define EO_MESSAGE_H_

#include "eoAbstractMessage.h"
#include "eoHalTypes.h"

/**
 * \class eoMessage
 * \brief Message Class for communication
 * \details this class describes a Message, a message is the virtual piece of information, which is exchanged between eoLink and the Gateway.
 *
 * It contains the payload data, the Source ID and the RORG information.
 */
class eoTelegram;
class eoMessage : public eoAbstractMessage
{
public:
	/**
	 * Copies the content of this eoMessage to another eoMessage.
	 * @return EO_OK
	 * @return OUT_OF_RANGE if the eoMessage.maxLength is smaller than this eoMessage.maxLength
	 */
	eoReturn copyTo(eoMessage &msg) const;
	/**
	 * Clears the message
	 * @return
	 */
	void Clear();
	/**
	 * Creates a new Message and reserves size bytes for the data in the ram
	 * @param size bytes ti reserve in the ram
	 */
	eoMessage(uint16_t size=1);
	/**
	 * Creates a new Message from a telegram
	 * @param tel ::eoTelegram used by the eoMessage.
	 */
	eoMessage(const eoTelegram &tel);


	virtual ~eoMessage();

	//! RORG as specified by EnOcean
	uint8_t RORG;
	//! status Information from device
	uint8_t status;

	/**
	 * \brief SourceID
	 \details When sending data= ID to use

	 \note can only be a valid id based from the BASE_ID or use 0x0 for the connected device ID

	 When it is a received Message, id from the transmitter.
	 */
	uint32_t sourceID;
	//! the destination ID
	uint32_t destinationID;
  //! Security level of the message.
	uint8_t securityLevel;

protected:

};
#endif
