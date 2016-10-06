#include "MP3Player.h"
#include "DirsList.h"
#include "SongsList.h"
#include <SdFat.h>
#include <SFEMP3Shield.h>
#include <stdint.h>
#include <string.h>
#include "MemoryFree.h"

DirsList dirsList;
SongsList songsList;
SFEMP3Shield MP3player;
SdFat sd;

int8_t currentDir;
int8_t currentSong;


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
  fillDirs(LS_R, 0, sdBaseFile);
  char** arr2 = dirsList.get();
  fillSongs(LS_R, arr2[currentDir]);
  logToSerial();
  play();

// MP3player.playMP3("1998-S~1/01-SUI~1.MP3");
}

void Mp3Player::nextDir(){
    changeDir(1);
    play();
    logToSerial();
}

void Mp3Player::nextSong(){
    changeSong(1);
    play();
    logToSerial();
}

void Mp3Player::prevDir(){
    changeDir(-1);
    play();
    logToSerial();
}

void Mp3Player::prevSong(){
    changeSong(-1);
    play();
    logToSerial();
}

void Mp3Player::loopSongs(){
    if (!MP3player.isPlaying()){
        changeSong(1);
        play();
    }
}

void Mp3Player::fillDirs(uint8_t flags, uint8_t indent, SdBaseFile *sdBaseFile){
    MP3player.stopTrack();
    if(sdBaseFile == NULL){
      sdBaseFile = sd.vwd();
    }
    
    sdBaseFile->rewind();

    int8_t status;
    indent = 0;
    while ((status = getNextDir(flags, indent, sdBaseFile))) {
            if (status > 1 && (flags & LS_R)) {
            uint16_t index = sdBaseFile->curPosition()/32 - 1;
            SdBaseFile s;
            if (s.open(sdBaseFile, index, O_READ)) {
                fillDirs(flags, indent + 1, &s);
            }
            s.seekSet(32 * (index + 1));
        }
    }
}

uint8_t Mp3Player::getNextDir(uint8_t flags, uint8_t indent,  SdBaseFile *sdBaseFile) {
  dir_t dir;
  
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
  //char songsOrFolder;
  char* songsOrFolder = (char*)malloc(10);

  for (uint8_t i = 0; i < 8; i++) {
    if (dir.name[i] == ' ')continue;
    if (i == 8) {
     songsOrFolder[i] = '.';
    }
    songsOrFolder[i] = dir.name[i];
  }
  if (DIR_IS_SUBDIR(&dir)) {
    songsOrFolder[8] = '/';
    songsOrFolder[9] = '\0';
    dirsList.add(songsOrFolder);
    Serial.print("dir name: ");
    Serial.println(songsOrFolder);
  } else {
     free(songsOrFolder);
  }
  // Serial.println();
  return DIR_IS_FILE(&dir) ? 1 : 2;
}

void Mp3Player::fillSongs(uint8_t flags, char* path){
  int8_t status;
  SdBaseFile s;
  s.open(path, O_READ);
  s.rewind();

  Serial.print("traverse dir: ");
  Serial.println(path);
  //Clear old songs and fill the new ones
  songsList.clear();
  
  while (status = getNextSong(flags, &s)) {
    Serial.print("Free ram:  ");
      Serial.println(freeMemory());
  }
}

uint8_t Mp3Player::getNextSong(uint8_t flags, SdBaseFile *sdBaseFile) {
  dir_t dir;
  while (1) {
    if (sdBaseFile->read(&dir, sizeof(dir)) != sizeof(dir)) return 0;
    if (dir.name[0] == DIR_NAME_FREE) return 0;
    // skip deleted entry and entries for . and  ..
    if (dir.name[0] != DIR_NAME_DELETED && dir.name[0] != '.'
      && DIR_IS_FILE_OR_SUBDIR(&dir)) break;
  }

  //Not enough memory
  if (songsList.count() > 2) return;
  char* song = (char*)malloc(14);
  for (uint8_t i = 0; i < 8; i++) {
    if (dir.name[i] == ' ')continue;
    song[i] = dir.name[i];
  }
  if (DIR_IS_SUBDIR(&dir)) {
     Serial.println("dir");
  } else {
      song[8] = '.';
      song[9] = 'M';
      song[10] = 'P';
      song[11] = '3';
      song[12] = '\0';
     Serial.println(song);
     songsList.add(song);
  }
 
  return DIR_IS_FILE(&dir) ? 1 : 2;
}

char* Mp3Player::concatStr(char* firstStr, char* secondStr) {
    uint8_t firstStrSize = getArrLength(firstStr);
    int secondStrSize = getArrLength(secondStr);
    int length = firstStrSize + secondStrSize;
    char* result = malloc(23);
    strcpy(result, firstStr);
    strcat(result, secondStr);
    result[23] = '\0';
    return result;
}

uint8_t Mp3Player::getArrLength(char* arr){
    return sizeof(arr) / sizeof(char);
}

void Mp3Player::changeDir(int8_t move){
    currentDir += move;

    if(currentDir > dirsList.count()){
        currentDir = 0;
    }

    if(currentDir < 0 ){
        currentDir = dirsList.count();
    }
    
    currentSong = 0;
    char ** dirs = dirsList.get(); 
    fillSongs(LS_R, dirs[currentDir]);
}

void Mp3Player::changeSong(int8_t move) {
    currentSong += move;

    if(currentSong > songsList.count()){
        changeDir(1);
    }

    if(currentSong < 0 ){
       changeDir(-1);
    }
}

void Mp3Player::play(){
    MP3player.stopTrack();
    char** dirs = dirsList.get();
    char** songs = songsList.get();
    char* songPath = concatStr(dirs[currentDir], songs[currentSong]);
    Serial.print("Song path: ");
    Serial.println(songPath);
    MP3player.playMP3(songPath);
    free(songPath);
}

void Mp3Player::logToSerial(){
   char** dirs = dirsList.get();
   Serial.print("Current dir: ");
   Serial.println(dirs[currentDir]);

   Serial.print("Current dir index: ");
   Serial.println(currentDir);

   char** songs = songsList.get();

   Serial.print("Current songs count: ");
   Serial.println(songsList.count());
   
   Serial.print("Current song: ");
   Serial.println(songs[currentSong]);

   Serial.print("Current song index: ");
   Serial.println(currentSong);
}

