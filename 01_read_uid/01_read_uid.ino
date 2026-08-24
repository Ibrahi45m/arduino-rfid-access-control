#include <SPI.h>
#include <MFRC522.h>

const byte SS_PIN = 10;
const byte RST_PIN = 9;

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();

  Serial.println(F("Approchez un TAG RFID..."));
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print(F("UID du TAG : "));

  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) {
      Serial.print('0');
    }

    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(' ');
  }

  Serial.println();

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

