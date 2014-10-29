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

#ifndef _SECU_H_INCLUDED
#define _SECU_H_INCLUDED

#include "../eoHalTypes.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif

#include "sec_api.h"

/****************************Variables ***********************************/
//! \addtogroup sec_iglb_var_grp SECURITY global variables internal
//! Global variables called only by the API internally
//! \ingroup sec_grp
//@{	
//! Rolling code window. In the receiver module it sets the maximal difference between the received message rolling code and the expected rolling code  
extern uint32_t u32RLCwindow;
//@}	

/****************************Functions**********************************/

//! \addtogroup sec_ifn_grp SECURITY functions internal
//! Intern functions called only by the API intern
//! \ingroup sec_grp
//! @{

/************************************************************************************************************************//*!
 Performs decryption	using the AES 128 algorithm
 
 \param[in,out]	state	  			Pointer to the byte array containing the data to be decrypted. The decrypted data will be store in the same array
 \param[in]  	key	  				Pointer to the key array.
 \return 		-

 \note
 The length of the key array must be 16 bytes.

 \note
 Example:
 key (in)			 = 000102030405060708090a0b0c0d0e0f
 data encrypted  (in) = 69c4e0d86a7b0430d8cdb78070b4c55a
 data decrypted (out) = 00112233445566778899aabbccddeeff

 
 \sa sec_ARC4enc, sec_AES128dec
 **************************************************************************************************************************/
void sec_AES128dec(uint8_t *state, uint8_t *key);

/************************************************************************************************************************//*!
 Performs encryption	using the AES 128 algorithm
 
 \param[in,out]	state	  			Pointer to the byte array containing the data to be encrypted. The encrypted data will be store in the same array
 \param[in]  	key	  				Pointer to the key array.
 \return 		-

 \note
 The length of the key array must be 16 bytes.

 \note
 Example:
 key (in)			 = 000102030405060708090a0b0c0d0e0f
 data plain  (in) 	 = 00112233445566778899aabbccddeeff
 data encrypted (out) = 69c4e0d86a7b0430d8cdb78070b4c55a

 
 \sa sec_ARC4enc, sec_AES128dec
 **************************************************************************************************************************/
void sec_AES128enc(uint8_t *state, uint8_t *key);

/************************************************************************************************************************//*!
 Creates a cipher-based message authentication code (CMAC) 
 
 \param[in]		dataIn	  			Pointer to the byte array containing the data whose CMAC is to be calculated. 
 \param[in]  	dataInSize	  		Number of bytes in the array pointed by dataIn.
 \param[in]  	key	  				Pointer to the key array.
 \param[in]  	subKey1	  			Pointer to the subkey1 array.
 \param[in]  	subKey2	  			Pointer to the subkey2 array.
 \param[out]  	CMAC	  			Pointer to the CMAC array. The array must be 16 bytes long

 \return 		-

 \note
 The length of the key array must be 16 bytes.

 \note
 The CMAC algorithm is described under rfc 4493 (http://www.rfc-editor.org/rfc/rfc4493.txt)

 \note
 Take the first CMAC bytes generated by the function concatenated in this same order.

 
 \sa sec_AES128enc
 **************************************************************************************************************************/
uint8_t sec_createCMAC(uint8_t *dataIn, uint8_t dataInSize, uint8_t *key, uint8_t *subKey1, uint8_t *subKey2, uint8_t *CMAC);

/************************************************************************************************************************//*!
 Creates the subkeys needed for the CMAC algorithm 
 
 \param[in]  	key	  				Pointer to the key array.
 \param[out]  	subKey1	  			Pointer to the subkey1 array.
 \param[out]  	subKey2	  			Pointer to the subkey2 array.

 \return 		-

 \note
 The generated subkeys by this function are used as input by the sec_convertToNonsecure and sec_convertToNonsecure, where CMAC is to be calculated 
 Therefore, store the result of this function under the members pu8CMACsubkey1, pu8CMACsubkey2 of the SECU_TYPE type
 
 \note
 The algorithm performs, among other things, a AES128 encryption operation. 
 The key array length must be 16 bytes.

 \note
 The subkey creation algorithm is described under rfc 4493 (http://www.rfc-editor.org/rfc/rfc4493.txt)

 \note
 The subkey 1 is only required in the CMAC calculation of messages whose data is 16 bytes or a multiple of 16 bytes. 
 The subkey 2 is only required in the CMAC calculation of messages whose data is not a multiple of 16 bytes. 
 To calculate subKey2 the algorithm in the function requires to calculate first subKey1.

 
 \sa SECU_TYPE, sec_convertToNonsecure, sec_convertToSecure
 **************************************************************************************************************************/
void sec_createCMACSubkeys(uint8_t *key, uint8_t *subKey1, uint8_t *subKey2);

/************************************************************************************************************************//*!
 the function copy a number of maximal 4 byte lenght into a byte array with the MSB first. 
 
 \param[in]		number  	Number to copy in the array. 
 \param[in]  	size	  	Amount of significant bytes of the number.
 \param[out]  	array	  	Pointer to the array where the number is copied to.

 \return 		-

 \note
 The array must be at least as long as the parameter size. But not smaller. 

 \note
 The MSB of the number is copied in the array[0] byte.  

 
 \sa sec_RLCinc
 **************************************************************************************************************************/
uint8_t sec_convertToArray(uint32_t number, uint8_t size, uint8_t *array);

/************************************************************************************************************************//*!
 Copies an array containing a muti-byte number with MSB byte first into a 4-byte number. 
 
 \param[in]		array  		Array containing the number. 
 \param[in]  	size	  	Amount of significant bytes of the array.
 \param[out]  	number	  	Pointer to the number.

 \return 		-

 \note
 The array cannot contain more than 4 bytes.

 \note
 The array[0] byte is interpreted as the MSB of the number. 
 
 \note
 The resulted number representation is HW-platform independent.  


 
 \sa sec_RLCinc
 **************************************************************************************************************************/
uint8_t sec_convertToNumber(uint8_t *array, uint8_t size, uint32_t *number);

/************************************************************************************************************************//*!
 Encryption of a text using AES128 CBC method (http://en.wikipedia.org/wiki/Block_cipher_modes_of_operation). 
 
 \param[in]  	pTextIn	  		Pointer to the first element of the text to encrypt.
 \param[in]  	sizeIn	  		Amount of bytes of the text to encrypt.
 \param[in]  	pkey  			Pointer to the 16-byte AES128 key array.
 \param[out]  	pTextOut  		Pointer to the encrypted text.  
 \param[out]  	maxSizeOut  	Pointer to the encrypted text.
 \param[out]  	sizeOut			Amount of bytes of the encrypted text

 \return 		SEC_SIZE_WRONG	Not enough place to store the encrypted text 
 \return 		SEC_OK			Encryption performed 

 \note
 IMPORTANT:
 For sizeIn=16*i 	--> maxSizeOut must be at least equal to 16*i .
 For sizeIn=16*i + j --> maxSizeOut must be at least equal to 16*(i+1) .

 \note
 In case size of the text to encrypt, sizeIn, is 16*i + j, with j != 0 && j<16, the result is  16*(i+1) bytes long!.
 The plain text is concatenated with a padding bit sequence 100..0 to complete a 16*(i+1) array before AES CBC encryption. 

 \note
 pTextOut can be the same address as pTextIn

 
 \sa sec_decryptAESCBC
 **************************************************************************************************************************/
SEC_RESULT sec_encryptAESCBC(uint8_t *pTextIn, uint16_t sizeIn, uint8_t *pkey, uint8_t *pTextOut, uint16_t maxSizeOut, uint16_t *sizeOut);

/************************************************************************************************************************//*!
 Decryption of an encrypted text using AES128 CBC method (http://en.wikipedia.org/wiki/Block_cipher_modes_of_operation). 
 
 \param[in]  	pTextIn	  		Pointer to the first element of the encrypted text.
 \param[in]  	sizeIn	  		Amount of bytes of the text to decrypt.
 \param[in]  	pKey  			Pointer to the 16-byte AES128 key array.
 \param[out]  	pTextOut  		Pointer to the plain text.  
 \param[out]  	maxSizeOut  	Amount of byte of the array where the plain text will be stored.

 \return 		SEC_SIZE_WRONG	sizeIn != 16*i, or not enough place to store the plain text 
 \return 		SEC_OK			Decryption performed 

 \note
 pTextOut can be the same address as pTextIn
 
 \note
 sizeIn must be of the form 16*i. 	Otherwise the function returns 

 \note
 For sizeIn=16*i 	--> maxSizeOut must be at least equal to 16*i .
 For sizeIn=16*i + j --> maxSizeOut must be at least equal to 16*(i+1) .

 
 \sa sec_decryptAESCBC
 **************************************************************************************************************************/
SEC_RESULT sec_decryptAESCBC(uint8_t *pTextIn, uint16_t sizeIn, uint8_t *pKey, uint8_t *pTextOut, uint16_t maxSizeOut);

/************************************************************************************************************************//*!
 Performs the difference between rolling code receive and rolling code expected. 
 
 \param[in]  	RLCrecv	  			Rolling code received in the message.
 \param[in]  	RLCexpect	  		Rolling code expected to be received.
 \param[in]  	RLCsizeCode	    Number of rolling code bytes.

 \return 		RLCdiff				RLCrecv - RLCexpect

 \note
 The function takes into account the number of rolling code bytes. 

 \note
 In case the value RLCsize is not 2 or 3 the function returns RLCdiff = 0xFFFFFFFF

 
 \sa sec_inc_RLC
 **************************************************************************************************************************/
uint32_t sec_RLCdiff(uint32_t RLCrecv, uint32_t RLCexpect, uint8_t RLCsizeCode);

/************************************************************************************************************************//*!
 Increments the RLC in 1 value. 
 
 \param[in,out]	RLC	  				Pointer to the rolling code to increment. 
 \param[in]  	RLCsize	  			Number of bytes of the RLC.

 \return 		-

 \note
 the functions clears the RLC when the RLC value is the maximum.

 \note
 Valid RLCsize values are 1, 2, 3 and 4. Other sizes are treated by the function as size 4. 

 \note
 The RLC pointer points to a number that is stored in 4 bytes, not an array of bytes. 
 To increment the RLC the user does not have to care about endianness.

 
 \sa sec_VAES128
 **************************************************************************************************************************/
void sec_RLCinc(uint32_t *RLC, uint8_t RLCsize);

/************************************************************************************************************************//*!
 Adds the bit sequence 10...0 to a byte array to complete a 16-byte array 
 
 \param[in]		array  				Pointer to the array whose bits are c. 
 \param[in]  	size				Amount of bytes in the array.
 \param[out]  	_16BytePadding		Pointer to the 16-byte array containing the input array plus the concatenated 10..0 bit sequence.

 \return 		-

 \note
 Maximal amount of bytes in the array is 15.

 \note
 Example.
 array[2]= 0x3479 --> _16BytePadding[16] =	0x34798000000000000000000000000000
 The hex. 8 after 79 contains the bit sequence 1000
 
 \sa sec_createCMACSubkeys
 **************************************************************************************************************************/
void sec_paddingTo16Bytes(uint8_t *array, uint8_t size, uint8_t *_16BytePadding);

/************************************************************************************************************************//*!
 Shifts all bits from an array to the "left". 
 
 \param[in,out]	array  		Pointer to the array whose bit are going to be shifted. 
 \param[in]  	size		Number of byte in the array.

 \return 		-

 \note
 Maximal amount of bytes in the array is 255.

 \note
 Shifting to the left means moving bits from its bit position to the next more significant bit position.

 
 \sa sec_createCMACSubkeys
 **************************************************************************************************************************/
void sec_shiftLinks(uint8_t *array, uint8_t size);

/************************************************************************************************************************//*!
 Swaps two bytes. 
 
 \param[in,out]		a  		Byte 1 to swap. 
 \param[in,out]  	b	  	Byte 2 to swap.
 \param[in]  	    temp	Temporal byte container.

 \return 		-

 
 \sa sec_ARC4creatKeystream
 **************************************************************************************************************************/
#define sec_swapBytes(a, b, temp)  	{ temp = a; a = b; b = temp; }

/*	#define sec_swapBytes(a, b, temp)  					a ^= b;    \
														b ^= a;	 \ 
 a ^= b; \
*/
/************************************************************************************************************************//*!
 Performs decryption	using the VAES algorithm
 
 \param[in]  	dataIn	  			Pointer to the byte array with the data to be decrypted.
 \param[in]  	dataInSize	  		Number of bytes to be decrypted. The maximal length is 16 bytes
 \param[in]  	RLC	  				Number of bytes in Data In array
 \param[in]  	RLCsize	  			Number of bytes in Data In array
 \param[in]  	key	  				Number of bytes in Data In array
 \param[out]  	dataOut	  			Pointer to a byte array with the data decrypted. The length of the decrypted data is dataInSize
 \return 		-

 \note
 The VAES algorithm requires of a correct rolling code to decrypt correctly the encrypted information contained in dataIn.
 
 \sa sec_ARC4enc, sec_AES128dec
 **************************************************************************************************************************/
#define sec_VAES128dec(dataIn, dataInSize, RLC, RLCsize, key, dataOut) 	sec_VAES128(dataIn, dataInSize, RLC, RLCsize, key, dataOut)

/************************************************************************************************************************//*!
 Performs encryption	using the VAES algorithm
 
 \param[in]  	dataIn	  			Pointer to the byte array with the data to be encrypted.
 \param[in]  	dataInSize	  		Number of bytes to be encrypted. The maximal length is 16 bytes
 \param[in]  	RLC	  				Rolling code value to be used when encrypting the information
 \param[in]  	RLCsize	  			Number of bytes in the rolling code
 \param[in]  	key	  				Pointer to the key
 \param[out]  	dataOut	  			Pointer to a byte array with the data decrypted. The length of the decrypted data is dataInSize
 \return 		-

 \note
 The VAES algorithm requires of a rolling code to vary the output (encrypted data), although the input data is constant.

 \note
 The key must be 16 bytes long

 
 \sa sec_ARC4enc, sec_AES128enc
 **************************************************************************************************************************/
#define sec_VAES128enc(dataIn, dataInSize, RLC, RLCsize, key, dataOut) 		sec_VAES128(dataIn, dataInSize, RLC, RLCsize, key, dataOut)

/************************************************************************************************************************//*!
 Variable length AES encryption/depcryption core algorithm.  
 
 \param[in]  	dataIn	  			Pointer to the data to encrypt or decrypt.
 \param[in]  	dataInSize		  	Amount of data bytes.
 \param[in]  	RLC  				Pointer to the most significant byte of the rolling code.
 \param[in]  	RLCsize  			Rolling code size in bytes.
 \param[in]  	key  				Pointer to the key.
 \param[in]  	dataOut  			Pointer to the encrypted/decrypted result.

 \return 		-

 \code
 -------------------
 | Constant-16-byte |
 -------------------
 |
 V
 ------      ----
 | RLC |---->| + |
 ------	  ----
 |
 V
 ------   -------------		 
 | key |->| AES128 ENC |
 ------   -------------		 
 |
 V
 ----------   ----
 | Data In |->| + |
 ----------	  ----
 |
 V
 -----------
 | Data Out |
 -----------
 \endcode	

 \note
 Although the Data In is constant, Data Out changes value since the rolling code (RLC) changes. 

 \note
 + operation indicates a bitwise XOR between bytes of same index within arrays. 

 \note
 The algorithm adds so many 0x00 bytes to the rolling code (RLC) as necessary to make a 16-byte array. 
 Example: RLC = 0xfedc  --> 	RLC = 0xfedc0000000000000000000000000000

 \note
 Constant-16-byte array in hexadecimal = 3410de8f1aba3eff9f5a117172eacabd

 \note
 The key is 16 bytes long
 
 \note
 The Data Out has the same length as Data in. 
 From the last XOR operation, only the bytes resulted from the XOR with Data In are taken to produce Data Out 

 \note
 The function writes the secure message choice under  mssgeSecure->u8Choice

 \note
 The application can provide the same array for Data In and Data Out to save memory resources. 
 In this case, the function will overwrite the Data In information and generate in its place Data Out. 

 
 \sa sec_AES128enc, sec_XOR
 **************************************************************************************************************************/
void sec_VAES128(uint8_t *dataIn, uint8_t dataInSize, uint8_t *RLC, uint8_t RLCsize, uint8_t *key, uint8_t *dataOut);

/************************************************************************************************************************//*!
 Bitwise XOR between bytes of two arrays. 
 
 \param[in]  	a	  		Pointer to first byte array.
 \param[in]  	b	  		Pointer to second byte array.
 \param[in]  	length  	Amount of bytes to XOR.
 \param[out]  	result  	Pointer to the result of the XOR operation.

 \return 		-

 \note
 The pointer to result can have the same address as the pointer to a or b arrays.
 In this case, the values stored in the source array will be overwritten by the generated result.
 
 \note
 The length value must be equal or smaller than the smallest array. The length parameter can not be bigger than (2^16)-1

 \note
 The array pointed to by result must have at least the size of the parameter length.

 
 \sa sec_VAES128, sec_ARC4dec, sec_ARC4enc
 **************************************************************************************************************************/
void sec_XOR(uint8_t *a, uint8_t *b, uint16_t length, uint8_t *result);

//!}@

#ifdef __cplusplus
}
#endif

#endif
