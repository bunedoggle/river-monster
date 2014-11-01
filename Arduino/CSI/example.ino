// Do not remove the include below
// Instantiate serial interface

CSI ui(&Serial);


void setup() {
        Serial.begin(9600);
        registerAllCommands(&ui);
}

void loop() {

        ui.serialEventHandler();

}
