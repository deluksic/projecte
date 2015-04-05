#include "projecte.h"

// waits for any key and returns it
char waitforkey(){
	char breakchar;
	printf("\nPress enter to continue.\n");
	scanf("%c", &breakchar);
	return breakchar;
}

// exits with a message and error
void errorexit(char* message, int code){
	printf("Error %d. %s\n", code, message);
	waitforkey();
	exit(code);
}

// exits with a message
void messageexit(char* message){
	printf("%s\n", message);
	waitforkey();
	exit(0);
}