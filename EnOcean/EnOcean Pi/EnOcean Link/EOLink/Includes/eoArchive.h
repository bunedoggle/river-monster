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

/**
 * \file eoArchive.h
 * \brief contains base for Archives
 * \author EnOcean GmBH
 */
#ifndef _EOARCHIVE_H_
#define _EOARCHIVE_H_
#include "eoHalTypes.h"
#include "eoISerialize.h"
#include "eoHeader.h"

/**
 * \ingroup storage
 * @{
 * \class eoArchive
 * \brief the base Archive
 * \details abstract class describing Archive Operations, for storing the & operator has been overloaded.
 */
class eoArchive
{

public:
	eoArchive();

	virtual ~eoArchive();
	/**
	 * Overloaded & operator to add an object to the archive.	
	 * @param obj Obejct to be add.
	 */    	
	virtual eoArchive& operator &(char *obj);
	/**
	 * Overloaded & operator to add an object to the archive.	
	 * @param obj Obejct to be add.
	 */    	
	virtual eoArchive& operator &(char const *obj);
	/**
	 * Overloaded & operator to add an object to the archive.	
	 * @param obj Obejct to be add.
	 */    	
	virtual eoArchive& operator &(uint32_t &obj);
	/**
	 * Overloaded & operator to add an object to the archive.	
	 * @param obj Obejct to be add.
	 */    	
	virtual eoArchive& operator &(int32_t &obj);
	/**
	 * Overloaded & operator to add an object to the archive.	
	 * @param obj Obejct to be add.
	 */    	
	virtual eoArchive& operator &(uint16_t &obj);
	/**
	 * Overloaded & operator to add an object to the archive.	
	 * @param obj Obejct to be add.
	 */    	
	virtual eoArchive& operator &(int16_t &obj);
	/**
	 * Overloaded & operator to add an object to the archive.	
	 * @param obj Obejct to be add.
	 */    	
	virtual eoArchive& operator &(uint8_t &obj);
	/**
	 * Overloaded & operator to add an object to the archive.	
	 * @param obj Obejct to be add.
	 */    	
	virtual eoArchive& operator &(int8_t &obj);
	/**
	 * Overloaded & operator to add an object to the archive.	
	 * @param obj Obejct to be add.
	 */    	
	virtual eoArchive& operator &(float& obj);
	/**
	 * Overloaded & operator to add an object to the archive.	
	 * @param obj Obejct to be add.
	 */    	
	virtual eoArchive& operator &(bool &obj);
	/**
	 * Overloaded & operator to add an object to the archive.	
	 * @param obj Obejct to be add.
	 */    	
	virtual eoArchive& operator &(eoISerialize *obj);
	/**
	 * Overloaded & operator to add an object to the archive.	
	 * @param obj Obejct to be add.
	 */    	
	virtual eoArchive& operator &(eoISerialize &obj);
	/**
	 * Opens the StreamBuffer/file
	 * @param strBuf file/stream buffer
	 * @return ::eoReturn
	 */
	virtual uint8_t Open(const char * strBuf);
	/**
	 * Closing the Serialisation stream.
	 */   	
	virtual void Close();

  /**
   * Start a block in serialisation stream.
   * @param BlockName name of the block.
   */          
	virtual void startBlock(const char* BlockName);

  /**
   * Make an empty line indent.
   */      
	virtual void indent();
	/**
	 * Start a block in serialisation stream.
	 */    	
	virtual void startBlock();
	/**
	 * End a block in serialisation stream.
	 */    	
	virtual void endBlock();

  //! Flag signalising storing.
	bool isStoring;
	//! String indentifier of the archive.
	char identifier[32];
protected:
  //! Header information with the versioning.
	eoHeader *h;
  //! Actual level of the serialisation stream.
	uint8_t level;
	//! Flag to signalise if name set.
	bool isName;
	//! Statemaschine indicator.
	uint8_t state;
private:
	//debug
};
/**
 @}
 */
#endif // !defined(EA_8062E719_2E73_4ad7_9D7D_AA6996E0FCB1__INCLUDED_)
