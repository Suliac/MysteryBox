#include "LiquidCrystal.h"

LiquidCrystal lcd(8,9,4,5,6,7);

void setup() {
  lcd.begin(16,2);

  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Hello World!");

  // set the data rate for the SoftwareSerial port
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);

  lcd.setCursor(0,0);
  lcd.print("S1: ");
  lcd.setCursor(0,1);
  lcd.print("S2: ");

  pinMode(45, INPUT_PULLUP);
}


void loop() {
  if (Serial1.available()) {
    int val = Serial1.read();
    lcd.setCursor(4,0);
    
    lcd.print("ID ");
    lcd.print(val & 0b00000011);
    
    if((val & 0b10000000) != 0)
      lcd.print(" WIN!");
    else
      lcd.print(" LOSE");
  } else {
    lcd.setCursor(4,0);
    lcd.print("           ");
  }
  
  if (Serial2.available()) {
    int val = Serial2.read();
    lcd.setCursor(4,1);
    
    lcd.print("ID ");
    lcd.print(val & 0b00000011);
    
    if((val & 0b10000000) != 0)
      lcd.print(" WIN!");
    else
      lcd.print(" LOSE");
  } else {
    lcd.setCursor(4,1);
    lcd.print("           ");
  }
}
