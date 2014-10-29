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

#include "eoLogger.h"
#include "eoTimer.h"
#include <time.h>
#include <stdlib.h>

eoLogger::eoLogger()
{
	logFile = NULL;
}

eoLogger::~eoLogger()
{
	Close();
}

eoReturn eoLogger::Open(const char *filename)
{
	logFile = fopen(filename, "wb");

	if (logFile == NULL)
		return EO_ERROR;

	unsigned char timestamp[4];
	time_t t = time(0);

	localtime_r(&t,&myTimeStruct);

	timestamp[0] = ((long long) t >> 24) & 0xFF;
	timestamp[1] = ((long long) t >> 16) & 0xFF;
	timestamp[2] = ((long long) t >> 8) & 0xFF;
	timestamp[3] = ((long long) t) & 0xFF;

	fwrite(&timestamp[0], 1, sizeof(unsigned char), logFile);
	fwrite(&timestamp[1], 1, sizeof(unsigned char), logFile);
	fwrite(&timestamp[2], 1, sizeof(unsigned char), logFile);
	fwrite(&timestamp[3], 1, sizeof(unsigned char), logFile);

	fflush(logFile);

	return EO_OK;
}

eoReturn eoLogger::Log(eoPacket &p, bool flush)
{
	uint32_t curTime = eoTimer::GetTickCount();
	int res = 0;
	unsigned char rawTs[4];
	unsigned char datLen[2];

	// Endianness independent
	rawTs[0] = (curTime >> 24) & 0xFF;
	rawTs[1] = (curTime >> 16) & 0xFF;
	rawTs[2] = (curTime >> 8) & 0xFF;
	rawTs[3] = (curTime) & 0xFF;

	datLen[0] = (p.dataLength >> 8) & 0xFF;
	datLen[1] = (p.dataLength) & 0xFF;

	// Endianness independent
	fwrite(&rawTs[0], 1, sizeof(unsigned char), logFile);
	fwrite(&rawTs[1], 1, sizeof(unsigned char), logFile);
	fwrite(&rawTs[2], 1, sizeof(unsigned char), logFile);
	fwrite(&rawTs[3], 1, sizeof(unsigned char), logFile);

	fwrite(&p.type, 1, sizeof(uint8_t), logFile);
	fwrite(&datLen[1], 1, sizeof(unsigned char), logFile);
	fwrite(&datLen[0], 1, sizeof(unsigned char), logFile);

	fwrite(&p.optionalLength, 1, sizeof(uint8_t), logFile);
	res = (int)fwrite(p.data, 1, p.dataLength + p.optionalLength, logFile);

	if (res != (p.dataLength + p.optionalLength))
		return EO_ERROR;

	if (flush)
		fflush(logFile);

	return EO_OK;
}

eoReturn eoLogger::Flush()
{
	if (fflush(logFile) != EO_OK)
		return EO_ERROR;
	return EO_OK;
}

eoReturn eoLogger::Close()
{
	if (logFile == NULL)
		return EO_OK;

	fflush(logFile);
	if (fclose(logFile) != EO_OK)
		return EO_ERROR;

	logFile = NULL;
	return EO_OK;
}

