//commun
//#define SG1
#define ATLANTIS
//#define UNIVERSE

#define BRIGHTNESS  64

#define NB_BANDEAUX      2

#define PIN_BANDEAU1     1 //glyphes
#define NB_LED_BANDEAU1  10
#define NB_LED_BANDEAU2  2

#define PIN_BANDEAU2     6 //chevrons
#define PIN_BANDEAU3     3 //horizon
#define PIN_BANDEAU4     9 //complementaire

#define PIN_BANDEAU5     0
#define PIN_BANDEAU6     0
#define PIN_BANDEAU7     0
#define PIN_BANDEAU8     0

#define LED_COLOR_ORDER_WS2812 GRB

Bandeau_t bandeaux[NB_BANDEAUX] = {
    {PIN_1, NB_LED_BANDEAU1, LED_WS2812, NULL, NULL, NULL},
    {PIN_2, NB_LED_BANDEAU2, LED_WS2812, NULL, NULL, NULL}
};

CRGB default_bandeau1[NB_LED_BANDEAU1] = {
    CRGB::Blue,
    CRGB::Red,
    CRGB::Green,
    CRGB::Blue,
    CRGB::Red,
    CRGB::Green,
    CRGB::Blue,
    CRGB::Red,
    CRGB::Green,
    CRGB::Black
};
CRGB default_bandeau2[NB_LED_BANDEAU2] = {
    CRGB::Blue,
    CRGB::Green
};

CRGB *default_bandeaux[NB_BANDEAUX] = {
    default_bandeau1,
    default_bandeau2
};

// ### ZONE DE TEST #################



element_t toto[50];

/*
element_t elements[NB_ELEMENT] = {
    {
      {x,y},{x,y},{x,y},
      {x,y},{x,y},{x,y},
      {x,y},{x,y},{x,y},{x,y},...
    },
    ...
};
*/
