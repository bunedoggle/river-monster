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
#ifndef _SECUAPI_H_INCLUDED
#define _SECUAPI_H_INCLUDED

#include "../eoHalTypes.h"
#include "../eoApiDef.h"
#include <stdio.h>

/*********************************************************************************************/
/************************  MESSAGE TRANSMISSION DEFINES AND PROTOTYPES ***********************/
/*********************************************************************************************/
/*!
 \addtogroup msg_grp  msg
 The message module allows to send longer radio message by using telegram chaining functionality.
 \ingroup ESSL
 */

//! @addtogroup msg_cfg_grp Message module structures
//! Message structures.
//! \ingroup msg_grp
//! @{
//! Message Type
typedef struct
{
	//! Message type.
	uint8_t u8Choice;
	//! Source ID
	uint32_t u32SourceId;
	//! The length of the u8Data
	uint16_t u16Length;
	//! The maximal length of the u8Data
	uint16_t u16MaxLength;
	//! Data buffer
	uint8_t *u8Data;
} MESSAGE_TYPE;

//! Message Module Parameters
typedef struct
{
	//! Maximal time between two radio telegrams in chain [ms]. Default = 100
	uint16_t u16ReceiveTimeout;
	//! Delay between two send radio telegrams in [ms]. Default = 40 ms
	uint16_t u16SendDelay;
} MESSAGE_PARAM;
//! @}

/*********************************************************************************************/
/************************************ SECURITY MODULE *******************************************/
/*********************************************************************************************/
/*! 
 \addtogroup sec_grp sec
 Security module. The module's functions are responsible for the encryption, decryption, authentication of messages.
 Several encryption algorithms like AES128 and ARC4 can be used. 
 Rolling code strategy is also included to avoid replay attacks.\n\n

 A detail description of the security protocol and secure strategies implemented can be read under http://www.enocean.com/en/knowledge-base/
 \ingroup ESSL
 */

//! @addtogroup sec_struct_grp Secure module structures	and constants
//! Data structures and constant values that are used in SECURITY module
//! \ingroup sec_grp 
//! @{

//! Amount of bytes of the CMAC subkeys
#define  CMAC_SUBKEY_SIZE			16

//!	\name teach-in info byte bit masks
//! @{
//! INFO field bit mask in teach-in info byte
#define  TEACH_IN_TYPE_MASK	0x0C
//! INFO field bit mask in teach-in info byte
#define  TEACH_IN_INFO_MASK	0x03
//! @} 

//!	\name Teach-in info byte fields values
//! @{
//! Non-specific type identification 
#define  TEACH_IN_TYPE_NON_SPEC	0x00
//! PTM type identification 
#define  TEACH_IN_TYPE_PTM		0x04
//! PTM info first rocker 
#define  TEACH_IN_INFO_ROCKER_A	0x00
//! PTM info second rocker 
#define  TEACH_IN_INFO_ROCKER_B	0x01
//! @}

//!	\name SLF byte bit masks
//! @{
//! Rolling code algorithm identification bit mask in SLF byte
#define  SLF_RLC_ALGO_MASK	0xC0
//! Rolling code send/not send bit mask in SLF byte
#define  SLF_RLC_TX_MASK	0x20
//! Message authentication code identificator bit mask in SLF byte.
#define  SLF_MAC_ALGO_MASK	0x18
//! Encryption identificator bit mask.
#define  SLF_DATA_ENC_MASK	0x07
//! @} 

//!	\name SLF byte fields values
//! @{
//! No rolling code identification code 
#define  SLF_NO_RLC_ALGO	0x00
//! 16-bit rolling code identification code 
#define  SLF_RLC_16_BIT		0x40
//! 24-bit rolling code identification code 
#define  SLF_RLC_24_BIT		0x80
//! Not sending rolling code in telegram identification code 
#define  SLF_RLC_TX_NO		0x00
//! Sending rolling code in telegram identification code 
#define  SLF_RLC_TX_YES		0x20
//! No athentication in telegram identification code 
#define  SLF_MAC_NO			0x00
//! 3-byte MAC identification code
#define  SLF_MAC_3_AES128	0x08
//! 4-byte MAC identification code
#define  SLF_MAC_4_AES128	0x10
//! No encryption identification code
#define  SLF_ENC_NO			0x00
//! ARC4 encryption identification code
#define  SLF_ENC_ARC4		0x02
//! Variable AES128  encryption identification code
#define  SLF_ENC_VAES128	0x03
//! AES128  encryption identification code
#define  SLF_ENC_AES128		0x04
//! @} 

//!Security module function return values.
typedef enum
{
	SEC_OK = 0,				//!< function correctly executed.
	SEC_RLC_OUT_OF_RANGE,		//!< Received rolling code out of range.
	SEC_SIZE_WRONG,	//!< One of the parameters had a not permitted amount of bytes.
	SEC_CMAC_WRONG,				//!< Received and expected CMAC do not match.
	SEC_CHOICE_WRONG,			//!< Message choice not valid.
	SEC_ENC_WRONG,			//!< Encryption method code in SLF byte not allowed.
	SEC_SLF_WRONG,				//!< Not valid SLF code.

} SEC_RESULT;

//!Security information structure.
typedef struct
{
	uint8_t u8TeachInInfo;//!< Teach-in info byte : | 4: RESERVED | 2: TYPE | 2: INFO |. Typically initialised by calling #sec_parseTeachIn function after reception of a teach-in radio message.											
	uint8_t u8SLF;//!< Security layer format byte : | 2: RLC_ALGO | 1: RLC_TX | 2: MAC_ALGO | 3: DATA_ENC |. Typically initialised by calling #sec_parseTeachIn function after reception of a teach-in radio message.
	uint32_t u32RLC;//!< Rolling code value. Typically initialised by calling #sec_parseTeachIn function after reception of a teach-in radio message.
	uint8_t u8Key[16];//!< Encryption/decryption key. Typically initialised by calling #sec_parseTeachIn function after reception of a teach-in radio message.  
	uint8_t u8KeySize;//!< Size of the key in bytes. Typically initialised by calling #sec_parseTeachIn function after reception of a teach-in radio message.
	uint8_t u8CMACsubkey1[16];//!< Subkey1 for the CMAC calculation. Typically initialised by calling #sec_parseTeachIn function after reception of a teach-in radio message.										
	uint8_t u8CMACsubkey2[16];//!< Subkey2 for the CMAC calculation. Typically initialised by calling #sec_parseTeachIn function after reception of a teach-in radio message.										

} SECU_TYPE;

//! @}

//! @addtogroup sec_fn_grp Secutity functions
//! Functions used for secure communication
//! \ingroup sec_grp
//! @{

/************************************************************************************************************************//*!
 Sets all the security module parameters
 
 \param[in]  	*pReserved	  			Reserved, can be NULL.
 \param[in]  	RLCwindow	  			In the receiver module, it sets the maximal difference between the received message rolling code and the expected rolling code  
 \return 		-
 
 \note
 A small RLCwindow value increases the security by narrowing the amount of rolling codes that the receiver will test before invalidating a message. 
 On the other hand it increases the risk of desynchronisation between sender and receiver in the event of sender activations without the receiver "listening" to these messages. 
 

 \sa sec_convertToNonsecure, sec_convertToSecure
 **************************************************************************************************************************/
void sec_init(uint8_t *pReserved, uint32_t RLCwindow);

/************************************************************************************************************************//*!
 Transforms a secure message into a non-secure message, decrypting the information, checking the CMAC and the rolling codes if necesssary. 
 
 \param[in]  	mssgeSecure	  			Pointer to the secure message.
 \param[out]  	mssgeNonsecure	  		Pointer to the non-secure message.
 \param[in]  	secuInfo  				Pointer to the security information structure.

 \return 		SEC_OK					Function exited correctly.
 \return 		SEC_SIZE_WRONG	    	Some of the input information contains non-valid length
 \return 		SEC_RLC_OUT_OF_RANGE	The received rolling code and the expected rolling code differ in a value bigger than the rolling code window. See #sec_init
 \return			SEC_CMAC_WRONG			The received message contains a wrong CMAC
 \return 		SEC_ENC_WRONG			Wrong encryption method code in the SLF byte.


 \note
 Under mssgeNonsecure->u8Data can be found the decrypted data. This data does include neither rolling code nor CMAC

 \code
 mssgeSecure->u8Data*			     mssgeNonsecure->u8Data
 |--------------|----------|----------|       |----------|        
 |	data_enc  |    rlc   |   CMAC 	|  -->	|	data   |     				
 |--------------|----------|----------|       |----------|
 *The information rlc and CMAC under mssgeSecure->u8Data is optional. 
 The encryption of data, data_enc, is also optional.
 The figure shows simply the most general case of securing information.
 \endcode

 \note
 #SECU_TYPE  secuInfo input parameter provides information about the secure message, such as the encryption method, the presence and amount of CMAC bytes, as well as rolling code and amount of bytes.
 With this information the function checks and decrypts the secure message.

 \note
 The function reports through the return value if the secure message contains a wrong authentication code (CMAC) or the received rolling code is out of range.

 \note 
 When the received mssgeSecure.u8Choice field is #RADIO_CHOICE_SEC, mssgeSecure->u8Data does not contain the non-secure message choice. This allows saving energy when sending. The mssgeNonsecure->u8Choice returned by the function is	a general #RADIO_CHOICE_NON_SEC.
 When the received mssgeSecure.u8Choice field is #RADIO_CHOICE_SEC_ENCAPS, the mssgeSecure->u8Data includes the Choice of the original plain message. 
 The returned mssgeNonsecure->u8Choice contains the original non-secure choice.  The returned mssgeNonsecure->u8Data	does not include the non-secure choice. Therefore the length of data = data_enc - 1. 

 \note 
 The function uses the CURRENT rolling code stored under secuInfo->u32RLC for the processing of the mssgeSecure.
 When the result of the function is OK, the rolling code value stored under secuInfo->u32RLC is +1 the rolling code in the received radio message.

 \note 
 The function handles the arithmetic overflow of the rolling code. 
 The user does not have to implement additional code to set the rolling value to 0 after the rolling code reaches its maximal value.

 \note
 In the case of variable AES encryption (VAES) the data_enc field can not be longer than 16 bytes.

 \code

 TEL_RADIO_TYPE      rTel;
 TEL_PARAM_TYPE      pTel;
 MESSAGE_TYPE        pMsgSec, pMsgNonSec;
 SECU_TYPE			secuInfo;
 uint8_t               u8MsgBuffer[32];


 pMsgSec.u8Data           = u8MsgBuffer;
 pMsgNonSec.u8Data        = u8MsgBuffer;		 	// The address where non-secure data will be stored can be the same as the array for the secure information...
 pMsgSec.u16MaxLength     = sizeof(u8MsgBuffer);	// ...if RAM space is a concern
 pMsgNonSec.u16MaxLength  = sizeof(u8MsgBuffer);
 
 
 mainInit(); 

 radio_enableRx(1);

 
 while(1)
 {           
 CLR_WDT();
 
 memset(&rTel, 0x00, sizeof(rTel));
 if ((radio_getTelegram(&rTel, &pTel) == OK)         &&
 (msg_receive(&pMsgSec, &pTel, &rTel, &pTel) == OK))
 {
 // Secure teach-in telegram received?
 if(pMsgSec.u8Choice == RADIO_CHOICE_SEC_TI)
 {
 sec_parseTeachIn(&pMsgSec, &secuInfo);			// The details of the encryption, authentication and rolling code are stored in secuInfo
 }
 // Secure telegram in operation mode?
 else if(pMsgSec.u8Choice == RADIO_CHOICE_SEC_ENCAPS || 
 pMsgSec.u8Choice == RADIO_CHOICE_SEC			)
 {
 // The non-encrypted information is stored in pMsgNonSec.u8Choice and pMsgNonSec.u8Data. 
 // You may check the return value of the function to be sure that the received mssgeSecure contains correct rolling code and correct authentication CMAC
 sec_convertToNonsecure(&mssgeSecure, &pMsgNonSec, &secuInfo);
 }
 }  
 }
 \endcode     
 
 \sa sec_convertToSecure
 **************************************************************************************************************************/
SEC_RESULT sec_convertToNonsecure(MESSAGE_TYPE *mssgeSecure, MESSAGE_TYPE *mssgeNonsecure, SECU_TYPE *secuInfo);

/************************************************************************************************************************//*!
 Transforms a non-secure message into a secure message, encrypting the information, adding a CMAC and a rolling codes if necesssary. 
 
 \param[in]  	mssgeNonsecure	  	Pointer to the non-secure message.
 \param[out]  	mssgeSecure		  	Pointer to the secure message.
 \param[in]  	secuInfo  			Pointer to the security information structure.

 \return 		SEC_OK					Function exited correctly.
 \return 		SEC_CHOICE_WRONG		Secure telegrams can not be encrypted again.
 \return 		SEC_SIZE_WRONG	    	Some of the input information contains non-valid length
 \return 		SEC_ENC_WRONG			Wrong encryption method code in the SLF byte.

 \note
 Under mssgeSecure->u8Data can be found the encrypted data, rolling code and CMAC.
 
 \code
 mssgeNonsecure->u8Data					  mssgeSecure->u8Data*
 |----------|		    |--------------|----------|----------|                           
 |	data   |	-->	    |	data_enc   |    rlc   |   CMAC 	 |                        				
 |----------|		    |--------------|----------|----------|                
 *the information rlc and CMAC under mssgeSecure->u8Data	are optional. The encryption of data, data_enc, is also optional.
 The figure shows simply the most general case of securing information.
 \endcode

 \note
 In the case the non-secure message choice field is equal to #RADIO_CHOICE_NON_SEC the non-secure data is used as payload for the calculation of data_enc. In this case the mssgeSecure->u8Choice is #RADIO_CHOICE_SEC   
 In the case the non-secure message choice field is not #RADIO_CHOICE_NON_SEC, the function concatenates the non-secure choice byte to the data field for the calculation of data_enc.
 Therefore, the length of data_enc = length of data + 1. Where 1 is the length of the mssgeNonsecure choice.	The mssgeSecure->u8Choice returned by the function is #RADIO_CHOICE_SEC_ENCAPS

 \note
 The data_enc field length for VAES algorithm can not be bigger than 16 bytes.

 \note
 secuInfo provides the information of what encryption method is to be used, the presence and amount of CMAC bytes, as well as rolling code presence and amount of bytes.
 According to this information the function creates the secure message.

 \note
 The function uses the CURRENT rolling code stored under secuInfo->u32RLC for the processing of the mssgeSecure.
 Afterwards the function increments the rolling code.
 After the function returns, the rolling code value under secuInfo->u32RLC is +1 than the rolling code used for the message.   

 \note 
 The function handles the arithmetic overflow of the rolling code. 
 The user does not have to implement additional code to set the rolling value to 0 after the rolling code reaches its maximal value.

 \note
 Secure PTM telegram can only be performed when the encryption method is set to VAES. Secure PTM message are 1 data byte long. 
 The 4 most significant bits of the data byte will be cleared by the function.


 \code
 MESSAGE_TYPE 	msgNonSec, msgSec;
 SECU_TYPE 		secuInfo;
 uint8_t			u8Buff[5] = {0x00, 0x01, 0x02, 0x03};
 uint8_t			u8BuffSec[11] ;  Choice(1) + Data(4) + RLC(3) + CMAC(3) bytes stored in this buffer.  


 mainInit(); 

 secuInfo.u8SLF 	= SLF_RLC_TX_NO + SLF_RLC_24_BIT + SLF_MAC_3_AES128 + SLF_ENC_VAES128;	  // Defines protocol

 msgNonSec.u8Data 		= u8Buff;					
 msgSec.u8Data 			= u8BuffSec;				
 msgNonSec.u8Choice 		= RADIO_CHOICE_4BS;
 msgNonSec.u16Length 	= sizeof(u8Buff) ;    	
 msgSec.u16MaxLength  	= sizeof(u8BuffSec);		

 secuInfo.u8SLF 	= SLF_RLC_TX_NO + SLF_RLC_24_BIT + SLF_MAC_3_AES128 + SLF_ENC_VAES128;
 secuInfo.u32RLC = 0x00000001;

 sec_convertToSecure(&msgNonSec, &msgSec, &secuInfo);

 while(1)
 {
 CLR_WDT();
 }

 \endcode 
 
 
 \sa sec_convertToNonsecure
 **************************************************************************************************************************/
SEC_RESULT sec_convertToSecure(MESSAGE_TYPE *mssgeNonsecure, MESSAGE_TYPE *mssgeSecure, SECU_TYPE *secuInfo);

/************************************************************************************************************************//*!
 Creates a security teach-in message. 
 
 \param[in]  	secuInfo  				Pointer to the security information structure.
 \param[out]  	teachInMsg	  			Pointer to the non-secure message.

 \return 		SEC_OK					Function exited correctly.
 \return 		SEC_SIZE_WRONG	    	Not enough space in the teachInMsg to place the information. 
 
 \note
 The function reads the information in the SLF byte

 \note
 secuInfo contains all the information about the secure message such as the encryption method, the presence and amount of CMAC bytes, as well as rolling code presence and amount of bytes, and key.
 With this information the function creates the secure teach-in message.	See within #msg_send, the teach-in message example, for a description of the teach-in message structure. 

 \note
 The current rolling code stored under the #SECU_TYPE structure is sent. The rolling code stored in #SECU_TYPE is not incremented.

 \note
 The function assigns the choice code #RADIO_CHOICE_SEC_TI to the teachInMssge->u8Choice field.

 
 \sa sec_createCMAC, sec_AES128enc
 **************************************************************************************************************************/
SEC_RESULT sec_createTeachIn(SECU_TYPE *secuInfo, MESSAGE_TYPE *teachInMsg);

/************************************************************************************************************************//*!
 From a received secure teach-in message the function generates the information for the SECU_TYPE structure. 
 
 \param[in]  	teachInMsg	  		Pointer to the non-secure message.
 \param[out]  	secInfo  			Pointer to the security information structure.

 \return 		SEC_CHOICE_WRONG	Message choice value not #RADIO_CHOICE_SEC_TI
 \return 		SEC_SIZE_WRONG		Some of the message fields contain wrong size information
 \return 		SEC_OK				Message correctly parse. Security information is now in secInfo.

 
 \note
 This function is typically implemented by the receiver. 
 The structure of type SECU_TYPE contains the necessary information (such as the key, encryption method, etc) for the decoding of received secure telegrams.
 See within the #msg_send function the teach-in message example for a description of the teach-in message structure.

 \note 
 The rolling code stored under the #SECU_TYPE structure is the expected rolling code to be received from the sender.

 
 \sa sec_createTeachIn, sec_AES128enc
 **************************************************************************************************************************/
SEC_RESULT sec_parseTeachIn(MESSAGE_TYPE *teachInMsg, SECU_TYPE *secInfo);

//! @}

#endif
