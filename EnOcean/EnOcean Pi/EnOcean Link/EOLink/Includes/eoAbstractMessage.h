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
 * \file eoAbstractMessage.h
 * \brief
 * \author EnOcean GmBH
 */


#ifndef EOABSTRACTMESSAGE_H_
#define EOABSTRACTMESSAGE_H_
#include "eoHalTypes.h"
#include "eoApiDef.h"
/**
 * \class eoAbstractMessage
 * \brief base class for all Messages
 * \details this class describes an abstract Message. It is the base class for all real Message Applications
 *
 */
class eoAbstractMessage
{

public:

	//! Data Pointer
	uint8_t* data;
	//! Payload data length
	uint16_t dataLength;
	/**
	 * maximal Length the message can have
	 */
	uint16_t maxLength;

	/**
	 * Gets the dataLength, when reallocate is set to true, a new data Buffer is allocated if the new Size is bigger then
	 * the max Size
	 * @param dataLen new dataLen Size
	 * @param reallocate Enables new allocation
	 * @return
	 */
	eoReturn SetDataLength(uint16_t dataLen, bool reallocate = false);
	/**
	 * Returns current DataLength
	 * @return data length
	 */
	uint16_t GetDataLength() const;
	/**
	 * Gets the maximal Message Length
	 * @return maximal Data Length
	 */
	uint16_t GetMaxLength() const;

protected:
  /**
   * Constructor.
   * @param size Default size of the message.   
   */     
	eoAbstractMessage(uint16_t size=1);
	virtual ~eoAbstractMessage();

};

#endif /* EOABSTRACTMESSAGE_H_ */
