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
 * \file eoIFilter.h
 * \brief eoIFilter
 * \author EnOcean GmBH
 */
#ifndef EOI_FILTER_H
#define EOI_FILTER_H

#include "eoHalTypes.h"
#include "eoMessage.h"
#include "eoTelegram.h"
#include "eoArchive.h"

/**
 * \typedef SUPPORTED_FILTERS
 * Supported filter types
 */  
typedef enum
{
	eoIDFILTER = 1,
	eoDBMFILTER
} SUPPORTED_FILTERS;

/**\ingroup eoFilter
 * @{
 */

/**
 * \class eoIFilter
 *  \ref GatewayFiltered_example.cpp
 *  \brief Filter Interface
 *  \details The Filter Interface allows you to easily Implement your own Filter strategies.Filters are used in the Gateway.
 */
class eoIFilter: public eoISerialize
{

public:
    //! Type
	uint8_t type;
	eoIFilter();

	virtual ~eoIFilter();

	/**
	 * Applies the specified filter on the Message.
	 * @param msg
	 * @return false when the message is filtered, else false.
	 */
	virtual bool Filter(eoMessage &msg);

	/**
	 * Applies the specified filter on the Telegram.
	 * @param tel
	 * @return false when the message is filtered, else false.
	 */
	virtual bool Filter(eoTelegram &tel);

	/**
	 * Serialization Function which will be called by the eoStorageManager
	 * This function will be called by the eoArchive(inside of the eoStorageManager) and allows the class to be Serialized.
	 * @param &arch Archive where to Load or to Store.
	 */
	virtual uint8_t Serialize(eoArchive &arch);

	/**
	 * Remove all IDS.
	 */
	virtual void RemoveAll();

};
/**
 @}
 */
#endif // !defined(EOI_FILTER_H)
