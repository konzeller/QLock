#include <Wire.h>
#include "FastLED.h"

#define LED_PIN 10
#define NUM_LEDS 114

CRGB LEDs[NUM_LEDS];
bool ESIST_OFF = true;

int FUNK[4] = {35, 48, 55, 68}; // FUNK
int UHR[3] = {82, 101, 103};
int AM[2] = {57, 66};
int PM[2] = {45, 58};

int ESIST[5]   = {10, 12, 32, 51, 52};        // static LED will not change

int LED_MINUTES[44] = {72, 91, 92, 112, 9, 13, 30, 33, 50, 53, 70, 73, 90, 93, 111, 8, 14, 29, 34, 49, 54, 69, 74, 89, 94, 110, 49, 54, 69, 74, 89, 94, 110, 7, 15, 28, 75, 88, 95, 109, 6, 16, 27, 36};
int FUENF_Z[4] = {72, 91, 92, 112};   // fünf vor oder nach
int ZEHN_F[4] = {9, 13, 30, 33};      // zehn vor oder nach
int ZWANZIG_F[7] = {50, 53, 70, 73, 90, 93, 111}; //zwanzig vor oder nach
int DREIVIERTEL_F[11] = {8, 14, 29, 34, 49, 54, 69, 74, 89, 94, 110}; // dreiviertel
int VIERTEL_F[7] = {49, 54, 69, 74, 89, 94, 110}; // viertel
int VOR[3] = {7, 15, 28};  // vor
int NACH[4] = {75, 88, 95, 109};    // nach
int HALB[4] = {6, 16, 27, 36};    // halb

int LED_HOURS[50] = {5, 17, 26, 3, 37, 77, 86, 97, 107, 4, 18, 25, 38, 78, 85, 98, 106, 76, 87, 96, 108, 3, 19, 24, 39, 44, 2, 20, 23, 40, 43, 60, 79, 84, 99, 105, 41, 42, 61, 62, 1, 21, 22, 56, 67, 63, 80, 83, 100, 104};
int EINS[4] = {5, 17, 26, 37};
int ZWEI[4] = {77, 86, 97, 107};
int DREI[4] = {4, 18, 25, 38};
int VIER[4] = {78, 85, 98, 106};
int FUENF[4] = {76, 87, 96, 108};
int SECHS[5] = {3, 19, 24, 39, 44};
int SIEBEN[6] = {2, 20, 23, 40, 43, 60};
int ACHT[4] = {79, 84, 99, 105};
int NEUN[4] = {41, 42, 61, 62};
int ZEHN[4] = {1, 21, 22, 41};
int ELF[3] = {56, 67, 76};
int ZWOELF[5] = {63, 80, 83, 100, 104};

int WORDS_HOUR[12] = {ZWOELF, EINS, ZWEI, DREI, VIER, FUENF, SECHS, SIEBEN, ACHT, NEUN, ZEHN, ELF};
int SIZEOF_WORDS_HOUR[12] = {5,4,4,4,4,4,5,6,4,4,4,3};

int PLUS_1[1] = {11};
int PLUS_2[1] = {113};
int PLUS_3[1] = {102};
int PLUS_4[1] = {0};
int PLUS_MIN[4] = {11, 113, 102, 0};

void LED_showStrip() {
   FastLED.show();
}

void LED_setPixel(int Pixel, byte red, byte green, byte blue) {
   // FastLED
   LEDs[Pixel].r = red;
   LEDs[Pixel].g = green;
   LEDs[Pixel].b = blue;
}

void LED_Blackout(){
  for(int i = 0; i < NUM_LEDS; i++ ) {
    LED_setPixel(i, 0x00, 0x00, 0x00); 
  }
  LED_showStrip();
}

void LED_Blackout(int text[], int size_of){
  for(int i = 0; i < size_of; i++ ) {
    LED_setPixel(text[i], 0x00, 0x00, 0x00); 
  }
  LED_showStrip();
}

void LED_setText(int text[], int size_of) {
  for(int i = 0; i<size_of; i++){
     LED_setPixel(text[i], 0x00, 0xff, 0xff);
  }
}

void LED_setText(int text) {
  LED_setPixel(text, 0x00, 0xff, 0xff);
}


void LED_init () {
  FastLED.addLeds<WS2811, LED_PIN, GRB>(LEDs, NUM_LEDS).setCorrection( TypicalLEDStrip );
  LED_Blackout();
}

void LED_showMinute(){
  if(NOW_MIN != LAST_MIN){
    LAST_MIN = NOW_MIN;
    int mod_minute = NOW_MIN % 5;
    if(mod_minute != 0){
      LED_setText(PLUS_MIN[mod_minute-1]);
    }else{
      LED_Blackout(LED_MINUTES, sizeof(LED_MINUTES)/sizeof(int));
      LED_Blackout(UHR, sizeof(UHR)/sizeof(int));
      LED_Blackout(PLUS_MIN, sizeof(PLUS_MIN)/sizeof(int));
      switch(NOW_MIN){
        case 0: LED_setText(UHR, sizeof(UHR)/sizeof(int));break;
        case 5: LED_setText(FUENF_Z, sizeof(FUENF_Z)/sizeof(int));LED_setText(NACH, sizeof(NACH)/sizeof(int));break;
        case 10: LED_setText(ZEHN_F, sizeof(ZEHN_F)/sizeof(int));LED_setText(NACH, sizeof(NACH)/sizeof(int));break;
        case 15: LED_setText(VIERTEL_F, sizeof(VIERTEL_F)/sizeof(int));LED_setText(NACH, sizeof(NACH)/sizeof(int));break;
        case 20: LED_setText(ZWANZIG_F, sizeof(ZWANZIG_F)/sizeof(int));LED_setText(NACH, sizeof(NACH)/sizeof(int));break;
        case 25: LED_setText(FUENF_Z, sizeof(FUENF_Z)/sizeof(int));LED_setText(VOR, sizeof(VOR)/sizeof(int));LED_setText(HALB, sizeof(HALB)/sizeof(int));break;
        case 30: LED_setText(HALB, sizeof(HALB)/sizeof(int));break;
        case 35: LED_setText(FUENF_Z, sizeof(FUENF_Z)/sizeof(int));LED_setText(NACH, sizeof(NACH)/sizeof(int));LED_setText(HALB, sizeof(HALB)/sizeof(int));break;
        case 40: LED_setText(ZWANZIG_F, sizeof(ZWANZIG_F)/sizeof(int));LED_setText(VOR, sizeof(VOR)/sizeof(int));break;
        case 45: LED_setText(VIERTEL_F, sizeof(VIERTEL_F)/sizeof(int));LED_setText(VOR, sizeof(VOR)/sizeof(int));break;
        case 50: LED_setText(ZEHN_F, sizeof(ZEHN_F)/sizeof(int));LED_setText(VOR, sizeof(VOR)/sizeof(int));break;
        case 55: LED_setText(FUENF_Z, sizeof(FUENF_Z)/sizeof(int));LED_setText(VOR, sizeof(VOR)/sizeof(int));break;
      }
    }
  }
}


void LED_showHour(){
  int tempHour = NOW_HOUR;
  if(NOW_MIN >= 25){tempHour +=1;}
  if(tempHour > 12){tempHour = tempHour - 12;}
  else if(tempHour == 12){tempHour = 0;}
  
  if(tempHour != LAST_HOUR){
    LAST_HOUR = tempHour;
    LED_Blackout(LED_HOURS, sizeof(LED_HOURS)/sizeof(int));
    LED_setText(WORDS_HOUR[tempHour],SIZEOF_WORDS_HOUR[tempHour]);
  }
}

void LED_showESIST(){
  if(ESIST_OFF){LED_setText(ESIST, sizeof(ESIST)/sizeof(int));ESIST_OFF=false;}
}
// check current time and set the LEDs
void LED_showCurrentTime(){

  LED_showESIST();
  LED_showMinute();
  LED_showHour();
  LED_showStrip();
    
}
