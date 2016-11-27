#include <dirent.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>



#include "puzzleMaker.h"

#define MAX_LINE_LENGTH 1024
#define MAX_LEN 30



void readfilesInDirs(const char *dirPath){
	
	DIR* dir;
	struct dirent* dirFile;
	int counter = 0;

	int numberOfItems = getNumberOfFilesInDir(dirPath);
	char *FilenameList[numberOfItems][2];
	dir = opendir(dirPath);
	while ((dirFile = readdir(dir))){ //save filename and fullpath to pointer 2d array

		if (!strcmp (dirFile->d_name, ".") ||!strcmp (dirFile->d_name, "..") ){
			continue;
		}

		char *filenameAndPath = malloc(1 + strlen(dirFile->d_name)+ strlen(dirPath) );
		char *filename = malloc(1 + strlen(dirFile->d_name)+ strlen(dirPath) );

		strcpy(filenameAndPath,dirPath );
		strcat(filenameAndPath,dirFile->d_name);
		strcpy(filename,dirFile->d_name);

		FilenameList[counter][1] =  malloc(sizeof(char *) * MAX_LINE_LENGTH);
		FilenameList[counter][0] =  malloc(sizeof(char *) * MAX_LINE_LENGTH);

		strcpy(FilenameList[counter][1], filenameAndPath);
		strcpy(FilenameList[counter][0], filename);
		free(filenameAndPath);
		free(filename);
 
		counter ++;		

	}
	closedir(dir);
	SortFileNames(FilenameList, counter);//sort filenames
	int numberOfRows = getNumberOfRows(FilenameList,counter ); //number of rows in puzzle
	int numberOfCols = getNumberOfcolumns(FilenameList,counter); // number of colums in puzzle
	FILE *filer[numberOfItems];
	char data[numberOfRows *  MAX_LEN][numberOfCols * MAX_LEN ]; // puzzle data

	
	int i = 0;
	int j = 0;
	//printf("Rows = %d and columns = %d\n",numberOfRows, numberOfCols ); //debug line

	for( i=0 ; i< numberOfItems; i++){  

		filer[i]= fopen(FilenameList[i][1],"r");

	} 		

	int num = 0;
	char c;
	int x = 0;
	int y = 0;
	for( i=0 ; i< numberOfCols  ; i++){ 

		for( j = 0; j<numberOfRows  ; j++ ){
			
			x = j * MAX_LEN;
			y = i  * MAX_LEN;
			writeToDataArray(filer[num],data,x,y);
			num++;
		}

	} 



	char *destFullPath = malloc(sizeof(char *) * MAX_LINE_LENGTH);
	strcpy(destFullPath,dirPath );
	destFullPath[strlen(destFullPath)-1] = 0;
	strcat(destFullPath,"_merged.txt");
	//printf("Output file [%s] is in current directory.\n",destFullPath); //debug line


	FILE *fileDest = fopen(destFullPath, "w"); 
	
	for( i=0 ; i< numberOfRows * MAX_LEN ; i++){  // write to dest. file

		for( j = 0; j< numberOfCols * MAX_LEN ; j++ ){

			fputc(data[i][j], fileDest);
			if(j == 89){ 
				fputs("\n",fileDest);
				//printf("\n"); //debug line
			}

		}
	
	} 

	fclose(fileDest);




	for( i=0 ; i< numberOfRows * MAX_LEN; i++){  // teller fremover

		for( j = 0; j< numberOfCols * MAX_LEN; j++ ){	
						
			printf("%c",data[i][j]);
			
			if(j == 89){

				printf("\n");
			}

		}

	} 

	printf("The same output merged to file : %s in current directory.\n",destFullPath);
	free(destFullPath);
	deallocatePArray(FilenameList, numberOfItems);

	for( i=0 ; i< numberOfItems; i++){  // close files

		fclose(filer[i]);

	} 		
	


}




void writeToDataArray(FILE *file,char data[][MAX_LEN * 3], int x, int y ){
	if(file == NULL){
		printf("is file open ??");	
	}
	char c;
	int i = 0;
	int j = 0;
	for(i = x; i< x + MAX_LEN; i++){

		for(j = y; j< y + MAX_LEN; j++){
			
			c = fgetc(file);

			if(c != EOF){	
				data[i][j] = c;	

			}
		} 
	}

}


int getNumberOfFilesInDir(const char *dirPath){ //validate folder and count files
	int count = 0;
	DIR* dir = opendir(dirPath);
	struct dirent* dirFile;

	if (dir == NULL){

		printf("Error : Failed to open directory\n");
		exit(1);

	}
	while ((dirFile = readdir(dir))){
	
		if (!strcmp (dirFile->d_name, ".") ||!strcmp (dirFile->d_name, "..") ){
			continue;
		}
		count++;
	}
	closedir(dir);
	return count;
}


void SortFileNames(char* names[][2], int length){
	int i,j;
	for (j = 0; j < length -1; j++){

		for (i = 0; i < length -1; i++){

			if (0 < strcmp(names[i][1], names[i +1][1])){

				char* temp = names[i][1];
				names[i][1] = names[i +1][1];
				names[i +1][1] = temp;
			}

			if (0 < strcmp(names[i][0], names[i +1][0])){

				char* temp2 = names[i][0];
				names[i][0] = names[i +1][0];
				names[i +1][0] = temp2;
			}



		}

	}

}


int getNumberOfcolumns(char* names[][2], int length){
	int numberOfRows = 0;
	for(int i=0 ; i< length; i++){ 
		char *rows = (char *)malloc(sizeof(char *) * 2);
		strncpy(rows, names[i][0] + 5 ,1);
		numberOfRows = atoi(rows) + 1; //starter på 0
		free(rows);
	} 

	return numberOfRows;
}

int getNumberOfRows(char* names[][2], int length){
	int numberOfCols = 0;
	for(int i=0 ; i< length; i++){  
		char *columns = (char *)malloc(sizeof(char *) * 2);
		strncpy(columns, names[i][0] + 7 ,1);
		numberOfCols = atoi(columns) + 1; //starter på 0
		free(columns);
	} 

	return numberOfCols;
}

void deallocatePArray(char* array[][2], int length){

	for(int i=0; i< length ; i++){
		
		free(array[i][0]);
		free(array[i][1]);
	}

}
