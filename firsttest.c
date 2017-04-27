#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
typedef struct _line{
long int tag;
long int index;
long int offset;
}line;

//convert hex address to binary
char* hexconvert(char* hexnum){
	char* binary=(char*)calloc(49,sizeof(char));
    int i = 0;
    /*
     * Extract first digit and find binary of each hex digit
     */
    for(i=0; hexnum[i]!='\0'; i++)
    {
        switch(hexnum[i])
        {
            case '0':
                strcat(binary, "0000");
                break;
            case '1':
                strcat(binary, "0001");
                break;
            case '2':
                strcat(binary, "0010");
                break;
            case '3':
                strcat(binary, "0011");
                break;
            case '4':
                strcat(binary, "0100");
                break;
            case '5':
                strcat(binary, "0101");
                break;
            case '6':
                strcat(binary, "0110");
                break;
            case '7':
                strcat(binary, "0111");
                break;
            case '8':
                strcat(binary, "1000");
                break;
            case '9':
                strcat(binary, "1001");
                break;
            case 'a':
            case 'A':
                strcat(binary, "1010");
                break;
            case 'b':
            case 'B':
                strcat(binary, "1011");
                break;
            case 'c':
            case 'C':
                strcat(binary, "1100");
                break;
            case 'd':
            case 'D':
                strcat(binary, "1101");
                break;
            case 'e':
            case 'E':
                strcat(binary, "1110");
                break;
            case 'f':
            case 'F':
                strcat(binary, "1111");
                break;
            default:
                printf("Invalid hexadecimal input.");
        }
    }
 
    return binary;
} 


//helper to substring
int substring(char* string,int length){
	char* substring=(char*)calloc(3,sizeof(char));
	int numb;
	strncpy(substring, string+5, length-6);
	int len=strlen(substring);
	substring[len] = '\0';
	numb=atoi(substring);
	return numb;
}

//helper method to check if number is a power of two
bool ispoweroftwo(int x){
    return (x != 0) && ((x & (x - 1)) == 0);
}

int main (int argc, char *argv[]){
int numsets;
char * counter;
char command;
char * address;
int cachesize;
char * assoc;
int blocksize;


char * filename =argv[4];
FILE * fp;

//make sure 4 inputs <cache size><associativity><block size><filename>
if(argc!=5){
		printf("error\n");
		return 0;
	}
int length=strlen(argv[2]);
assoc=(char*)malloc(length*sizeof(char));

cachesize=(int)argv[1];
strncpy(assoc,argv[2],length);
blocksize=(int)argv[3];

//make sure inputs are valid
	//cachesize and blocksize must be powers of 2
	if(ispoweroftwo(cachesize)==false||cachesize<=0){
		printf("Cache size is not a power of two!");
		return 0;
	}
	if(ispoweroftwo(blocksize)==false||blocksize<=0){
		printf("Block size is not a power of two!");
	}
	//if direct, 1 block per set
	if(strncmp(assoc,"direct",length)==0){
		numsets=cachesize/(1*blocksize);
		line* cachearr=(line*)malloc(numsets*sizeof(line));
	//if assoc, fully associative 1 set
	}else if(strncmp(assoc,"assoc",length)==0){
		numsets=1;
		line* cachearr=(line*)malloc(numsets*sizeof(line));
	//if other associativity n sets
	}else if(strncmp(assoc,"assoc:",length)==0){
		int associativity=substring(assoc,length);
		if(ispoweroftwo(associativity)==false||associativity<=0){
			printf("n is not a power of two.");
			return 0;
		}
		numsets=cachesize/(associativity*blocksize);
		line* cachearr=(line*)malloc(numsets*sizeof(line));
	//assoc must be "direct","assoc", or "assoc:n"
	}else{
		printf("Associativity input is not direct, assoc, or assoc:n!");
		return 0;
	}
//open file 
fp= fopen(filename, "r");
//if file is not in directory
	if(fp==NULL){
		return 0;
	}
//read file
while(fscanf(fp, "%s %c %s\n", counter, &command, address)!= EOF){

address=hexconvert(address);
printf("%s",address);
/*	if(command=='R'){
		//call read function
	}else{
		//call write function
	}*/


}

fclose(fp);

}
