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
 * \file eoConverter.h
 * \brief different converter
 * \author EnOcean GmBH
 */
#if !defined(_EOCONVERTER_H_)
#define _EOCONVERTER_H_

#include "eoHalTypes.h"
#include "eoMessage.h"
#include "eoTelegram.h"
#include "eoPacket.h"
#include "eoApiDef.h"
/**
 * \class eoConverter
 * \brief contains static Helper Functions
 */
class eoConverter
{
public:
	/**
	 * Helper function, which will convert a Telegram to a Packet
	 * @param tel Telegram to convert
	 * @param packet Packet to store
	 * @return ::eoReturn
	 */
	static eoReturn radioToPacket(const eoTelegram &tel, eoPacket &packet); 
	/**
	 * Helper function, which will convert a Message to a Packet
	 * @param msg Message to convert
	 * @param packet Packet to store
	 * @return ::eoReturn
	 */
	static eoReturn radioToPacket(const eoMessage &msg, eoPacket &packet);
	/**
	 * Helper function, which will convert a Packet to a Telegram
	 * @param packet Packet to convert
	 * @param tel Telegram to store
	 * @return ::eoReturn
	 */

	static eoReturn packetToRadio(const eoPacket &packet, eoTelegram &tel);
	/**
	 * Helper function, which will convert a Advanced Packet to a Telegram
	 * @param packet Advanced Packet to convert
	 * @param tel Telegram to store
	 * @return ::eoReturn
	 */

	static eoReturn advancedPacketToRadio(const eoPacket &packet, eoTelegram &tel);
	/**
	 * Helper function which converts decrypted Tigris Telegram to RPS
	 * @param inTel
	 * @param outTel
	 * @return
	 */
	static uint8_t TigrisToRPS(eoTelegram &inTel, eoTelegram &outTel);
	/**
	 * Converts the LSB to hex Char
	 * @param num
	 * @return 0-F
	 */
	static const char * NumToHex(uint8_t num);
	/**
	 * Simple hash function, which generates an uint32_t hash from a char string
	 * @param str pointer to char string
	 * @return	32bit Hash
	 */
	static uint32_t Hash(char const * str);
	/**
	 * Helper function, which will convert Fahrenheit into Celsius
	 * @param value Value to be converted
	 * @return ::eoReturn
	 */
	static eoReturn fahrenheitToCelsius(float &value);
	/**
	 * Helper function, which will convert Celsius into Fahrenheit
	 * @param value Value to be converted
	 * @return ::eoReturn
	 */
	static eoReturn celsiusToFahrenheit(float &value);
};

#endif /* _EOCONVERTER_H_ */
