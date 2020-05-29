/* Labor Informatik SS20 Ansgar Specht,
 *  Studentenkennung: span1017
 *  Fachrichtung:     Fahrzeugtechnologie
 *  
 *  Dieses Programm steuert einen WS2812B LED - Streifen  
 *  in Abhängigkeit von der Umgebunshelligkeit.
 *  Verwendet wird die Adafruit Neopixel library, diese muss zuvor installiert werden.
 *  Datum: 29.05.2020
 */






/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */
#include <Adafruit_NeoPixel.h>      // inkludieren der benötigten Bibliotheken
#define LED_PIN          6          // Data Pin an dem das Data-Kabel der LED angeschlossen ist
#define LED_COUNT        60         // Anzahl der einzelnen LEDs


int Referenzwert = 150;                                               //globale Variable,  durch Auswertung von Sensorwerten geeigneten Wert ermitteln!

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB+NEO_KHZ800);   /*Deklaration mit Pixel Anzahl, Data Pin, Kombination aus      NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)        <- für WS2812 Streifen
                                                                                                                                  NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
                                                                                                              und
                                                                                                                                  NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)     <- Ich benutze einen GRB Streifen :) 
                                                                                                                                  NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
                                                                                                                                  NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)    
                                                                                                                                  */

/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */
void setup() {


strip.begin();                                                  // initialisierung NeoPixel library
strip.show();                                                   //  Alle Pixel/LEDs werden auf 'Aus' geschaltet
Serial.begin(9600);
strip.setBrightness(50);                                       // Helligkeit Einstellen, zwischen 0 und 255 möglich hier mit 50 ca 1/5 der maximal Helligkeit
//Werte für eine geeignete Farbe eingeben

}

/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */



void loop() { 
uint32_t color1 = strip.Color(255, 222,173);        /*(G,R,B) durch reduzierung vom Blau-Anteil wirkt das Licht wärmer*/     // uint32_t ist ein eigener Datatyp der 32bit speichern kann. Mit diesem kann ich Farbeinstellungen als Variablen deklarieren.
uint32_t color2 = strip.Color(173,173,255);         /*mehr Blau-Anteil, Licht wird "kälter"*/

int Sensorwert= analogRead(A0);               // Die Variable Sensorwert wird deklariert mit dem gemessenen Sensorwert des LDR / Light Dependent Resistor, dieser ist bei mir an den pin A0 angeschlossen
Serial.println(Sensorwert);                   // Ausgabe des Sensorwerts über den Seriellen Monitor
delay(1000);                                  // 1s Verzögerung


  if (Sensorwert < Referenzwert)              //  if-Bedingung, Falls der Sensor einen Wert misst, der unter dem Schwellwert(Referenzwert) liegt, soll folgender Code ausgeführt werden.
  {
    
    
      colorWipe(color1,50);                   //  externer Funktionsaufruf colorWipe( Farbe , Dauer)
      strip.setBrightness(255);               
      strip.show();                           // Damit wird der Status des LED controllers aktualisiert
     
     
      Serial.println("Es ist dunkel");        // über den Seriellen Monitor wird ausgegeben dass die Umgebungshelligkeit unter dem Referenzwert liegt
     
    
    
  }
  else                                        // sollte die if-Bedingung nicht erfüllt werden rutscht das Programm in diesen Abschnitt
     
  {
     
      colorWipe(color2,50);                 // vgl. if-Bedingung
      strip.setBrightness(255);
      strip.show();                         // vgl. if-Bedingung
     
     
      Serial.println("Es ist hell");        // über den Seriellen Monitor wird ausgegeben dass die Umgebungshelligkeit über dem Referenzwert liegt
      
  }

  
  delay(2000);                              // 2s Verzögerung
}
 

/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */ 
void colorWipe(uint32_t color, int wait)    //Ausgelagerte Funktion
{
  // Schleife 
  for(int i=0; i<strip.numPixels(); i++) { // entweder strip.numPixels() oder 59 eintragen, da die LED zwar 60 pixel besitzt aber der Compiler von 0-59 zählt und nicht von 1-60
    strip.setPixelColor(i, color);         //  für die Pixelfarbeden Übergabeparameter color einsetzen
    strip.show();                          //  LED aktualisieren
    delay(wait);                           //  warten befor der nächste Pixel geändert wird -> es sieht dann so aus als ob die Farben über die LEDs "gewischt werden" 
  }
}


/*  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  */


  
  
