#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "puzzleMaker.h"

int main(int argc, char *argv[]){

	
	if(argc > 1 &&  argv[1][strlen(argv[1])-1] == 47){
		// check that argv[1] exsists, and it ends with a "/" 47 is the ascki code for /
			
		readfilesInDirs(argv[1]);	
	}else{
		
		printf("Please provide a directory name including the (/)\n");		
	
	}

	
	
	
	return 0;

}


