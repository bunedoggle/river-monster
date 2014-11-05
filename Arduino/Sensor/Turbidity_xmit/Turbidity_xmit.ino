
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

#define UID 0

//RH_ASK::RH_ASK(uint16_t speed, uint8_t rxPin, uint8_t txPin, uint8_t pttPin, bool pttInverted)
RH_ASK driver( 1200, 2, 3, 4, 5 );

typedef struct {
	uint8_t id;
	uint32_t time;
	uint8_t temperature;
	uint8_t turbidity;	
	} PACKET_T;

PACKET_T data;
	
void setup()
{
	Serial.begin(9600);	  // Debugging only
	if (!driver.init() )
	Serial.println("init failed");
	data.time = 0;
}

void loop()
{	
	data.id = UID;
	data.time += 1;
	data.temperature = analogRead(A0);   
	data.turbidity = analogRead(A1);     
	
	driver.send((uint8_t*)&data,sizeof(data));
	driver.waitPacketSent();
	delay(1000);
}
