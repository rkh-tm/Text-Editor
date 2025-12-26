#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"

// https://www.ascii-code.com/

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
            pushDynamicArray(((DynamicArray **)text->array)[text->size-1], &buf);
            if(!((int)buf==10 || (int)buf==13)) continue;

            // if LN or CR
            DynamicArray *tmp = malloc(sizeof(DynamicArray));
            *tmp = initDynamicArray(CHAR);
            pushDynamicArray(text, &tmp);
        }

        fclose(file);
    }

    while(1){
        system("clear");
        printf("1. View all\n2. View line\n3. Exit\nPick operation: ");

        char buf[1000];
        char *end;
        int op = strtol(fgets(buf, sizeof(buf), stdin), &end, 10);
        if(*end!=10 || op<1 || op>3){
            printf("Error: Invalid operation!\n");
            for(int i=0; i<10; i++){
                printf("%d ", buf[i]);
            }
            fgets(buf, sizeof(buf), stdin);
            system("clear");
            continue;
        }

        switch(op){
            case 1:
                system("clear");
                printAll(text, 10);
                break;
            case 2:
                system("clear");
                printf("View line: ");
                int line = strtol(fgets(buf, sizeof(buf), stdin), &end, 10);
                if(*end!=10){
                    printf("Error: Not a number!\n");
                    break;
                }
                printLine(text, line);
                fgets(buf, sizeof(buf), stdin);
                break;
            case 3:
                goto cleanup;
        }
    }

cleanup:
    system("clear");
    text = freeDynamicArray(text);
	return 0;
}