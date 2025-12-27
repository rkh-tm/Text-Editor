#include <stdio.h>
#include <stdlib.h>
#include "../library/include/dynamic_array.h"

void read(const DynamicArray *text, const FILE *file){
	if(!text){
		printf("Error: Missing array");
		return;
	}

	if(!file){
		printf("Error: Missing file");
		return;
	}

	char buf;
	while(fscanf(file, "%c", &buf)!=EOF){
		if(!((int)buf==10 || (int)buf==13)){
			pushDynamicArray(((DynamicArray **)text->array)[text->size-1], &buf);
			continue;
		}

		// if LN or CR
		DynamicArray *tmp = malloc(sizeof(DynamicArray));
		*tmp = initDynamicArray(CHAR);
		pushDynamicArray(text, &tmp);
	}

	return;
}