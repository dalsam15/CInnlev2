#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 30



void readfilesInDirs(const char *dirPath);
void SortFileNames(char* names[][2], int length);
int getNumberOfFilesInDir(const char *dirPath);
int getNumberOfRows(char* names[][2], int length);
int getNumberOfcolumns(char* names[][2], int length);
void writeToDataArray(FILE *file,char data[][MAX_LEN * 3], int x, int y );
void deallocatePArray(char* array[][2], int length);

