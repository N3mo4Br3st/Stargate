// ### GESTION WIFI ####################

struct Def_Reseau {
    String ssid;
    String pwd;
};

// ### GESTION MODES ###################

enum Mode_porte { autonome, wifi }; //serie ?

// ### GESTION ENDPOINTS ###############

// Niveau d'accessibilite des options
enum Perimetre {total, glyphe, chevron, horizon};

// ### GESTION LEDS ####################

struct Bandeau {
    CRGB leds[];
    int pin;
    int nbleds;
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
