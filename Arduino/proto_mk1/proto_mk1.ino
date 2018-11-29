// ### INFOS ###########################

// Declarations des variables et constantes dans secure.h :
// const struct Def_Reseau CONF_RESEAUX[CONF_NB_RESEAUX]

// ### HEADERS #########################

#include <FastLED.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "structures.h"

// include de configuration par porte
#include "secure.h"
#include "conf.h"

// ### CONSTANTES ######################

#define DEF_COLOR_ORDER = GRB

// ### VARIABLES GLOBALES ##############

bool getnet = false;
int sel_lvl = 0;
Def_Reseau sel_reseau = {"", ""};
bool good_ssid[CONF_NB_RESEAUX];
ESP8266WebServer server(8080);

// ### FUNCTIONS #######################

// ##### WIFI HELPERS

// scanning network and check if there is one in the whitelist available
bool scanning() {
    bool res = false;
    int nbn = WiFi.scanNetworks();
    sel_lvl = CONF_NB_RESEAUX;
    for (int i = 0; i < nbn; i++) {
        String tmp_ssid = WiFi.SSID(i);
        for (int j = 0; j < sel_lvl; j++) {
            if (good_ssid[j] && tmp_ssid == CONF_RESEAUX[j].ssid) {
                sel_lvl = j;
                sel_reseau.ssid = CONF_RESEAUX[j].ssid;
                sel_reseau.pwd = CONF_RESEAUX[j].pwd;
                res = true;
                break;
            }
        }
    }
    return res;
}

// if there is no connection, this function try to init a new wireless setup
void connecting() {
    // scan for available network, with the conf.h whitelist
    getnet = scanning();
    // if there is no network available
    if (!getnet) { delay(5000); } // delay the next scan in 5 seconds
    else {
        // try to connect to the selected network
        WiFi.begin(sel_reseau.ssid.c_str(), sel_reseau.pwd.c_str());
        // loop until the esp succeed to connect, or failed
        bool tryconnect = true;
        while (tryconnect) {
            if (WiFi.status() == WL_CONNECT_FAILED) {
                getnet = false;
                good_ssid[sel_lvl] = false;
                delay(1000);
                tryconnect = false;
            }
            else if (WiFi.status() == WL_CONNECTED) {
                tryconnect = false;
            }
            delay(300);
        }
    }
}

// ##### SERVER HELPERS

void initEndPoints() {
    server.on("/info", handleInfo);
    server.on("/show", []() { handleShow(Perimetre::total); });
    server.on("/show/glyphe", []() { handleShow(Perimetre::glyphe); });
    server.on("/show/chevron", []() { handleShow(Perimetre::chevron); });
    server.on("/show/horizon", []() { handleShow(Perimetre::horizon); });
    server.on("/raz", []() { handleRaz(Perimetre::total); });
    server.on("/raz/glyphe", []() { handleRaz(Perimetre::glyphe); });
    server.on("/raz/chevron", []() { handleRaz(Perimetre::chevron); });
    server.on("/raz/horizon", []() { handleRaz(Perimetre::horizon); });
    server.on("/couleur", []() { handleCouleur(Perimetre::total); });
    server.on("/couleur/glyphe", []() { handleCouleur(Perimetre::glyphe); });
    server.on("/couleur/chevron", []() { handleCouleur(Perimetre::chevron); });
    server.on("/couleur/horizon", []() { handleCouleur(Perimetre::horizon); });
    server.on("/prog", []() {
        //
        //
    });
    server.on("/prog/list", []() {
        //
        //
    });
    server.on("/prog/activation/complete", []() {
        //
        //
    });
    server.on("/prog/activation/dial", []() {
        //
        //
    });
    server.on("/prog/activation/chevrons", []() {
        //
        //
    });
    server.on("/prog/activation/horizon", []() {
        //
        //
    });
}

void handleInfo() {
    //
    // TODO : renvoi les infos sur la porte
    //
}

void handleShow(Perimetre perimetre) {
    //
    switch (perimetre) {
        case Perimetre::total:
            //
            break;
            //
    }
    //
}

void handleRaz(Perimetre perimetre) {
    //
    //
}

void handleCouleur(Perimetre perimetre) {
    //
    //
}

// ### CLASSES #########################
// ### MAIN ############################

void setup() {
    delay(3000); // power-up safety delay
    //
    // TODO : connexion wifi
    //
    // TODO : mise en mode broadcast udp pour découverte (à faire quand le udp sonar handshake sera dév par Killian)
    //
    // TODO : initialiser des variables
    //
    // TODO : initialiser les LEDS
    //a refaire foreeach (bandeaux ) FastLED.addLeds<LED_TYPE, bandeaux[i].LED_PIN, DEF_COLOR_ORDER>(bandeaux[i].leds, bandeaux[i].numled).setCorrection( TypicalLEDStrip );
    //
    // ## Initialisation du serveur
    initEndPoints();
    server.begin();
}

void loop() {
    server.handleClient();
}
