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

#include "eoStorageManager.h"
#include "eoArchiveTXT.h"

eoStorageManager::eoStorageManager()
{
	arch = new eoArchiveTXT();
	strncpy(arch->identifier, EO_STORAGE_IDENTIFIER, 32);
}

eoStorageManager::eoStorageManager(eoArchive &archive)
{
	arch = &archive;
	strncpy(arch->identifier, EO_STORAGE_IDENTIFIER, 32);
}

eoStorageManager::~eoStorageManager()
{
	name_object_map::iterator it;
	for (it = list.begin(); it != list.end(); it++)
		delete ((*it).second);
	delete arch;
}

eoReturn eoStorageManager::addObject(const char * name, eoISerialize *object)
{

	serialize_object *myObj;
	uint32_t id = eoConverter::Hash(name);
	//size_t nameHas = std::hash<std::char>(name);
	myObj = list[id];
	if (myObj == NULL)
	{
		list[id] = new serialize_object;
		myObj = list[id];

	}
	else if (strncmp(myObj->name, name, 32) == 0)
	{
		if (myObj->object == object)
			return EO_OK;
		else
			return WRONG_PARAM;
		//objectname is the same...
	}
	strncpy(myObj->name, name, 32);
	myObj->name[32] = '\0';
	myObj->object = object;
	return EO_OK;
}

eoReturn eoStorageManager::RemoveObject(const char * name)
{
	uint32_t id = eoConverter::Hash(name);
	if (list.find(id) != list.end())
	{
		serialize_object *myObj = list[id];
		delete myObj;
		list.erase(id);
	}
	return EO_OK;
}

eoReturn eoStorageManager::Load(const char * strBuf)
{
	name_object_map::iterator it;
	arch->isStoring = false;
	if (arch->Open(strBuf) != EO_OK)
		return EO_ERROR;
	for (it = list.begin(); it != list.end(); it++)
	{
		*arch & ((*it).second)->name & ((*it).second)->object;
	}
	arch->Close();
	//Foreach object in the manager obj.serialize
	return EO_OK;
}

eoReturn eoStorageManager::Save(const char * strBuf)
{
	name_object_map::iterator it;
	arch->isStoring = true;
	arch->Open(strBuf);
	for (it = list.begin(); it != list.end(); it++)
	{
		*arch & ((*it).second)->name & ((*it).second)->object;
	}
	arch->Close();
	//Foreach object in the manager obj.serialize
	return EO_OK;
}
