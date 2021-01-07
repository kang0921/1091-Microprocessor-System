#define NUM 25

int leds[NUM] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, D14, D15, A0, A1, A2, A3, LED1, LED2, LED3, LED4
};

#define SIZE 16

int myLeds[SIZE] = {
  0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, D14, D15
};
void setup() {
  //初始設定，因為leds3設成OUTPUT蜂鳴器會叫，所以讓他變成不要OUTPUT
  for(int i = 0; i < NUM; i++){
    if(i!=3){
      pinMode(leds[i], OUTPUT);
    }
  }
}

//在這個function傳一個數字，Leds會對應顯示
void LedsMapping(unsigned int value){
  unsigned tmp = value & 0xFFFF;  

  for(int i = 0; i < SIZE; i++){
    if(tmp & 0x1){  //看他是不是1
        digitalWrite(myLeds[i], HIGH); // 如果1會亮      
    }
    else{
        digitalWrite(myLeds[i], LOW); //如果0會滅
    }
    tmp >>= 1;  //逐一比對
  }
}

// the loop function runs over and over again forever
void loop() {
  for( int i = 0; i<3; i++){
      //讓奇數滅偶數亮
      LedsMapping(0x5555);  //0x5555 = 0101010101010101
      delay(300);
      //讓奇數亮偶數滅
      LedsMapping(0xAAAA);  //0xAAAA = 1010101010101010
      delay(300);
  }

  for( int i = 0; i<3; i++){
      LedsMapping(0x0);//全亮
      delay(300);
      LedsMapping(0xFFFF);//全滅
      delay(300);
  }
}




