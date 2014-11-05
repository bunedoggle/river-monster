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
 * \file eoDeviceManager.h
 * \brief eoDeviceManager
 * \author EnOcean GmBH
 */
#if !defined(_DEVICE_MANAGER_H)
#define _DEVICE_MANAGER_H

class eoDevice;
class eoArchive;
#include "eoHalTypes.h"
#include "eoISerialize.h"

#include <map>
/**
 * A std::map using the Device ID as key, and containing eoDevice as values.
 */
typedef std::map<uint32_t, eoDevice*> id_device_map;
/**\class eoDeviceManager
 * \brief Manages the devices
 * \details The DeviceManagaer helps you to manage different devices. Using it functions you can get a eoDevice Pointer to the Devices.
 * \example deviceManager_example.cpp
 */
class eoDeviceManager: public eoISerialize
{

public:
	/**
	 * Constructor
	 */
	eoDeviceManager();
	~eoDeviceManager();
	/**
	 * It a device with same id already exist, returns a pointer to this Device
	 * otherwise adds a device with the id to the device manager
	 * @param id The SourceID of the Device
	 * @return Pointer to the Device
	 */
	eoDevice* Add(uint32_t id);
	/**
	 * Searches for the id in the DeviceManager and returns a Device pointer if there was a device found otherwise NULL
	 * @param id The SourceID of the Device
	 * @return Pointer to the Device
	 */
	eoDevice* Get(uint32_t id);
	/**
	 * Removes the Device from the DeviceManager if the Device exists
	 * @param id of the Device to Delete
	 */
	void Remove(uint32_t id);
	/**
	 * Returns the map containing all the Devices.
	 * @return Reference to the id_device_map of the DeviceManager
	 */
	const id_device_map & GetDeviceList() const;
	/**
	 * Gets the number of Devices in the DeviceManager
	 * @return number of Devices
	 */
	uint32_t Size() const;

	uint8_t Serialize(eoArchive &a);

private:
	id_device_map list;

};

#endif // !defined(_DEVICE_MANAGER_H)
