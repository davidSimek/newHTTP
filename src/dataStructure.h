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

// ----------
// | STRING |
// ----------

typedef DynamicArray String;

bool add_char(String* string, char character);
bool add_string(String* string, char* source, size_t length);
void copy_string(String* string, char* destination, size_t length);
size_t string_lenght(String* string);
bool create_string(String* string);
void destroy_string(String* string);

// ---------------
// | STRING VIEW |
// ---------------

typedef struct {
    char* start;
    size_t length;
} StringView;

void create_string_view(StringView* string_view, char* start, char* end);
void print_string_view(StringView* string_view);
void copy_string_view(StringView* string_view, void* destination);
size_t string_view_length(StringView* string_view);

#endif
