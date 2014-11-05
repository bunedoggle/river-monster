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
 * \file eoIDFilter.h
 * \brief eoIDFilter
 * \author EnOcean GmBH
 */
#ifndef EO_ID_FILTER_H
#define EO_ID_FILTER_H

#include "eoIFilter.h"

#include <set>
//! Definition of the ID Set with 32 bit EnoCean IDs.
typedef std::set<uint32_t> id_set;

/**\ingroup eoFilter
 * @{
 */

/**
 * \class eoIDFilter
 * \brief uses EnOcean IDs as filter base
 * \details eoIDFilter is an easy filter, which allows you to filter a Telegram / Message via the ID
 * \ref GatewayFiltered_example.cpp
 */
class eoIDFilter: public eoIFilter
{
private:
	std::set<uint32_t> idset;
public:
	eoIDFilter();
	virtual ~eoIDFilter();

	/**
	 * Filters the Message using the internal ID List
	 * @param msg Message to Filter
	 * @return true when the Message::sourceID is in the Filter list.
	 */
	bool Filter(eoMessage &msg);

	/**
	 * Filters the Message using the internal ID List
	 * @param tel Telegram to Filter
	 * @return true when the Message::sourceID is in the Filter list.
	 */
	bool Filter(eoTelegram &tel);

public:

	virtual uint8_t Serialize(eoArchive &arch);

	/**
	 * Adds an EnOcean ID to the filter
	 * @param id uint32_t ID
	 */
	void Add(uint32_t id);

	/**
	 * Removes an EnOcean ID to the filter
	 * @param id uint32_t ID
	 */
	void Remove(uint32_t id);

	/**
	 * Remove all IDS.
	 */
	void RemoveAll();
};
/**
 * @}
 */

#endif // !defined(EO_ID_FILTER_H)
