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

#include "eoManufacturer.h"
#include <string.h>

const char eoManufacturer::list[][MAX_NAME_LENGTH] =
{
		"Manufacturer Reserved"			, //= 0x000, MANUFACTURER_RESERVED
		"Peha"							, //= 0x001, PEHA
		"Thermokon"						, //= 0x002, THERMOKON
		"servodan"						, //= 0x003, SERVODAN
		"EchoFlex Solutions"			, //= 0x004, ECHOFLEX_SOLUTIONS
		"Omnio AG"						, //= 0x005, OMNIO_AG
		"Hardmeier electronics"			, //= 0x006, HARDMEIER_ELECTRONICS
		"Regulvar Inc"					, //= 0x007, REGULVAR_INC
		"Ad Hoc Electronics"			, //= 0x008, AD_HOC_ELECTRONICS
		"Distech Controls"				, //= 0x009, DISTECH_CONTROLS
		"Kieback + Peter"				, //= 0x00A, KIEBACK_AND_PETER
		"EnOcean GmbH"					, //= 0x00B, ENOCEAN_GMBH
		"Probare"						, //= 0x00C, PROBARE
		"Eltako"						, //= 0x00D, ELTAKO
		"Leviton"						, //= 0x00E, LEVITON
		"Honeywell"						, //= 0x00F, HONEYWELL
		"Spartan Peripheral Devices"	, //= 0x010, SPARTAN_PERIPHERAL_DEVICES
		"Siemens"						, //= 0x011, SIEMENS
		"T-Mac"							, //= 0x012, T_MAC
		"Reliable Controls corporation"	, //= 0x013, RELIABLE_CONTROLS_CORPORATION
		"Elsner Elektronik GmbH "		, //= 0x014, ELSNER_ELEKTRONIK_GMBH
		"Diehl Controls"				, //= 0x015, DIEHL_CONTROLS
		"BSC Computer"					, //= 0x016, BSC_COMPUTER
		"S+S Regeltechnik GmbH"			, //= 0x017, S_AND_S_REGELTECHNIK_GMBH
		"Masco Corporation"				, //= 0x018, MASCO_CORPORATION
		"Intesis Software SL"			, //= 0x019, INTESIS_SOFTWARE_SL
		"Viessmann"						, //= 0x01A, VIESSMANN
		"Lutuo Technology"				, //= 0x01B, LUTUO_TECHNOLOGY
		"CAN2GO"						, //= 0x01C, CAN2GO
		"Sauter"						, //= 0x01D, SAUTER
		"Boot-Up"						, //= 0x01E, BOOT_UP
		"Osram Sylvania"				, //= 0x01F, OSRAM_SYLVANIA
		"Unotech"						, //= 0x020, UNOTECH
		"N/A"							, //= 0x021
		"Unitronic AG"					, //= 0x022, UNITRONIC_AG
		"NanoSense"						, //= 0x023, NANOSENSE
		"The S4 Ggroup"					, //= 0x024, THE_S4_GROUP
		"MSR Solutions "				, //= 0x025, MSR_SOLUTIONS
		"N/A"							, //= 0x026
		"Maico"							, //= 0x027, MAICO
		"N/A"							, //= 0x028
		"N/A"							, //= 0x029
		"KM Controls"					, //= 0x02A, KM_CONTROLS
		"Ecologix Controls"				, //= 0x02B, ECOLOGIX_CONTROLS
		"N/A"							, //= 0x02C
		"Afriso Euro Index"				, //= 0x02D, AFRISO_EURO_INDEX
		"N/A"							, //= 0x02E
		"N/A"							, //= 0x02F
		"NEC AccessTechnica Ltd"		, //= 0x030, NEC_ACCESSTECHNICA_LTD
		"ITEC Corporation"				, //= 0x031, ITEC_CORPORATION
};

const char eoManufacturer::listDefault[2][MAX_NAME_LENGTH] =
{
		"Multi User Manufacturer"	, //= 0x7FF, MULTI_USER_MANUFACTURER
		"N/A"						, //= all other
};


eoManufacturer::~eoManufacturer()
{
}

const char* eoManufacturer::GetName(const uint16_t manufacturerID)
{
	if (manufacturerID < (sizeof(list)/MAX_NAME_LENGTH))
		return list[manufacturerID];

	if (manufacturerID == MULTI_USER_MANUFACTURER)
		return listDefault[0];

	return listDefault[1];
}



