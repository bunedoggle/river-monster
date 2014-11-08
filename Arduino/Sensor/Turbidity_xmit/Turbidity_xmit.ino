#include <LowPower.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

#define UID 0

//RH_ASK::RH_ASK(uint16_t speed, uint8_t rxPin, uint8_t txPin, uint8_t pttPin, bool pttInverted)
RH_ASK driver( 1200, 2, 3, 4, 5 );

typedef struct __attribute__((packed)){
	uint8_t id;
	uint32_t time;
	uint16_t temperature;
	uint16_t turbidity;	
	} PACKET_T;

PACKET_T data;
	
void setup()
{
	Serial.begin(9600);	  // Debugging only
	if (!driver.init() )
	Serial.println("init failed");
	data.time = 0;
	
	// Using this pin to power the turbidity sensor
	pinMode(A2,OUTPUT);
	digitalWrite(A2,HIGH);
	
	//analogReference(INTERNAL);
}

void loop()
{	
	// Turn on sensor
	digitalWrite(A2,HIGH);
	
	// Let the sensor settle
	delay(50);
	
	// Read sensor and build packet
	data.id = UID;
	data.time += 1;
	data.temperature = analogRead(A1);   
	data.turbidity = analogRead(A0);     

	//Serial.print("XMIT");
	//Serial.println(data.time);

	//Serial.print("Turb:");
	//Serial.print(analogRead(A0));
	//driver.printBuffer()

	// Turn off sensor while xmit
	digitalWrite(A2,LOW);

	// Send data
	driver.send((uint8_t*)&data,sizeof(data));
	driver.waitPacketSent();
	
	// Sleep (most power)
	//delay(1000);

	// Low power sleep (less power)
	//LowPower.idle(SLEEP_1S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);
	
	// Deep powerdown (least power)
	longPowerDown(60); // in Seconds 
}

// Most power efficient in multiples of 8 seconds
void longPowerDown(int seconds){
	int i;
	
	for(i=0; i<(seconds/8); i++){
		LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
	}
	
	for(i=0;i<(seconds%8); i++){
		LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
	}
}
