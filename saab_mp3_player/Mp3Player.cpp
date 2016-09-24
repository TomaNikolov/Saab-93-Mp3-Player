#include "MP3Player.h"
#include <SdFat.h>
#include <SFEMP3Shield.h>
#include <stdint.h>

SFEMP3Shield MP3player;
SdFat sd;
String dirs[3][29];
uint8_t currentDir;
uint8_t currentSong;
char *currentIndent = "";

void Mp3Player::init(){
  uint8_t result; //result code from some function as to be tested at later time.

  Serial.print(F("F_CPU = "));
  Serial.println(F_CPU);
  Serial.print(F("Free RAM = ")); // available in Version 1.0 F() bases the string to into Flash, to use less SRAM.
  Serial.print(FreeRam(), DEC);  // FreeRam() is provided by SdFatUtil.h
  Serial.println(F(" Should be a base line of 1017, on ATmega328 when using INTx"));

  //Initialize the SdCard.
  if(!sd.begin(SD_SEL, SPI_FULL_SPEED)) sd.initErrorHalt();
  // depending upon your SdCard environment, SPI_HAVE_SPEED may work better.
  if(!sd.chdir("/")) sd.errorHalt("sd.chdir");

  //Initialize the MP3 Player Shield
  result = MP3player.begin();
  //check result, see readme for error codes.
  if(result != 0) {
    Serial.print(F("Error code: "));
    Serial.print(result);
    Serial.println(F(" when trying to start MP3 player"));
    if( result == 6 ) {
      Serial.println(F("Warning: patch file not found, skipping.")); // can be removed for space, if needed.
      Serial.println(F("Use the \"d\" command to verify SdCard can be read")); // can be removed for space, if needed.
    }
  }
  SdBaseFile *sdBaseFile = sd.vwd();
  fillSongs(LS_R, 0, sdBaseFile);
}

void Mp3Player::nextDir(){
    char song2[] = "MUSE-G~1/01-STA~1.MP3";
    MP3player.stopTrack();
    MP3player.playMP3(song2);
    Serial.println(song2);
}

void Mp3Player::nextSong(){
    char song2[] = "MUSE-G~1/01-TAK~1.MP3";
    MP3player.stopTrack();
    MP3player.playMP3(song2);
    Serial.println(song2);
}

void Mp3Player::prevDir(){
    char song2[] = "MUSE-G~1/03-NEW~1.MP3";
    MP3player.stopTrack();
    MP3player.playMP3(song2);
    Serial.println(song2);
}

void Mp3Player::prevSong(){
    char song2[] = "MUSE-G~1/08-APO~1.MP3";
    MP3player.stopTrack();
    MP3player.playMP3(song2);
    Serial.println(song2);
}

void Mp3Player::loopSongs(){
    char song2[] = "MUSE-G~1/08-APO~1.MP3";
    if (!MP3player.isPlaying()){
        MP3player.playMP3(song2);
        Serial.println(song2);
    }
}

void Mp3Player::fillSongs(uint8_t flags, uint8_t indent, SdBaseFile *sdBaseFile){
    MP3player.stopTrack();
    if(sdBaseFile == NULL){
      sdBaseFile = sd.vwd();
    }
    
    sdBaseFile->rewind();

    int8_t status;
    indent = 0;
    while ((status = getNext(flags, indent, sdBaseFile))) {
            if (status > 1 && (flags & LS_R)) {
            uint16_t index = sdBaseFile->curPosition()/32 - 1;
            SdBaseFile s;
            if (s.open(sdBaseFile, index, O_READ)) {
                Serial.println("inside");
                fillSongs(flags, indent + 1, &s);
            }
            s.seekSet(32 * (index + 1));
        }
    }
}

uint8_t song = 0;
uint8_t Mp3Player::getNext(uint8_t flags, uint8_t indent,  SdBaseFile *sdBaseFile) {
  dir_t dir;
  uint8_t w = 0;
  
  while (1) {
    if (sdBaseFile->read(&dir, sizeof(dir)) != sizeof(dir)) return 0;
    if (dir.name[0] == DIR_NAME_FREE) return 0;
    // skip deleted entry and entries for . and  ..
    if (dir.name[0] != DIR_NAME_DELETED && dir.name[0] != '.'
      && DIR_IS_FILE_OR_SUBDIR(&dir)) break;
  }
  // indent for dir level
  for (uint8_t i = 0; i < indent; i++) Serial.print(' ');

  // print name
  for (uint8_t i = 0; i < 11; i++) {
    if (dir.name[i] == ' ')continue;
    if (i == 8) {
      //Serial.print('.');
      w++;
    }
    //Serial.print((char)dir.name[i]);
    w++;
  }
  if (DIR_IS_SUBDIR(&dir)) {
    //Serial.print('/');
    currentIndent = dir.name + '/';
    song = 0;
    w++;
  } else {
      char *str;
      strcat(currentIndent, str);
      strcat(dir.name, str);
      dirs[indent][song] = str;
      song++;
       Serial.println(dirs[indent][song]);
  }
   Serial.println();
  return DIR_IS_FILE(&dir) ? 1 : 2;
}
