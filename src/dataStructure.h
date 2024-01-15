#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// -----------------
// | DYNAMIC ARRAY |
// -----------------

typedef struct {
    void* buffer;
    size_t allocated;
    size_t used;
    int elementSize;
} DynamicArray;

bool createDynamicArray(DynamicArray* thisArray, size_t elementSize);
void destroyDynamicArray(DynamicArray* thisArray);
bool addToDynamicArray(DynamicArray* thisArray, void* value);
bool addMultipleToDynamicArray(DynamicArray* thisArray, void* first, size_t count);
void* getFromDynamicArray(DynamicArray* thisArray, size_t index);

// only for debugging
void dynamicArrayInfo(DynamicArray* dynamicArray);

#endif
