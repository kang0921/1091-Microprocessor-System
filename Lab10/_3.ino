// include the library code:
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int delay_number = 100;

void setup() {
 pinMode(BT1, INPUT);
 pinMode(BT2, INPUT);
 pinMode(BT3, INPUT);
 pinMode(BT4, INPUT);
 //pinMode(A0, INPUT);
 //pinMode(A1, INPUT);
 //pinMode(A2, INPUT);
 //pinMode(A3, INPUT);

 // set up the LCD's number of columns and rows:
 lcd.begin(16, 2);
}

void loop() {
  lcd.clear();  // 清空螢幕
  lcd.print("Andes Hello");   //  印出"Andes Hello"
  delay(delay_number);
}
