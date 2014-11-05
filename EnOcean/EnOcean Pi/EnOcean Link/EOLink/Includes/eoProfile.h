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
 * \file eoProfile.h
 * \brief
 * \author EnOcean GmBH
 */
#ifndef __EOPROFILE_INCLUDED_
#define __EOPROFILE_INCLUDED_

#include "eoApiDef.h"
#include "eoChannelInfo.h"
#include "eoHalTypes.h"
#include "eoMessage.h"
#include "eoISerialize.h"
#include "eoArchive.h"

/**
 * \ingroup gateway
 * @{
 */

/**
 * \class eoProfile
 * \brief base class for Profile parsing
 * \details The eoProfile class, enables an abstract Layer for handling the two different Profile Worlds of the EnOcean world.
 * It adds an easy to use Interface for your application, and in the most cases your application does not need to care which sort
 * of profile you're using. The GetValue and SetValue enables an easy way to read and write Sensor and other Data to a Message.
 *
 * The Real Implementation for EEP is done in the eoEEProfile and for the Generic Profiles in the eoGenericProfile class.
 * \ref profile_examples.cpp
 *  \example genericProfile_examples.cpp
 */
class eoProfile: public eoISerialize
{
public:   
  //! R-ORG
	uint8_t rorg;   
	//! Func
	uint8_t func;   
	//! Type
	uint8_t type;  
  //! Manufacturer
	uint16_t manufacturer;

	/** eoProfile constructor.
	 *	@param size Default size of messages.
	*/
	eoProfile(uint16_t size = 0);
	virtual ~eoProfile();

	/**
	 * Returns true if rorg,func and type are the same.
	 * @param othProfile
	 * @return true or false
	 */
	virtual bool operator==(const eoProfile &othProfile) const;

	/**
	 * Returns true if rorg,func and type are different.
	 * @param othProfile
	 * @return true or false
	 */
	virtual bool operator!=(const eoProfile &othProfile) const;

	/**
	 * All raw values of the internal Message will be set to zero.
	 */
	virtual void ClearValues();
	//virtual int LearnIn(uint8_t rorg, uint8_t func, uint8_t type);
	//virtual void LearnIn(Message m, Device d);
	/**
	 * \brief Generates an EEP Message
	 * \details This functions generates a Message for the specified EEP, with the current ChannelInfo values
	 * @param m Reference to the Message (will be cleared and generated new)
	 * @return ::eoReturn EO_OK,NOT_SUPPORTED,NOT_IMPLEMENTED
	 */
	virtual eoReturn Create(eoMessage &m);
	/**
	 * \brief Generates an EEP Telegram(only not chained supported!!1)
	 * \details This functions generates a Message for the specified EEP, with the current ChannelInfo values
	 * @param m Reference to the Message (will be cleared and generated new)
	 * @return ::eoReturn EO_OK,NOT_SUPPORTED,NOT_IMPLEMENTED
	 */
	virtual eoReturn CreateTeachIN(eoMessage &m);
	/**
	 *\brief Parses a msg using learned in Profile from Device
	 *\details This function will parse the Message msg using the Profile Specific data
	 * @param msg Message to parse
	 * @return ::eoReturn EO_OK,NOT_SUPPORTED,NOT_IMPLEMENTED
	 */
	virtual eoReturn Parse(const eoMessage &msg);
	/**
	 * \brief Gets the Value as Floating Point
	 * \details Using the ::CHANNEL_TYPE type information, this information gets the floating point value accordingly,
	 * 	if the Profile does not support the requested ::CHANNEL_TYPE NOT_SUPPORTED is returned,
	 * 	if the functions is not implemented for
	 * 	the chosen profile,  NOT_IMPLEMENTED is returned
	 * @param type ::CHANNEL_TYPE
	 * @param value Reference to floating point
	 * @return  ::eoReturn EO_OK,NOT_SUPPORTED,NOT_IMPLEMENTED
	 */
	//virtual uint8_t GetValue(uint8_t chanNumb,uint16_t &type, float &value);//?
	virtual eoReturn GetValue(CHANNEL_TYPE type, float &value);

	/**
	 * \brief Gets the Value as Floating point
	 * \details Using the ::CHANNEL_TYPE type information, this information gets the unsigned integer value accordingly,
	 * 	if the Profile does not support the requested ::CHANNEL_TYPE NOT_SUPPORTED is returned,
	 * 	if the functions is not implemented for
	 * 	the chosen profile,  NOT_IMPLEMENTED is returned
	 * @param type ::CHANNEL_TYPE
	 * @param value Reference to floating point
	 * @param subFlag Sub flag
	 * @return  ::eoReturn EO_OK,NOT_SUPPORTED,NOT_IMPLEMENTED
	 */
	virtual eoReturn GetValue(CHANNEL_TYPE type, float &value, uint8_t subFlag);
	/**
	 * \brief Gets the Value as unsigned integer
	 * \details Using the ::CHANNEL_TYPE type information, this information gets the unsigned integer value accordingly,
	 * 	if the Profile does not support the requested ::CHANNEL_TYPE NOT_SUPPORTED is returned,
	 * 	if the functions is not implemented for
	 * 	the chosen profile,  NOT_IMPLEMENTED is returned
	 * @param type ::CHANNEL_TYPE
	 * @param value Reference to uint8_t
	 * @param subFlag Sub flag
	 * @return  ::eoReturn EO_OK,NOT_SUPPORTED,NOT_IMPLEMENTED
	 */
	virtual eoReturn GetValue(CHANNEL_TYPE type, uint8_t &value, uint8_t subFlag);
	/**
	 * \brief Gets the Value as a float
	 * \details Using the ::CHANNEL_TYPE type information, this information gets the unsigned integer value accordingly,
	 * 	if the Profile does not support the requested ::CHANNEL_TYPE NOT_SUPPORTED is returned,
	 * 	if the functions is not implemented for
	 * 	the chosen profile,  NOT_IMPLEMENTED is returned
	 * @param type ::CHANNEL_TYPE
	 * @param value Reference to floating point
	 * @param subFlag Sub flag
	 * @return  ::eoReturn EO_OK,NOT_SUPPORTED,NOT_IMPLEMENTED
	 */
	virtual eoReturn SetValue(CHANNEL_TYPE type, float value, uint8_t subFlag);
	/**
	 * \brief Sets the Value using a unsigned integer
	 * \details Using the ::CHANNEL_TYPE type information, this information sets the channel raw value, using the floating point value accordingly,
	 * 	if the Profile does not support the requested ::CHANNEL_TYPE NOT_SUPPORTED is returned,
	 * 	if the functions is not implemented for
	 * 	the chosen profile,  NOT_IMPLEMENTED is returned
	 * @param type ::CHANNEL_TYPE
	 * @param value Reference to floating point
	 * @param value Reference to uint8_t
	 * @return  ::eoReturn EO_OK,NOT_SUPPORTED,NOT_IMPLEMENTED
	 */
	virtual eoReturn GetValue(CHANNEL_TYPE type, uint8_t &value);
	/**
	 * \brief Gets the Value as unsigned integer
	 * \details Using the ::CHANNEL_TYPE type information, this information gets the unsigned integer value accordingly,
	 * 	if the Profile does not support the requested ::CHANNEL_TYPE NOT_SUPPORTED is returned,
	 * 	if the functions is not implemented for
	 * 	the chosen profile,  NOT_IMPLEMENTED is returned
	 * @param type ::CHANNEL_TYPE
	 * @param value Reference to uint8_t
	 * @param subFlag Sub flag
	 * @return  ::eoReturn EO_OK,NOT_SUPPORTED,NOT_IMPLEMENTED
	 */
	virtual eoReturn SetValue(CHANNEL_TYPE type, uint8_t value, uint8_t subFlag);

	/**
	 * \brief Sets the Value using a Floating Point
	 * \details Using the ::CHANNEL_TYPE type information, this information sets the channel raw value, using the floating point value accordingly,
	 * 	if the Profile does not support the requested ::CHANNEL_TYPE NOT_SUPPORTED is returned,
	 * 	if the functions is not implemented for
	 * 	the chosen profile,  NOT_IMPLEMENTED is returned
	 * @param type ::CHANNEL_TYPE
	 * @param value Reference to floating point
	 * @return  ::eoReturn EO_OK,NOT_SUPPORTED,NOT_IMPLEMENTED
	 */

	virtual eoReturn SetValue(CHANNEL_TYPE type, float value);
	/**
	 * \brief Sets the Value using a uint8_t
	 * \details Using the ::CHANNEL_TYPE type information, this information sets the channel raw value, using  the uint8_t value accordingly,
	 * 	if the Profile does not support the requested ::CHANNEL_TYPE NOT_SUPPORTED is returned,
	 * 	if the functions is not implemented for
	 * 	the chosen profile,  NOT_IMPLEMENTED is returned
	 * @param type ::CHANNEL_TYPE
	 * @param value Reference to floating point
	 * @return  ::eoReturn ::EO_OK,NOT_SUPPORTED,NOT_IMPLEMENTED
	 */
	virtual eoReturn SetValue(CHANNEL_TYPE type, uint8_t value);
	/**
	 * Returns the channel for the selected type and subtype
	 * @param type CHANNEL_TYPE
	 * @param subType is either the numeric "subChannelNUmber" (temperature CHannel 0,1,2,3) or a specified keyword for it(see profile)
	 * @return Pointer to Channel
	 */
	virtual eoChannelInfo* GetChannel(CHANNEL_TYPE type, uint8_t subType);

	/**
	 * Returns the channel for the selected type
	 * @param type ::CHANNEL_TYPE
	 * @return Pointer to ChannelInfo or Null
	 */
	virtual eoChannelInfo* GetChannel(CHANNEL_TYPE type);

	/**
	 * returns the pointer to eoChannelInfo for the selected channelNumber or NULL
	 * @param channelNumber
	 * @return Pointer to Channel
	 */
	virtual eoChannelInfo* GetChannel(uint8_t channelNumber);


	/**
	 * Sets and checks if the specified [EEP] type is supported
	 * @param type
	 * @return ::eoReturn EO_OK or NOT_SUPPORTED
	 */

	virtual eoReturn SetType(uint8_t type);

	virtual uint8_t Serialize(eoArchive &a);
	/**
	 * Returns Number of channels for this profile
	 * @return number of channels
	 */
	virtual uint8_t GetChannelCount() const;

	/**
	 * Sets the manufacturer ID.
	 * @return ::eoReturn EO_OK or NOT_SUPPORTED
	 */
	eoReturn SetManufacturer (uint16_t manufacturerID);

private:

	static uint16_t BitIdxToByte(const uint16_t &bitIdx);	//! helper function to convert bits
protected:
	//char profileString[10];
	eoMessage msg;
	/**
	 * \brief Creates floating Point from Raw Value
	 * \details Converts the rawValue into a floating Point value, using the parameters and the formula specified in the [GP]<br>
	 * To get values use GetValue() ! <br>
	 * <b>!Warning this function does not check if the rawValue is in range!</b>
	 * @param rawValue rawValue to convert
	 * @param rangeMin maximal rawValue
	 * @param rangeMax minimal rawValue
	 * @param scaleMin minimal Value
	 * @param scaleMax minimal Value
	 * @return the Value as floating Point
	 */
	float ScaleFromRAW(uint32_t rawValue, uint32_t rangeMin, uint32_t rangeMax, float scaleMin, float scaleMax);
	/**
	 * \brief Creates Raw Value from a floating Point
	 * \details Converts the floating Point into a raw value, using the parameters and the formula specified in the [GP]<br>
	 * To set values use SetValue() ! <br>
	 * <b>!Warning this function does not check if the rawValue is in range!</b>
	 * @param value Floating Point to convert
	 * @param rangeMin maximal rawValue
	 * @param rangeMax minimal rawValue
	 * @param scaleMin minimal Value
	 * @param scaleMax minimal Value
	 * @return
	 */
	uint32_t ScaleToRAW(float value, uint32_t rangeMin, uint32_t rangeMax, float scaleMin, float scaleMax);
  
  //! Mask array  
	const static uint8_t maskArray[8];
	/**
	 * \brief Gives raw data Value from a Message
	 * \details Given the right position(offset) and the bitsize(size), this function gives the rawData Value from a message
	 * @param msg Message to use to get the rawValue
	 * @param value the rawValue
	 * @param offset position of the Data in the telegram
	 * @param size size of the data
	 * @return ::eoReturn
	 */
	static eoReturn GetRawValue(const eoMessage &msg, uint32_t &value, uint16_t offset, uint8_t size);

	/**
	 * \brief Inserts raw data Value in a message
	 * \details Given the right position(offset) and the bitsize(size), this function modifies the rawValue of a message
	 *(other information will not bet set!)
	 * @param msg Message to use to get the rawValue
	 * @param value the rawValue
	 * @param offset position of the Data in the telegram
	 * @param size size of the data
	 * @return ::eoReturn
	 */
	static eoReturn SetRawValue(eoMessage &msg, uint32_t &value, uint16_t offset, uint8_t size);

};
//static eoProfile emptyProfile = eoProfile(0);
/**
 * @}
 */
#endif // __EOPROFILE_INCLUDED_
