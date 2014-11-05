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

#ifndef EOA5EEPROFILE_H_
#define EOA5EEPROFILE_H_

/** \file eoA5EEProfile.h
 * \brief
 * \author EnOcean GmbH
 */

#include "eoEEProfile.h"
#include "eoApiDef.h"
//! Fan Speed for 5 Stages ie A5-10-01
typedef enum
{
	//! <b>Stage 3</b> 0..144
	STAGE_3 = 0,
	//! <b>Stage 2</b> 145..164
	STAGE_2 = 1,
	//! <b>Stage 1</b> 165..189
	STAGE_1 = 2,
	//! <b>Stage 0</b> 190..209
	STAGE_0 = 3,
	//! <b>Stage Auto</b>210..255
	STAGE_AUTO = 4,

} ENUM_FAN_SPEED_5STAGE;

//! Fan Speed for 7 Stages ie A5-10-18
typedef enum
{
	//! <b>Stage Auto</b> 0
	SPEED_AUTO = 0,
	//! <b>Speed 0</b> 1
	SPEED_0 = 1,
	//! <b>Speed 1</b> 2
	SPEED_1 = 2,
	//! <b>Speed 2</b> 3
	SPEED_2 = 3,
	//! <b>Speed 3</b> 4
	SPEED_3 = 4,
	//! <b>Speed 4</b> 5
	SPEED_4 = 5,
	//! <b>Speed 5</b> 6
	SPEED_5 = 6,
	//! <b>Speed Off</b> 7
	SPEED_OFF = 7,

} ENUM_FAN_SPEED_7STAGE;

//! VOC (Volatile organic compound) Enum definition for a5-09-05
typedef enum
{
	VOC_total = 0,
	VOC_Formaldehyde = 1,
	VOC_Benzene = 2,
	VOC_Styrene = 3,
	VOC_Toluene = 4,
	VOC_Tetrachloroethylene = 5,
	VOC_Xylene = 6,
	VOC_n_Hexane = 7,
	VOC_n_Octane = 8,
	VOC_Cyclopentane = 9,
	VOC_Methanol = 10,
	VOC_Ethanol = 11,
	VOC_1_Pentanol = 12,
	VOC_Acetone = 13,
	VOC_ethylene_oxide = 14,
	VOC_Acetaldehyde_ue = 15,
	VOC_Acetic_Acid = 16,
	VOC_Propionice_Acid = 17,
	VOC_Valeric_Acid = 18,
	VOC_Butyric_Acid = 19,
	VOC_Ammoniac = 20,
	VOC_Hydrogen_Sulfide = 21,
	VOC_Dimethylsulfide = 22,
	VOC_2_Butanol = 23,
	VOC_2_Methylpropanol = 24,
	VOC_Diethyl_ether = 25,
	VOC_ozone = 255
} ENUM_VOC;

/**
 * \ingroup eepProfiles
 *  @{
 *  \class eoA5EEProfile
 * \brief EnOcean Equipment Profiles
 * \details base class for EnOcean Equipment Profiles, contains functions which are always the same
 */
class eoA5EEProfile: public eoEEProfile
{
public:
	/**
	 * Constructor.
	 * @param size Default size of the expected message.
	 */
	eoA5EEProfile(uint16_t size = 4);
	virtual ~eoA5EEProfile();

	virtual eoReturn GetValue(CHANNEL_TYPE type, float &value);
	virtual eoReturn GetValue(CHANNEL_TYPE type, float &value, uint8_t index);
	virtual eoReturn GetValue(CHANNEL_TYPE type, uint8_t &value, uint8_t index);
	virtual eoReturn SetValue(CHANNEL_TYPE type, float value);
	virtual eoReturn SetValue(CHANNEL_TYPE type, uint8_t value, uint8_t index);
	virtual eoReturn SetValue(CHANNEL_TYPE type, float value, uint8_t index);
	virtual eoReturn CreateTeachIN(eoMessage &m);
	virtual eoReturn Parse(const eoMessage &msg);
	/**
	 * Checks if the message is a 4BS data Telegram as in [EEP]
	 * @param m Message to check
	 * @return true=yes; false=no
	 */
	bool Is4BSData(const eoMessage &m);
};
/** @}*/

#endif /* EOEEPPROFILE_H_ */
