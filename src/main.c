#include <stdio.h>
#include <stdlib.h>
#include "../library/include/dynamic_array.h"
#include "../library/include/math_extra.h"

#include "print.c"
#include "parser.c"
#include "action.c"

int main(int argc, char *argv[]){
    if(argc!=2){
        printf("Error: Invalid arguments");
        return 1;
    }

    DynamicArray *text = initDynamicArray(DYNAMIC_ARRAY);
	DynamicArray *tmp = initDynamicArray(CHAR);
    pushDynamicArray(text, &tmp);

	read(text, argv[1]);
	
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
		case WRITE:
			write(text, argv[1]);
			system("clear");
			printPage(text, line, LINE_PER_PAGE);
			printf("File saved");
			fgets(buf, sizeof(buf), stdin);
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