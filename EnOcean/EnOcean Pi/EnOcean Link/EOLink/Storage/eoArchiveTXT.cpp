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

#include "eoArchiveTXT.h"

eoArchiveTXT::eoArchiveTXT()
{
	curName = "";
	h = new eoHeader(_ARCHIVE_VER_MAJOR, _ARCHIVE_VER_MINOR, _ARCHIVE_TYPE_NAME);
	state = 0;
	level = 0;
	isName = true;
	isStoring = true;
	newBlock = false;
}

eoArchiveTXT::~eoArchiveTXT()
{
	delete h;
	Close();
}

uint8_t eoArchiveTXT::Open(const char * strBuf)
{
	if (myFile.is_open())
		Close();


	if (isStoring)
	{
		myFile.open(strBuf, std::ios::out | std::ios::trunc);
		if (!myFile.is_open())
			return EO_ERROR;
		myFile << identifier;
		myFile << std::endl;
		*this & "HEADER" & h;
	}
	else
	{
		myFile.open(strBuf, std::ios::in);
		if (!myFile.is_open())
			return EO_ERROR;
		blockItems.clear();
		std::string mystring;
		std::getline(myFile, mystring);
		if (strcmp(identifier, mystring.c_str()))
			return NOT_SUPPORTED;
		//magic of loading
		if (ParseFile() != EO_OK)
			return NOT_SUPPORTED;

		eoHeader * tmpHeader = new eoHeader();
		*this & "HEADER" & tmpHeader;
		//if(strcmp(tmpHeader->name,_ARCHIVE_TYPE_NAME));
		//	return NOT_SUPPORTED;
		delete tmpHeader;

	}

	return EO_OK;
}
eoReturn eoArchiveTXT::ParseBlock(std::string blockName)
{
	eoReturn ret = EO_OK;
	std::string tmpNameString;
	//std::string *dataString;
	std::string line;
	std::getline(std::ws(myFile), line);
	//we should get as first line a '{'
	if (line != "{")	//means chunk could also be empty...
		ret = NOT_SUPPORTED;
	else
	{
		while (std::getline(std::ws(myFile), line))
		{
			tmpNameString = blockName;
			tmpNameString += ".";
			if (line.find(":") != std::string::npos)
			{
				tmpNameString += line.substr(0, line.find(":"));
				blockItems[tmpNameString] = line.substr(line.find(":") + 1);
			}
			else if (line == "}")
				break;
			else
			{
				tmpNameString.append(line);
				blockItems[tmpNameString];
				ParseBlock(tmpNameString);
			}
		}
	}
	return ret;
}

eoReturn eoArchiveTXT::ParseFile()
{
	std::string line;
	while (std::getline(std::ws(myFile), line))
	{
		//The main file should not contain  objects!
		if (line.find(":") != std::string::npos)
		{
			//skip
		}
		else if (line.find("{") != std::string::npos || line.find("}") != std::string::npos)//more skipping
		{

		}
		else
		{
			blockItems[line];
			ParseBlock(line);
		}
	}
	return EO_OK;
}
std::ostream& eoArchiveTXT::indent(std::ostream &s, uint8_t level)
{
	for (int n = 0; n < level; n++)
		s << " ";
	return s;
}

std::ostream& eoArchiveTXT::startBlock(std::ostream &s, uint8_t level)
{
	s << std::endl;
	for (int n = 0; n < level; n++)
		s << " ";
	s << "{" << std::endl;
	return s;
}

std::ostream& eoArchiveTXT::endBlock(std::ostream &s, uint8_t level)
{
	for (int n = 0; n < level; n++)
		s << " ";
	s << "}" << std::endl;
	return s;
}

void eoArchiveTXT::indent()
{
	indent((myFile), level);
}

void eoArchiveTXT::startBlock(const char* blockName)
{
	indent();
	(myFile) << blockName;
	startBlock((myFile), level);
	level++;
}

void eoArchiveTXT::startBlock()
{
	if (isStoring)
		startBlock((myFile), level);
	else
		newBlock = true;
	level++;
}
void eoArchiveTXT::endBlock()
{
	level--;
	if (isStoring)
		endBlock((myFile), level);
	else
		curName.erase(curName.rfind('.'));
}

void eoArchiveTXT::Close()
{
	myFile.close();
	blockItems.clear();
}
eoArchive& eoArchiveTXT::operator &(char *obj)
{
	if (!myFile.is_open())
		return *this;
	if (isStoring)
	{
		if (isName)
		{
			indent();
			(myFile) << obj << ':';
			isName = false;
		}
		else
		{
			isName = true;

			(myFile) << obj << std::endl;
		}
	}
	else
	{
		if (isName)
		{

			if (level != 0)
			{
				if (curName.rfind('.') != std::string::npos && !newBlock)
					curName.erase(curName.rfind('.'));
				curName += ".";
				curName += obj;
			}
			else
			{
				curName = obj;
			}
			newBlock = false;
			isName = false;
		}
		else
		{
			//delete[] obj;
			if (blockItems.find(curName) == blockItems.end())
				obj[0] = '\0';
			//	else
			//		strncpy(obj,blockItems[curName].c_str(),(int)blockItems[curName].size());
			isName = true;
		}
	}
	return *this;
}

eoArchive& eoArchiveTXT::operator &(char const *obj)
{
	if (!myFile.is_open())
		return *this;
	if (isStoring)
	{
		if (isName)
		{
			indent();
			myFile << obj << ':';
			isName = false;
		}
		else
		{
			isName = true;
			(myFile) << obj << std::endl;
		}
	}
	else
	{
		if (isName)
		{
			if (level != 0)
			{
				if (curName.rfind('.') != std::string::npos && !newBlock)
					curName.erase(curName.rfind('.'));
				curName += ".";
				curName += obj;
			}
			else
			{
				curName = obj;
			}
			newBlock = false;
			isName = false;
		}
		else
		{
			//Not supported!
			isName = true;
		}
	}
	return *this;
}

void eoArchiveTXT::ExchangeInt(int &obj)
{
	if (isName)
		return;
	isName = true;
	if (isStoring)
	{
		(myFile) << "0x" << std::hex << obj << std::endl;
	}
	else
	{
		if (blockItems.find(curName) == blockItems.end())
			obj = 0;
		else
		{
			//line.substr(line.find(":")+1)
			std::string tmpString = blockItems[curName].substr(blockItems[curName].find("0x") + 2);
			std::istringstream si(tmpString);
			uint32_t tmpInt;
			si >> std::hex >> tmpInt;
			obj = (int) tmpInt;
		}
	}
}

eoArchive & eoArchiveTXT::operator &(uint8_t &obj)
{
	int exchange = obj;
	ExchangeInt(exchange);
	obj = (uint8_t)exchange;
	return *this;
}
eoArchive & eoArchiveTXT::operator &(int8_t &obj)
{
	int exchange = obj;
	ExchangeInt(exchange);
	obj = (uint8_t)exchange;
	return *this;
}
eoArchive & eoArchiveTXT::operator &(uint16_t &obj)
{
	int exchange = obj;
	ExchangeInt(exchange);
	obj = (uint16_t)exchange;
	return *this;
}
eoArchive & eoArchiveTXT::operator &(int16_t &obj)
{
	int exchange = obj;
	ExchangeInt(exchange);
	obj = (uint16_t)exchange;
	return *this;
}

eoArchive & eoArchiveTXT::operator &(uint32_t &obj)
{
	int exchange = obj;
	ExchangeInt(exchange);
	obj = exchange;
	return *this;
}
eoArchive & eoArchiveTXT::operator &(int32_t &obj)
{
	int exchange = obj;
	ExchangeInt(exchange);
	obj = exchange;
	return *this;
}

eoArchive & eoArchiveTXT::operator &(float &obj)
{
	if (isName)
		return *this;
	isName = true;
	if (isStoring)
	{
		(myFile) << std::dec << obj << std::endl;
	}
	else
	{
		std::istringstream si(blockItems[curName]);
		si >> std::dec >> obj;
	}
	return *this;
}

eoArchive & eoArchiveTXT::operator &(bool &obj)
{
	if (isName)
		return *this;
	isName = true;
	if (isStoring)
	{
		if (obj)
			(myFile) << "TRUE" << std::endl;
		else
			(myFile) << "FALSE" << std::endl;
	}
	else
	{
		if (blockItems[curName] == "TRUE")
			obj = true;
		else if (blockItems[curName] == "FALSE")
			obj = false;
	}
	return *this;
}

eoArchive& eoArchiveTXT::operator &(eoISerialize *obj)
{
	//id
	if (isName)
		return *this;
	isName = true;
	if (isStoring)
		myFile.seekg(-1, std::ios::cur);

	startBlock();
	if (obj != NULL)
		obj->Serialize(*this);
	endBlock();

	return *this;
}

eoArchive & eoArchiveTXT::operator &(eoISerialize &obj)
{
	if (isName )
		return *this;
	isName = true;
	if (isStoring)
		myFile.seekg(-1, std::ios::cur);

	startBlock();
	obj.Serialize(*this);
	endBlock();

	return *this;
}

