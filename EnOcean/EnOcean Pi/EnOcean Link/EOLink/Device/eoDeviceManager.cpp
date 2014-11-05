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

#include "eoDeviceManager.h"
#include "eoArchive.h"
#include "eoConverter.h"
#include "eoDevice.h"

eoDeviceManager::eoDeviceManager()
{
	list = id_device_map();
}

eoDeviceManager::~eoDeviceManager()
{
	id_device_map::iterator it;
	for (it = list.begin(); it != list.end(); it++)
		delete ((*it).second);

	list.clear();
}

uint32_t eoDeviceManager::Size() const
{
	return (uint32_t)(list.size());
}

eoDevice* eoDeviceManager::Add(uint32_t id)
{
	eoDevice *myDev;
	myDev = list[id];
	if (myDev == NULL)
	{
		list[id] = new eoDevice;
		myDev = list[id];
	}
	myDev->ID = id;
	return myDev;
}

const id_device_map & eoDeviceManager::GetDeviceList() const
{
	return list;
}

eoDevice* eoDeviceManager::Get(uint32_t id)
{
	eoDevice * myDev = NULL;
	if (list.find(id) != list.end())
		myDev = list[id];
	return myDev;
}

void eoDeviceManager::Remove(uint32_t id)
{
	if (list.find(id) != list.end())
	{
		eoDevice *myDev = list[id];
		if(myDev!=NULL)
			delete myDev;
		list.erase(id);
	}
}

uint8_t eoDeviceManager::Serialize(eoArchive &a)
{
	id_device_map::iterator it;
	if (a.isStoring)
	{
		uint32_t tmpCnt = (int32_t) list.size();
		a & "Counter" & tmpCnt;
		if (tmpCnt == 0)
			return EO_OK;
		tmpCnt = 0;
		for (it = list.begin(); it != list.end(); it++)
		{
			char tmpName[12] = "Device_";
			tmpName[7] = *eoConverter::NumToHex((uint8_t)(tmpCnt >> 24));
			tmpName[8] = *eoConverter::NumToHex((uint8_t)(tmpCnt >> 16));
			tmpName[9] = *eoConverter::NumToHex((uint8_t)(tmpCnt >> 8));
			tmpName[10] = *eoConverter::NumToHex((uint8_t)(tmpCnt));
			tmpName[11] = 0;
			tmpCnt++;
			//could be a NULL pointer, shouldn't be...
			a & tmpName & ((*it).second);
		}
	}
	else
	{
		uint32_t tmpCnt;
		uint32_t cnt = 0;
		eoDevice *myDev;
		a & "Counter" & cnt;
		for (tmpCnt = 0; tmpCnt < cnt; tmpCnt++)
		{
			char tmpName[12] = "Device_";
			tmpName[7] = *eoConverter::NumToHex((uint8_t)(tmpCnt >> 24));
			tmpName[8] = *eoConverter::NumToHex((uint8_t)(tmpCnt >> 16));
			tmpName[9] = *eoConverter::NumToHex((uint8_t)(tmpCnt >> 8));
			tmpName[10] = *eoConverter::NumToHex((uint8_t)(tmpCnt));
			tmpName[11] = 0;
			myDev = new eoDevice();
			a & tmpName & myDev;
			list[myDev->ID] = myDev;
		}
	}
	return EO_OK;
}
