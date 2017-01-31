

#include <LiquidCrystal.h>
/*
Liquid flow rate sensor -DIYhacking.com Arvind Sanjeev

Measure the liquid/water flow rate using this code. 
Connect Vcc and Gnd of sensor to arduino, and the 
signal line to arduino digital pin 2.



 
 */



/*
Insterrupt Service Routine
 */




byte statusLed    = 13;



byte sensorInterrupt = 0;  // 0 = digital pin 2
byte sensorPin       = 2;


// The hall-effect flow sensor outputs approximately 4.5 pulses per second per
// litre/minute of flow.
float calibrationFactor = 4.5;


volatile byte pulseCount;  


float flowRate;

unsigned int flowMilliLitres;

unsigned long totalMilliLitres;


unsigned long oldTime;




/*
Insterrupt Service Routine
 */
void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
 
}

/*
SparkFun Inventor's Kit 
Example sketch 15

LIQUID CRYSTAL DISPLAY (LCD)

  A Liquid Crystal Display (LCD) is a sophisticated module 
  that can be used to display text or numeric data. The display
  included in your SIK features two lines of 16 characters, and
  a backlight so it can be used at night.

  If you've been using the Serial Monitor to output data,
  you'll find that a LCD provides many of the same benefits
  without needing to drag a large computer around.

  This sketch will show you how to connect an LCD to your Arduino
  and display any data you wish.

Hardware connections:

  The LCD has a 16-pin male header attached to it along the top
  edge. Pin 1 is the pin closest to the corner of the LCD.
  Pin 16 is the pin closest to the center of the LCD.

  Plug the LCD into your breadboard.

  As usual, you will want to connect the + and - power rails
  on the side of the breadboard to 5V and GND on your Arduino.

  Plug your 10K potentiometer into three unused rows on your
  breadboard. Connect one side of the potentiometer to 5V,
  and the other side to GND (it doesn't matter which). When you
  run this sketch, you'll use the potentiometer to adjust the
  contrast of the LCD so you can see the display.

  Now connect the LCD pins. Remember that pin 1 on the LCD
  is the one closest to the corner. Start there and work your
  way up.

  1 to GND
  2 to 5V
  3 to the center pin on the potentiometer
  4 to Arduino digital pin 12
  5 to GND
  6 to Arduino digital pin 11
  7 (no connection)
  8 (no connection)
  9 (no connection)
  10 (no connection)
  11 to Arduino  digital pin 5
  12 to Arduino  digital pin 4
  13 to Arduino  digital pin 3
  14 to Arduino  digital pin 2
  15 to 5V
  16 to GND

  Once everything is connected, load this sketch into the
  Arduino, and adjust the potentiometer until the display
  is clear.

Library

  The LCD has a chip built into it that controls all the
  individual dots that make up the display, and obeys commands
  sent to it by the the Arduino. The chip knows the dot patterns
  that make up all the text characters, saving you a lot of work.

  To communicate with this chip, we'll use the LiquidCrystal
  library, which is one of the standard libraries that comes
  with the Arduino. This library does most of the hard work
  of interfacing to the LCD; all you need to pick a location
  on the display and send your data!

Tips

  The LCD comes with a protective film over the display that
  you can peel off (but be careful of the display surface as
  it scratches easily).

  The LCD has a backlight that will light up when you turn on
  your Arduino. If the backlight doesn't turn on, check your 
  connections.

  As we said above, the potentiometer adjusts the contrast of
  the display. If you can't see anything when you run the sketch,
  turn the potentiometer's knob until the text is clear.

This sketch was written by SparkFun Electronics,
with lots of help from the Arduino community.
This code is completely free for any use.
Visit https://www.sparkfun.com/products/12060 for SIK information.
Visit http://www.arduino.cc to learn about the Arduino.

Version 1.0 2/2013 MDG
*/

// Load the LiquidCrystal library, which will give us
// commands to interface to the LCD:

#include <LiquidCrystal.h>

// Initialize the library with the pins we're using.
// (Note that you can use different pins if needed.)
// See http://arduino.cc/en/Reference/LiquidCrystal
// for more information:

LiquidCrystal lcd(12,11,6,5,4,3);



  void setup()
  {
  // Initialize a serial connection for reporting values to the host
  Serial.begin(38400);
   
  // Set up the status LED line as an output
  pinMode(statusLed, OUTPUT);
  digitalWrite(statusLed, HIGH);  // We have an active-low LED attached
  
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);

  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;

  // The Hall-effect sensor is connected to pin 2 which uses interrupt 0.
  // Configured to trigger on a FALLING state change (transition from HIGH
  // state to LOW state)
  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);

  
  }

void loop()
{

 if((millis() - oldTime) > 1000)    // Only process counters once per second
  { 
   
    detachInterrupt(sensorInterrupt);
        
   
    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
   
    oldTime = millis();
 
    flowMilliLitres = (flowRate / 60) * 1000;
    
    totalMilliLitres += flowMilliLitres;
      
    unsigned int frac;
    
    
    Serial.print("Flow rate: ");
    Serial.print(int(flowRate));  
    Serial.print(".");             
    frac = (flowRate - int(flowRate)) * 10;
    Serial.print(frac, DEC) ;      
    Serial.print("L/min");
  
    Serial.print("  Current Liquid Flowing: ");           
    Serial.print(flowMilliLitres);
    Serial.print("mL/Sec");

    // Print the cumulative total of litres flowed since starting
    Serial.print("  Output Liquid Quantity: ");             // Output separator
    Serial.print(totalMilliLitres);
    Serial.println("mL"); 

    // Reset the pulse counter so we can start incrementing again
    pulseCount = 0;
    
    // Enable the interrupt again now that we've finished sending output
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);

  
  }

  lcd.setCursor(0,1);



 
  // The LiquidCrystal library can be used with many different
  // LCD sizes. We're using one that's 2 lines of 16 characters,
  // so we'll inform the library of that:

  lcd.begin(16,1);





  lcd.print(flowRate);


  

}



  // so we'll inform the library of that:




  




 











