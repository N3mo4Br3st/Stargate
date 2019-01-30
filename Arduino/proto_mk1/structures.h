// ### GESTION WIFI ####################

struct Def_Reseau {
    String ssid;
    String pwd;
};

// ### GESTION MODES ###################

enum Mode_porte { MD_AUTONOME, MD_WIFI }; //serie ?

// ### GESTION ENDPOINTS ###############

// Niveau d'accessibilite des options
enum Perimetre {PR_TOTAL, PR_GLYPHE, PR_CHEVRON, PR_HORIZON};

// ### GESTION LEDS ####################

#define MAX_NB_LEDS 

enum Led_type {LED_WS2812, LED_WS2811};

enum Led_pin {PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7, PIN_8};

struct Bandeau {
    const Led_pin pin;
    const int nbleds;
    const Led_type type;
    CRGB *leds;
};

struct Liaison_Composant_Leds {
    Bandeau *bandeau;
    int leds[];
};

// structure regroupant les glyphes et les chevrons
struct Composant {
    //
    Liaison_Composant_Leds liaisons[];
    //
    //
    //
};



//bandeaux[]=[bandeau[numLedBd1,pin6] , bandeau[numLedBd2,pin7],...];


// pour le show des [glyph/chevron] 
// c'est une liste de bandeau qu'on show 
// sachant qu'un bandeau a une liste de led
// led composé de rgb

//

// pour set d'un [glyph/chevron] mapping :

//glyph[1]=[{NumBandeneau = 1; NumLed = 3}]
//glyph[2]=[{NumBandeneau = 1; NumLed = 4},{NumBandeneau = 2; NumLed = 3},...]
