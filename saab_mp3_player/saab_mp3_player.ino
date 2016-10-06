#include <SPI.h>
#include "Mp3Player.h"

Mp3Player Mp3player;

void setup() {
  Serial.begin(115200);
  Mp3player.init();
}

void loop() {
 // Mp3player.loopSongs();
  while(Serial.available()) {
    String message = Serial.readString();// read the incoming data as string 
    parceMenu(message);
  }

  delay(100);
}

void parceMenu(String message){
   if(message == "nextSong"){
      Mp3player.nextSong();
    } else if(message == "prevSong"){
      Mp3player.prevSong();
    } else if(message == "nextDir"){
      Mp3player.nextDir();
    } else if(message == "prevDir"){
      Mp3player.prevDir();
    } else if(message == "readDir"){
      Mp3player.fillDirs(4, 0, NULL);
    }
}


