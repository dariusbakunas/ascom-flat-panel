/*
 Name:		arduino_firmware.ino
 Created:	4/30/2023 5:03:11 PM
 Author:	bakun
*/

#include <Servo.h>

Servo opener;

constexpr auto SEPARATOR = '#';
constexpr auto CMD_OPEN = "OPEN";
constexpr auto CMD_CLOSE = "CLOSE";
constexpr auto CMD_IS_OPEN = "IS_OPEN";
constexpr auto POS_CLOSED = 0;
constexpr auto POS_OPEN = 180;
auto open = false;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(57600);
	Serial.flush();
	opener.attach(2);
}

// the loop function runs over and over again until power down or reset
void loop() {
	String cmd;

	if (Serial.available() > 0) {
		cmd = Serial.readStringUntil(SEPARATOR);

		if (cmd == CMD_IS_OPEN) {
			if (open) {
				Serial.print("OPEN");
			}
			else {
				Serial.print("CLOSED");
			}
			Serial.println(SEPARATOR);
		}
		else if (cmd == CMD_CLOSE) {
			opener.write(POS_CLOSED);
			open = false;
			Serial.println(SEPARATOR);
		}
		else if (cmd == CMD_OPEN) {
			opener.write(POS_OPEN);
			open = true;
			Serial.println(SEPARATOR);
		}		
	}
}
