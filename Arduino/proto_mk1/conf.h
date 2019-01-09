//commun
#define BRIGHTNESS  64

//bandeau chervron
#define LED_PIN_CHEV     6
#define NUM_LEDS_CHEV    9

#define NB_BANDEAUX      4

#define PIN_BANDEAU1     1 //glyphes
#define NB_LED_BANDEAU1  10

#define PIN_BANDEAU2     6 //chevrons
#define PIN_BANDEAU3     3 //horizon
#define PIN_BANDEAU4     9 //complementaire


struct Bandeau bandeaux[NB_BANDEAUX] = {
    {PIN_BANDEAU1, NB_LED_BANDEAU1, LED_WS2812, NULL},
    {PIN_BANDEAU2, NB_LED_BANDEAU1, LED_WS2812, NULL},
    {PIN_BANDEAU3, NB_LED_BANDEAU1, LED_WS2812, NULL},
    {PIN_BANDEAU4, NB_LED_BANDEAU1, LED_WS2812, NULL}
};


// ### ZONE DE TEST #################

//struct Bandeau bandeautest = {1, 5, NULL};

/*
bandeaux[Bandeau] 

bandeaux[0] = .....
const Bandeau BandeauGlyphes = {
    [],
    //
}

const Composant Glyphe1 = {
    //
    //
}
*/
