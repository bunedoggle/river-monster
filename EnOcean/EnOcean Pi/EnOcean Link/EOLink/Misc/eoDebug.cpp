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
#include "eoDebug.h"
#include "eoManufacturer.h"
#include <stdio.h>

void eoDebug::Print(const eoTelegram &tel)
{
	printf("RORG: %02X    Data: ", tel.RORG);
	for (int i = 0; i < tel.GetDataLength(); i++)
		printf("%02X ", tel.data[i]);

	printf("   SrcID: %08X ", tel.sourceID);
	printf("   Status: %02X ", tel.status);
	printf("   DstID: %08X ", tel.destinationID);
	printf("   dBm: %i ", tel.dBm);
	printf("   SubtelCount: %i ", tel.subtelCount);
	printf("\n");
}

void eoDebug::Print(const eoMessage &msg)
{
	printf("RORG: %02X    Data: ", msg.RORG);
	for (int i = 0; i < msg.GetDataLength(); i++)
		printf("%02X ", msg.data[i]);

	printf("   SrcID: %08X ", msg.sourceID);
	printf("   Status: %02X ", msg.status);
	printf("   DstID: %08X ", msg.destinationID);
	printf("\n");
}

void eoDebug::Print(const eoPacket &p)
{
	printf("Type: %02X    Data: ", p.type);
	for (int i = 0; i < p.dataLength; i++)
		printf("%02X ", p.data[i]);

	printf("  OptionalData: ");
	for (int i = 0; i < p.optionalLength; i++)
		printf("%02X ", p.data[p.dataLength + i]);

	printf("\n");
}

