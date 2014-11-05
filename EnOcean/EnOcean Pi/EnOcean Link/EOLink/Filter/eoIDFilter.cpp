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
#include "eoIDFilter.h"
#include "eoConverter.h"

eoIDFilter::eoIDFilter()
{
}

eoIDFilter::~eoIDFilter()
{
}

bool eoIDFilter::Filter(eoMessage &msg)
{
	idset.begin();
	return (idset.find(msg.sourceID) != idset.end());
}

bool eoIDFilter::Filter(eoTelegram &tel)
{
	idset.begin();
	return (idset.find(tel.sourceID) != idset.end());
}
void eoIDFilter::Add(uint32_t id)
{
	idset.insert(id);
}

void eoIDFilter::Remove(uint32_t id)
{
	idset.erase(id);
}

void eoIDFilter::RemoveAll()
{
	idset.clear();
}

uint8_t eoIDFilter::Serialize(eoArchive &arch)
{
	std::set<uint32_t>::iterator it;
	if (arch.isStoring)
	{
		uint32_t tmpCnt = (int32_t) idset.size();
		uint32_t tmpID;
		uint8_t type = eoIDFILTER;
		arch & "type" & type;
		arch & "Counter" & tmpCnt;
		tmpCnt = 0;
		for (it = idset.begin(); it != idset.end(); it++)
		{
			char tmpName[8] = "ID_";
			tmpName[3] = *eoConverter::NumToHex((uint8_t)(tmpCnt >> 24));
			tmpName[4] = *eoConverter::NumToHex((uint8_t)(tmpCnt >> 16));
			tmpName[5] = *eoConverter::NumToHex((uint8_t)(tmpCnt >> 8));
			tmpName[6] = *eoConverter::NumToHex((uint8_t)(tmpCnt));
			tmpName[7] = 0;
			tmpCnt++;
			tmpID = *it;
			arch & tmpName & tmpID;
		}
	}
	else
	{
		uint32_t tmpCnt;
		uint32_t cnt = 0;
		uint32_t tmpID;
		arch & "Counter" & cnt;
		for (tmpCnt = 0; tmpCnt < cnt; tmpCnt++)
		{
			char tmpName[8] = "ID_";
			tmpName[3] = *eoConverter::NumToHex((uint8_t)(tmpCnt >> 24));
			tmpName[4] = *eoConverter::NumToHex((uint8_t)(tmpCnt >> 16));
			tmpName[5] = *eoConverter::NumToHex((uint8_t)(tmpCnt >> 8));
			tmpName[6] = *eoConverter::NumToHex((uint8_t)(tmpCnt));
			tmpName[7] = 0;

			arch & tmpName & tmpID;
			idset.insert(tmpID);
		}
	}
	return EO_OK;
}
