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
 * \file eoProfileFactory.h
 * \brief
 * \author EnOcean GmBH
 */
#ifndef EO_PROFILE_FACTORY_H_
#define EO_PROFILE_FACTORY_H_

#include "eoHalTypes.h"
#include "eoMessage.h"

#include "eoDevice.h"
#include "eoProfile.h"

/**
 *\class eoProfileFactory
 *\brief creates Profiles
 *\details this helper class, helps you to create an EoProfile.
 */
class eoProfileFactory
{

public:
	/**
	 * \brief Returns eoProfile based on TEACH_IN Message
	 * \details This helper function, will parse the TEACH_IN Message and when the profile is supported a pointer
	 * to the eoProfile or otherwise a null Pointer.
	 *
	 * For Generic Profiles, the GP_TI Message will parsed, and a new eoGenericProfile will be returned.
	 * @param msg TEACH_IN Message to parse
	 * @return a Pointer to the right eoProfile or NULL
	 */
	static eoProfile* CreateProfile(const eoMessage &msg);
	/**
	 * \brief Returns eoProfile based on the specified rorg,func and type
	 * \details This helper function, returns the specified eoProfile based on the rorg,func and type information or a null pointer if it is not supported.
	 * @param rorg  see [EEP]
	 * @param func see [EEP]
	 * @param type see [EEP]
	 * @return a Pointer to the right eoProfile or NULL
	 */
	static eoProfile* CreateProfile(const uint8_t rorg, const uint8_t func, const uint8_t type);
};
#endif
