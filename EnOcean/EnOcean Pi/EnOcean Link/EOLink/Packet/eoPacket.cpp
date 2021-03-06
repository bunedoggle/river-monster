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

#include "eoPacket.h"
#include "eoApiDef.h"
#include <string.h>

eoPacket::eoPacket()
{
	externalBuffer = false;
	bufferSize = 550;
	data = new uint8_t[550];
	dataLength = 0;
	optionalLength = 0;
	type = 0;
}

eoPacket::~eoPacket()
{
	if (!externalBuffer)
	{
		delete[] data;
		data = NULL;
	}

}

uint16_t eoPacket::getBufferSize()
{
	return bufferSize;
}

eoPacket::eoPacket(uint8_t* dataBuffer, uint16_t size)
{
	externalBuffer = true;
	data = dataBuffer;
	bufferSize = size;
	dataLength = 0;
	optionalLength = 0;
	type = 0;
}

eoPacket::eoPacket(uint16_t size)
{
	externalBuffer = false;
	bufferSize = size;

	data = new uint8_t[size];
	dataLength = 0;
	optionalLength = 0;
	type = 0;
}

eoPacket::eoPacket(eoPacket &packet)
{
	this->externalBuffer = false;
	this->bufferSize = packet.getBufferSize();
	this->data = new uint8_t[this->bufferSize];

	memcpy(this->data, packet.data, this->bufferSize);

	this->dataLength = packet.dataLength;
	this->optionalLength = packet.optionalLength;
	this->type = packet.type;
}

uint8_t eoPacket::copyTo(eoPacket &packet)
{
	if (packet.bufferSize < (dataLength + optionalLength))
		return OUT_OF_RANGE;

	packet.type = type;
	packet.dataLength = dataLength;
	packet.optionalLength = optionalLength;

	memcpy(packet.data, data, dataLength + optionalLength);
	return EO_OK;
}
