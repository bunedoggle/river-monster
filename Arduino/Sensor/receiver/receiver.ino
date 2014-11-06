
#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

//RH_ASK::RH_ASK(uint16_t speed, uint8_t rxPin, uint8_t txPin, uint8_t pttPin, bool pttInverted)
RH_ASK driver( 1200, 12, 3, 4, 5 );
//RH_ASK driver;

typedef struct {
	uint8_t id;
	uint32_t time;
	uint16_t temperature;
	uint16_t turbidity;	
	} PACKET_T;

PACKET_T data;

void setup()
{  
  Serial.begin(9600);	// Debugging only
  if (!driver.init())
       Serial.println("init failed");
}

void loop()
{
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);

    if (driver.recv(buf, &buflen)) // Non-blocking
    {
	// Message with a good checksum received, dump it.
	driver.printBuffer("Raw Packet:", buf, buflen);
        
        data.id = buf[0];
       	Serial.print("Device ID:");
	Serial.println(data.id);
        
        data.time = (uint32_t)buf[1];
       	Serial.print("  Packet num:");
	Serial.println(data.time);
        
        data.temperature = (uint16_t) buf[buflen-4];
       	Serial.print("  Temp:");
	Serial.println(data.temperature);
        
        data.turbidity = (uint16_t)buf[buflen-2];
	Serial.print("  Turb:");
	Serial.println(data.turbidity);

    }
}
