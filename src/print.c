#include <stdio.h>
#include "../library/include/dynamic_array.h"

int printLine(DynamicArray *text, unsigned int line){
    if(line>=text->size){
        printf("Error: Out of bounds\n");
        return 1;
    }
	
    int len = ((DynamicArray **)text->array)[line]->size;
    char *arr = ((DynamicArray **)text->array)[line]->array;
    for(int i=0; i<len; i++) printf("%c", arr[i]);

    return 0;
}

int printAll(DynamicArray *text, int line){
    char buf[1000];
    for(int i=0; i<text->size;){
        for(int j=i; j<i+line && j<text->size; j++){
            printf("%d | ", j+1);
            if(printLine(text, j)) return 1;
        }
        fgets(buf, sizeof(buf), stdin);
        system("clear");
        i += line;
    }
    
    return 0;
}