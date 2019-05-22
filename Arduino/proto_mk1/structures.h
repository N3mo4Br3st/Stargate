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

#define NB_MAX_LED_ELT 20

enum Led_type {LED_WS2812, LED_WS2811};

enum Led_pin {PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7, PIN_8};

typedef struct {
    const Led_pin pin;
    const short nbleds;
    const Led_type type;
    boolean *mask;
    CRGB *prepa_leds;
    CRGB *leds;
} Bandeau_t;

typedef struct {
    short id_bdx;
    short id_led;
} coord_led_t;

typedef struct {
    coord_led_t list_led[NB_MAX_LED_ELT];
} element_t;
