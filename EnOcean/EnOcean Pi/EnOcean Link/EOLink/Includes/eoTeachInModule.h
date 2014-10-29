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
 * \file eoTeachInModule.h
 * \brief
 * \author EnOcean GmBH
 */
#ifndef EO_TEACH_IN_MODULE_H_
#define EO_TEACH_IN_MODULE_H_
#include "eoHalTypes.h"
#include "eoMessage.h"
#include "eoDevice.h"
class eoDeviceManager;

#include <map>

//! Teach message structure.
typedef struct
{
     //! Teached in
	bool teachedIN;
} TEACH_STRUCT;

//! Teach process return codes.
typedef enum
{
	//! <b>0</b> -Tried to add an object with the same name, which differ!
	NO_TEACH_IN = 0,         //!< NO_TEACH_IN
	//! <b>1</b> -Added a new device
	NEW_DEVICE,             //!< NEW_DEVICE
	//! <b>2</b> - EEP teach in has been set
	EEP_TEACH_IN,           //!< EEP_TEACH_IN
	//! <b>3</b>- EEP teach in and new Device
	NEW_DEVICE_AND_EPP,     //!< NEW_DEVICE_AND_EPP
	//! <b>4</b>- SECURITY Teach IN
	SECURITY_TEACH_IN,      //!< SECURITY_TEACH_IN
	//! <b>5</b>- RECEIVED A SECOND TEACH IN
	SECOND_TEACH_IN,        //!< SECOND_TEACH_IN
} TEACH_RETURN;

//!UTE Response codes.
typedef enum
{
	//! <b>0</b> - Request not accepted because of general reason
	GENERAL_REASON		 = 0,         //!< GENERAL_REASON
	//! <b>1</b> - Request accepted, teach-in successful
	TEACH_IN_ACCEPTED	 = 1,         //!< TEACH_IN_ACCEPTED
	//! <b>2</b> - Request accepted, deletion of teach-in successful
	TEACH_OUT_ACCEPTED 	= 2,         //!< TEACH_OUT_ACCEPTED
	//! <b>3</b> - Request not accepted, EEP not supported
	EEP_NOT_SUPPORTED	 = 3,         //!< EEP_NOT_SUPPORTED
} UTE_RESPONSE;

//!UTE Direction response codes.
typedef enum
{
	//! <b>0</b> - Unidirectional
	UTE_DIRECTION_UNIDIRECTIONAL		 = 0,         //!< UTE_DIRECTION_UNIDIRECTIONAL
	//! <b>1</b> - Bidirectional
	UTE_DIRECTION_BIDIRECTIONAL			 = 1,         //!< UTE_DIRECTION_BIDIRECTIONAL
} UTE_DIRECTION;

//! Map type definition for teached devices.
typedef std::map<uint32_t, TEACH_STRUCT> teach_id_map;
/**
 * \ingroup gateway
 * @{
 */
/**
 * \class eoTeachInModule
 * \brief handles TeachIn Messages
 * \details a helper class to handle EEP Teach-IN as specified.
 */
class eoTeachInModule
{

public:
	/**
	 *	Standard constructor for the TeachInModule
	 * @param eoDevManager eoDeviceManager
	 * @param sec security Module to use to handle security Messages
	 */
	eoTeachInModule(eoDeviceManager *eoDevManager);
	virtual ~eoTeachInModule();

	/**
	 * Allows you to set the manual RPS EEP to use
	 * @param func
	 * @param type
	 */
	void SetRPS(uint8_t func, uint8_t type);
	/**
	 * Allows you to set the manual 1BS EEP to use
	 * @param func
	 * @param type
	 */
	void Set1BS(uint8_t func, uint8_t type);
	/**
	 * Allows you to set the manual 4BS EEP to use
	 * @param func
	 * @param type
	 */
	void Set4BS(uint8_t func, uint8_t type);
	/*
	 * \brief handles Teach IN
	 * \details
	 * If the sourceID of the telegram is not in the device manager, a new device will be created.
	 * Afterwards the telegram is parsed, and if a teach-in message(as specified in EEP 2.1 ) is received,
	 * the profile will be set in the Device Manager accordingly.
	 * If a second TeachIN is received, SECOND_TEACH_IN will be returned.
	 * @param telegram
	 * @return ::TEACH_RETURN  NO_TEACH_IN,NEW_DEVICE , SECOND_TEACH_IN, NEW_DEVICE_AND_EPP, EEP_TEACH_IN
	 */
	//TEACH_RETURN TeachIN(eoTelegram &telegram);
	/**
	 * \brief handles Security Teach IN
	 * \details
	 * Handles security TEACH IN
	 * @param m
	 * @return ::TEACH_RETURN NO_TEACH_IN or SEC_TEACH_IN
	 */
	TEACH_RETURN TeachIN(eoMessage &m);

	/**
	 * Removes all saved information about a device
	 * @param id Device ID
	 */
	void TeachOut(uint32_t id);
	/**
	 * Returns True if it is a teach IN telegram for 4BS or 1BS
	 * @param telegram to check
	 * @return true or false
	 */
	static bool isTeachIN(eoMessage &telegram);
	/**
	 * Checks if the device belonging to the Message is teached IN
	 * @param telegram
	 * @return true or false
	 */
	 bool isTeachedIN(eoMessage &telegram) ;
	/**
	 * Checkes if the device is Teached IN
	 * @param dev device to check
	 * @return true or false
	 */
	 bool isTeachedIN(eoDevice &dev) ;                     
	/**
	 * Parse the message into UTE
	 * @param msg
	 * @return EO_OK
	 */
	 eoReturn ParseUTE (eoMessage &msg);           
	/**
	 * Creates UTE teach in response from UTE teach in request
	 * @param teachInUTE
	 * @param [out] responseUTE
	 * @param type ::UTE_RESPONSE
	 * @param direction ::UTE_DIRECTION     	 
	 * @return EO_OK
	 */
	 eoReturn CreateUTEResponse (eoMessage &teachInUTE, eoMessage &responseUTE, UTE_RESPONSE type, UTE_DIRECTION direction);
private:
	teach_id_map teachInformation;
	eoDeviceManager * deviceManager;
	uint8_t rps_func, rps_type, bs1_func, bs1_type, bs4_func, bs4_type, ute_rorg, ute_func, ute_type;

};
/**
 * @}
 */
#endif // !defined(EA_62DB5BA2_ABF0_41c3_9291_81B05C9C37AD__INCLUDED_)
