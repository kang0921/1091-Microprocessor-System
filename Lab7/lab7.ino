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
int speakerPin = D3;
// 依照簡譜的順序，填入代表的音符，空白代表休止符
char notes[] = "geefddcdefggggeefddceggedddddefeeeeefggeefddceegc";
float beats[] =  {0.5, 0.5, 1, 0.5, 0.5, 1, 0.5,0.5,0.5,0.5,0.5,0.5,1,
0.5,0.5,1,0.5,0.5,1,0.5,0.5,0.5,0.5,2,
0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 1, 0.5,0.5,0.5,0.5,0.5,0.5,1,
0.5, 0.5, 1, 0.5, 0.5 , 1, 0.5, 0.5, 0.5, 0.5, 2};
// 利用 sizeof()，算出總共要多少音符
int length = sizeof(notes);
// 決定一拍多長，這邊一拍 600 ms
int tempo = 600;
int tones_low[] = { 261, 294, 330, 349, 392, 440, 494, 523 };
int tones_mid[] = { 523, 587, 659, 698, 784, 880, 988, 1046 };
int tones_high[] = { 1046, 1175, 1318, 1397, 1568, 1760, 1976, 2000 };

void setup() {
  // put your setup code here, to run once:
  pinMode(speakerPin, OUTPUT);
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
    if ((keyscan()==true) && (keyindex=(Row-1)*4+Col))
    {
       if(Row == 1 && Col == 1){
      // 利用 for 來播放我們設定的歌曲，一個音一個音撥放
          for (int i = 0; i < length; i++) {
          // 如果是空白的話，不撥放音樂
            if (notes[i] == ' ') {
              delay(beats[i] * tempo); // rest
            } else {
           // 呼叫 palyNote() 這個 function，將音符轉換成訊號讓蜂鳴器發聲
              playNote(speakerPin,notes[i], beats[i] * tempo, tones_low);
            }
            // 每個音符之間的間隔，這邊設定的長短會有連音 or 段音的效果
            delay(tempo/10);
          }
       }
         else if(Row == 1 && Col == 2){
      // 利用 for 來播放我們設定的歌曲，一個音一個音撥放
            for (int i = 0; i < length; i++) {
            // 如果是空白的話，不撥放音樂
              if (notes[i] == ' ') {
                delay(beats[i] * tempo); // rest
              } else {
             // 呼叫 palyNote() 這個 function，將音符轉換成訊號讓蜂鳴器發聲
                playNote(speakerPin,notes[i], beats[i] * tempo, tones_mid);
              }
              // 每個音符之間的間隔，這邊設定的長短會有連音 or 段音的效果
              delay(tempo/10);
          }
        }
        else if(Row == 1 && Col == 3){
      // 利用 for 來播放我們設定的歌曲，一個音一個音撥放
            for (int i = 0; i < length; i++) {
            // 如果是空白的話，不撥放音樂
              if (notes[i] == ' ') {
                delay(beats[i] * tempo); // rest
              } else {
             // 呼叫 palyNote() 這個 function，將音符轉換成訊號讓蜂鳴器發聲
                playNote(speakerPin,notes[i], beats[i] * tempo, tones_high);
              }
              // 每個音符之間的間隔，這邊設定的長短會有連音 or 段音的效果
              delay(tempo/10);
          }
        }
    }
   }
}


void playNote(int OutputPin, char note, unsigned long duration, int tones[]) {
   // 音符字元與對應的頻率由兩個矩陣表示
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  // 播放音符對應的頻率
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      tone(OutputPin,tones[i], duration);
  //下方的 delay() 及 noTone ()，測試過後一定要有這兩行，整體的撥放出來的東西才不會亂掉，可能是因為 Arduino 送出tone () 頻率後會馬上接著執行下個指令，不會等聲音播完，導致撥出的聲音混合而亂掉
      delay(duration);
      noTone(OutputPin);
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





