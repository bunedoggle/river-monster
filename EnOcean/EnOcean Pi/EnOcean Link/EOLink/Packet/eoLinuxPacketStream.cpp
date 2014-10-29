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

#include "eoLinuxPacketStream.h"
#include <termios.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define BDR_ESP3 B57600

eoLinuxPacketStream::eoLinuxPacketStream()
{
	fd = -1;
	curByte = 0;
	numBytes = 0;
}

eoLinuxPacketStream::~eoLinuxPacketStream()
{
	Close();
}

void eoLinuxPacketStream::Close()
{
	tcflush(fd, TCIFLUSH);
	close(fd);
	fd = -1;
}

eoReturn eoLinuxPacketStream::Open(const char * port)
{
	curByte = 0;
	numBytes = 0;
	bool blocking = false; // Specifies if read operation is blocking

	//Settings structure old and new
	struct termios newtio;

	fd = open(port, O_RDWR | O_NOCTTY | (blocking ? 0 : O_NDELAY));
	if (fd < 0)
	{
		return PORT_ERROR;
	}

	//zero new settings
	bzero(&newtio, sizeof(newtio));

	if (cfsetispeed(&newtio, BDR_ESP3) != 0)
		return PORT_ERROR;
	if (cfsetospeed(&newtio, BDR_ESP3) != 0)
		return PORT_ERROR;

	newtio.c_cflag &= ~PARENB;
	newtio.c_cflag &= ~CSTOPB;
	newtio.c_cflag &= ~CSIZE;
	newtio.c_cflag |= CS8;
	newtio.c_cflag &= ~CRTSCTS;

	//Hardware control of port
	// Blocking:     VTIME = 1
	// Non-blocking: VTIME = 0 + O_NDELAY
	newtio.c_cc[VTIME] = blocking ? 1 : 0; // Read-timout 100ms when blocking
	newtio.c_cc[VMIN] = 0;

	tcflush(fd, TCIFLUSH);
	//Acquire new port settings
	if (tcsetattr(fd, TCSANOW, &newtio) != 0)
		puts(strerror(errno));

	return EO_OK;
}

eoReturn eoLinuxPacketStream::ReceiveByte(uint8_t* u8RxByte)
{
	int res;

	if (fd == -1)
		return PORT_ERROR;

	if (curByte < numBytes)
	{
		*u8RxByte = buf[curByte];
		curByte++;
		return EO_OK;
	}
	else
	{
		res = read(fd, &buf, buffSize);
		if (res == 1)
		{
			*u8RxByte = buf[0];
			return EO_OK;
		}
		else if (res > 1)
		{
			numBytes = res;
			curByte = 1;
			*u8RxByte = buf[0];
			return EO_OK;
		}
	}
	return NO_RX;
}

eoReturn eoLinuxPacketStream::SendByte(uint8_t u8TxByte)
{
	int res;

	if (fd == -1)
		return PORT_ERROR;

	res = write(fd, &u8TxByte, 1);

	if (res == 1)
		return EO_OK;

	return EO_ERROR;
}
