#include <stdio.h>
#include <stdlib.h>
#include "../library/include/dynamic_array.h"

void read(DynamicArray *text, const char *file_name){
	FILE *file = fopen(file_name, "r");
	if(!text || !file){
		printf("Error: Invalid pointer\n");
		return;
	}

	char buf;
	while(fscanf(file, "%c", &buf)!=EOF){
		if(!((int)buf==10 || (int)buf==13)){
			pushDynamicArray(((DynamicArray **)text->array)[text->size-1], &buf);
			continue;
		}

		// if LN or CR
		DynamicArray *tmp = initDynamicArray(CHAR);
		pushDynamicArray(text, &tmp);
	}

	fclose(file);

	return;
}

void write(DynamicArray *text, const char *file_name){
	FILE *file = fopen(file_name, "w");
	if(!text || !file){
		printf("Error: Invalid pointer\n");
		return;
	}
	
	for(int i=0; i<text->size; i++){
		DynamicArray *tmp = ((DynamicArray **)text->array)[i];
		for(int j=0; j<tmp->size; j++) fprintf(file, "%c", ((char *)tmp->array)[j]);
		if(i+1<text->size) fprintf(file, "\n");
	}
	
	fclose(file);

	return;
}