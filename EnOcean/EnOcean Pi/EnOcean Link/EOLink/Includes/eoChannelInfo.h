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
 * \file eoChannelInfo.h
 * \brief contains the eoChannelInfo Class
 * \author EnOcean GmBH
 */
#ifndef _eoCHANNELINFO_H
#define	_eoCHANNELINFO_H

#include "eoHalTypes.h"
#include "eoChannelEnums.h"
//! get Unit String
#define UNIT 0x00
//! get String Name
#define NAME 0x01

/**
 * \struct EEP_ITEM
 * Structure to describe the EEP Related information. It can be used in channel decoding and usage.
 */    
typedef struct
{
  //!Help flag if channel available.
	bool exist;
	//!Offset of the data value in telegram in bits. 
	uint16_t bitoffs;
	//!Size of the data value in telegram.
	uint16_t bitsize;
	//!Range of the data value - minimum.
	uint32_t rangeMin;
	//!Range of the data value - maximum.
	uint32_t rangeMax;
	//!Scaling application for the data value - minimum. 
	float scaleMin;
	//!Scaling application for the data value - maximum.
	float scaleMax;
	//! ::CHANNEL_TYPE
	CHANNEL_TYPE type;
  //! Subchannel type - or index. This is only used if two of the same ::CHANNEL_TYPE members are available and we need to differ between them. 	
	uint8_t index;
} EEP_ITEM;


/**
 * \class eoChannelInfo
 * \brief Abstract class for channel information.  
 * Abstract class for channel information. From this class specific channel informations classes for Generic Profiles or EEP are derived.
 */  
class eoChannelInfo
{
public:
  //! ::CHANNEL_TYPE
	CHANNEL_TYPE type;		
	//! Current, Setpoint Absolute, Setpoint relative
	VALUE_TYPE signalType;	
	//! UINT32, UINT8, float
	VALUE_FORMAT valueFormat;
  //! Min as clear value	
	float min;
  //! Max as clear value		
	float max;		
	/**
	 * Returns for signalTypes either the NAME or the UNIT, for flags a small desc
	 * @param strType NAME(0x00) or UNIT(0x01)
	 * @return Pointer to const String
	 */
	const char* ToString(uint8_t strType);
};

/**
 * \class eoEEPChannelInfo
 * \brief Specific class for EEP channel information.  
 * Class used to decribe the EEP channels. It has the EEP_ITEM to describe the EEP channel values and the subtype - index.
 */
class eoEEPChannelInfo: public eoChannelInfo
{
public:
  //! points to static description of EEP
	const EEP_ITEM* eepItem;		
};

#endif // _CHANNELINFO_H
