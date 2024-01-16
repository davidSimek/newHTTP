#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dataStructure.h"
#include "logs.h"

bool createDynamicArray(DynamicArray* thisArray, size_t elementSize) {
    thisArray->buffer = malloc(elementSize * 4);
    if (thisArray->buffer == NULL)
        return false;

    thisArray->allocated = elementSize * 4;
    thisArray->used = 0;
    thisArray->elementSize = elementSize;
    return true;
}

void destroyDynamicArray(DynamicArray* thisArray) {
    free(thisArray->buffer);
    thisArray->buffer = 0;
}

void dynamicArrayInfo(DynamicArray* dynamicArray){
    printf("Dynamic Array:\n\tallocated: %zuB, used: %zuB\n", dynamicArray->allocated, dynamicArray->used);
    
    if (dynamicArray->buffer == NULL) {
        log_error("calling dynamicArrayInfo() on unallocated array");
        return;
    }

    if (dynamicArray->elementSize == sizeof(int)) {
        printf("int[%zu]\n", dynamicArray->used/dynamicArray->elementSize);
        
        int* current = dynamicArray->buffer;
        for(int i = 0; i < dynamicArray->used / dynamicArray->elementSize; i++) {
            printf("[%d], ", *current);
            current++;
        }
        printf("\n");
    }
}

bool addToDynamicArray(DynamicArray* thisArray, void* value) {
    // is full 
    if (thisArray->allocated == thisArray->used) {

        size_t newSize = thisArray->allocated * 1.5f;
        void* newArray = realloc(thisArray->buffer, newSize); 

        // reallocation failed
        if (newArray == 0) {
            free(thisArray->buffer);
            thisArray->buffer = 0;
            thisArray->allocated = 0;
            thisArray->used = 0;
            thisArray->elementSize = 0;
            return false;
        }

        thisArray->buffer = newArray;
        thisArray->allocated = newSize;
    }

    memcpy(&thisArray->buffer[thisArray->used], value, thisArray->elementSize);
    thisArray->used += thisArray->elementSize;
    return true;
}

bool addMultipleToDynamicArray(DynamicArray* thisArray, void* first, size_t count) {
    // is full 
    if (thisArray->allocated <= thisArray->used + count * thisArray->elementSize - thisArray->elementSize) {
        size_t newSize;
        void* newArray;

        // normal procedure can't handle
        if (count + thisArray->allocated > thisArray->used * 1.5f)
            newSize = (thisArray->allocated + count * thisArray->elementSize) * 1.5f;
        else
            newSize = thisArray->allocated * 1.5f;

        newArray = realloc(thisArray->buffer, newSize);     
        
        // reallocation failed
        if (newArray == 0) {
            free(thisArray->buffer);
            thisArray->buffer = 0;
            thisArray->allocated = 0;
            thisArray->used = 0;
            thisArray->elementSize = 0;
            return false;
        }

        thisArray->buffer = newArray;
        thisArray->allocated = newSize;
    }

    memcpy(&thisArray->buffer[thisArray->used], first, thisArray->elementSize * count);
    thisArray->used += thisArray->elementSize * count;
    return true;
}

void* getFromDynamicArray(DynamicArray* thisArray, size_t index) {
    if (index > (thisArray->used / thisArray->elementSize)) {
        return NULL;
    }
    return &((char*)thisArray->buffer)[index * thisArray->elementSize];
}
