#include <stdint.h>
#include <SdFat.h>

class Mp3Player {
  public:
    void init();
    void nextSong();
    void prevSong();
    void nextDir();
    void prevDir();
    void loopSongs();
    void fillDirs(uint8_t flags, uint8_t indent, SdBaseFile *sdBaseFile);
    void fillSongs(uint8_t flags, char* path);
  private:
    void play();
    void changeSong(int8_t move);
    void Mp3Player::changeDir(int8_t move);
    uint8_t getNextDir(uint8_t flags, uint8_t indent, SdBaseFile *sdBaseFile);
    uint8_t getNextSong(uint8_t flags, SdBaseFile *sdBaseFile);
    uint8_t getArrLength(char* arr);
    char* concatStr(char* firstStr, char* secondStr);
    void logToSerial();
    };
