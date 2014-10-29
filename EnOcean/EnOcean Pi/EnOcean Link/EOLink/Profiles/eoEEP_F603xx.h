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

//! \file eoEEP_F603xx.h

#if  !defined(eoEEP_F603_H__INCLUDED_)
#define eoEEP_F603_H__INCLUDED_
/** \ingroup eepProfiles
 *  @{
 */
#include "eoF6EEProfile.h"
/**\class eoEEP_F603xx
 * \brief The class to handle EEP f603 profiles
 * \details Allows the user to handle EEP f603 profiles, the following profiles are available:
 * 		- F6-03-01
 * 		- F6-03-02\n
 * The following channels are available:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::E_ROCKER_A   |uint8_t |
 * | 1             | ::E_ROCKER_B	|uint8_t |
 * | 2             | ::E_ROCKER_C   |uint8_t |
 * | 3             | ::E_ROCKER_D	|uint8_t |
 * | 4             | ::E_ENERGYBOW  |uint8_t |
 * | 5             | ::E_MULTIPRESS |uint8_t |
 */
class eoEEP_F603xx: public eoF6EEProfile
{
private:
	eoReturn RockerHelper();
	uint8_t rockerA;
	uint8_t rockerB;
	uint8_t rockerC;
	uint8_t rockerD;

public:
	eoReturn SetType(uint8_t type);
	virtual eoReturn GetValue(CHANNEL_TYPE type, uint8_t &value);
	virtual eoReturn SetValue(CHANNEL_TYPE type, uint8_t value);
	void ClearValues();
	eoEEP_F603xx();
	virtual ~eoEEP_F603xx();
	virtual eoChannelInfo* GetChannel(CHANNEL_TYPE type);
};
/** @}*/

#endif // !defined(EA_259BDE62_FE41_490e_8B3E_427A72922C4A__INCLUDED_)
