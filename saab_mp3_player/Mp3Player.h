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
    void fillSongs(uint8_t flags, uint8_t indent, SdBaseFile *sdBaseFile);
  private: 
    uint8_t getNext(uint8_t flags, uint8_t indent, SdBaseFile *sdBaseFile);
};
