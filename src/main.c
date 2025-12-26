#include <stdio.h>
#include <stdlib.h>
#include "../library/include/dynamic_array.h"
#include "../library/include/math_extra.h"

#include "print.c"
#include "parser.c"

// https://www.ascii-code.com/

void save(char *file_name, DynamicArray *text){
	FILE *file = fopen(file_name, "w");
	
	for(int i=0; i<text->size; i++){
		DynamicArray *tmp = ((DynamicArray **)text->array)[i];
		for(int j=0; j<tmp->size; j++) fprintf(file, "%c", ((char *)tmp->array)[j]);
		if(i+1<text->size) fprintf(file, "\n");
	}
	
	fclose(file);

	printf("File saved\n");
	char buf[1000];
	fgets(buf, sizeof(buf), stdin);

	return;
}

int main(int argc, char *argv[]){
    if(argc!=2){
        printf("Error: Invalid arguments");
        return 1;
    }

    DynamicArray *text = malloc(sizeof(DynamicArray));
    *text = initDynamicArray(DYNAMIC_ARRAY);
    DynamicArray *tmp = malloc(sizeof(DynamicArray));
    *tmp = initDynamicArray(CHAR);
    pushDynamicArray(text, &tmp);

    FILE *file = fopen(argv[1], "r");
    if(file){
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

        fclose(file);
    }

	const int LINE_PER_PAGE = 36;
	int line = 0;
    while(1){
		system("clear");
		
		printPage(text, line, LINE_PER_PAGE);

		char buf[1000];
		Action op = parse();
		switch(op){
		case ERROR: continue;
		case QUIT: goto cleanup;
		case SAVE:
			save(argv[1], text);
			break;
		case NEXT:
			line = min(line+LINE_PER_PAGE/2, max(0, text->size-LINE_PER_PAGE));
			break;
		case PREVIOUS:
			line = max(0, line-LINE_PER_PAGE/2);
			break;
		}
    }

cleanup:
    system("clear");
    text = freeDynamicArray(text);
	return 0;
}