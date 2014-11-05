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
 * \file eoChannelEnums.h
 * \brief Contains Channel Enums
 * \author EnOcean GmBH
 */
#ifndef _eoCHANNELENUMS_H
#define	_eoCHANNELENUMS_H

#include "eoHalTypes.h"
//STOP CHANGING THEM!

//!Data type flag
#define	T_DATA 0x0000

//!Flag type flag
#define	T_FLAG 0x0F00
//!Enum type flag
#define	T_ENUM 0xE000

//! Absolute Setpoint
#define	SP_ABS 0x1000
//! Relative Setpoint
#define	SP_REL 0x2000

//!Number of named signals 
#define NUM_SIGNAL_STRINGS 0x2C
//!List of named signal types. When you add a new channel type, you've to update the description!!
const char signalStrings[NUM_SIGNAL_STRINGS][2][26] =
{
{ "N/A", "N/A" },
{ "Acceleration", "m/s^2" }, // 00000001	=	Acceleration m/s^2
{ "Angle", "degrees" }, // 00000010	=	Angle degrees
{ "Angular velocity", "degrees/s" },
{ "Area", "m^2" },
{ "Concentration", "ppm" },
{ "Current", "Amps" },
{ "Distance", "meters" },
{ "Electric field strength", "V/m" },
{ "Energy", "J - W*s" },
{ "Enumeration", "N/A" },
{ "Force", "Newtons" },
{ "Frequency", "Hz" },
{ "Heat flux density", "W/m^2/s" },
{ "Impulse", "N*s/kg" },
{ "Luminance intensity", "Lux" },
{ "Magnetic field strength", "A/m" },
{ "Mass", "kg" },
{ "Mass density", "kg/m^3" },
{ "Mass flow", "kg/s" },
{ "Power", "Watts" },
{ "Pressure", "Pascals" },
{ "Relative humidity", "Percent" },
{ "Resistance", "Ohms" },
{ "Temperature", "Deg C" },
{ "Time", "Seconds" },
{ "Torque", "N*m" },
{ "Velocity", "m/s" },
{ "Voltage", "Volts" },
{ "Volume", "m^3" },
{ "Volumetric Flow", "m^3/s" },
{ "Set point", "number" },
{ "Particles", "ug/m^3"},
{ "Dimming", "n/a"},
{ "Solar radiation", "W/m^2"},
{ "Percentage", "%"},
{ "Value", "n/a"},
{ "RGB", "n/a"},
{ "Error code", "n/a"},
};

//!Number of named flags
#define NUM_FLAG_STRINGS 0x11
//!String names for flag channles
const char flagStrings[NUM_FLAG_STRINGS][32] =
{ "",
"Automatic flag",
"Button pressed",// 00000010	=	Button pressed (1 when pressed, 0 when not changed)
"Button released",// 00000011	=	Button released (1 when released, 0 when not changed)
"Button triggered",	// 00000100	=	Button triggered *
"Day/Night",	// 00000101	=	Day(1) / night(0)
"Down",	// 00000110	=	Down "-" (1 when pressed)
"General alarm",	// 00000111	=	General alarm (1)
"Heat (1) / cool (0)",	// 00001000	=	Heat (1) / cool (0)
"High (1) / low (0)",	// 00001001	=	High (1) / low (0)
"Occupied (1) / unoccupied (0)",// 00001010	=	Occupied (1) / unoccupied (0)
"On (1) / off (0)",	// 00001011	=	On (1) / off (0)
"Open (1) / closed (0)",	// 00001100	=	Open (1) / closed (0)
"Power alarm (1)",	// 00001101	=	Power alarm (1)
"Start (1) / stop (0)",	// 00001110	=	Start (1) / stop (0)
"Up 'p'",	// 00001111	=	Up "+" (1 when pressed)
"Vibration(1) / No vibration (0)", // 00010000	=	Vibration (1) / No vibration (0)
};

//!Number of named enums
#define NUM_ENUMS_STRINGS 0x20
//!String names for enum channles
const char enumStrings[NUM_ENUMS_STRINGS][32] =
{
"",
"Rocker Button A",
"Rocker Button B",
"Rocker Button C",
"Rocker Button D",
"Energybow direction",
"Multiple Buttons pressed?",
"Windowhandle",
"Fan Speed",
"Tariff information",
"VOC (Volatile organic compound)",
"Controller mode",
"Error state",
"State",
"End position",
"Occupancy",
"User action",
"Presence",
"Dim value",
"Input/Output channel",
"Units",
"Days",
"Commands"
};


/**
 * \ingroup eepProfiles
 * The Channel Type contains all defined Signal Types, Flag Types and Enumeration Types.
 * Every Type Group is a 8bit value + a type group specific offset.
 * \note Signal Types are floating point and Enums/Flags are uint8_t
 */
typedef enum
{

	S_RES = 0x00,	//!< S_RES
	// Signal data types - float
	//! <b>1</b> - Acceleration m/s^2
	S_ACCEL = 0x01,					// 00000001	=	Acceleration m/s^2    
	//! Acceleration m/s^2 - absolute setpoint
	S_ACCEL_ABS = S_ACCEL + SP_ABS, 	// Absolute setpoint    
	//! Acceleration m/s^2 - relative setpoint
	S_ACCEL_REL = S_ACCEL + SP_REL, 	// Relative setpoint
	//! <b>2</b> - Angle in degrees
	S_ANGLE = 0x02,		// 00000010	=	Angle degrees  
	//! Angle in degrees - absolute setpoint
	S_ANGLE_ABS = S_ANGLE + SP_ABS, 	// Absolute setpoint  
	//! Angle in degrees - relative setpoint
	S_ANGLE_REL = S_ANGLE + SP_REL, 	// Relative setpoint
	//! <b>3</b> - Angular velocity degrees/s
	S_ANGVD = 0x03,		// 00000011	=	Angular velocity degrees/s      
	//! Angular velocity degrees/s - absolute setpoint
	S_ANGVD_ABS = S_ANGVD + SP_ABS, 	// Absolute setpoint     
	//! <b>3</b> - Angular velocity degrees/s
	S_ANGVD_REL = S_ANGVD + SP_REL, 	// Relative setpoint
	//! <b>4</b> - Area m^2
	S_AREA = 0x04,		// 00000100	=	Area m^2   
	//! Area m^2 - absolute setpoint
	S_AREA_ABS = S_AREA + SP_ABS, 		// Absolute setpoint 
	//! Area m^2 - relative setpoint
	S_AREA_REL = S_AREA + SP_REL, 		// Relative setpoint
	//! <b>5</b> - Concentration ppm
	S_CONC = 0x05,		// 00000101	=	Concentration ppm  
	//! Concentration ppm - absolute setpoint
	S_CONC_ABS = S_CONC + SP_ABS, 		// Absolute setpoint
	//! Concentration ppm - relative setpoint
	S_CONC_REL = S_CONC + SP_REL, 		// Relative setpoint
	//! <b>6</b> - Concentration ppm
	S_CURRENT = 0x06,		// 00000110	=	Current Amps
	//! Concentration ppm - absolute setpoint
	S_CURRENT_ABS = S_CURRENT + SP_ABS,	// Absolute setpoint 
	//! Concentration ppm - relative setpoint
	S_CURRENT_REL = S_CURRENT + SP_REL, 	// Relative setpoint
	//! <b>7</b> - Distance meters
	S_DISTANCE = 0x07,		// 00000111	=	Distance meters 
	//! Distance meters - absolute setpoint
	S_DISTANCE_ABS = S_DISTANCE + SP_ABS, 	// Absolute setpoint 
	//! Distance meters - relative setpoint
	S_DISTANCE_REL = S_DISTANCE + SP_REL, 	// Relative setpoint
	//! <b>8</b> - Electric field strength V/m
	S_ELECFSTR = 0x08,		// 00001000	=	Electric field strength V/m 
	//! Electric field strength V/m - absolute setpoint
	S_ELECFSTR_ABS = S_ELECFSTR + SP_ABS, 	// Absolute setpoint 
	//! Electric field strength V/m - relative setpoint
	S_ELECFSTR_REL = S_ELECFSTR + SP_REL, 	// Relative setpoint
	//! <b>9</b> -Energy W*h
	S_ENERGY = 0x09,		// 00001001	=	Energy J - W*s 
	//! Energy W*h - absolute setpoint
	S_ENERGY_ABS = S_ENERGY + SP_ABS, 	// Absolute setpoint
	//! Energy W*h - relative setpoint
	S_ENERGY_REL = S_ENERGY + SP_REL, 	// Relative setpoint
	//! <b>10</b> - Counter
	S_COUNTER = 0x0A,		// 00001010	=	Counter  
	//! Counter - absolute setpoint
	S_COUNTER_ABS = S_COUNTER + SP_ABS, 	// Absolute setpoint
	//! Counter - relative setpoint
	S_COUNTER_REL = S_COUNTER + SP_REL, 	// Relative setpoint
	//! <b>11</b> - Force Newtons
	S_FORCE = 0x0B,		// 00001011	=	Force Newtons
	//! Force Newtons - absolute setpoint
	S_FORCE_ABS = S_FORCE + SP_ABS, 	// Absolute setpoint 
	//! Force Newtons - relative setpoint
	S_FORCE_REL = S_FORCE + SP_REL, 	// Relative setpoint
	//! <b>12</b> - Frequency Hz
	S_FREQ = 0x0C,		// 00001100	=	Frequency Hz   
	//! Frequency Hz - absolute setpoint
	S_FREQ_ABS = S_FREQ + SP_ABS, 		// Absolute setpoint 
	//! Frequency Hz - relative setpoint
	S_FREQ_REL = S_FREQ + SP_REL, 		// Relative setpoint
	//! <b>13</b> - Heat flux density W/m^2/s
	S_HEATFLUX = 0x0D,		// 00001101	=	Heat flux density W/m^2/s
	//! Heat flux density W/m^2/s - absolute setpoint
	S_HEATFLUX_ABS = S_HEATFLUX + SP_ABS, 	// Absolute setpoint
	//! Heat flux density W/m^2/s - relative setpoint
	S_HEATFLUX_REL = S_HEATFLUX + SP_REL, 	// Relative setpoint
	//! <b>14</b> - Impulse N*s/kg
	S_IMPULSE = 0x0E,		// 00001110	=	Impulse N*s/kg  
	//! Impulse N*s/kg - absolute setpoint
	S_IMPULSE_ABS = S_IMPULSE + SP_ABS, 	// Absolute setpoint 
	//! Impulse N*s/kg - relative setpoint
	S_IMPULSE_REL = S_IMPULSE + SP_REL, 	// Relative setpoint
	//! <b>15</b> -Luminance intensity Lux
	S_LUMINANCE = 0x0F,		// 00001111	=	Luminance intensity Lux    
	//! Luminance intensity Lux - absolute setpoint
	S_LUMINANCE_ABS = S_LUMINANCE + SP_ABS, // Absolute setpoint 
	//! Luminance intensity Lux - relative setpoint
	S_LUMINANCE_REL = S_LUMINANCE + SP_REL, // Relative setpoint
	//! <b>16</b> - Magnetic field strength A/m
	S_MAGNETICF = 0x10,		// 00010000	=	Magnetic field strength A/m 
	//! Magnetic field strength A/m - absolute setpoint
	S_MAGNETICF_ABS = S_MAGNETICF + SP_ABS, // Absolute setpoint  
	//! Magnetic field strength A/m - relative setpoint
	S_MAGNETICF_REL = S_MAGNETICF + SP_REL, // Relative setpoint
	//! <b>17</b> - Mass kg
	S_MASS = 0x11,		// 00010001	=	Mass kg          
	//! Mass kg - absolute setpoint
	S_MASS_ABS = S_MASS + SP_ABS, 		// Absolute setpoint
	//! Mass kg - relative setpoint
	S_MASS_REL = S_MASS + SP_REL, 		// Relative setpoint
	//! <b>18</b> - Mass density kg/m^3
	S_MASSDENS = 0x12,		// 00010010	=	Mass density kg/m^3  
	//! Mass density kg/m^3 - absolute setpoint
	S_MASSDENS_ABS = S_MASSDENS + SP_ABS, 	// Absolute setpoint  
	//! Mass density kg/m^3 - relative setpoint
	S_MASSDENS_REL = S_MASSDENS + SP_REL, 	// Relative setpoint
	//! <b>19</b> - Mass flow kg/s
	S_MASSFLOW = 0x13,		// 00010011	=	Mass flow kg/s 
	//! Mass flow kg/s - absolute setpoint
	S_MASSFLOW_ABS = S_MASSFLOW + SP_ABS, 	// Absolute setpoint 
	//! Mass flow kg/s - relative setpoint
	S_MASSFLOW_REL = S_MASSFLOW + SP_REL, 	// Relative setpoint
	//! <b>20</b> - Power Watts in W
	S_POWER = 0x14,		// 00010100	=	Power Watts  
	//! <Power Watts in W - absolute setpoint
	S_POWER_ABS = S_POWER + SP_ABS, 	// Absolute setpoint
	//! Power Watts in W - relative setpoint
	S_POWER_REL = S_POWER + SP_REL, 	// Relative setpoint
	//! <b>21</b> - Pressure Pascals
	S_PRESSURE = 0x15,		// 00010101	=	Pressure Pascals   
	//! Pressure Pascals - absolute setpoint
	S_PRESSURE_ABS = S_PRESSURE + SP_ABS, 	// Absolute setpoint 
	//! Pressure Pascals - relative setpoint
	S_PRESSURE_REL = S_PRESSURE + SP_REL, 	// Relative setpoint
	//! <b>22</b> - Relative humidity Percent
	S_RELHUM = 0x16,		// 00010110	=	Relative humidity Percent
	//! Relative humidity Percent - absolute setpoint
	S_RELHUM_ABS = S_RELHUM + SP_ABS, 	// Absolute setpoint
	//! Relative humidity Percent - relative setpoint
	S_RELHUM_REL = S_RELHUM + SP_REL, 	// Relative setpoint
	//! <b>23</b> - Resistance Ohms
	S_RESIST = 0x17,		// 00010111	=	Resistance Ohms
	//! Resistance Ohms - absolute setpoint
	S_RESIST_ABS = S_RESIST + SP_ABS, 	// Absolute setpoint
	//! Resistance Ohms - relative setpoint
	S_RESIST_REL = S_RESIST + SP_REL, 	// Relative setpoint
	//! <b>24</b> - Temperature Deg C
	S_TEMP = 0x18,		// 00011000	=	Temperature Deg C 
	//! Temperature Deg C - absolute setpoint
	S_TEMP_ABS = S_TEMP + SP_ABS, 		// Absolute setpoint
	//! Temperature Deg C - relative setpoint
	S_TEMP_REL = S_TEMP + SP_REL, 		// Relative setpoint
	//! <b>25</b> - Time Seconds
	S_TIME = 0x19,		// 00011001	=	Time Seconds     
	//! Time Seconds - absolute setpoint
	S_TIME_ABS = S_TIME + SP_ABS, 		// Absolute setpoint
	//! Time Seconds - relative setpoint
	S_TIME_REL = S_TIME + SP_REL, 		// Relative setpoint
	//! <b>26</b> - Torque N*m
	S_TORQUE = 0x1A,		// 00011010	=	Torque N*m  
	//! Torque N*m - absolute setpoint      
	S_TORQUE_ABS = S_TORQUE + SP_ABS, 	// Absolute setpoint 
	//! Torque N*m - relative setpoint
	S_TORQUE_REL = S_TORQUE + SP_REL, 	// Relative setpoint
	//! <b>27</b> - Velocity m/s
	S_VELOCITY = 0x1B,		// 00011011	=	Velocity m/s
	//! Velocity m/s - absolute setpoint
	S_VELOCITY_ABS = S_VELOCITY + SP_ABS, 	// Absolute setpoint
	//! Velocity m/s - relative setpoint
	S_VELOCITY_REL = S_VELOCITY + SP_REL, 	// Relative setpoint
	//! <b>28</b> - Voltage Volts
	S_VOLTAGE = 0x1C,		// 00011100	=	Voltage Volts         
	//! Voltage Volts - absolute setpoint
	S_VOLTAGE_ABS = S_VOLTAGE + SP_ABS, 	// Absolute setpoint 
	//! Voltage Volts - relative setpoint
	S_VOLTAGE_REL = S_VOLTAGE + SP_REL, 	// Relative setpoint 
	//! <b>29</b> - Volume m^3
	S_VOLUME = 0x1D,		// 00011101	=	Volume m^3    
	//! Volume m^3 - relative setpoint
	S_VOLUME_ABS = S_VOLUME + SP_ABS, 	// Absolute setpoint 
	//! Volume m^3 - absolute setpoint
	S_VOLUME_REL = S_VOLUME + SP_REL, 	// Relative setpoint
	//! <b>30</b> -Volumetric Flow m^3/s
	S_VOLFLOW = 0x1E,		// 00011110	=	Volumetric Flow m^3/s  
	//! Volumetric Flow m^3/s - absolute setpoint
	S_VOLFLOW_ABS = S_VOLFLOW + SP_ABS, 	// Absolute setpoint  
	//! Volumetric Flow m^3/s - relative setpoint
	S_VOLFLOW_REL = S_VOLFLOW + SP_REL, 	// Relative setpoint
	//! <b>31</b> - Setpoint
	S_SETPOINT = 0x1F,		// 00011111	=	Setpoint  
	//! Setpoint - absolute setpoint
	S_SETPOINT_ABS = S_SETPOINT + SP_ABS, 	// Absolute setpoint 
	//! Setpoint - relative setpoint
	S_SETPOINT_REL = S_SETPOINT + SP_REL, 	// Relative setpoint
	//! <b>32</b> - Particles
	S_PARTICLES = 0x20,		// 00100000	=	Particles ug/m^3  
	//! Particles - absolute setpoint
	S_PARTICLES_ABS = S_PARTICLES + SP_ABS, // Absolute setpoint 
	//! Particles - relative setpoint
	S_PARTICLES_REL = S_PARTICLES + SP_REL, // Relative setpoint
	//! <b>33</b> - Dimming
	S_DIMMING = 0x21,		// 00100001	=	Dimming   
	//! Dimming - absolute setpoint
	S_DIMMING_ABS = S_DIMMING + SP_ABS, // Absolute setpoint
	//! Dimming - relative setpoint
	S_DIMMING_REL = S_DIMMING + SP_REL, // Relative setpoint
	//! <b>34</b> - Solar radiation
	S_SOLAR_RAD = 0x22,		// 00100010	=	Solar radiation 
	//! Solar radiation - absolute setpoint
	S_SOLAR_RAD_ABS = S_SOLAR_RAD + SP_ABS, // Absolute setpoint
	//! Solar radiation - relative setpoint
	S_SOLAR_RAD_REL = S_SOLAR_RAD + SP_REL, // Relative setpoint
	//! <b>35</b> - Percentage %
	S_PERCENTAGE = 0x23,		// 00100011	=	Percentage % 
	//! Percentage % - absolute setpoint
	S_PERCENTAGE_ABS = S_PERCENTAGE + SP_ABS, // Absolute setpoint 
	//! Percentage % - relative setpoint
	S_PERCENTAGE_REL = S_PERCENTAGE + SP_REL, // Relative setpoint
	//! <b>36</b> - Value
	S_VALUE = 0x24,		// 00100100	=	Value  
	//! Value - absolute setpoint
	S_VALUE_ABS = S_VALUE + SP_ABS, // Absolute setpoint 
	//! Value - relative setpoint
	S_VALUE_REL = S_VALUE + SP_REL, // Relative setpoint
	//! <b>37</b> - RGB
	S_RGB = 0x25,		// 00100101	=	RGB    
	//! RGB - absolute setpoint
	S_RGB_ABS = S_RGB + SP_ABS, // Absolute setpoint 
	//! RGB - relative setpoint
	S_RGB_REL = S_RGB + SP_REL, // Relative setpoint
	//! <b>38</b> - Error code
	S_ERROR_CODE = 0x26,		// 00100110	=	Error code  
	//! Error code - absolute setpoint
	S_ERROR_CODE_ABS = S_ERROR_CODE + SP_ABS, // Absolute setpoint
	//! Error code - relative setpoint
	S_ERROR_CODE_REL = S_ERROR_CODE + SP_REL, // Relative setpoint

	//Enum flags...

	//! <b>T_ENUM + 1</b> - Rocker Button A ::ENUM_ROCKER_STATE
	E_ROCKER_A = T_ENUM + 0x01,	// Rocker A Button Information 0=I,1=O,2=Not pressed
	//! <b>T_ENUM + 2</b> - Rocker Button B ::ENUM_ROCKER_STATE
	E_ROCKER_B = T_ENUM + 0x02,	// Rocker B Button Information 0=I,1=O,2=Not pressed
	//! <b>T_ENUM + 3</b> - Rocker Button C ::ENUM_ROCKER_STATE
	E_ROCKER_C = T_ENUM + 0x03,	// Rocker B Button Information 0=I,1=O,2=Not pressed
	//! <b>T_ENUM + 4</b> - Rocker Button D ::ENUM_ROCKER_STATE
	E_ROCKER_D = T_ENUM + 0x04,	// Rocker B Button Information 0=I,1=O,2=Not pressed
	//! <b>T_ENUM + 5</b> - ::ENUM_ENERGY_STATE
	E_ENERGYBOW = T_ENUM + 0x05,	// Energy Bow pressed releases or pressed
	//! <b>T_ENUM + 6</b> - ::ENUM_MULTIPRESS_STATE;
	E_MULTIPRESS = T_ENUM + 0x06,// Rocker 1 Button Information 3 or more buttons pressed
	//! <b>T_ENUM + 7</b> - ::ENUM_WINDOW_STATE
	E_WINDOWHANDLE = T_ENUM + 0x07,	// Window handle enum
	//! <b>T_ENUM + 8</b> - ::ENUM_FAN_SPEED_5STAGE, ::ENUM_FAN_SPEED_7STAGE , ::CS_FAN_STAGE, ::HVCA_FANSPEED !! See EEP for selected profile!!
	E_FANSPEED = T_ENUM + 0x08,
	//! <b>T_ENUM + 9</b> - Tariff information
	E_TARIFF = T_ENUM + 0x09,
	//! <b>T_ENUM + 10</b> - ::ENUM_VOC VOC (Volatile organic compound) information
	E_VOC = T_ENUM + 0x0A,
	//! <b>T_ENUM + 11</b> - ::CS_ENUM_CONTROLLER_MODE, ::HVAC_MODE, ::HVCA_CONTROLLER_MODE
	E_CONTROLLER_MODE = T_ENUM + 0x0B,
	//! <b>T_ENUM + 12</b> - ::CS_ENUM_03_ERROR_STATE, ::CS_ENUM_04_ERROR_STATE, ::VLD_ERROR_LEVEL
	E_ERROR_STATE = T_ENUM + 0x0C, //Error state
	//! <b>T_ENUM + 13</b> - ::CS_ENUM_BLIND_STATE, ::CC_LOCKING_OPERATIONS, ::VLD_DEFAULT_STATE, ::VLD_SMOKE_DETECTION, ::VLD_QUERY_STATUS
	E_STATE = T_ENUM + 0x0D, //State
	//! <b>T_ENUM + 14</b> - ::CS_ENUM_END_POS, ::HVCA_VANE_POSITION
	E_END_POS = T_ENUM + 0x0E, //End position
	//! <b>T_ENUM + 15</b> - ::CS_ENUM_ROOM_OCCUPANCY, ::HVCA_ROOM_OCCUPANCY, ::HVCA_ROOM_OCCUPANCY_TYPE_20, ::CC_ROOM_OCCUPANCY 
	E_OCCUPANCY = T_ENUM + 0x0F, //Room occupancy
	//! <b>T_ENUM + 16</b> - ::CC_FUNCTIONS, ::RCP_USER_ACTION
	E_USER_ACTION = T_ENUM + 0x10, //User Action
	//! <b>T_ENUM + 17</b> - ::RCP_PRESENCE
	E_PRESENCE = T_ENUM + 0x11, //Presence
	//! <b>T_ENUM + 18</b> - ::VLD_DIM_VALUE
	E_DIM_VALUE = T_ENUM + 0x12, //Dim value
	//! <b>T_ENUM + 19</b> - ::VLD_IO_CHANNEL
	E_IO_CHANNEL = T_ENUM + 0x13, //Input/Output channel
	//! <b>T_ENUM + 20</b> - ::CC_ENERGY_UNITS, 
	E_UNITS = T_ENUM + 0x14, //Unit
	//! <b>T_ENUM + 21</b> - ::EA_ENUM_DAYS
	E_DAYS = T_ENUM + 0x15, //Days
	//! <b>T_ENUM + 22</b> - Commands for the VLD Families and EEP Profiles with more then one telegram type. 
	E_COMMAND = T_ENUM + 0x16, //Commands
	//! <b>T_ENUM + 23</b> - Directions for A5-20-xx profile
	E_DIRECTION = T_ENUM + 0x17, //Directions
	//! <b>T_ENUM + 24</b> - Room size for D2-20-xx profile
	E_ROOM_SIZE = T_ENUM + 0x18, //Room Size

	// Flag data types - uint8_t
	//! <b>T_FLAG + 0x01</b> Automatic (1) / manual (0)
	F_AUTO_MAN = T_FLAG + 0x01,	// 00000001	=	Automatic (1) / manual (0)
	//! <b>T_FLAG + 0x02</b> Button pressed (1 when pressed, 0 when not changed)
	F_BTN_PRESS = T_FLAG + 0x02,// 00000010	=	Button pressed (1 when pressed, 0 when not changed)
	//! <b>T_FLAG + 0x03</b> Button triggered *
	F_BTN_TRIGGER = T_FLAG + 0x03,	// 00000011	=	Button triggered *
	//! <b>T_FLAG + 0x04</b> Day(1) / night(0)
	F_DAY_NIGHT = T_FLAG + 0x04,	// 00000100	=	Day(1) / night(0)
	//! <b>T_FLAG + 0x05</b> Down "-" (1 when pressed)
	F_DOWN = T_FLAG + 0x05,	// 00000101	=	Down "-" (1 when pressed)
	//! <b>T_FLAG + 0x06</b> General alarm (1)
	F_GENALARM = T_FLAG + 0x06,	// 00000101	=	General alarm (1)
	//! <b>T_FLAG + 0x07</b> Heat (1) / cool (0)
	F_HEAT_COOL = T_FLAG + 0x07,	// 00000111	=	Heat (1) / cool (0)
	//! <b>T_FLAG + 0x08</b> High (1) / low (0)
	F_HIGH_LOW = T_FLAG + 0x08,	// 00001000	=	High (1) / low (0)
	//! <b>T_FLAG + 0x09</b> Occupied (1) / unoccupied (0)
	F_OCCUPIED = T_FLAG + 0x09,	// 00001001	=	Occupied (1) / unoccupied (0)
	//! <b>T_FLAG + 0x10</b> On (1) / off (0)
	F_ON_OFF = T_FLAG + 0x0A,	// 00001010	=	On (1) / off (0)
	//! <b>T_FLAG + 0x11</b> Open (1) / closed (0)
	F_OPEN_CLOSED = T_FLAG + 0x0B,	// 00001011	=	Open (1) / closed (0)
	//! <b>T_FLAG + 0x12</b> Power alarm (1)
	F_POWERALARM = T_FLAG + 0x0C,	// 00001100	=	Power alarm (1)
	//! <b>T_FLAG + 0x13</b> Start (1) / stop (0)
	F_START_STOP = T_FLAG + 0x0D,	// 00001101 =	Start (1) / stop (0)
	//! <b>T_FLAG + 0x14</b> Up "+" (1 when pressed)
	F_UP = T_FLAG + 0x0E,	// 00001110	=	Up "+" (1 when pressed)
	//! <b>T_FLAG + 0x15</b> Vibration (1) / No vibration (0)
	F_VIBRATION = T_FLAG + 0x0F,// 00001111	=	Vibration (1) / No vibration (0)
	F_RES = T_FLAG + 0xFF,	//< F_RES

} CHANNEL_TYPE;

//! Value types
typedef enum
{
	VAL_CURR = 0x01,		// 01 = Current value
	VAL_SP_ABS = 0x02,		// 10 = Setpoint absolute
	VAL_SP_REL = 0x03,		// 11 = Setpoint relative
} VALUE_TYPE;

//! Value Format
typedef enum
{
	VAL_UINT32 = 0x10,
	VAL_UINT8 = 0x20,
	VAL_FLAG = 0x30,
	VAL_FLOAT = 0x40,
	VAL_TIME = 0x50,
} VALUE_FORMAT;

#endif // _CHANNELENUMS_H
