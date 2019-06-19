// ### INFOS ###########################

// Declarations des variables et constantes dans secure.h :
// const struct Def_Reseau CONF_RESEAUX[CONF_NB_RESEAUX]

// ### HEADERS #########################

#include <FastLED.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
//#include <ESP8266WebServer.h>

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "structures.h"

// include de configuration par porte
#include "secure.h"
#include "conf.h"

#ifdef UNIVERSE
#ifndef ATLANTIS
#define ATLANTIS
#endif
#endif

// ### CONSTANTES ######################

#define DEF_COLOR_ORDER_WS2812 = GRB

// ### VARIABLES GLOBALES ##############

bool getnet = false;
int sel_lvl = 0;
Def_Reseau sel_reseau = {"", ""};
bool good_ssid[CONF_NB_RESEAUX];

//ESP8266WebServer server(8080);
AsyncWebServer server(8080);

// ### FUNCTIONS #######################

// ##### GLOBAL HELPERS

void init_bandeaux_tab(short t[NB_BANDEAUX]) { for (short i = 0;i<NB_BANDEAUX;++i) { t[i] = i; } }

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

// passage d'une chaine de caracteres a un tableau de nombres (short)
short split_short(AsyncWebParameter* p, short tableau[]) {
    const String data = p->value();
    String data_clean = data.substring(1, data.length()-1);
    size_t prev = 0, pos = 0;
    short taille = 0;
    do {
        pos = data_clean.indexOf(',', prev);
        if (pos == -1) pos = data_clean.length();
        tableau[taille] = data_clean.substring(prev, pos).toInt();
        taille++;
        prev = pos+1;
    } while (pos < data_clean.length() && prev < data_clean.length());
    return taille;
}

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void initEndPoints() {
    server.on("/info", HTTP_GET, handleInfo);
    server.on("/mask", HTTP_POST, [](AsyncWebServerRequest *request) { handleMask(request); });
    server.on("/show", HTTP_POST, [](AsyncWebServerRequest *request) { handleShow(PR_TOTAL, request); });
    server.on("/couleur", HTTP_POST, [](AsyncWebServerRequest *request) { handleCouleur(PR_TOTAL, request); });
    server.on("/raz", HTTP_POST, [](AsyncWebServerRequest *request) { handleRaz(PR_TOTAL, request); });
    server.on("/show/chevron", HTTP_POST, [](AsyncWebServerRequest *request) { handleShow(PR_CHEVRON, request); });
    server.on("/couleur/chevron", HTTP_POST, [](AsyncWebServerRequest *request) { handleCouleur(PR_CHEVRON, request); });
    server.on("/raz/chevron", HTTP_POST, [](AsyncWebServerRequest *request) { handleRaz(PR_CHEVRON, request); });
    #ifdef ATLANTIS
    server.on("/show/glyphe", HTTP_POST, [](AsyncWebServerRequest *request) { handleShow(PR_GLYPHE, request); });
    server.on("/couleur/glyphe", HTTP_POST, [](AsyncWebServerRequest *request) { handleCouleur(PR_GLYPHE, request); });
    server.on("/raz/glyphe", HTTP_POST, [](AsyncWebServerRequest *request) { handleRaz(PR_GLYPHE, request); });
    #endif
    server.on("/show/horizon", HTTP_POST, [](AsyncWebServerRequest *request) { handleShow(PR_HORIZON, request); });
    server.on("/couleur/horizon", HTTP_POST, [](AsyncWebServerRequest *request) { handleCouleur(PR_HORIZON, request); });
    server.on("/raz/horizon", HTTP_POST, [](AsyncWebServerRequest *request) { handleRaz(PR_HORIZON, request); });

    // Prog API
    server.on("/prog", HTTP_POST, [](AsyncWebServerRequest *request) {
        //
        request->send(200, "text/plain", "Prog");
        //
    });
    server.on("/prog/list", HTTP_GET, [](AsyncWebServerRequest *request) {
        //
        request->send(200, "text/plain", "Prog");
        //
    });
    server.on("/prog/activation/complete", HTTP_POST, [](AsyncWebServerRequest *request) {
        //
        request->send(200, "text/plain", "Prog");
        //
    });
    server.on("/prog/activation/dial", HTTP_POST, [](AsyncWebServerRequest *request) {
        //
        request->send(200, "text/plain", "Prog");
        //
    });
    server.on("/prog/activation/chevrons", HTTP_POST, [](AsyncWebServerRequest *request) {
        //
        request->send(200, "text/plain", "Prog");
        //
    });
    server.on("/prog/activation/horizon", HTTP_GET, [](AsyncWebServerRequest *request) {
        //
        request->send(200, "text/plain", "Prog");
        //
    });
}

void handleInfo(AsyncWebServerRequest *request) {
    //
    // TODO : renvoi les infos sur la porte
    //
    // TODO : renvoi type ATLANTIS / SG1 / UNIVERSE
    //
    request->send(200, "text/plain", "Info");
    //
}

void handleMask(AsyncWebServerRequest *request) {
    if (request->hasParam("ids", true)) {
        //
        request->getParam("ids", true);
        //
        //
        //[]
        //[1=1,2=0,3=1]
        //[1=[1=1,5=0,6=1],2=[2=1,3=1,4=0]]
        //[1=1,2=[1=0,2=1,3=0],3=...]
        //
        request->send(200, "text/plain", "mask");
        //
    }
    else {
        request->send(400, "text/plain", "bad syntax for the mask");
    }
}

void handleShow(Perimetre perimetre, AsyncWebServerRequest *request) {
    short bandeaux[NB_BANDEAUX] = {0};
    short taille = 0;
    switch (perimetre) {
        case PR_TOTAL:
            if (request->hasParam("bandeau_ids", true)) {
                // si le parametre bandeau_ids existe, alors il faut parser la chaine de la request et en faire un tableau de short
                taille = split_short(request->getParam("bandeau_ids", true), bandeaux);
            }
            else {
                // si bandeau_ids inexistant, bandeaux doit etre sette avec une boucle
                taille = NB_BANDEAUX;
                init_bandeaux_tab(bandeaux);
            }
            break;
        case PR_GLYPHE:
        case PR_CHEVRON:
        case PR_HORIZON:
            break;
    }
    funDAO_show(taille, bandeaux);
    FastLED.show();
    request->send(200, "text/plain", "show");
}

void handleRaz(Perimetre perimetre, AsyncWebServerRequest *request) {
    short bandeaux[NB_BANDEAUX] = {0};
    short taille = 0;
    if (request->hasParam("bandeau_ids", true)) {
      taille = split_short(request->getParam("bandeau_ids", true), bandeaux);
    }
    else {
      taille = NB_BANDEAUX;
      init_bandeaux_tab(bandeaux);
    }
    funDAO_raz(taille, bandeaux);
    request->send(200, "text/plain", "raz");
}

void handleCouleur(Perimetre perimetre, AsyncWebServerRequest *request) {
    //
    request->send(200, "text/plain", "Info");
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

void funDAO_show(short taille, short ids[NB_BANDEAUX]) {
  // la fonction prend un ou plusieurs bandeaux, et transmet la couleur préparée dans bandeaux[x].prepa_leds à bandeaux[x].leds
  for (short i = 0; i<taille; ++i) {
    for (short j = 0; j<bandeaux[ids[i]].nbleds; ++j) {
      if (bandeaux[ids[i]].mask[j]) {
        bandeaux[ids[i]].leds[j] = bandeaux[ids[i]].prepa_leds[j];
      }
      else {
        bandeaux[ids[i]].leds[j] = CRGB::Black;
      }
    }
  }
}

void funDAO_raz(short taille, short ids[NB_BANDEAUX]) {
  // la fonction remet le(s) tableau(x) de préparation à zéro, en reprenant la configuration par défaut
  for (short i = 0; i<taille;++i) {
    for (short j = 0;j<bandeaux[ids[i]].nbleds;++j) {
      bandeaux[i].prepa_leds[j] = default_bandeaux[i][j];
    }
  }
}

// ##### CONTROLS HELPERS

bool check_delay(int delay_time) {
  //
  // TODO : check for interruption
  //
  delay(delay_time);
  //
  // TODO : check for interruption
  //
  return true;
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
      bandeaux[i].mask = (boolean*) malloc(bandeaux[i].nbleds*sizeof(boolean));
      bandeaux[i].prepa_leds = (CRGB*) malloc(bandeaux[i].nbleds*sizeof(CRGB));
      bandeaux[i].leds = (CRGB*) malloc(bandeaux[i].nbleds*sizeof(CRGB));
      for (int j = 0; j < bandeaux[i].nbleds; ++j) {
        bandeaux[i].mask[j] = false;
        bandeaux[i].prepa_leds[j] = default_bandeaux[i][j];
        bandeaux[i].leds[j] = CRGB::Black;
      }
      switch (bandeaux[i].type) {
        case LED_WS2812: initSwitchLED_WS2812(i); break;
      }
    }
    FastLED.show();
    //
    //
    memset(toto, 0, 50*sizeof(element_t));
    //
    // TODO : est-ce qu'on init les chevrons, glyphes, etc
    //
    // init du serveur
    initEndPoints();
    server.onNotFound(notFound);
    server.begin();
}

void loop() {
    //
    //
}
