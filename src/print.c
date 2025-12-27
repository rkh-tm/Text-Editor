#include <stdio.h>
#include "../library/include/dynamic_array.h"

int printLine(const DynamicArray *text, const unsigned int line){
    if(line>=text->size){
        printf("Error: Out of bounds\n");
        return 1;
    }
	
    int len = ((DynamicArray **)text->array)[line]->size;
    char *arr = ((DynamicArray **)text->array)[line]->array;
    for(int i=0; i<len; i++) printf("%c", arr[i]);
	printf("\n");

    return 0;
}

void printPage(const DynamicArray *text, const unsigned int line, const int LINE_PER_PAGE){
	for(int i=line; i<line+LINE_PER_PAGE && i<text->size; i++){
		printf("%d\t", i+1);
		printLine(text, i);
	}

	return;
}