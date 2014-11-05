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
 * \file eodBmFilter.h
 * \brief contains a dBm based Filter
 * \author EnOcean GmBH
 */
#if !defined(EO_DBM_FILTER_H)
#define EO_DBM_FILTER_H

#include "eoIFilter.h"
#include <set>

/**\ingroup eoFilter
 * @{
 */

/**
 * \class eodBmFilter
 * \brief uses Telegram dBm values as filter base
 * \details eodBmFilter is an easy filter, which allows you to filter a Telegram via the dBm Value
 * \note the dBm value is a signed! value and normally between (far away)-90...-40dBm(near)
 *  \example GatewayFiltered_example.cpp
 */
class eodBmFilter: public eoIFilter
{
private:
	std::set<uint32_t> idset;
public:

	/**
	 * Using this constructor, no Telegrams get filtered
	 */
	eodBmFilter();

	/**
	 * Constructor which sets max and min DBM
	 * @param maxDBm maximal dBM Value allowed
	 * @param minDBm minimal dBM Value needed
	 */
	eodBmFilter(int8_t maxDBm, int8_t minDBm);
	virtual ~eodBmFilter();

	/**
	 * You can't filter normal messages, as they don't contain a dBm Information!
	 * @param msg Message to Filter
	 * @return false
	 */
	bool Filter(eoMessage &msg);

	/**
	 * Filters the Telegram comparing its dBm against the set dBm
	 * @param tel Telegram to Filter
	 * @return true when the dBm value is between max and min is in the Filter list.
	 */
	bool Filter(eoTelegram &tel);

public:

	virtual uint8_t Serialize(eoArchive &arch);
	/** maximal dBm value which is allowed */
	int8_t maxdBm;
	/**  minimal dBm value which is allowed */
	int8_t mindBm;

};
/**
 * @}
 */

#endif // !defined(EO_DBM_FILTER_H)
