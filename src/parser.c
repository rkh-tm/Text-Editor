#include <stdio.h>
#include <string.h>

typedef enum Action{
	QUIT, SAVE, APPEND, DELETE, NEXT, PREVIOUS, ERROR
} Action;

Action parse(){
	char buf[1000];
	fgets(buf, sizeof(buf), stdin);
	if(strcspn(buf, "\n")!=1) goto error;
	
	switch(buf[0]){
		case 'q': return QUIT;
		case 's': return SAVE;
		case 'a': return APPEND;
		case 'd': return DELETE;
		case 'n': return NEXT;
		case 'p': return PREVIOUS;
		default: goto error;
	}
	
error:
	system("clear");
	printf("Error: Invalid operation!\n");
	fgets(buf, sizeof(buf), stdin);
	return ERROR;
}