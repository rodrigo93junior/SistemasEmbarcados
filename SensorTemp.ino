/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>
#include <string.h>

 

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int pinTemp = A0;
float tempSensor = 0.0;
float tempCelsius = 0.0;
float maptempCelsius = 0.0;
// *1,28 +32
float fahrenheit = 0.0;

 

byte a[8]= {B00110,B01001,B00110,B00000,B00000,B00000,B00000,B00000,};

 

void setup() {
  lcd.begin(16, 2);
  pinMode(pinTemp, INPUT);
  Serial.begin(9600);
  lcd.createChar(1, a);
  lcd.setCursor(5,0);
  //Escreve o simbolo de grau
  lcd.write(1);
  lcd.setCursor(6, 0);
  lcd.print("C");
}

 

void loop() {
  tempSensor = analogRead(pinTemp);
  maptempCelsius = map(tempSensor, 20.00, 358.00, -40.00, 125.00);
  tempCelsius = calculaGrausCelsius(tempSensor);
  fahrenheit = celciusToFahrenheit(tempCelsius);
  Serial.println(tempSensor);
  Serial.println(tempCelsius);
  Serial.println(maptempCelsius);
  
  lcd.setCursor(0, 0);
  lcd.print(String(tempCelsius));
  delay(10000);
}

 

float calculaGrausCelsius(float valor){
    float tensao=(valor/1024)*5;
      return (tensao-0.5)*100;
}

 

float celciusToFahrenheit(float valor){
  return valor * 1.8 + 32;
}