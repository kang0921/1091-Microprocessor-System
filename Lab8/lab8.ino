//Sample using LiquidCrystal library
#include <LiquidCrystal.h>

/*******************************************************

This program will test the LCD panel and the buttons
Mark Bramwell, July 2010

********************************************************/

// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
char KeyValue[]={'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};
byte Row=0, Col=0;
int flag = 1; 
void setup() {
  // put your setup code here, to run once:
 
  pinMode(10, INPUT); //R1: S1,S2,S3,S4 (1,2,3,A)                                   
  pinMode(11, INPUT_PULLUP); //R2: S5,S6,S7,S8 (4,5,6,B)
  pinMode(12, INPUT_PULLUP); //R3: S9, S10, S11,S12 (7,8,9,C)
  pinMode(13, INPUT_PULLUP); //R4: (*,0,#,D)
  pinMode(A0, OUTPUT); //A1, C1: S1,S5,S9 (1,4,7,*)
  pinMode(A1, OUTPUT); //A2, C2: S2,S6,S10 (2,5,8,0)
  pinMode(A2, OUTPUT); //A3, C3: S3,S7,S11 (3,6,9,#)
  pinMode(A3, OUTPUT); //A4, C4, S4,S8,S12 (*,0, #,D)
  //Pin left to right :R1 R2 R3 R4 C1 C2 C3 C4

  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
  digitalWrite(A2,HIGH);
  digitalWrite(A3,HIGH);
  lcd.begin(16, 2);              // start the library
  lcd.setCursor(0,0);
} 

void loop() {
  // put your main code here, to run repeatedly:
  static int keypressedcount=0;
  byte keyindex=0;
  //if key is pressed in the first round scan, 
  //then call keyscan() again to check if the key pressed in first round is actually pressed 
  if(keyscan()==true) 
  {
    keyindex=(Row-1)*4+Col;
    delay(5);

    // 以 push button 1 控制第一組文字顯示
    if ((keyscan()==true) && (keyindex==1))
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Better the devil you know than the devil you do not know.");
      delayMicroseconds(100);
      while( (digitalRead(2)==LOW) || (digitalRead(3)==LOW))
        ;  
    }
    // 以 push button 4 控制第二組文字顯示。
    else if ((keyscan()==true) && (keyindex==5))
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("It is better to learn a certain trade than to possess a large fortune.");
      delayMicroseconds(100);
    }
    // 以 push button A 控制文字左移。
    else if ((keyscan()==true) && (keyindex==4))
    {
      lcd.scrollDisplayLeft();
      delay(150);
    }
    // 以 push button B 控制文字右移。
    else if ((keyscan()==true) && (keyindex==8))
    {
      lcd.scrollDisplayRight();
      delay(150);
    }
    // 以 push button C 控制 Clear Display。
    else if ((keyscan()==true) && (keyindex==12))
    {
      lcd.clear();
    }
    
    // 以 push button * 控制 Cursor on/off。
    else if ((keyscan()==true) && (keyindex==13))
    {
      if(flag == 1){
        lcd.cursor();
        flag = 0;
      }
      else if(flag == 0){
        lcd.noCursor();
        flag = 1;
      }
    }
    // 以 push button D 控制 Return Home。
    else if ((keyscan()==true) && (keyindex==16))
    {
      lcd.home();
    }
  } 
}

bool keyscan( )
{
  Row=0;Col=0;
  bool keypressed = false;
  //scan col1
  digitalWrite(A0, LOW);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  delayMicroseconds(100);
  //Read keys in row.1
  if(digitalRead(10)==LOW)
  {
      digitalWrite(A0, HIGH);
      Col=1;Row=1;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.2
  if(digitalRead(11)==LOW)
  {
      digitalWrite(A0, HIGH);
      Col=1;Row=2;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.3
  if(digitalRead(12)==LOW)
  {
      digitalWrite(A0, HIGH);
      Col=1;Row=3;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.4
  if(digitalRead(13)==LOW)
  {
       digitalWrite(A0, HIGH);
      Col=1;Row=4;
      keypressed = true;
      return(keypressed);
  }
  //scan col 2  
  digitalWrite(A0, HIGH);
  digitalWrite(A1, LOW);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, HIGH);
  delayMicroseconds(100);
  //Read keys in row.1
  if(digitalRead(10)==LOW)
  {
      digitalWrite(A1, HIGH);
      Col=2;Row=1;
      keypressed = true;
      return(keypressed);
  }
    //Read keys in row.2
  if(digitalRead(11)==LOW)
  {
      digitalWrite(A1, HIGH);
      Col=2;Row=2;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.3
  if(digitalRead(12)==LOW)
  {
      digitalWrite(A1, HIGH);
      Col=2;Row=3;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.4
  if(digitalRead(13)==LOW)
  {
      digitalWrite(A1, HIGH);
      Col=2;Row=4;
      keypressed = true;
      return(keypressed);
  }

  //scan col 3  
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, LOW);
  digitalWrite(A3, HIGH);
  delayMicroseconds(100);
  //Read keys in row.1
  if(digitalRead(10)==LOW)
  {
      digitalWrite(A2, HIGH);
      Col=3;Row=1;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.2
  if(digitalRead(11)==LOW)
  {
      digitalWrite(A2, HIGH);
      Col=3;Row=2;
      keypressed = true;
      return(keypressed);
  }  
  //Read keys in row.3
  if(digitalRead(12)==LOW)
  {
      digitalWrite(A2, HIGH);
      Col=3;Row=3;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.4
  if(digitalRead(13)==LOW)
  {
      digitalWrite(A2, HIGH);
      Col=3;Row=4;
      keypressed = true;
      return(keypressed);
  }
  
  //scan col 4  
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A3, LOW);
  delayMicroseconds(100);
  //Read keys in row.1
  if(digitalRead(10)==LOW)
  {
      digitalWrite(A3, HIGH);
      Col=4;Row=1;
      keypressed = true;
      return(keypressed);
  }
    //Read keys in row.2
  if(digitalRead(11)==LOW)
  {
      digitalWrite(A3, HIGH);
      Col=4;Row=2;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.3
  if(digitalRead(12)==LOW)
  {
      digitalWrite(A3, HIGH);
      Col=4;Row=3;
      keypressed = true;
      return(keypressed);
  }
  //Read keys in row.4
  if(digitalRead(13)==LOW)
  {
      digitalWrite(A3, HIGH);
      Col=4;Row=4;
      keypressed = true;
      return(keypressed);
  }
  return(false);
}



