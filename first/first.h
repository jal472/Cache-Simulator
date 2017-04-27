#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct Node{
	long data;
	struct Node* next;
}Node;

typedef struct Queue{
	Node* tag;
	int size;
}Queue;

char* hexconvert(char* hexnum);
bool ispoweroftwo(int x);
int search(Queue* cache, long tag);
void push(Queue* cache, long tag);
void pop(Queue* cache);

int numsets;
char counter[15];
char command[5];
char address[15];
int cachesize;
char * assoc;
int blocksize;
int numlines;
char* binary;
long tagA;
long tagB;
long indexA;
long indexB;
char* filename;
FILE * fp;
int length;
int indexbits;
int offsetbits;
int tagbits;
int max;
char *ptr;
int i;
int memreadsA;
int memreadsB;
int memwritesA;
int memwritesB;
int cachehitsA;
int cachehitsB;
int cachemissesA;
int cachemissesB;
int s;