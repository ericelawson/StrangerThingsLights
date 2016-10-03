#include <bitswap.h>
#include <chipsets.h>
#include <color.h>
#include <colorpalettes.h>
#include <colorutils.h>
#include <controller.h>
#include <cpp_compat.h>
#include <dmx.h>
#include <FastLED.h>
#include <fastled_config.h>
#include <fastled_delay.h>
#include <fastled_progmem.h>
#include <fastpin.h>
#include <fastspi.h>
#include <fastspi_bitbang.h>
#include <fastspi_dma.h>
#include <fastspi_nop.h>
#include <fastspi_ref.h>
#include <fastspi_types.h>
#include <hsv2rgb.h>
#include <led_sysdefs.h>
#include <lib8tion.h>
#include <noise.h>
#include <pixelset.h>
#include <pixeltypes.h>
#include <platforms.h>
#include <power_mgt.h>

#define NUM_LEDS  100
#define DATA_PIN  5
#define MESSAGE_COUNT 16

//Stranger Things lighting constants
#define LETTER_DURATION 1500
#define LETTER_SPACING  1000
#define MIN_MESSAGE_SPACING 10000

CRGB leds[NUM_LEDS];
const char* messages[MESSAGE_COUNT];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); 
  randomSeed(analogRead(0));
  setAll(0,0,0);

  messages[0] = "run";
  messages[1] = "right here";
  messages[2] = "yes";
  messages[3] = "kill trump";
  messages[4] = "no";
  messages[5] = "thats dumb";
  messages[6] = "what";
  messages[7] = "dont care";
  messages[8] = "behind you";
  messages[9] = "bill cosby";
  messages[10] = "ask again";
  messages[11] = "walk briskly";
  messages[12] = "who farted";
  messages[13] = "soylent green is people";
  messages[14] = "thats like your opinion man";
  messages[15] = "not today";
}

//--------------------------------

void loop() {
  //Write a message here!
  int messageIndex = random(0, MESSAGE_COUNT - 1); 

  //Write the message out slowly
  writeMessage(messageIndex);

  //Wait a sufficiently long time to show another message
  
  delay(MIN_MESSAGE_SPACING);
}


//--------------------------------

void writeMessage(int idx) {
   const char* msg = messages[idx];
   int len = strlen(msg);

    for (int i = 0; i < len; i++) {
       //Get the appropriate light index for the character
       int lightIdx = translateChar(msg[i]);
       if (lightIdx >= 0) {
         //Illuminate the appropriate light
         setAll(0,0,0);
         setPixel(lightIdx, 255, 255, 255);
         showStrip();
         delay(LETTER_DURATION);
       }
       else {
         //For non-text characters (such as spaces), Don't do anything and wait for the character pause
       }
        
       //Clear all lights and wait until next character
       setAll(0,0,0);
       showStrip();
       delay(LETTER_SPACING);
    }
}

int translateChar(char c) {
  /* This will vary based on the positions of the lights. The numbers specified here were where the lights laid out on my wall. Adjust the numbers accordingly
     for your display */  
   switch(c) {
      case 'a':
          return 99;
      case 'b':
          return 97;
      case 'c':
          return 95;
      case 'd':
          return 93;          
      case 'e':
          return 91;
      case 'f':
          return 89;
      case 'g':
          return 87;
      case 'h':
          return 85;
      case 'i':
          return 65;
      case 'j':
          return 67;
      case 'k':
          return 69;
      case 'l':
          return 71;
      case 'm':
          return 73;
      case 'n':
          return 75;
      case 'o':
          return 77;
      case 'p':
          return 79;       
      case 'q':
          return 81;
      case 'r':
          return 60;
      case 's':
          return 58;
      case 't':
          return 56;
      case 'u':
          return 54;
      case 'v':
          return 52;
      case 'w':
          return 50;
      case 'x':
          return 49;          
      case 'y':
          return 47;
      case 'z':
          return 45;
      default:
          return -1;
   }
}

//Helper functions
void shiftRight() {
  for (int i = NUM_LEDS - 1; i > 0; i--) {
    //For each position, move the value from the previous LED into the next LED    
    clonePixel(i-1, i);
  }
}

void showStrip() {
   FastLED.show();
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
   leds[Pixel].g = red;
   leds[Pixel].r = green;
   leds[Pixel].b = blue;
}

void clonePixel(int source, int dest) {
   leds[dest].g = leds[source].g;
   leds[dest].r = leds[source].r;
   leds[dest].b = leds[source].b;
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
}
