#include "public_interface.h"
#include "logs.h"
#include "dataStructure.h"

#include <stdio.h>

int main(void)
{
    puts("HI");
    init_server(IPV4, HTTP, 1234);
    
    int a = 3;
    int b = 4;
    int c = 2;
    int d = 1;
    int e = 9;

    DynamicArray names;
    createDynamicArray(&names, sizeof(int));

    addToDynamicArray(&names, &a);
    addToDynamicArray(&names, &b);
    addToDynamicArray(&names, &c);
    addToDynamicArray(&names, &d);
    addToDynamicArray(&names, &e);
    
    dynamicArrayInfo(&names);
    int arr[] = {2, 3, 4};
    log_info("adding now...");
    addMultipleToDynamicArray(&names, arr, 3);
    log_info("added!!");
    dynamicArrayInfo(&names);

    int* f = getFromDynamicArray(&names, 0);
    int* g = getFromDynamicArray(&names, 3);
    if (f != NULL && g != NULL) {
        printf("There is %d in array and %d in it", *f, *g);
    }
    dynamicArrayInfo(&names);

    destroyDynamicArray(&names);
}
