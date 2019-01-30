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

#define DEF_COLOR_ORDER_WS2812 = GRB

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
    server.on("/show", []() { handleShow(PR_TOTAL); });
    server.on("/show/glyphe", []() { handleShow(PR_GLYPHE); });
    server.on("/show/chevron", []() { handleShow(PR_CHEVRON); });
    server.on("/show/horizon", []() { handleShow(PR_HORIZON); });
    server.on("/raz", []() { handleRaz(PR_TOTAL); });
    server.on("/raz/glyphe", []() { handleRaz(PR_GLYPHE); });
    server.on("/raz/chevron", []() { handleRaz(PR_CHEVRON); });
    server.on("/raz/horizon", []() { handleRaz(PR_HORIZON); });
    server.on("/couleur", []() { handleCouleur(PR_TOTAL); });
    server.on("/couleur/glyphe", []() { handleCouleur(PR_GLYPHE); });
    server.on("/couleur/chevron", []() { handleCouleur(PR_CHEVRON); });
    server.on("/couleur/horizon", []() { handleCouleur(PR_HORIZON); });
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
        case PR_TOTAL:
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

// ##### LEDS HELPERS

void initSwitchLED_WS2812(int i) {
  switch(bandeaux[i].pin) {
    case PIN_1:
      FastLED.addLeds<WS2812, PIN_BANDEAU1, LED_COLOR_ORDER_WS2812>(bandeaux[i].leds, bandeaux[i].nbleds).setCorrection(TypicalLEDStrip);
      break;
    case PIN_2:
      FastLED.addLeds<WS2812, PIN_BANDEAU2, LED_COLOR_ORDER_WS2812>(bandeaux[i].leds, bandeaux[i].nbleds).setCorrection(TypicalLEDStrip);
      break;
    case PIN_3:
      FastLED.addLeds<WS2812, PIN_BANDEAU3, LED_COLOR_ORDER_WS2812>(bandeaux[i].leds, bandeaux[i].nbleds).setCorrection(TypicalLEDStrip);
      break;
    case PIN_4:
      FastLED.addLeds<WS2812, PIN_BANDEAU4, LED_COLOR_ORDER_WS2812>(bandeaux[i].leds, bandeaux[i].nbleds).setCorrection(TypicalLEDStrip);
      break;
    case PIN_5:
      FastLED.addLeds<WS2812, PIN_BANDEAU5, LED_COLOR_ORDER_WS2812>(bandeaux[i].leds, bandeaux[i].nbleds).setCorrection(TypicalLEDStrip);
      break;
    case PIN_6:
      FastLED.addLeds<WS2812, PIN_BANDEAU6, LED_COLOR_ORDER_WS2812>(bandeaux[i].leds, bandeaux[i].nbleds).setCorrection(TypicalLEDStrip);
      break;
    case PIN_7:
      FastLED.addLeds<WS2812, PIN_BANDEAU7, LED_COLOR_ORDER_WS2812>(bandeaux[i].leds, bandeaux[i].nbleds).setCorrection(TypicalLEDStrip);
      break;
    case PIN_8:
      FastLED.addLeds<WS2812, PIN_BANDEAU8, LED_COLOR_ORDER_WS2812>(bandeaux[i].leds, bandeaux[i].nbleds).setCorrection(TypicalLEDStrip);
      break;
  }
}

// ### CLASSES #########################
// ### MAIN ############################

void setup() {
    delay(3000); // power-up safety delay
    // setup wifi
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    // init des leds
    for (int i = 0; i < NB_BANDEAUX; ++i) {
      bandeaux[i].leds = (CRGB*) malloc(bandeaux[i].nbleds*sizeof(CRGB));
      for (int j = 0; j < bandeaux[i].nbleds; ++j) {
        bandeaux[i].leds[j] = CRGB::Black;
      }
      switch (bandeaux[i].type) {
        case LED_WS2812: initSwitchLED_WS2812(i); break;
      }
    }
    // init des elements ???
    //
    // TODO : est-ce qu'on init les chevrons, glyphes, etc
    //
    // init du serveur
    initEndPoints();
    server.begin();
}

void loop() {
    server.handleClient();
}
