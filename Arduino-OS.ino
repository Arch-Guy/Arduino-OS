#include <EEPROM.h>
byte buffer[1024];
void setup() {
	memset(buffer, 0, sizeof(buffer));
	Serial.begin(9600);
	Serial.println("Welcome to Arduino OS!");
}
void loop() {
	if (Serial.available()) {
		String input = Serial.readStringUntil('\n');
		input.trim();
		if (input.startsWith("write(")) {
			int commaIndex = input.indexOf(',');
			int quoteStart = input.indexOf('"');
			int quoteEnd = input.lastIndexOf('"');
			int addr = input.substring(6, commaIndex).toInt();
			String data = input.substring(quoteStart + 1, quoteEnd);
			int i = 0;
			while (i < data.length()) {
				EEPROM.write(addr, data[i]);
				addr++;
				i++;
			}
			Serial.println("OK");
		}
		else if (input.startsWith("read(")) {
			int commaIndex = input.indexOf(',');
			int addr = input.substring(5, commaIndex).toInt();
			int length = input.substring(commaIndex + 1, input.length() - 1).toInt();
			int i = 0;
			while (i < length) {
				Serial.write(EEPROM.read(addr));
				addr++;
				i++;
			}
			Serial.println();
		}
		else {
			Serial.println("Invalid Command.");
		}
	}
}