//commun
#define BRIGHTNESS  64

#define NB_BANDEAUX      4

#define PIN_BANDEAU1     1 //glyphes
#define NB_LED_BANDEAU1  10

#define PIN_BANDEAU2     6 //chevrons
#define PIN_BANDEAU3     3 //horizon
#define PIN_BANDEAU4     9 //complementaire

#define PIN_BANDEAU5     0
#define PIN_BANDEAU6     0
#define PIN_BANDEAU7     0
#define PIN_BANDEAU8     0

#define LED_COLOR_ORDER_WS2812 GRB

Bandeau_t bandeaux[NB_BANDEAUX] = {
    {PIN_1, NB_LED_BANDEAU1, LED_WS2812, NULL},
    {PIN_2, NB_LED_BANDEAU1, LED_WS2812, NULL},
    {PIN_3, NB_LED_BANDEAU1, LED_WS2812, NULL},
    {PIN_4, NB_LED_BANDEAU1, LED_WS2812, NULL}
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
