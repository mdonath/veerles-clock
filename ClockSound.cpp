#include "ClockSound.hpp"

void ClockSound::begin(int tx, int rx) {
	mySoftwareSerial = new SoftwareSerial(tx, rx);
	mySoftwareSerial->begin(9600);
	delay(100);

	if (!mp3player.begin(*mySoftwareSerial)) {
		Serial.println(F("Unable to begin:"));
		Serial.println(F("1.Please recheck the connection!"));
		Serial.println(F("2.Please insert the SD card!"));
		while (true) {
			delay(0); // Code to compatible with ESP8266 watch dog.
		}
	}
	Serial.println(F("DFPlayer Mini online."));

	this->volume(5);
}

void ClockSound::volume(int volume) {
	this->mp3player.volume(volume);
}

int ClockSound::readFileCountsInFolder(int folder) {
	return this->mp3player.readFileCountsInFolder(folder);
}

void ClockSound::playLargeFolder(uint8_t folderNumber, uint16_t fileNumber) {
	this->mp3player.playLargeFolder(folderNumber, fileNumber);
}

void ClockSound::stop() {
	this->mp3player.stop();
}

void ClockSound::waitUntilFinished() {
	while (true) {
		if (this->mp3player.available()) {
			int type = this->mp3player.readType();
			Serial.println(type);
			if (type == DFPlayerPlayFinished) {
				break;
			}
		}
		delay(1);
	}
}

void ClockSound::update_player() {
	if (mp3player.available()) {
		printDetail(mp3player.readType(), mp3player.read());
	}
}

void ClockSound::printDetail(uint8_t type, int value) {
	switch (type) {
		case TimeOut:
			Serial.println(F("Time Out!"));
			break;
		case WrongStack:
			Serial.println(F("Stack Wrong!"));
			break;
		case DFPlayerCardInserted:
			Serial.println(F("Card Inserted!"));
			break;
		case DFPlayerCardRemoved:
			Serial.println(F("Card Removed!"));
			break;
		case DFPlayerCardOnline:
			Serial.println(F("Card Online!"));
			break;
		case DFPlayerUSBInserted:
			Serial.println("USB Inserted!");
			break;
		case DFPlayerUSBRemoved:
			Serial.println("USB Removed!");
			break;
		case DFPlayerPlayFinished:
			Serial.print(F("Number:"));
			Serial.print(value);
			Serial.println(F(" Play Finished!"));
			break;
		case DFPlayerError:
			Serial.print(F("DFPlayerError:"));
			switch (value) {
				case Busy:
					Serial.println(F("Card not found"));
					break;
				case Sleeping:
					Serial.println(F("Sleeping"));
					break;
				case SerialWrongStack:
					Serial.println(F("Get Wrong Stack"));
					break;
				case CheckSumNotMatch:
					Serial.println(F("Check Sum Not Match"));
					break;
				case FileIndexOut:
					Serial.println(F("File Index Out of Bound"));
					break;
				case FileMismatch:
					Serial.println(F("Cannot Find File"));
					break;
				case Advertise:
					Serial.println(F("In Advertise"));
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}
