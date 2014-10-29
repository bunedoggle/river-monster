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

#if !defined(_EO_LOGGER_H)
#define _EO_LOGGER_H

//! \file eoLogger.h

#include "eoApiDef.h"
#include "eoPacket.h"
#include <stdio.h>
#include <time.h>

/**
 * \class eoLogger
 * \brief Logs Packets
 * \details The eoLogger logs Packets in binary to a specified file. Each packets precedes a timestamp.
 */
class eoLogger
{

public:
	/**
	 * Constructor
	 */
	eoLogger();

	virtual ~eoLogger();
	/**
	 * Opens a file for binary write access. Overwrites it if it exists. 
	 * @return 0 for successful opening the file. -1 otherwise.
	 */
	eoReturn Open(const char *filename);
	/**
	 *	Closes the file that was opened using open()
	 * @return 0 for successful closing the file.
	 */
	eoReturn Close();	
	/**
	 *Logs a Packet of type Packet by appending it to the opened file with a preceding timestamp.
	 * @param p The Packet to be logged.
	 * @param flush If true, after logging the packet p, the file is flushed
	 * @return Returns 0 if successful.
	 */
	eoReturn Log(eoPacket &p, bool flush = false);

  /**
   *  Flushes the stream to file.
   */    
	eoReturn Flush();

private:
	FILE* logFile;
	tm myTimeStruct;
};

#endif // !defined(_EO_LOGGER_H)
