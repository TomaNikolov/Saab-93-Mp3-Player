#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "SongsList.h"

#include <SdFat.h>
#include <SFEMP3Shield.h>
#include <stdint.h>
#include <string.h>

char* songs[4];
uint8_t index = 0;


char** SongsList::get(){
    return songs;
}

uint8_t SongsList::count(){
    return index;
}

void SongsList::clear() {
    for(uint8_t i = 0; i < index; i++) {
        free(songs[i]);
    }

    index = 0;
}

void SongsList::add(char* element){
    if(shouldResize()){
        resize();
    }
 
    songs[index] = element;
    index++;
}

void SongsList::resize(){
    uint8_t length = 2 * index;
    char* result[length];
    memcpy(result, songs, length);
    free(songs);
    **songs = &result;
}

bool SongsList::shouldResize(){
    return index >= listSize();
}

uint8_t SongsList::listSize(){
    return sizeof(songs);
}
