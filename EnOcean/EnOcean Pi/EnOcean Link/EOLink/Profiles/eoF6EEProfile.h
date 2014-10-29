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

/** \file eoF6EEProfile.h
 * \brief
 * \author EnOcean GmbH
 */
#include "eoEEProfile.h"
#ifndef EOF6EEPROFILE_H_
#define EOF6EEPROFILE_H_
//! Rocker States
typedef enum
{
	//! <b>0</b> xI Button Pressed
	STATE_I = 0,
	//! <b>1</b> x0 Button Pressed
	STATE_O = 1,
	//! <b>2</b> Rocker Button has not been Pressed
	STATE_NP = 2,
	//! <b>3</b> Both Rocker Button Pressed
	STATE_IO = 3,
} ENUM_ROCKER_STATE;

//! Window States
typedef enum
{
	//! <b>0</b> Window Handle is at upper Position
	WINDOW_DOWN = 0,
	//! <b>1</b> Window Handle is at middle Position
	WINDOW_MIDDLE = 1,
	//! <b>2</b> Window Handle is at down Position
	WINDOW_UP = 2,
} ENUM_WINDOW_STATE;

//! Energybow state
typedef enum
{
	//! <b>0</b> Energy bow pressed
	ENERGY_PRESSED = 0,
	//! <b>1</b> Energy bow released
	ENERGY_RELEASED = 1,

} ENUM_ENERGY_STATE;

//! Multipress state
typedef enum
{
	//! <b>0</b> 1 or 2 buttons pressed
	MULTIPRESS_NOT = 0,
	//! <b>1</b> More then 2 buttons pressed
	MULTIPRESS_YES = 1,
} ENUM_MULTIPRESS_STATE;
/** \ingroup <eepProfiles>
 *  @{
 */
/**
 * \brief EnOcean Equipment Profiles class for RORG F6.
 * \details Base class for EnOcean Equipment Profiles - RORG - 0xF6, contains functions which are always the same for all derivated F6 Profiles.
 */
class eoF6EEProfile: public eoEEProfile
{
public:
	eoF6EEProfile();

	virtual eoReturn Create(eoMessage &msg);
	virtual eoReturn Parse(const eoMessage &msg);
	virtual ~eoF6EEProfile();

};
/** @}*/

#endif /* EOEEPPROFILE_H_ */
