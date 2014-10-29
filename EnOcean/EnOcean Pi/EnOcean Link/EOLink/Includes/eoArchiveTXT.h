/**
 * \file eoArchiveTXT.h
 * \brief contains human readable class
 * \author EnOcean GmBH
 */
#if !defined(_EOARCHIVETXT_H)
#define _EOARCHIVETXT_H

#include "eoArchive.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <map>

//!Name of the arvice
#define _ARCHIVE_TYPE_NAME "_HUMAN_ARCHIVE\0"
//!Version fo the archiver - MAJOR
#define _ARCHIVE_VER_MAJOR 0
//!Version fo the archiver - MINOR
#define _ARCHIVE_VER_MINOR 4
/**
 *\ingroup storage
 * @{
 * \class eoArchiveTXT
 * \brief Archive for Human readable Text files
 * \details this eoArchive is used to generate and parse Text Files for serialization.
 * Numbers are stored as hex value.
 */
typedef std::map<std::string, std::string> parsed_Items;
class eoArchiveTXT: public eoArchive
{
public:
	eoArchiveTXT();

	virtual ~eoArchiveTXT();

	virtual eoArchive& operator &(char const *obj);
	virtual eoArchive& operator &(char *obj);
//	virtual eoArchive&  operator  &(int &obj);
	virtual eoArchive& operator &(uint32_t &obj);
	virtual eoArchive& operator &(int32_t &obj);
	virtual eoArchive& operator &(uint16_t &obj);
	virtual eoArchive& operator &(int16_t &obj);
	virtual eoArchive& operator &(uint8_t &obj);
	virtual eoArchive& operator &(int8_t &obj);
	virtual eoArchive& operator &(float& obj);
	virtual eoArchive& operator &(bool &obj);
	virtual eoArchive& operator &(eoISerialize *obj);
	virtual eoArchive& operator &(eoISerialize &obj);
	/**
	 *Echange an stored integer.
	 *@param obj Intended object.
	 */      	
	void ExchangeInt(int &obj);

	virtual uint8_t Open(const char * strBuf);
	virtual void Close();


	void indent();
	void startBlock();
	void endBlock();

	void startBlock(const char* BlockName);
private:
	std::fstream myFile;

	// identifier for the current Level...
	std::string curName;

	bool newBlock;
	parsed_Items blockItems;
	eoReturn ParseFile();
	eoReturn ParseBlock(std::string blockName);
	static std::ostream& indent(std::ostream &s, uint8_t level);
	static std::ostream& startBlock(std::ostream &s, uint8_t level);
	static std::ostream& endBlock(std::ostream &s, uint8_t level);

};
/**
 @}
 */
#endif
