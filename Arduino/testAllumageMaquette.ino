#include <FastLED.h>
#include <SoftwareSerial.h>

//commun
#define BRIGHTNESS  64
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

//bandeau chervron
#define LED_PIN_CHEV     6
#define NUM_LEDS_CHEV    9
CRGB chevrons[NUM_LEDS_CHEV];

//bandeau glyphs
#define LED_PIN_GLYPHS     5
#define NUM_LEDS_GLYPHS    36
CRGB glyphs[NUM_LEDS_GLYPHS];

//bandeau horizon
#define LED_PIN_HORIZON     7
#define NUM_LEDS_HORIZON    30
CRGB horizon[NUM_LEDS_HORIZON];

CRGBPalette16 currentPalette;
TBlendType    currentBlending;
#define UPDATES_PER_SECOND 100

int adresse[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
int glyphOrigine = 4;
int mode = 0;
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
 
ESP8266WebServer server(8080);
 


 const char* ssid = "*****";
const char* password = "*******";

 
void handleBodyM0() { //Handler for the body path
 
     /* if (server.hasArg("application/x-www-form-urlencoded")== false){ //Check if body received
 
            server.send(200, "text/plain", "Body not received");
            return;
 
      }*/
       if (server.hasArg("glyph1")== false || server.hasArg("glyph2")== false|| server.hasArg("glyph3")== false|| server.hasArg("glyph4")== false
       || server.hasArg("glyph5")== false|| server.hasArg("glyph6")== false|| server.hasArg("glyph7")== false){ //Check if body received
 
            server.send(200, "text/plain", "glyph not found");
            return;
 
      }
 adresse[0]= server.arg("glyph1").toInt();
 adresse[1]= server.arg("glyph2").toInt();
  adresse[2]= server.arg("glyph3").toInt();
   adresse[3]= server.arg("glyph4").toInt();
    adresse[4]= server.arg("glyph5").toInt();
     adresse[5]= server.arg("glyph6").toInt();
      adresse[6]= server.arg("glyph7").toInt();
      
      String message = "Body received:\n";
             message += server.arg("plain");
             message += "\n";
   String incoming = server.arg("plain");

    //todo traitement du message recu

  //  traitementChoixGlyph(incoming);
 Serial.println("adresse[0]  :");
 Serial.println(adresse[0],DEC);

  Serial.println("adresse[1]  :");
 Serial.println(adresse[1],DEC);

  Serial.println("adresse[2]  :");
 Serial.println(adresse[2],DEC);

  Serial.println("adresse[3]  :");
 Serial.println(adresse[3],DEC);

  Serial.println("adresse[4]  :");
 Serial.println(adresse[4],DEC);

  Serial.println("adresse[5]  :");
 Serial.println(adresse[5],DEC);

  Serial.println("adresse[6]  :");
 Serial.println(adresse[6],DEC);

  Serial.println("adresse[7]  :");
 Serial.println(adresse[7],DEC);
 
      server.send(200, "text/plain", message);
      Serial.println(message);
      
    casM0();
 

}

void handleBodyM1() { //Handler for the body path
 
     /* if (server.hasArg("application/x-www-form-urlencoded")== false){ //Check if body received
 
            server.send(200, "text/plain", "Body not received");
            return;
 
      }*/
     
      
      String message = "Body received:\n";
             message += server.arg("plain");
             message += "\n";
   String incoming = server.arg("plain");

    //todo traitement du message recu

  //  traitementChoixGlyph(incoming);
 Serial.println("adresse[0]  :");
 Serial.println(adresse[0],DEC);

  Serial.println("adresse[1]  :");
 Serial.println(adresse[1],DEC);

  Serial.println("adresse[2]  :");
 Serial.println(adresse[2],DEC);

  Serial.println("adresse[3]  :");
 Serial.println(adresse[3],DEC);

  Serial.println("adresse[4]  :");
 Serial.println(adresse[4],DEC);

  Serial.println("adresse[5]  :");
 Serial.println(adresse[5],DEC);

  Serial.println("adresse[6]  :");
 Serial.println(adresse[6],DEC);

  Serial.println("adresse[7]  :");
 Serial.println(adresse[7],DEC);
 
      server.send(200, "text/plain", message);
      Serial.println(message);
      
    casM0();
 

}

bool testExistancePrecedentGlyph(int glyph,int GlyphPosition){
  if(adresse[GlyphPosition] != -1){
    for(int i = 0;i<GlyphPosition+1;i++ ){
      if(glyph == glyphOrigine || glyph == adresse[i]){
          return true;
       }
    }
  }
  return false;
}

void setup() {
  // put your setup code here, to run once:
 
  delay( 3000 ); // power-up safety delay

  for(int i=0;i<8;i++){
    bool continueChercher = true;
    do{
     int randGlyph = random(36);
continueChercher = testExistancePrecedentGlyph(randGlyph,i);
    if(!continueChercher){
      adresse[i]= randGlyph;
      }
    }while(continueChercher);
    
    }
    adresse[8] = glyphOrigine;
     Serial.begin(115200);
    WiFi.begin(ssid, password);  //Connect to the WiFi network
 
    while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
 
        delay(500);
        Serial.println("Waiting to connect...");
 
    }
 
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());  //Print the local IP
 
    server.on("/M0", handleBodyM0); //Associate the handler function to the path
    server.on("/M1", handleBodyM1); //Associate the handler function to the path
 
    server.begin(); //Start the server
    Serial.println("Server listening");

  FastLED.addLeds<LED_TYPE, LED_PIN_CHEV, COLOR_ORDER>(chevrons, NUM_LEDS_CHEV).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED_PIN_GLYPHS, COLOR_ORDER>(glyphs, NUM_LEDS_GLYPHS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED_PIN_HORIZON, COLOR_ORDER>(horizon, NUM_LEDS_HORIZON).setCorrection( TypicalLEDStrip );
  
  FastLED.setBrightness(  BRIGHTNESS );
      currentPalette = OceanColors_p ;
    currentBlending = LINEARBLEND;
    
  Serial.println("avant raz");
RAZ();
Serial.println("fin init");
}

void RAZ(){
  for(int i =0; i< NUM_LEDS_CHEV;i++){
  chevrons[i] = CRGB::Black;
}
for(int i =0; i< NUM_LEDS_GLYPHS;i++){
  glyphs[i] = CRGB::Black;
}

for(int i =0; i< NUM_LEDS_HORIZON;i++){
  horizon[i] = CRGB::Black;
}

    Serial.println("glyphs show raz");
FastLED.show();

}

void allumage(){
  for(int i =0; i< NUM_LEDS_CHEV;i++){
  chevrons[i] = CRGB::Blue;
}
for(int i =0; i< NUM_LEDS_GLYPHS;i++){
  glyphs[i] = CRGB::Blue;
}
    Serial.println("glyphs + chevron show allumage complet");
FastLED.show();

}

void animationHorizon(int nbRepet){
  for(int t=0 ;t<nbRepet; t++){
      static uint8_t startIndex = 0;
    startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors(startIndex);
    
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
}
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS_HORIZON; i++) {
        horizon[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
  
  }

int offsetGlyphNumberFromchevron(int chevron){
int offset = 22+chevron*4;
if(offset>35){
  offset = offset - 36;
  }
  return offset;
}

void traitementChoixGlyph(String incoming) {
 
   Serial.println(incoming.indexOf("glyphe1="));
    if(incoming.indexOf("glyphe1=")>=0){
adresse[0]=incoming.substring(incoming.indexOf("glyphe1=")+8,incoming.indexOf("&",incoming.indexOf("glyphe1="))).toInt();
 Serial.println("adresse[0]  :");
 Serial.println(adresse[0],DEC);
    }
       if(incoming.indexOf("glyphe2=")>=0){
adresse[1]=incoming.substring(incoming.indexOf("glyphe2=")+8,incoming.indexOf("&",incoming.indexOf("glyphe2="))).toInt();
 Serial.println("adresse[1]  :");
 Serial.println(adresse[1],DEC);
    }
        if(incoming.indexOf("glyphe3=")>=0){
adresse[2]=incoming.substring(incoming.indexOf("glyphe3=")+8,incoming.indexOf("&",incoming.indexOf("glyphe3="))).toInt();
 Serial.println("adresse[2]  :");
 Serial.println(adresse[2],DEC);
    }
        if(incoming.indexOf("glyphe4=")>=0){
adresse[3]=incoming.substring(incoming.indexOf("glyphe4=")+8,incoming.indexOf("&",incoming.indexOf("glyphe4="))).toInt();
 Serial.println("adresse[3]  :");
 Serial.println(adresse[3],DEC);
    }
        if(incoming.indexOf("glyphe5=")>=0){
adresse[4]=incoming.substring(incoming.indexOf("glyphe5=")+8,incoming.indexOf("&",incoming.indexOf("glyphe5="))).toInt();
 Serial.println("adresse[4]  :");
 Serial.println(adresse[4],DEC);
    }
        if(incoming.indexOf("glyphe6=")>=0){
adresse[5]=incoming.substring(incoming.indexOf("glyphe6=")+8,incoming.indexOf("&",incoming.indexOf("glyphe6="))).toInt();
 Serial.print("adresse[5] :");
 Serial.println(adresse[5],DEC);
    }
        if(incoming.indexOf("glyphe7=")>=0){
adresse[6]=incoming.substring(incoming.indexOf("glyphe7=")+8,incoming.indexOf("&",incoming.indexOf("glyphe7="))).toInt();
 Serial.print("adresse[6] :");
 Serial.println(adresse[6],DEC);
    } 

}
void loop() {


   server.handleClient(); //Handling of incoming requests

 
 
}
void casM0() {
for(int c =0; c< NUM_LEDS_CHEV;c++){
  //utilisation que de 7 chevron pour le moment
 if(c!= 3 && c !=4){
int offsetChevron = 5 + c;
if(offsetChevron>8){
  offsetChevron = offsetChevron - 9;
  }
int offsetDebut = offsetGlyphNumberFromchevron(c);
  for(int i =0; i< NUM_LEDS_GLYPHS;i++){

   int offset = offsetDebut + i;
   if(offset>35){
  offset = offset - 36;
  }
    glyphs[offset] = CRGB::Blue;
    //Serial.println("glyphs show up");
                FastLED.show();
            // clear this led for the next time around the loop
            if(adresse[c] == offset){
              glyphs[offset] = CRGB::Blue;
            }else{
            glyphs[offset] = CRGB::Black;
            }
            delay(50);
    }

  for(int i = NUM_LEDS_GLYPHS - 2; i >= 0;i--){
    int offset = offsetDebut + i;
   if(offset>35){
  offset = offset - 36;
  }
    glyphs[offset] = CRGB::Blue;
    // Serial.println("glyphs show down");
                FastLED.show();
            // clear this led for the next time around the loop
            if(adresse[c] == offset){
              glyphs[offset] = CRGB::Blue;
            }else{
            glyphs[offset] = CRGB::Black;
            }
            delay(50);
    }
   glyphs[adresse[c]] = CRGB::Black;
  chevrons[offsetChevron] = CRGB::Blue;
   Serial.print("chevron show n°:");
Serial.println(adresse[c],DEC);
    FastLED.show();
    delay(70);    
  }
}
allumage();
  animationHorizon(3000);
  delay(10); 
  RAZ();
  mode = 0;
}
