**Projet Stargate**
=

Le but est de piloter l'éclairage d'une porte des étoiles.
Pour ce faire, le projet sera découpé en plusieurs parties.

1. Bas niveau : connexion des rubans de led à l'arduino puis de l'arduino a un raspberry pi
2. Back : mise en place d'un serveur web + backend sur le raspberry pi
3. Front : création d'une ihm pour le pilotage (très surement angular)

-----------

Partie 1 - Bas Niveau
--
Dossier: /Arduino
Les rubans de led sont connectés chacun sur une sortie de l’arduino et alimentés par une alimentation externe (dont la masse est reliée à l’arduino). 
3 rubans :

- Allumage des symboles

- Allumage des chevrons

- Allumage ambiance centrale

Datasheet led : https://www.mikrocontroller.net/attachment/180459/WS2812B_preliminary.pdf
L’arduino n’aura qu’un rôle d’affichage.

- Format d’envoi d’une tram d’allumage des leds : [L0.G7 L0.G6 L0.G5 L0.G4 L0.G3 L0.G2 L0.G1 L0.G0 L0.R7 L0.R6 L0.R5 L0.R4 L0.R3 L0.R2 L0.R1 L0.R0 L0.B7 L0.B6 L0.B5 L0.B4 L0.B3 L0.B2 L0.B1 L0.B0] [L1.G7 L1.G6 L1.G5 L1.G4 L1.G3 L1.G2 L1.G1 L1.G0 L1.R7 L1.R6 L1.R5 L1.R4 L1.R3 L1.R2 L1.R1 L1.R0 L1.B7 L1.B6 L1.B5 L1.B4 L1.B3 L1.B2 L1.B1 L1.B0][…] 
- Le choix de la couleur de chaque led se fait depuis le raspberry pi par une liaison série usb (penser à choisir le baud rate)
- Allumage de toutes les led avec n° led 0 ?
- Vérification intégrité des données ? 

-Une lib et un example existe pour la gestion des rubans de led: https://randomnerdtutorials.com/guide-for-ws2812b-addressable-rgb-led-strip-with-arduino/  (l'example se trouve aussi sous  Stargate/Arduino/testLedStrip.ino )    

Partie 2 - Back 
--
Back si possible en java et serveur web à définir

- Envoi sur le port série du choix de couleur de chaque led du ruban choisi
- Programmation de séquences 
- Serveur web (pour dialogue avec la partie front)
- Mise à disposition d’api rest (choix mode fonctionnement, choix couleur, choix led/groupes de led …)
- Enregistrement d’une séquence
- Option : utilisation de capteur pour activation

Partie 3 : Front
-
Dans le cadre de la mise en application de formations le front sera fait en angular

- Appel au back pour jouer des séquences prédéfinies 
- séquence d’activation depuis le DHD (vérification validité dans le back), chaque symbole engagé doit être illuminé sur le DHD.
- Choix des couleurs et de l’intensité lumineuse 
- Création de séquences ou ambiances avec enregistrement. Possiblement 1 partie (chevrons/symbole/vortex) à la fois puis mixage.
- Ajout effet sonore à l’appui des symboles lors de la composition « live » de la séquence d’activation.

Exemple de DHD :

![DHD](https://i.imgur.com/kqxS8XB.png "DHD")
