#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>
#include <Servo.h>

const byte SS_PIN = 10;
const byte RST_PIN = 9;
const byte BUTTON_PIN = 2;
const byte SERVO_PIN = 3;
const byte GREEN_LED_PIN = 4;
const byte RED_LED_PIN = 5;

const int EEPROM_UID_ADDRESS = 0;
const int EEPROM_MARKER_ADDRESS = 4;
const byte EEPROM_MARKER = 0xA5;

const byte DOOR_CLOSED_ANGLE = 0;
const byte DOOR_OPEN_ANGLE = 90;

MFRC522 rfid(SS_PIN, RST_PIN);
Servo doorServo;

byte authorizedUid[4];
bool uidIsStored = false;
bool editMode = false;

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

void saveUid(const byte newUid[]) {
  for (byte i = 0; i < 4; i++) {
    authorizedUid[i] = newUid[i];
    EEPROM.update(EEPROM_UID_ADDRESS + i, newUid[i]);
  }

  EEPROM.update(EEPROM_MARKER_ADDRESS, EEPROM_MARKER);
  uidIsStored = true;

  Serial.print(F("Nouvel UID enregistre : "));
  printUid(authorizedUid);
}

void loadUid() {
  if (EEPROM.read(EEPROM_MARKER_ADDRESS) != EEPROM_MARKER) {
    uidIsStored = false;
    Serial.println(F("Aucun UID n'est enregistre."));
    Serial.println(F("Appuyez sur le bouton pour enregistrer un TAG."));
    return;
  }

  for (byte i = 0; i < 4; i++) {
    authorizedUid[i] = EEPROM.read(EEPROM_UID_ADDRESS + i);
  }

  uidIsStored = true;
  Serial.print(F("UID charge depuis l'EEPROM : "));
  printUid(authorizedUid);
}

bool uidMatches(const byte readUid[]) {
  if (!uidIsStored) {
    return false;
  }

  for (byte i = 0; i < 4; i++) {
    if (readUid[i] != authorizedUid[i]) {
      return false;
    }
  }

  return true;
}

void enterEditMode() {
  editMode = true;
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(RED_LED_PIN, HIGH);

  Serial.println();
  Serial.println(F("Mode edition active."));
  Serial.println(F("Passez le nouveau TAG devant le lecteur."));
}

void grantAccess() {
  Serial.println(F("Acces autorise."));

  digitalWrite(GREEN_LED_PIN, HIGH);
  doorServo.write(DOOR_OPEN_ANGLE);

  delay(1000);
  digitalWrite(GREEN_LED_PIN, LOW);

  delay(4000);
  doorServo.write(DOOR_CLOSED_ANGLE);

  Serial.println(F("Porte fermee."));
}

void denyAccess() {
  Serial.println(F("Acces refuse."));

  digitalWrite(RED_LED_PIN, HIGH);
  delay(3000);
  digitalWrite(RED_LED_PIN, LOW);
}

void checkButton() {
  if (digitalRead(BUTTON_PIN) != LOW) {
    return;
  }

  delay(50);

  if (digitalRead(BUTTON_PIN) == LOW) {
    enterEditMode();

    while (digitalRead(BUTTON_PIN) == LOW) {
      // Attendre que le bouton soit relache.
    }

    delay(50);
  }
}

void readTag() {
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  if (rfid.uid.size != 4) {
    Serial.println(F("UID incompatible : il doit contenir 4 octets."));
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
    return;
  }

  byte readUid[4];

  for (byte i = 0; i < 4; i++) {
    readUid[i] = rfid.uid.uidByte[i];
  }

  Serial.print(F("UID detecte : "));
  printUid(readUid);

  if (editMode) {
    saveUid(readUid);
    editMode = false;

    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);

    Serial.println(F("Mode edition termine."));
  } else if (uidMatches(readUid)) {
    grantAccess();
  } else {
    denyAccess();
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

void setup() {
  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);

  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);

  doorServo.attach(SERVO_PIN);
  doorServo.write(DOOR_CLOSED_ANGLE);

  SPI.begin();
  rfid.PCD_Init();

  Serial.println(F("Systeme de controle d'acces RFID"));
  Serial.println(F("--------------------------------"));

  loadUid();
}

void loop() {
  checkButton();
  readTag();
}

