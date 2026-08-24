# Algorithmes

## 1. Lecture de l'UID

```text
Debut
    Initialiser la liaison serie
    Initialiser SPI et le lecteur RC522

    Repeter
        Si un nouveau TAG est detecte alors
            Lire son UID
            Afficher les octets de l'UID en hexadecimal
        Fin si
    Fin repeter
Fin
```

## 2. Enregistrement dans l'EEPROM

```text
Debut
    Initialiser le lecteur RC522
    Configurer le bouton en INPUT_PULLUP

    Repeter
        Si un TAG est detecte alors
            Lire et memoriser son UID
        Fin si

        Si le bouton est appuye alors
            Si un UID a deja ete lu alors
                Enregistrer ses quatre octets dans l'EEPROM
            Sinon
                Afficher un message d'erreur
            Fin si
        Fin si
    Fin repeter
Fin
```

## 3. Controle d'acces

```text
Debut
    Initialiser RC522, le servomoteur, le bouton et les LEDs
    Charger l'UID autorise depuis l'EEPROM
    Fermer la porte

    Repeter
        Si le bouton est appuye alors
            Activer le mode d'edition
            Allumer les deux LEDs
        Fin si

        Si un TAG est detecte alors
            Lire son UID

            Si le mode d'edition est actif alors
                Enregistrer l'UID dans l'EEPROM
                Eteindre les deux LEDs
                Quitter le mode d'edition
            Sinon si l'UID est autorise alors
                Allumer la LED verte pendant une seconde
                Ouvrir la porte pendant cinq secondes
                Fermer la porte
            Sinon
                Allumer la LED rouge pendant trois secondes
            Fin si
        Fin si
    Fin repeter
Fin
```

