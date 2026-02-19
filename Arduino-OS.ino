#include <EEPROM.h> // Include EEPROM Services
byte buffer[1024]; // Create 1 KB RAM Buffer
void setup() {
	memset(buffer, 0, sizeof(buffer)); // Clear memory
	Serial.begin(9600); // Start Serial services at 9600 baud
	Serial.println("Welcome to Arduino OS!"); // Splash Screen
}
void loop() {
	if (Serial.available()) {
		String input = Serial.readStringUntil('\n');
		input.trim();
		if (input.startsWith("write(")) {   // Write command parsing
			int commaIndex = input.indexOf(',');
			int quoteStart = input.indexOf('"');
			int quoteEnd = input.lastIndexOf('"');
			int addr = input.substring(6, commaIndex).toInt();
			String data = input.substring(quoteStart + 1, quoteEnd);
			int i = 0;
			while (i < data.length()) {   // Write data
				EEPROM.write(addr, data[i]);
				addr++;
				i++;
			}
			Serial.println("OK");
		}
		else if (input.startsWith("read(")) {   // Read command parsing
			int commaIndex = input.indexOf(',');
			int addr = input.substring(5, commaIndex).toInt();
			int length = input.substring(commaIndex + 1, input.length() - 1).toInt();
			int i = 0;
			while (i < length) {   // Read Data
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
