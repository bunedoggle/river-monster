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
 * \file eoDevice.h
 * \brief eoDevice
 * \author EnOcean GmBH
 */
#if !defined(EO_DEVICE_H)
#define EO_DEVICE_H

#include "eoProfile.h"
#include "eoISerialize.h"
#include "eoArchive.h"
/**
 *\class eoDevice
 *\brief a class to describe an EnOcean Device
 *\details this class contains all Information to handle a Device.
 */
class eoDevice: public eoISerialize
{

public:
	eoDevice();
	/**
	 *Constructor.
	 *@param id EnOcean ID of the device.
	 */      	
	eoDevice(uint32_t id);
	virtual ~eoDevice();
	/**
	 * The used Profile will be destroyed and myProfile will be used for the Device
	 * @param myProfile
	 * @return eoReturn::EO_OK or eoReturn::WRONG_PARAM if the profile overmitted has the same EEP
	 */
	eoReturn SetProfile(eoProfile* myProfile);
	/**
	 * The old Profile will be destroyed and a new one according rorg - func and type will be used. If the choosen profile can not
	 * be created an empty eoProfile will be used
	 * @param rorg EEP RORG
	 * @param func EEP Func
	 * @param type EEP Type
	 * @return eoReturn::EO_OK or eoReturn::NOT_SUPPORTED
	 */
	eoReturn SetProfile(const uint8_t rorg, const uint8_t func, const uint8_t type);
	/**
	 * Gets the Pointer to the eoProfile from this instance
	 * @return the device eoProfile
	 */
	eoProfile* GetProfile() const;
	/**
	 * last dBm
	 */
	int8_t dBm;
	/**
	 * ID of the Device
	 */
	uint32_t ID;

	uint8_t Serialize(eoArchive &a);

private:
	eoProfile *profile;

};
#endif // !defined(EO_DEVICE_H)
