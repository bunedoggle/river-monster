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

#include "eoEEP_A504xx.h"

#include "eoChannelEnums.h"
#include <string.h>
/*
 * Some internal informations CHANNEL 0= Humidity and CHANNEL 1 = Temperature
 */

const uint8_t numOfChan = 2;
const uint8_t numOfProfiles = 0x02;
const EEP_ITEM listA504xx[numOfProfiles][numOfChan] =
{
// exist	,bitoffs,bitsize,rangeMin,rangeMax,scaleMin, scaleMax,type;
//TYPE:00
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 } },
//TYPE:01
{
{ true, 8, 8, 0, 250, 0.0, 100.0, S_RELHUM, 0 }, //Humidity
{ true, 16, 8, 0, 250, 0.0, 40.0, S_TEMP, 0 } //Temperature
} };

eoEEP_A504xx::eoEEP_A504xx()
{
	channel = new eoEEPChannelInfo[2];
	channelCount = 0;

	rorg = RORG_4BS;
	func = 0x04;
}

eoEEP_A504xx::~eoEEP_A504xx()
{
	//TOBI: added null check
	if(channel!=NULL)
		delete[] channel;
	channel = NULL;
}

eoReturn eoEEP_A504xx::GetValue(CHANNEL_TYPE type, float &value)
{
	//SEE EEP SPEC
	if (type == S_TEMP && ((msg.data[3] & 0x02) != 0x02))
		return NOT_SUPPORTED;
	return eoA5EEProfile::GetValue(type, value);
}

eoReturn eoEEP_A504xx::SetValue(CHANNEL_TYPE type, float value)
{
	//SEE EEP SPEC
	if (type == S_TEMP)
		msg.data[3] |= 0x02;
	return eoA5EEProfile::SetValue(type, value);
}

eoReturn eoEEP_A504xx::SetType(uint8_t type)
{
	uint8_t tmpChannelCount;
	//tobi moved type> numOfProfiles to this point, so that we don't access memory above our array
	if (type > numOfProfiles)
		return NOT_SUPPORTED;
	for (tmpChannelCount = 0; tmpChannelCount < numOfChan; tmpChannelCount++)
	{
		if (listA504xx[type][tmpChannelCount].exist)
		{
			channel[channelCount].type = listA504xx[type][tmpChannelCount].type;
			channel[channelCount].max = listA504xx[type][tmpChannelCount].scaleMax;
			channel[channelCount].min = listA504xx[type][tmpChannelCount].scaleMin;
			channel[channelCount].eepItem = &listA504xx[type][tmpChannelCount];
			channelCount++;
		}
	}

	this->type = type;
	if ( type == 0 || channelCount == 0)
		return NOT_SUPPORTED;

	return EO_OK;
}
