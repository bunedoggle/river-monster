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

#include "eoApiDef.h"
#include "eoProfileFactory.h"
#include "eoEEP_F602xx.h"
#include "eoEEP_F603xx.h"
#include "eoEEP_F604xx.h"
#include "eoEEP_F610xx.h"
#include "eoEEP_D500xx.h"
#include "eoEEP_A502xx.h"
#include "eoEEP_A504xx.h"
#include "eoEEP_A506xx.h"
#include "eoEEP_A507xx.h"
#include "eoEEP_A510xx.h"
#include "eoEEP_A512xx.h"

eoProfile* eoProfileFactory::CreateProfile(const eoMessage &msg)
{
	switch (msg.RORG)
	{
		case RORG_4BS:
			if ((msg.data[3] & 0x88) == 0x80) // Is Learn telegram?
			{
				uint8_t rorg = RORG_4BS;
				uint8_t func = msg.data[0] >> 2;
				uint8_t type = ((msg.data[0] & 3) << 5) | (msg.data[1] >> 3);

				eoProfile *profile = eoProfileFactory::CreateProfile(rorg, func, type);
				if (profile != NULL)
					profile->manufacturer = (msg.data[1] & 7) << 8 | msg.data[2];

				return profile;
			}
			break;

		case RORG_VLD:
		{
			uint8_t rorg = RORG_VLD;
			uint8_t func = msg.data[0] >> 2;
			uint8_t type = ((msg.data[0] & 3) << 5) | (msg.data[1] >> 3);

			eoProfile *profile = eoProfileFactory::CreateProfile(rorg, func, type);
			if (profile != NULL)
				profile->manufacturer = (msg.data[1] & 7) << 8 | msg.data[2];

			return profile;
		}
			break;
	}

	return NULL;
}

eoProfile* eoProfileFactory::CreateProfile(const uint8_t rorg, const uint8_t func, const uint8_t type)
{
	eoProfile *eep = NULL;

	switch (rorg)
	{
		case RORG_RPS:
			switch (func)
			{
				case 0x02:
					eep = new eoEEP_F602xx();
					break;
				case 0x03:
					eep = new eoEEP_F603xx();
					break;
				case 0x04:
					eep = new eoEEP_F604xx();
					break;
				case 0x10:
					eep = new eoEEP_F610xx();
					break;
				default:
					break;
			}
			break;

		case RORG_4BS:
			switch (func)
			{
				case 0x02:
					eep = new eoEEP_A502xx();
					break;
				case 0x04:
					eep = new eoEEP_A504xx();
					break;
				case 0x06:
					eep = new eoEEP_A506xx();
					break;
				case 0x07:
					eep = new eoEEP_A507xx();
					break;
				case 0x10:
					eep = new eoEEP_A510xx();
					break;
				case 0x12:
					eep = new eoEEP_A512xx();
					break;
					break;
				default:
					break;
			}

			break;
		case RORG_1BS:
			switch (func)
			{
				case 0x00:
					eep = new eoEEP_D500xx();
					break;
			}
			break;

		case RORG_SECD:
			break;
		case RORG_VLD:
			break;

		default:
			break;

	}
	//Not supported types will deleted
	if (eep != NULL && eep->SetType(type) != EO_OK)
	{
		delete eep;
		eep = NULL;
	}

	return eep;
}
