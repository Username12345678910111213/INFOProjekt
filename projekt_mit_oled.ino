/* Labor Informatik SS20 Ansgar Specht,
 *  Studentenkennung: span1017
 *  Fachrichtung:     Fahrzeugtechnologie
 *  
 *  Dieses Programm steuert einen WS2812B LED - Streifen  
 *  in Abhängigkeit von der Umgebunshelligkeit.
 *  Verwendet wird die Adafruit Neopixel library, diese muss zuvor installiert werden.
 *  
 *  In diesem Programm werden jedoch die Seriellen Ausgaben "Es ist hell" und "Es ist dunkel" über ein OLED Display ausgegeben.
 *  Hierfür muss die "U8glib" Library installiert werden.
 *  Datum: 29.05.2020
 */







#include "U8glib.h"

#include <Adafruit_NeoPixel.h>
#define LED_PIN          6
#define LED_COUNT   60

#include <Arduino.h>



int Referenzwert = 150;

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB+NEO_KHZ800);
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);

void setup() {
u8g.begin();


strip.begin();  // initalize NeoPixel library
strip.show();  //initialize all pixels to 'off'
Serial.begin(9600);
strip.setBrightness(50);

 u8g.setFont(u8g_font_unifont);
u8g.setPrintPos(0,10);
 

}
/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */
void loop() { 
uint32_t color1 = strip.Color(255, 222,173);
uint32_t color2 = strip.Color(173,173,255);
int Sensorwert= analogRead(A0);
Serial.println(Sensorwert);
delay(1000);
  if (Sensorwert < Referenzwert)
  {
      colorWipe(color1,50);
      strip.setBrightness(255);
      strip.show(); 
     
      Serial.println("Es ist dunkel");
      u8g.firstPage(); 
      do {
      u8g.drawStr(0,20,"Es ist dunkel");
     } while( u8g.nextPage() );
    
   }
  else
  { 
      colorWipe(color2,50);
      strip.setBrightness(255);
      strip.show();
     
     
      Serial.println("Es ist hell");
      u8g.firstPage();
      do{
      u8g.drawStr(0,20,"Es ist hell");
      } while (u8g.nextPage());   
  }
  delay(2000);
}
/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */

void colorWipe(uint32_t color, int wait){
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
