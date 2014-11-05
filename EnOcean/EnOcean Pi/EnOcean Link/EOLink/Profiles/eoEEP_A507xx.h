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

//! \file eoEEP_A507xx.h

#if  !defined(eoEEP_A507_H__INCLUDED_)
#define eoEEP_A507_H__INCLUDED_
/** \ingroup eepProfiles
 *  @{
 */
#include "eoA5EEProfile.h"
/**\class eoEEP_A507xx
 * \brief The class to handle EEP a507 profiles
 * \details Allows the user to handle EEP a507 profiles, the following profile is available:
 * 		- A5-07-01
 * 		- A5-07-02
 * 		- A5-07-03\n
 * The following channels are available for type 01:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::S_VOLTAGE    |float |
 * | 1             | ::F_OCCUPIED   |uint8_t |
 * \n
 * The following channels are available for type 02 and for type 03:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::S_VOLTAGE    |float |
 * | 1             | ::S_LUMINANCE  |float |
 * | 2             | ::F_OCCUPIED   |uint8_t |
 *
 */

class eoEEP_A507xx: public eoA5EEProfile
{

public:
	eoReturn SetType(uint8_t type);

	eoEEP_A507xx();
	virtual ~eoEEP_A507xx();
	eoReturn GetValue(CHANNEL_TYPE type, float &value);
	eoReturn SetValue(CHANNEL_TYPE type, float value);
	eoReturn GetValue(CHANNEL_TYPE type, uint8_t &value);
	eoReturn SetValue(CHANNEL_TYPE type, uint8_t value);
};
/** @}*/

#endif // !defined(EA_259BDE62_FE41_490e_8B3E_427A72922C4A__INCLUDED_)
