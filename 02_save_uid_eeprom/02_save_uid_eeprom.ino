#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>

const byte SS_PIN = 10;
const byte RST_PIN = 9;
const byte BUTTON_PIN = 2;

const int EEPROM_UID_ADDRESS = 0;
const int EEPROM_MARKER_ADDRESS = 4;
const byte EEPROM_MARKER = 0xA5;

MFRC522 rfid(SS_PIN, RST_PIN);

byte lastUid[4];
bool uidAvailable = false;

void printUid(const byte uid[]) {
  for (byte i = 0; i < 4; i++) {
    if (uid[i] < 0x10) {
      Serial.print('0');
    }

    Serial.print(uid[i], HEX);
    Serial.print(' ');
  }

  Serial.println();
}

void saveLastUid() {
  for (byte i = 0; i < 4; i++) {
    EEPROM.update(EEPROM_UID_ADDRESS + i, lastUid[i]);
  }

  EEPROM.update(EEPROM_MARKER_ADDRESS, EEPROM_MARKER);
  Serial.println(F("UID enregistre dans l'EEPROM."));
}

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  SPI.begin();
  rfid.PCD_Init();

  Serial.println(F("Passez un TAG devant le lecteur."));
  Serial.println(F("Ensuite, appuyez sur le bouton."));
}

void loop() {
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    if (rfid.uid.size == 4) {
      for (byte i = 0; i < 4; i++) {
        lastUid[i] = rfid.uid.uidByte[i];
      }

      uidAvailable = true;
      Serial.print(F("Dernier UID lu : "));
      printUid(lastUid);
    } else {
      Serial.println(F("Ce TAG ne possede pas un UID de 4 octets."));
    }

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }

  if (digitalRead(BUTTON_PIN) == LOW) {
    delay(50);

    if (digitalRead(BUTTON_PIN) == LOW) {
      if (uidAvailable) {
        saveLastUid();
      } else {
        Serial.println(F("Erreur : lisez d'abord un TAG RFID."));
      }

      while (digitalRead(BUTTON_PIN) == LOW) {
        // Attendre que le bouton soit relache.
      }

      delay(50);
    }
  }
}

