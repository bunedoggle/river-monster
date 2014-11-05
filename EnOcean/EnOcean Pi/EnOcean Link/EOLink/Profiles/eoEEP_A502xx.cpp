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

#include "eoEEP_A502xx.h"

#include "eoChannelEnums.h"
#include <string.h>

const uint8_t numOfChan = 1;
const uint8_t numOfProfiles = 0x31;
const EEP_ITEM listA502xx_temperature[numOfProfiles][numOfChan] =
{
// exist	,bitoffs,bitsize,rangeMin,rangeMax,scaleMin, scaleMax,type;
//TYPE:00
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 },
},
//TYPE:01
{
{ true, 16, 8, 255, 0, -40.0, 00.0, S_TEMP, 0 }, //Temperature
},
//TYPE:02
{
{ true, 16, 8, 255, 0, -30.0, 10.0, S_TEMP, 0 }, //Temperature
},
//TYPE:03
{
{ true, 16, 8, 255, 0, -20.0, 20.0, S_TEMP, 0 }, //Temperature
},
//TYPE:04
{
{ true, 16, 8, 255, 0, -10.0, 30.0, S_TEMP, 0 }, //Temperature
},
//TYPE:05
{
{ true, 16, 8, 255, 0, 0.0, 40.0, S_TEMP, 0 }, //Temperature
},
//TYPE:06
{
//Temperature
{ true, 16, 8, 255, 0, 10.0, 50.0, S_TEMP, 0 }, },
//TYPE:07
{
//Temperature
{ true, 16, 8, 255, 0, 20.0, 60.0, S_TEMP, 0 }, },
//TYPE:08
{
//Temperature
{ true, 16, 8, 255, 0, 30.0, 70.0, S_TEMP, 0 }, },
//TYPE:09
{
//Temperature
{ true, 16, 8, 255, 0, 40.0, 80.0, S_TEMP, 0 }, },
//TYPE:0A
{
//Temperature
{ true, 16, 8, 255, 0, 50.0, 90.0, S_TEMP, 0 }, },
//TYPE:0B
{
//Temperature
{ true, 16, 8, 255, 0, 60.0, 100.0, S_TEMP, 0 }, },
//TYPE:0C
{
//Temperature
{ false, 16, 8, 255, 0, -60.0, 20.0, S_TEMP, 0 }, },
//TYPE:0D
{
//Temperature
{ false, 16, 8, 255, 0, -50.0, 30.0, S_TEMP, 0 }, },
//TYPE:0E
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 40.0, S_TEMP, 0 }, },
//TYPE:0F
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 }, },
//TYPE:10
{
//Temperature
{ true, 16, 8, 255, 0, -60.0, 20.0, S_TEMP, 0 }, },
//TYPE:11
{
//Temperature
{ true, 16, 8, 255, 0, -50.0, 30.0, S_TEMP, 0 }, },
//TYPE:12
{
//Temperature
{ true, 16, 8, 255, 0, -40.0, 40.0, S_TEMP, 0 }, },
//TYPE:13
{
//Temperature
{ true, 16, 8, 255, 0, -30.0, 50.0, S_TEMP, 0 }, },
//TYPE:14
{
//Temperature
{ true, 16, 8, 255, 0, -20.0, 60.0, S_TEMP, 0 }, },
//TYPE:15
{
//Temperature
{ true, 16, 8, 255, 0, -10.0, 70.0, S_TEMP, 0 }, },
//TYPE:16
{
//Temperature
{ true, 16, 8, 255, 0, 0.0, 80.0, S_TEMP, 0 }, },
//TYPE:17
{
//Temperature
{ true, 16, 8, 255, 0, 10.0, 90.0, S_TEMP, 0 }, },
//TYPE:18
{
//Temperature
{ true, 16, 8, 255, 0, 20.0, 100.0, S_TEMP, 0 }, },
//TYPE:19
{
//Temperature
{ true, 16, 8, 255, 0, 30.0, 110.0, S_TEMP, 0 }, },
//TYPE:1A
{
//Temperature
{ true, 16, 8, 255, 0, 40.0, 120.0, S_TEMP, 0 }, },
//TYPE:1B
{
//Temperature
{ true, 16, 8, 255, 0, 50.0, 130.0, S_TEMP, 0 }, },
//TYPE:1C
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 }, },
//TYPE:1D
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 }, },
//TYPE:1E
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 }, },
//TYPE:1F
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 }, },
//TYPE:20
{
//Temperature
{ true, 14, 10, 1023, 0, -10.0, 41.2F, S_TEMP, 0 }, },
//TYPE:21
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 }, },
//TYPE:22
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 }, },
//TYPE:23
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 }, },
//TYPE:24
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 }, },
//TYPE:25
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 }, },
//TYPE:26
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 }, },
//TYPE:27
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 }, },
//TYPE:28
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 }, },
//TYPE:29
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 }, },
//TYPE:2A
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 }, },
//TYPE:2B
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 }, },
//TYPE:2C
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 }, },
//TYPE:2D
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 }, },
//TYPE:2E
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 }, },
//TYPE:2F
{
//Temperature
{ false, 16, 8, 255, 0, -40.0, 00.0, S_RES, 0 }, },
//TYPE:30
{
//Temperature
{ true, 14, 10, 1023, 0, -40.0, 62.3F, S_TEMP, 0 }, }, };

eoEEP_A502xx::eoEEP_A502xx()
{
	channel = new eoEEPChannelInfo[numOfChan];
	channelCount = 0;

	this->rorg = RORG_4BS;
	this->func = 0x02;
}

eoEEP_A502xx::~eoEEP_A502xx()
{
	//Tobi Review: added delete parameter to free memory
	if(channel!=NULL)
		delete[] channel;
	channel=NULL;
}

eoReturn eoEEP_A502xx::SetType(uint8_t type)
{
	uint8_t tmpChannelCount;
	if (type > numOfProfiles)
		return NOT_SUPPORTED;
	for (tmpChannelCount = 0; tmpChannelCount < numOfChan; tmpChannelCount++)
	{
		if (listA502xx_temperature[type][tmpChannelCount].exist)
		{
			channel[channelCount].type = listA502xx_temperature[type][tmpChannelCount].type;
			channel[channelCount].max = listA502xx_temperature[type][tmpChannelCount].scaleMax;
			channel[channelCount].min = listA502xx_temperature[type][tmpChannelCount].scaleMin;
			channel[channelCount].eepItem = &listA502xx_temperature[type][tmpChannelCount];
			channelCount++;
		}
	}

	if (type == 0 || channelCount == 0)
		return NOT_SUPPORTED;

	this->type = type;
	return EO_OK;
}

