# Montage du systeme

## Lecteur RFID RC522

| RC522 | Arduino Uno |
| --- | --- |
| SDA / SS | D10 |
| SCK | D13 |
| MOSI | D11 |
| MISO | D12 |
| IRQ | Non connecte |
| GND | GND |
| RST | D9 |
| 3.3V | 3.3V |

> Attention : le module RC522 fonctionne sous 3.3 V. Ne pas connecter sa broche VCC au 5 V.

## Bouton-poussoir

Le programme utilise la resistance de pull-up interne de l'Arduino.

| Bouton | Arduino Uno |
| --- | --- |
| Premiere patte | D2 |
| Patte opposee | GND |

## Servomoteur SG90

| Fil du servomoteur | Connexion |
| --- | --- |
| Orange ou jaune (signal) | D3 |
| Rouge (alimentation) | 5 V |
| Marron ou noir (masse) | GND |

Pour un montage fiable, il est recommande d'alimenter le servomoteur avec une alimentation externe 5 V et de relier la masse de cette alimentation au GND de l'Arduino.

## LEDs

| Composant | Arduino Uno |
| --- | --- |
| LED verte | D4 avec une resistance de 220 ohms |
| LED rouge | D5 avec une resistance de 220 ohms |
| Cathodes des deux LEDs | GND |

Connexion d'une LED : `broche Arduino -> resistance 220 ohms -> anode de la LED`, puis `cathode -> GND`.

