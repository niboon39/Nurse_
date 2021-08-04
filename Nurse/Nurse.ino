#include "SoftwareSerial.h"
SoftwareSerial mySerial(10, 11);
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]

# define ACTIVATED LOW

int buttonNext = 2;
int buttonPause = 3;
int buttonPrevious = 4;
boolean isPlaying = false;

void setup(){
  pinMode(buttonPause, INPUT_PULLUP);
  pinMode(buttonNext , INPUT_PULLUP);
  pinMode(buttonPrevious, INPUT_PULLUP);

  mySerial.begin(9600);
  delay(1000);
  isPlaying = true ; 
}
void execute_CMD(byte CMD , byte Par1 , byte Par2){
   // Calculate the command and parameters 
   word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);
   // Build the command line 
   byte Command_line[10] = {Start_Byte , Version_Byte , Command_Length , CMD , Acknowledge
                            , Par1 , Par2 , highByte(checksum) , lowByte(checksum), End_Byte};
   for (byte c=0; c<10; c++){
    mySerial.write( Command_line[c]);
   }
}
void playFirst(){
  execute_CMD(0x3F , 0 , 0);
  delay(500);
  setVolume(20);
  delay(500);
  execute_CMD(0x11, 0 , 1);
  delay(500);
}
void pause(){
  execute_CMD(0x0E , 0 , 0);
  delay(500);
}
void play(){
  execute_CMD(0x0D , 0 , 1);
  delay(500);
}
void playNext(){
  execute_CMD(0x01, 0 , 1);
  delay(500);
}
void playPrevious(){
  execute_CMD(0x02 , 0 , 1);
  delay(500);
}
void setVolume(int volume){
  execute_CMD(0x06 , 0 , volume); // set the volume (0x00 -> 0x30)
  delay(2000);
}
void DF_mp3(){
  int Read_BPause = digitalRead(buttonPause);
  int Read_BNext = digitalRead(buttonNext);
  int Read_BPrev = digitalRead(buttonPrevious);

  if (Read_BPause == ACTIVATED){
    if (isPlaying){
      pause();
      isPlaying = false ; 
    }
    else{
      isPlaying = true ;
      play();
    }
  }
  if (Read_BNext == ACTIVATED){
    if (isPlaying){
      playNext();
    }
  }
  if (Read_BPrev == ACTIVATED){
    if (isPlaying){
      playPrevious();
    }
  }
}
void loop(){
  DF_mp3();
}
