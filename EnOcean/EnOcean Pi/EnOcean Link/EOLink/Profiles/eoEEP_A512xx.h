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

//! \file eoEEP_A512xx.h

#if  !defined(eoEEP_A512_H__INCLUDED_)
#define eoEEP_A512_H__INCLUDED_
/** \ingroup eepProfiles
 *  @{
 */
#include "eoA5EEProfile.h"
/**\class eoEEP_A512xx
 * \brief The class to handle EEP a512 Automated meter reading (AMR) profiles
 * \details Allows the user to handle EEP a512 Automated meter reading (AMR) profiles, the following profiles are available:
 * 		- A5-12-00
 * 		- A5-12-01 Electricity
 * 		- A5-12-02 Gas
 * 		- A5-12-03 Water\n
 *
 * The following channels are available for Profile 0:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::S_COUNTER  |float |
 * | 1             | ::S_VOLUME	  |float |
 * | 2             | ::E_TARIFF	  |uint8_t |
 * \n
 *
 * The following channels are available for Profile 01:
 * | Channel Index | Channel Type | Type | Comment |
 * |:-------------:|:------------:|:----:| |
 * | 0             | ::S_ENERGY   |float | |
 * | 1             | ::S_POWER	  |float | Unit is kWh |
 * | 2             | ::E_TARIFF	  |uint8_t | |
 * \n
 *
 * The following channels are available for Profile 02 and 03:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::S_VOLFLOW  |float |
 * | 1             | ::S_VOLUME	  |float |
 * | 2             | ::E_TARIFF	  |uint8_t |
 * \n
 */

typedef enum
{
	CUMULATIVE = 0x00, //1 or kWh or m^3
	CURRENT = 0x01	   //1/s or W or liter/s
} DATA_TYPE_METER_READING;

class eoEEP_A512xx: public eoA5EEProfile
{

public:
	eoReturn SetType(uint8_t type);

	eoEEP_A512xx();
	virtual ~eoEEP_A512xx();
	virtual eoReturn GetValue(CHANNEL_TYPE type, float &value);
	virtual eoReturn SetValue(CHANNEL_TYPE type, float value);
	virtual eoChannelInfo* GetChannel(CHANNEL_TYPE type);
};
/** @}*/

#endif // !defined(EA_259BDE62_FE41_490e_8B3E_427A72922C4A__INCLUDED_)
