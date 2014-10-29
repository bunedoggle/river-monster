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
 * \file eoStorageManager.h
 * \brief
 * \author EnOcean GmBH
 */
#include "eoArchive.h"
#include "eoHeader.h"
#include "eoISerialize.h"
#include "eoConverter.h"
#include "eoHalTypes.h"
#include <string.h>
#include <map>

#ifndef EO_STORAGE_MANAGER_H_
#define EO_STORAGE_MANAGER_H_

//!Storage indentifier.- can be changed 
#define EO_STORAGE_IDENTIFIER "_EOLINK_SAVE"

//! Serialised obejct type definition to save learned devices.
typedef struct
{
  //! Serialize object
	eoISerialize *object;
	//! Name
	char name[33];
	//seems that i don't need this...
	//! Has been loaded
	bool hasBeenLoaded;
	//! Unique ID
	uint32_t uniqueID;
} serialize_object;

//! Map type definition for serialized objects.
typedef std::map<uint32_t, serialize_object*> name_object_map;

/**
 * \ingroup storage
 * @{
 *\class eoStorageManager
 *\brief handles the Storage of Object
 *\details Manages for you the saving or loading of ISerialize objects, which you can add via addObject or loadObject
 *\code
 *	eoStorageManager myManager;
 *	myManager.Add(myGateway);
 *	myManager.Save("mySaveFile");
 *\endcode
 *\example storage_example.cpp
 */
class eoStorageManager
{

public:
	/**
	 * The standard constructor uses the eoArchiveTXT
	 */
	eoStorageManager();
	/**
	 * The Storage Manager Constructor
	 * @param archive eoArchive Format to save to.
	 */
	eoStorageManager(eoArchive &archive);
	virtual ~eoStorageManager();
	/**
	 * \brief Adds an eoISerialize Object to the storageManager
	 * \details all Objects which have been added to the storageManager, will be handled in the save and load functionality of the Storage Manager.
	 * @param name The object identifier used in your Application to load/save the ISerialize object (maximal 32 characters)
	 * @param object an ISerialize object which you want to save or load
	 * @return ::eoReturn
	 */
	eoReturn addObject(const char * name, eoISerialize *object);

	/**
	 * \brief Removes an ISerialize Object from the StorageManager
	 * \details The eoISerialize object will be removed from the StorageManager handling
	 * @param name The object identifier used in your Application to load/save the ISerialize object (maximal 32 characters)
	 * @return ::eoReturn
	 */
	eoReturn RemoveObject(const char * name);
	/**
	 * Loads from the specified stream allObjects
	 * @param strBuf
	 * @return ::eoReturn
	 */
	eoReturn Load(const char * strBuf);
	/**
	 * Saves your object to the specified Buffer
	 * @param strBuf the Buffer to save to, using the choosen Archive type
	 * @return ::eoReturn
	 */
	eoReturn Save(const char * strBuf);


private:
	name_object_map list;
	eoArchive * arch;
};
/**
 * @}
 */
#endif // !defined(EA_E73F2DAC_8C52_496f_8AAC_BA2DE5B7E9B8__INCLUDED_)
