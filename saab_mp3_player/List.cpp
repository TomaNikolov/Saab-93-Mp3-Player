#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "List.h"

#include <SdFat.h>
#include <SFEMP3Shield.h>
#include <stdint.h>
#include <string.h>

char* arr[4];
uint8_t currentIndex = 0;

char** List::init(){
    return arr;
}

void List::add(char* element){
    if(shouldResize()){
        resize();
    }
 
    arr[currentIndex] = element;
    currentIndex++;
}

void List::resize(){
    uint8_t length = 2 * currentIndex;
    char* result[length];
    memcpy(result, arr, length);

    **arr = &result;
}

bool List::shouldResize(){
    return currentIndex >= listSize();
}

uint8_t List::listSize(){
    return sizeof(arr);
}
