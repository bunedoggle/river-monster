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

#if  !defined(eoEEP_A510_H__INCLUDED_)
#define eoEEP_A510_H__INCLUDED_
/** \ingroup eepProfiles
 *  @{
 */
#include "eoA5EEProfile.h"
/**\class eoEEP_A510xx
 * \brief The class to handle EEP a510 profiles
 * \details Allows the user to handle EEP a510 profiles, the following profiles are available:
 * 		- A5-10-01
 * 		- A5-10-02
 * 		- A5-10-03
 * 		- A5-10-04
 * 		- A5-10-05
 * 		- A5-10-06
 * 		- A5-10-07
 * 		- A5-10-08
 * 		- A5-10-09
 * 		- A5-10-0A
 * 		- A5-10-0B
 * 		- A5-10-0C
 * 		- A5-10-0D
 * 		- A5-10-10
 * 		- A5-10-11
 * 		- A5-10-12
 * 		- A5-10-13
 * 		- A5-10-14
 * 		- A5-10-15
 * 		- A5-10-16
 * 		- A5-10-17
 * 		- A5-10-18
 * 		- A5-10-19
 * 		- A5-10-1A
 * 		- A5-10-1B
 * 		- A5-10-1C
 * 		- A5-10-1D
 * 		- A5-10-1E\n\n
 * The following channels are available for 01 profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::E_FANSPEED   	|::ENUM_FAN_SPEED_5STAGE |
 * | 1             | ::S_SETPOINT   	|float |
 * | 2             | ::S_TEMP       	|float |
 * | 3             | ::F_BTN_PRESS   	|uint8_t |
 * \n
 * The following channels are available for 02 profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::E_FANSPEED   	|::ENUM_FAN_SPEED_5STAGE |
 * | 1             | ::S_SETPOINT   	|float |
 * | 2             | ::S_TEMP       	|float |
 * | 3             | ::F_DAY_NIGHT  	|uint8_t |
 * \n
 * The following channels are available for 03 profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::S_SETPOINT   	|float |
 * | 1             | ::S_TEMP       	|float |
 * \n
 * The following channels are available for 04 profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::E_FANSPEED   	|::ENUM_FAN_SPEED_5STAGE |
 * | 1             | ::S_SETPOINT   	|float |
 * | 2             | ::S_TEMP       	|float |
 * \n
 * The following channels are available for 05 profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::S_SETPOINT   	|float |
 * | 1             | ::S_TEMP       	|float |
 * | 2             | ::F_BTN_PRESS   	|uint8_t |
 * \n
 * The following channels are available for 06 profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::S_SETPOINT   	|float |
 * | 1             | ::S_TEMP       	|float |
 * | 2             | ::F_DAY_NIGHT  	|uint8_t |
 * \n
 * The following channels are available for 07 profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::E_FANSPEED   	|::ENUM_FAN_SPEED_5STAGE |
 * | 1             | ::S_TEMP       	|float |
 * \n
 * The following channels are available for 08 profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::E_FANSPEED   	|::ENUM_FAN_SPEED_5STAGE |
 * | 1             | ::S_TEMP       	|float |
 * | 2             | ::F_BTN_PRESS   	|uint8_t |
 * \n
 * The following channels are available for 09 profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::E_FANSPEED   	|::ENUM_FAN_SPEED_5STAGE |
 * | 1             | ::S_TEMP       	|float |
 * | 2             | ::F_DAY_NIGHT  	|uint8_t |
 * \n
 * The following channels are available for 0A profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::S_SETPOINT   	|float |
 * | 1             | ::S_TEMP       	|float |
 * | 2             | ::F_OPEN_CLOSED 	|uint8_t |
 * \n
 * The following channels are available for 0B profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::S_TEMP       	|float |
 * | 1             | ::F_OPEN_CLOSED 	|uint8_t |
 * \n
 * The following channels are available for 0C profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::S_TEMP       	|float |
 * | 1             | ::F_BTN_PRESS   	|uint8_t |
 * \n
 * The following channels are available for 0D profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::S_TEMP       	|float |
 * | 1             | ::F_DAY_NIGHT  	|uint8_t |
 * \n
 * The following channels are available for 10 profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::S_SETPOINT   	|float |
 * | 1             | ::S_TEMP       	|float |
 * | 2             | ::F_BTN_PRESS   	|uint8_t |
 * | 3             | ::S_RELHUM   		|float |
 * \n
 * The following channels are available for 11 profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::S_SETPOINT   	|float |
 * | 1             | ::S_TEMP       	|float |
 * | 2             | ::F_DAY_NIGHT  	|uint8_t |
 * | 3             | ::S_RELHUM   		|float |
 * \n
 * The following channels are available for 12 profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::S_SETPOINT   	|uint8_t |
 * | 1             | ::S_TEMP       	|float |
 * | 2             | ::S_RELHUM   	|float |
 * \n
 * The following channels are available for 13 profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::S_TEMP       	|float |
 * | 1             | ::F_BTN_PRESS   	|uint8_t |
 * | 2             | ::S_RELHUM   		|float |
 * \n
 * The following channels are available for 14 profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::S_TEMP       	|float |
 * | 1             | ::F_DAY_NIGHT   	|uint8_t |
 * | 2             | ::S_RELHUM   		|float |
 * \n
 * The following channels are available for 15 profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::S_SETPOINT   	|float |
 * | 1             | ::S_TEMP       	|float |
 * \n
 * The following channels are available for 16 profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::S_SETPOINT   	|float |
 * | 1             | ::S_TEMP       	|float |
 * | 2             | ::F_BTN_PRESS   	|uint8_t |
 * \n
 * The following channels are available for 17 profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::S_TEMP       	|float |
 * | 1             | ::F_BTN_PRESS   	|uint8_t |
 * \n
 * The following channels are available for 18 profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::E_FANSPEED   	|::ENUM_FAN_SPEED_7STAGE |
 * | 1             | ::S_LUMINANCE   	|float |
 * | 2             | ::S_TEMP_ABS		|float |
 * | 3             | ::S_TEMP       	|float |
 * | 4             | ::F_BTN_PRESS 		|uint8_t |
 * \n
 * The following channels are available for 19 profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::E_FANSPEED   	|::ENUM_FAN_SPEED_7STAGE |
 * | 1             | ::S_RELHUM   		|float |
 * | 2             | ::S_TEMP_ABS		|float |
 * | 3             | ::S_TEMP       	|float |
 * | 4             | ::F_BTN_PRESS 		|uint8_t |
 * \n
 * The following channels are available for 1A profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::E_FANSPEED   	|::ENUM_FAN_SPEED_7STAGE |
 * | 1             | ::S_VOLTAGE   		|float |
 * | 2             | ::S_TEMP_ABS		|float |
 * | 3             | ::S_TEMP       	|float |
 * | 4             | ::F_BTN_PRESS	   	|uint8_t |
 * \n
 * The following channels are available for 1B profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::E_FANSPEED   	|::ENUM_FAN_SPEED_7STAGE  |
 * | 1             | ::S_LUMINANCE   	|float |
 * | 2             | ::S_VOLTAGE		|float |
 * | 3             | ::S_TEMP       	|float |
 * | 4             | ::F_BTN_PRESS   	|uint8_t |
 * \n
 * The following channels are available for 1C profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::E_FANSPEED   		|::ENUM_FAN_SPEED_7STAGE |
 * | 1             | ::S_LUMINANCE   		|float |
 * | 2             | ::S_LUMINANCE_ABS		|float |
 * | 3             | ::S_TEMP       		|float |
 * | 4             | ::F_BTN_PRESS 			|uint8_t |
 * \n
 * The following channels are available for 1D profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::E_FANSPEED   	|::ENUM_FAN_SPEED_7STAGE |
 * | 1             | ::S_RELHUM   		|float |
 * | 2             | ::S_RELHUM_ABS		|float |
 * | 3             | ::S_TEMP       	|float |
 * | 4             | ::F_BTN_PRESS  	|uint8_t |
 * \n
 * The following channels are available for 1E profile:
 * | Channel Index | Channel Type | Type |
 * |:-------------:|:------------:|:----:|
 * | 0             | ::E_FANSPEED   	|::ENUM_FAN_SPEED_7STAGE  |
 * | 1             | ::S_LUMINANCE   	|float |
 * | 2             | ::S_VOLTAGE		|float |
 * | 3             | ::S_TEMP       	|float |
 * | 4             | ::F_BTN_PRESS   	|uint8_t |
 * \n
 * The following channels are available for 1F profile:
 * | Channel Index | Channel Type | Type | Comment |
 * |:-------------:|:------------:|:----:|:-------:|
 * | 0             | ::E_FANSPEED   	|::ENUM_FAN_SPEED_5STAGE |  |
 * | 1             | ::S_SETPOINT   	|float | |
 * | 2             | ::S_TEMP			|float |   |   
 * | 3             | ::F_BTN_PRESS     	|uint8_t | Occupancy, ::OCCUPANCY |
 * | 4             | ::F_BTN_PRESS   	|uint8_t | Unoccupancy, ::UNOCCUPANCY |
 * \n
 */

/**
 * \file eoEEP_A510xx.h
 */
//! Buttons for A5-10-1F profile.
typedef enum
{
	//! <b>Occupancy</b> 0
	OCCUPANCY = 0x00,	//Occupancy button
	//! <b>Unoccupancy</b> 1
	UNOCCUPANCY = 0x01	//Unoccupancy button
} ROP_1F_BUTTONS;

class eoEEP_A510xx: public eoA5EEProfile
{

public:
	eoReturn SetType(uint8_t type);

	eoEEP_A510xx();
	virtual ~eoEEP_A510xx();
	virtual eoReturn GetValue(CHANNEL_TYPE type, float &value);
	virtual eoReturn GetValue(CHANNEL_TYPE type, uint8_t &value, uint8_t subFlag);
	virtual eoReturn SetValue(CHANNEL_TYPE type, float value);
	virtual eoReturn SetValue(CHANNEL_TYPE type, uint8_t value, uint8_t subFlag);
	eoReturn GetValue(CHANNEL_TYPE type, uint8_t &value);
	eoReturn SetValue(CHANNEL_TYPE type, uint8_t value);
};
/** @}*/

#endif // !defined(EA_259BDE62_FE41_490e_8B3E_427A72922C4A__INCLUDED_)
