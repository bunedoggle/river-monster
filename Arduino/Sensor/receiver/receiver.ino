// Turbidity chart
// fluid              reading   voltage
//------------------------------------------
// water	        924	2.95
// milk	                19	0.065

// Temperature Chart
// Deg                reading   voltage
// 34                  266
// 44                  315
// 78                  525
// 145                 800

#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

//RH_ASK::RH_ASK(uint16_t speed, uint8_t rxPin, uint8_t txPin, uint8_t pttPin, bool pttInverted)
RH_ASK driver( 1200, 12, 3, 4, 5 );

typedef struct __attribute__((packed)){
	uint8_t id;
	uint32_t time;
	uint16_t temperature;
	uint16_t turbidity;
	} PACKET_T;

PACKET_T data;
PACKET_T* dataPtr;

// nodes for linear equations / nodepoits are concatening  lines
float tempPoints[5][2]= {
  {
    266,34  }
  , {
    315,44  }
  , {
    413,65  }
  , {
    523,78  }
  ,{
    800,145  }
};

float turbPoints[4][2]= {
  {
    18,4000  }
  , {
    155,1500  }
  , {
    915,10  }
  , {
    1023, 0 }
};



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
        
        dataPtr = (PACKET_T*) buf;
       	Serial.print("Device ID:");
	Serial.println(dataPtr->id);
                
       	Serial.print("  Packet num:");
	Serial.println(dataPtr->time);
               
       	Serial.print("  Temp:(raw:");
        Serial.print(dataPtr->temperature);
        Serial.print("): ");
	Serial.println(reMap(tempPoints, dataPtr->temperature));
        
	Serial.print("  Turb:(raw:");
        Serial.print(dataPtr->turbidity);
        Serial.print("): ");
	Serial.println(reMap(turbPoints, dataPtr->turbidity));
    }
}


//***************************************************************************
//
int reMap(float pts[10][2], int input) {
  int rr;
  float bb,mm;

  for (int nn=0; nn < 4; nn++) {

    if (input >= pts[nn][0] && input <= pts[nn+1][0]) {
      mm= ( pts[nn][1] - pts[nn+1][1] ) / ( pts[nn][0] - pts[nn+1][0] );
      mm= mm * (input-pts[nn][0]);
      mm = mm +  pts[nn][1];
      rr = mm;
    }
  }
  return(rr);
}
