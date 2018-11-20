// ### INFOS ###########################
// ### HEADERS #########################

#include <FastLED.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "secure.h"
#include "conf.h"

// ### STRUCTURES ######################

// Niveau d'accessibilité des options
enum Perimetre {total, glyphe, chevron, horizon};

// ### CONSTANTES ######################

#define DEF_COLOR_ORDER = GRB

// ### VARIABLES GLOBALES ##############

ESP8266WebServer server(8080);

// ### FUNCTIONS #######################

// ##### WIFI HELPERS

// scanning network and check if there is one in the whitelist available
bool scanning() {
    //
    // TODO : A REFAIRE AVEC LA NOUVELLE VERSION DU SECURE.H !!!!!!!!
    //
    bool res = false;
    int nbn = WiFi.scanNetworks();
    sel_lvl = CONF_NB_SSID;
    for (int i = 0; i < nbn; i++) {
        String tmp_ssid = WiFi.SSID(i);
        for (int j = 0; j < sel_lvl; j++) {
            if (tmp_ssid == CONF_SSIDS[j]) {
                sel_lvl = j;
                sel_ssid = CONF_SSIDS[j];
                sel_pwd = CONF_PASSES[j];
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
        WiFi.begin(sel_ssid.c_str(), sel_pwd.c_str());
        // loop until the esp succeed to connect, or failed
        bool tryconnect = true;
        while (tryconnect) {
            if (WiFi.status() == WL_CONNECT_FAILED) {
                getnet = false;
                delay(5000);
                tryconnect = false;
            }
            else if (WiFi.status() == WL_CONNECTED) {
                tryconnect = false;
            }
            delay(500);
        }
        // if the connection succeed
        if (getnet) {
            //
            //
            // TODO : setup webserver ?
            // TODO : setup udp ?
            //
        }
    }
}

// ##### SERVER HELPERS

void initEndPoints() {
    server.on("/info", handleInfo);
    server.on("/show", []() { handleShow(Perimetre::total); });
    server.on("/show/glyphe", []() { handleShow(Perimetre::glyphe); });
    server.on("/show/chevron", []() { handleShow(Perimetre::chevron); });
    server.on("/show/horizon", []() { handleShow(Perimetre::horizon); });
    server.on("/raz", []() { handleRaz(Perimetre::total); });
    server.on("/raz/glyphe", []() { handleRaz(Perimetre::glyphe); });
    server.on("/raz/chevron", []() { handleRaz(Perimetre::chevron); });
    server.on("/raz/horizon", []() { handleRaz(Perimetre::horizon); });
    server.on("/couleur", []() { handleCouleur(Perimetre::total); });
    server.on("/couleur/glyphe", []() { handleCouleur(Perimetre::glyphe); });
    server.on("/couleur/chevron", []() { handleCouleur(Perimetre::chevron); });
    server.on("/couleur/horizon", []() { handleCouleur(Perimetre::horizon); });
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

void handleShow(Perimetre perimetre) {
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
    //
    // ## Initialisation du serveur
    initEndPoints();
    server.begin();
}

void loop() {
    server.handleClient();
}
