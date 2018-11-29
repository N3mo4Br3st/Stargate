//commun
#define BRIGHTNESS  64
#define LED_TYPE    WS2812


//bandeau chervron
#define LED_PIN_CHEV     6
#define NUM_LEDS_CHEV    9

/bandeaux[]=[bandeau[numLedBd1,pin6] , bandeau[numLedBd2,pin7],...];

struct bandeau(int numLed,int pin){
  pin = pin;
  led[numLed];
  }

// pour le show des [glyph/chevron] 
// c'est une liste de bandeau qu'on show 
// sachant qu'un bandeau a une liste de led
// led composé de rgb

//

// pour set d'un [glyph/chevron] mapping :

glyph[1]=[{NumBandeneau = 1; NumLed = 3}]
glyph[2]=[{NumBandeneau = 1; NumLed = 4},{NumBandeneau = 2; NumLed = 3},...]
