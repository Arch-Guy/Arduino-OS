#include <EEPROM.h> // Include EEPROM Services
void setup() {
	Serial.begin(9600);  // Start Serial Services at 9600 Baud
	Serial.println("Welcome to Arduino BIOS!");  // Boot splash
}
void loop() {
	if (Serial.available()) {  // Input Available?
		String input = Serial.readStringUntil('\n');  // Input
		input.trim();  // Remove any spaces around the input
		String* ram = new String(input); // Store input in buffer
		if (input.startsWith("write(")) {  // Write command?
			int commaIndex = input.indexOf(',');  // Find comma
			int quoteStart = input.indexOf('"');  // Find double quote #1
			int quoteEnd = input.lastIndexOf('"');  // Find double quote #2
			int addr = input.substring(6, commaIndex).toInt();  // Fetch address
			String data = input.substring(quoteStart + 1, quoteEnd);  // Fetch string
			int i = 0;  // Create iterator
			while (i < data.length()) { // Until data's length is over
				EEPROM.update(addr, data[i]);  // Write byte at address
				addr++;  // Increment address
				i++;  // Increment iterator
			}
			Serial.println("OK");
		}
		else if (input.startsWith("read(")) {  // Read command?
			int commaIndex = input.indexOf(',');  // Find comma
			int addr = input.substring(5, commaIndex).toInt();  // Find start address
			int length = input.substring(commaIndex + 1, input.length() - 1).toInt();  // Find data length
			int i = 0;  // Create iterator
			while (i < length) { // Until length of data is finished
				Serial.write(EEPROM.read(addr));  // Print out the EEPROM Data of the current address
				addr++;  // Increment address
				i++;  // Increment iterator
			}
			Serial.println();
		}
		else {
			Serial.println("Invalid Command.");
		}
	}
}
/*And some notes here. If you're wondering WHY I didn't add bounds checking, it's because I LOVE that there is no extra error. I love corruptness.*/
