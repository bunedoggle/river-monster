/**
 * \file   eoLink.h
 * \author EnOcean GmbH
 * \date   August, 20th, 2013
 * \version 1.2.0.0
 * \brief  EnOcean Link Main Header
 * The Main Header to include into your Project File
 \mainpage EnOcean Link Manual
 \tableofcontents
 \section int Introduction  
 EnOcean Link is a powerful library to handle packets, telegrams and messages received in an ESP3 Format.

 Using EnOcean Link you can write your own Application in a few easy steps, and uses it function to handle for you the most common EnOcean Tasks.

 The following features are included:
 - EnOcean Equipment Profile 2.5 and Generic Profiles data Handling
 + Set and Get Values as float or integer(depending on the datatype). See eoProfile::SetValue and   eoProfile::GetValue
 + Handling the Teach-IN Process for you. See eoTeachInModule and eoGateway.
 - Security Teach-IN and decryption (eoSecurity and eoGateway)
 - Sending and Receiving of telegrams
 - Storing and loading of configurations in an human readable Version
 - Message Chaining
 - Remote Management
 - Serial Commands Interface with eoSerialCommand
 - Different Software filter, to filter telegrams
 + You can implement your own Filter, using the IFitler class
 
 \note In the following document about EnOcean Link, it is assumed that you've a basic concept about EEP2.1,ESP3,GP and EnOcean world itself.
 
 The current release contains a eoPacketStream reader for Linux only (eoLinuxPacketStream).

 All examples & tutorials have been tested on a Linux x86 PC.
 
 To start use the  \ref stepbystep Guide

 \section libs Used Libraries
 EnOcean Link uses the following libraries for the Linux based Implementation
 - std::map
 - std::vector
 - std::list
 - std::string
 - std::set
 - std::iostream
 - <time.h>
 - ctime
 - <termios.h>
 - <fcntl.h>
 - <stdint.h>
 - <math.h>

 If you want to integrate EnOcean Link to other platforms/os system you've to create your own PacketStream class to handle receive/sendByte and your own Timer Class.

 \section def Defines
 - Gateway : eoGateway
 - Packet: eoPacket
 - Message : eoMessage
 - Telegram : eoTelegram
 
 \section con Continue Reading
 - \ref stepbystep
 - \ref tut
 - \ref refs


 \page refs References
 <b>Referenced EnOcean Specification Documents:</b>\n
 <ul>
 <li>[ESP3 - EnOcean Serial Protocol 3](http://www.enocean.com/en/esp3/)</li>
 <li>[EEP2.5 - EnOcean Equipment Protocol](http://www.enocean-alliance.org/eep/)</li> 
 <li>[GP]() not yet relesead</li>
 </ul>
 \n
 <b>Usefull Links for developers:</b>\n
 <ul>
 <li>[Knowledge Base](http://www.enocean.com/en/knowledge-base/) find here all developer documentation and specifications e.g. Radio Protocol</li>
 <li>[GatewayController Firmware User manual - TCM 310](http://www.enocean.com/en/enocean_modules/tcm-310/)</li>
 <li>[GatewayController Firmware User manual - USB 300](http://www.enocean.com/en/enocean_modules/usb-300-oem/)</li> 
 <li>[Software Product page](http://www.enocean.com/en/download/)</li>
 </ul>

 \example tutorial1.cpp 
 \example tutorial2.cpp 
 \example tutorial3.cpp
 \example tutorial4.cpp
 \example tutorial5.cpp
 \example tutorial6.cpp
 \example HelloWorld.cpp
 */

/**
 * @defgroup <apiinterface API Interface 
 * @{
 * \brief This section describes most improtant part of EnOcean Link API interface to the application.
 * \class eoConverter
 * \class eoDebug
 * \class eoDebugLogger
 * \class eoTimer     
 * @}    
 */   

/**
 *@defgroup <eepProfiles EEP2.5 Profiles API Interface
 * \brief This section describes most improtant part of EnOcean Equipment profiles. 
 *  In all classes are tables available that show the translation into CHANNEL_TYPE. 
 *  All profiles have mapped all channels. If profile has two same CHANNEL_TYPE they are differed by index aka subtype. 
 *  The subtype is specific for every profile or profile family. 
 * @{ 
 * @ingroup apiinterface
 * \class eoEEPChannelInfo 
 * \class eoManufacturer       
 * @} 
 */

/**
 *@defgroup <gpProfiles Generic Profile Interface
 * \brief This section describes most improtant part of Generic profiles. This part is still not full released since the TWG has not completely released the Generic Profile Specification.  
 * @{ 
 * @ingroup apiinterface
 * \class eoGenericProfile
 * \class eoGPChannelInfo
 * \class eoManufacturer       
 * @} 
 */

/**
 *@defgroup <gateway Gateway API Interface
 * @{
 * \brief This section describes the Gateway functionality and cooperation with GatewayController firmware. 
 * @ingroup apiinterface
 * \class eoGateway 
 * \class eoDevice
 * \class eoDeviceManager
  
 * 
 * \class eoMessage
 * \class eoPacket
 * \class eoChannelInfo 
 * 
 * \class TEACH_STRUCT  
 * @}
 *  
 *@defgroup filters Filters
 * @{
 * \brief This section describes the filter functionality of the Gateway.  
 * @ingroup gateway
 * \class eodBmFilter
 * \class eoIDFilter
 * \class eoIFilter 
 * @} 
 * 
 *@defgroup remote Remote Management API Interface
 * @{
 * \brief This section shows the functions and structures used for remote management.  
 * @ingroup gateway
 * \class eoRemoteManager   
 * \class FLASH_READ_RESPONSE
 * \class LEARNED_SENSOR_RESPONSE
 * \class MAILBOX_SETTINGS_RESPONSE
 * \class PING_RESPONSE
 * \class QUERY_FUNCTION_RESPONSE
 * \class QUERY_ID
 * \class QUERY_STATUS_RESPONSE 
 * @}
 * 
 *@defgroup esp3 ESP 3 Command Support
 * @{
 * \brief This part holds the structures for the support of COMMON COMMANDs from EnOcen Serial Protocol. 
 * @ingroup gateway
 * \class eoGateway
 * \class eoSerialCommand 
 * \class CO_RD_FILTER_RESPONSE
 * \class CO_RD_IDBASE_RESPONSE
 * \class CO_RD_REPEATER_RESPONSE
 * \class CO_RD_VERSION_RESPONSE
 * \class CO_READY_RESPONSE
 * @}
 * 
 *@defgroup smack Smart Acknowledge Support
 *\brief This section holds the functions and structures used for smart acknowledge. Smart Acknowledge Lrn is part of the normal teach in process too. 
 * @{
 * @ingroup gateway 
 * \class eoSerialCommand 
 * \class SA_LEARN_ACK_RESPONSE
 * \class SA_RD_LEARNEDCLIENTS_RESPONSE
 * \class SA_RD_LEARNMODE_RESPONSE
 * \class SA_CONFIRM_LEARN_RESPONSE
 * @}   
 */


/**
 *@defgroup <storage Storage API Interface 
 * @{
 *@ingroup apiinterface 
 * \class eoRollingCodeStorage
 * \class serialize_object   
 * @} 
 */    
   
 
#ifndef EOLINK_H_
#define EOLINK_H_

//! Main Version number.
#define EOLINK_VERSION_MAIN			1
//! Beta Version number.
#define EOLINK_VERSION_BETA			0
//! Alpha Version number.
#define EOLINK_VERSION_ALPHA		0
//! Build Version number.
#define EOLINK_VERSION_POINT		0

/*
#include "Includes/eoApiDef.h"
#include "Includes/eoHalTypes.h"
#include "Includes/eoDebug.h"
#include "Includes/eoConverter.h"
#include "Includes/eoGateway.h"
#include "Includes/eoDevice.h"
#include "Includes/eoStorageManager.h"
#include "Includes/eoPacketStream.h"
#include "Includes/eoTimer.h"
#include "Includes/eoIFilter.h"
#include "Includes/eoIDFilter.h"
#include "Includes/eodBmFilter.h"
#include "Includes/eoFilterFactory.h"
#include "Includes/eoProfileFactory.h"
#include "Includes/eoRemoteManager.h"
#include "Includes/eoSerialCommand.h"
#include "Storage/eoRollingCodeStorage.h"
#include "Includes/eoReManChainer.h"
#include "Includes/eoGenericProfile.h"
*/
#include "Includes/eoAbstractMessage.h"
#include "Includes/eoApiDef.h"
#include "Includes/eoArchive.h"
#include "Includes/eoArchiveTXT.h"
#include "Includes/eoChannelEnums.h"
#include "Includes/eoChannelInfo.h"
#include "Includes/eoConverter.h"
#include "Includes/eodBmFilter.h"
#include "Includes/eoDebug.h"
#include "Includes/eoDevice.h"
#include "Includes/eoDeviceManager.h"
#include "Includes/eoEEProfile.h"
#include "Includes/eoFilterFactory.h"
#include "Includes/eoGateway.h"
#include "Includes/eoHalTypes.h"
#include "Includes/eoHeader.h"
#include "Includes/eoIDFilter.h"
#include "Includes/eoIFilter.h"
#include "Includes/eoISerialize.h"
#include "Includes/eoLinuxPacketStream.h"
#include "Includes/eoManufacturer.h"
#include "Includes/eoMessage.h"
#include "Includes/eoPacket.h"
#include "Includes/eoPacketStream.h"
#include "Includes/eoProc.h"
#include "Includes/eoProfileFactory.h"
#include "Includes/eoProfile.h"
#include "Includes/eoSerialCommand.h"
#include "Includes/eoStorageManager.h"
#include "Includes/eoTeachInModule.h"
#include "Includes/eoTelegram.h"
#include "Includes/eoTimer.h"

#endif /* EOLINK_H_ */
