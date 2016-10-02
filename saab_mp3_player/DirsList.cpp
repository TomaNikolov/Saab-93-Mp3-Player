#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "DirsList.h"

#include <SdFat.h>
#include <SFEMP3Shield.h>
#include <stdint.h>
#include <string.h>

char* arr[4];
uint8_t currentIndex = 0;


char** DirsList::get(){
    return arr;
}

uint8_t DirsList::count(){
    return currentIndex;
}

void DirsList::add(char* element){
    if(shouldResize()){
        resize();
    }
 
    arr[currentIndex] = element;
    currentIndex++;
}

void DirsList::resize(){
    uint8_t length = 2 * currentIndex;
    char* result[length];
    memcpy(result, arr, length);
    free(arr);
    **arr = &result;
}

bool DirsList::shouldResize(){
    return currentIndex >= listSize();
}

uint8_t DirsList::listSize(){
    return sizeof(arr);
}
