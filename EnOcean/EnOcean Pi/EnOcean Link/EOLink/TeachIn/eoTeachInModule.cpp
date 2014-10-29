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

#include "eoTeachInModule.h"
#include "eoMessage.h"
#include "eoDeviceManager.h"
#include "eoProfileFactory.h"

eoTeachInModule::eoTeachInModule(eoDeviceManager *eoDevManager)
{
	deviceManager = eoDevManager;
	rps_func = 0;
	rps_type = 0;
	bs1_func = 0;
	bs1_type = 0;
	bs4_func = 0;
	bs4_type = 0;
	ute_rorg = 0;
	ute_type = 0;
	ute_func = 0;
}

eoTeachInModule::~eoTeachInModule()
{

}

bool eoTeachInModule::isTeachIN(eoMessage &m)
{
	bool retBool = false;
	if ((m.RORG == RORG_4BS) && (m.data[3] & 0x08) == 0x00)
		retBool = true;
	else if ((m.RORG == RORG_1BS) && (m.data[0] & 0x08) == 0x00)
		retBool = true;
	return retBool;
}

void eoTeachInModule::TeachOut(uint32_t id)
{
	deviceManager->Remove(id);
	teachInformation.erase(id);
}

bool eoTeachInModule::isTeachedIN(eoMessage &m)
{
	bool retBool = false;
	if(teachInformation.find(m.sourceID) == teachInformation.end())
		retBool=(teachInformation[m.sourceID]).teachedIN;

	return retBool ;
}

bool eoTeachInModule::isTeachedIN(eoDevice &dev)
{
	bool retBool = false;
	if(teachInformation.find(dev.ID) == teachInformation.end())
		retBool=(teachInformation[dev.ID]).teachedIN;

	return retBool;
}

TEACH_RETURN eoTeachInModule::TeachIN(eoMessage &m)
{
	TEACH_RETURN ret = NO_TEACH_IN;
	eoDevice* device = deviceManager->Get(m.sourceID);
	eoProfile *profile = NULL;
	bool teachIN = isTeachIN(m);
	//Init structure
	if(teachInformation.find(m.sourceID) == teachInformation.end())
	{
		teachInformation[m.sourceID].teachedIN=false;
	}

	if (device == NULL)
	{
		device = deviceManager->Add(m.sourceID);
		ret = NEW_DEVICE;
	}
	//This covers the case, that the device was deleted from the device manager= manual teach out
	else if (teachInformation[m.sourceID].teachedIN && teachIN)
		ret = SECOND_TEACH_IN;

	switch (m.RORG)
	{
		case RORG_4BS:
			if ((m.data[3] & 0x88) == 0x00)
			{
				profile = eoProfileFactory::CreateProfile(RORG_4BS, bs4_func, bs4_type);
				teachInformation[m.sourceID].teachedIN = true;
			}
			else if ((m.data[3] & 0x88) == 0x80)
			{
				profile = eoProfileFactory::CreateProfile(m);
				teachInformation[m.sourceID].teachedIN = true;
			}
			break;
		case RORG_RPS:
			profile = eoProfileFactory::CreateProfile(RORG_RPS, rps_func, rps_type);
			teachInformation[m.sourceID].teachedIN = true;
			break;
		case RORG_1BS:
			if (teachIN)
			{
				profile = eoProfileFactory::CreateProfile(RORG_1BS, bs1_func, bs1_type);
				teachInformation[m.sourceID].teachedIN = true;
			}
			break;
		case RORG_UTE:
			if(ParseUTE(m) == EO_OK)
			{
				profile = eoProfileFactory::CreateProfile(ute_rorg, ute_func, ute_type);
				profile->manufacturer = ((m.data[3] & 7) << 8) | m.data[2];
				ret = EEP_TEACH_IN;
			}
			break;
		default:
			break;
	}
	if (device->SetProfile(profile) == EO_OK)
		ret = EEP_TEACH_IN;

	else
		delete profile;

	if (ret == NEW_DEVICE)
	{
		deviceManager->Remove(m.sourceID);
		ret = NO_TEACH_IN;
	}

	return ret;
}

void eoTeachInModule::SetRPS(uint8_t func, uint8_t type)
{
	rps_func = func;
	rps_type = type;
}

void eoTeachInModule::Set1BS(uint8_t func, uint8_t type)
{
	bs1_func = func;
	bs1_type = type;
}

void eoTeachInModule::Set4BS(uint8_t func, uint8_t type)
{
	bs4_func = func;
	bs4_type = type;
}

eoReturn eoTeachInModule::ParseUTE(eoMessage &msg)
{
	ute_rorg = msg.data[6];
	ute_func = msg.data[5];
	ute_type = msg.data[4];
	return EO_OK;
}

eoReturn eoTeachInModule::CreateUTEResponse(eoMessage &teachInUTE, eoMessage &responseUTE, UTE_RESPONSE type = TEACH_IN_ACCEPTED, UTE_DIRECTION direction = UTE_DIRECTION_BIDIRECTIONAL)
{
	teachInUTE.copyTo(responseUTE);

	responseUTE.destinationID = teachInUTE.sourceID;
	responseUTE.data[0] = 1;
	responseUTE.data[0] |= (type&0x3) << 4;
	responseUTE.data[0] |= (direction&0x1) << 7;

	return EO_OK;
}
