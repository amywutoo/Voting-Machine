#include<LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define sw1 15
#define sw4 18

const int ledPinY = 7; 
int ledStateY = LOW;         // the current state of the output pin
int buttonStateY;             // the current reading from the input pin
int lastButtonStateY = LOW;   // the previous reading from the input pin
long lastDebounceTimeY = 0;  // the last time the output pin was toggled
long debounceDelayY = 50;    // the debounce time; increase if the output flickers
int totalYesPress = 0;

const int ledPinN = 8; 
int ledStateN = LOW;           // the current state of the output pin
int buttonStateN;             // the current reading from the input pin            
int lastButtonStateN = LOW;   // the previous reading from the input pin
long lastDebounceTimeN = 0;  // the last time the output pin was toggled
long debounceDelayN = 50;    // the debounce time; increase if the output flickers
int totalNoPress = 0; 


void setup()  {

  //initialize serial communications at a 9600 baud rate
  Serial.begin(9600);
  
  pinMode(sw1,INPUT);
  pinMode(ledPinY, OUTPUT);
  digitalWrite(ledPinY, ledStateY);

  pinMode(sw4,INPUT);
  pinMode(ledPinN, OUTPUT);
  digitalWrite(ledPinN, ledStateN);

  lcd.begin(16, 2);
  lcd.print("Have you been to");
  lcd.setCursor(0,1);
  lcd.print("Queens, NY?");
  delay(1500);
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("YES");
  lcd.setCursor(4,0);
  lcd.setCursor(8,0);
  lcd.setCursor(12,0);
  lcd.print("NO");
  
}

void loop() {

  lcd.setCursor(0,0);
  lcd.print("YES");
  lcd.setCursor(1,1);
  lcd.print(totalYesPress);
  lcd.setCursor(12,0);
  lcd.print("NO"); 
  lcd.setCursor(13,1);
  lcd.print(totalNoPress);

  // read the state of the switch into a local variable
  int yesVal = digitalRead(sw1);
  int noVal = digitalRead(sw4);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:
  
  if (yesVal != lastButtonStateY) {
  // reset the debouncing timer
  lastDebounceTimeY = millis();
  }
  
  if (noVal != lastButtonStateN) {
  lastDebounceTimeN = millis();
  }

  
if ((millis() - lastDebounceTimeY) > debounceDelayY) {

  if(yesVal != buttonStateY) {
    buttonStateY = yesVal;

    //only toggle the LED if the new button state is HIGH
    if (buttonStateY == LOW) {
      ledStateY = !ledStateY;

      if(digitalRead(sw1)==0) {
      totalYesPress++; 
      Serial.write(1);
      }
    }
  }
    else {
      ledStateY = LOW;
    } 
}


if ((millis() - lastDebounceTimeN) > debounceDelayN) {
  
  if(noVal != buttonStateN) {
    buttonStateN = noVal;
    
    if (buttonStateN == LOW) {
      ledStateN = !ledStateN;

      if(digitalRead(sw4)==0) {
      totalNoPress++;
      Serial.write(4); 
      }

    }
  }

  else {
      ledStateN = LOW;
    } 
}

//set the LED
digitalWrite(ledPinY, ledStateY);
lastButtonStateY = yesVal;

digitalWrite(ledPinN, ledStateN);
lastButtonStateN = noVal;

}
