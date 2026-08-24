# Arduino RFID Access Control

Systeme de controle d'acces realise avec un Arduino Uno et un lecteur RFID RC522. Le projet permet de lire l'UID d'un badge, de l'enregistrer dans la memoire EEPROM et de commander une porte avec un servomoteur.

## Fonctionnalites

- Lecture et affichage de l'UID d'un TAG RFID.
- Enregistrement permanent d'un UID dans l'EEPROM.
- Modification du badge autorise avec un bouton-poussoir.
- Signalisation par LED verte ou rouge.
- Ouverture d'une porte avec un servomoteur pendant cinq secondes.

## Materiel utilise

- Arduino Uno
- Lecteur RFID RC522
- Badges ou cartes RFID
- Servomoteur SG90
- Bouton-poussoir
- LED verte et LED rouge
- Deux resistances de 220 ohms
- Fils de connexion et breadboard

## Organisation du projet

| Dossier | Description |
| --- | --- |
| `01_read_uid` | Lecture et affichage de l'UID dans le moniteur serie |
| `02_save_uid_eeprom` | Enregistrement du dernier UID lu dans l'EEPROM |
| `03_access_control` | Systeme final de controle d'acces |
| `docs/wiring.md` | Branchement de tous les composants |
| `docs/algorithm.md` | Algorithmes des trois parties |

## Bibliotheques Arduino

Installer la bibliotheque **MFRC522** depuis le gestionnaire de bibliotheques de l'Arduino IDE. Les bibliotheques `SPI`, `EEPROM` et `Servo` sont normalement fournies avec l'Arduino IDE.

## Utilisation

1. Realiser le montage decrit dans [`docs/wiring.md`](docs/wiring.md).
2. Ouvrir le fichier `.ino` correspondant a la partie a tester.
3. Selectionner la carte **Arduino Uno** et le bon port serie.
4. Televerser le programme.
5. Ouvrir le moniteur serie a **9600 bauds**.

Pour le programme final :

1. Appuyer sur le bouton pour activer le mode d'edition.
2. Les LEDs rouge et verte s'allument simultanement.
3. Approcher le badge qui doit etre autorise.
4. Approcher ensuite le meme badge pour ouvrir la porte.
5. Un autre badge provoque un refus d'acces et allume la LED rouge.

## Connexions principales du RC522

| RC522 | Arduino Uno |
| --- | --- |
| SDA / SS | D10 |
| SCK | D13 |
| MOSI | D11 |
| MISO | D12 |
| RST | D9 |
| GND | GND |
| VCC | 3.3 V |

> Attention : ne jamais alimenter le RC522 avec 5 V.

## Hardware Prototype

The RFID access control system was implemented and tested on real hardware using an Arduino Uno and an MFRC522 RFID reader connected via SPI.

### Full Prototype
![RFID Prototype](docs/images/rfid_prototype_full.jpg)

### Wiring Close-up
![RFID Wiring](docs/images/rfid_wiring_closeup.jpg)

The hardware tests confirmed reliable RFID card detection and UID reading before integrating EEPROM-based storage and access control logic.

## Auteur

Ibrahim Ait Massoud

