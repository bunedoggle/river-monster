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

//! \file eoEEP_A502xx.h

#if  !defined(eoEEP_A502_H__INCLUDED_)
#define eoEEP_A502_H__INCLUDED_
#include "eoA5EEProfile.h"
/** \ingroup eepProfiles
 *  @{
 */

/**\class eoEEP_A502xx
 * \brief The class to handle EEP a502 profiles
 * \details Allows the user to handle EEP a502 profiles, the following profiles are available:
 * 		- A5-02-01
 * 		- A5-02-02
 * 		- A5-02-03
 * 		- A5-02-04
 * 		- A5-02-05
 * 		- A5-02-06
 * 		- A5-02-07
 * 		- A5-02-08
 * 		- A5-02-09
 * 		- A5-02-0A
 * 		- A5-02-0B
 * 		- A5-02-10
 * 		- A5-02-11
 * 		- A5-02-12
 * 		- A5-02-13
 * 		- A5-02-14
 * 		- A5-02-15
 * 		- A5-02-16
 * 		- A5-02-17
 * 		- A5-02-18
 * 		- A5-02-19
 * 		- A5-02-1A
 * 		- A5-02-1B
 * 		- A5-02-20
 * 		- A5-02-30\n
 * The following channels are available:
 * | Channel Index | CHANNEL_TYPE| Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::S_TEMP       |float |
 */

class eoEEP_A502xx: public eoA5EEProfile
{

public:
	eoReturn SetType(uint8_t type);
	eoEEP_A502xx();
	virtual ~eoEEP_A502xx();
};
/** @}*/

#endif // !defined(EA_259BDE62_FE41_490e_8B3E_427A72922C4A__INCLUDED_)
