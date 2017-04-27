#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "first.h"

/*convert hex address to binary*/
char* hexconvert(char* hexnum){
	char* binary=(char*)calloc(49,sizeof(char));
    int i = 0;
    /*
     * Extract first digit and find binary of each hex digit
     */
    for(i=2; hexnum[i]!='\0'; i++)
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
 	
 	if(strlen(binary)<48){
 		int zeros=48-strlen(binary);
 		char* new=(char*)calloc(49,sizeof(char));
 		int i;
 		for(i=0;i<zeros;i++){
 			strcat(new,"0");
 		}
 		strcat(new, binary);
 		binary=new;
 	}

    return binary;
} 

/*helper method to check if number is a power of two*/
bool ispoweroftwo(int x){
    return (x != 0) && ((x & (x - 1)) == 0);
}

int search(Queue* cache, long tag){
	if(cache->tag==NULL){
		return 0;
	}
	Node* front=cache->tag;
	while(front!=NULL){
		if(front->data==tag){
			return 1;	
		}
		front=front->next;
	}
	return 0;
}

void push(Queue* cache, long tag){
	Node* front;
	if(cache->tag==NULL){
		front=(Node*)malloc(sizeof(Node));
		front->data=tag;
		front->next=NULL;
		cache->tag=front;
	}else{
		front=cache->tag;
		Node* temp=(Node*)malloc(sizeof(Node));
		temp->data=tag;
		temp->next=front;
		cache->tag=temp;
	}
	cache->size++;
	return;
}

void pop(Queue* cache){
	if(cache->tag==NULL){
		return;
	}else if(cache->size==1){
		cache->tag=NULL;
		cache->size=0;
		return;
	}else{
		Node* prev=NULL;
		Node* ptr=cache->tag;
		while(ptr->next!=NULL){
			prev=ptr;
			ptr=ptr->next;
		}
		prev->next=NULL;
		free(ptr);
		cache->size--;
		return;
	}
}

int main (int argc, char *argv[]){
/*get name of file from user*/
filename =argv[4];
FILE * fp;

/*make sure there are 4 inputs <cache size><associativity><block size><filename>*/
if(argc!=5){
		printf("error\n");
		return 0;
	}
/*get length of associativity input to store in assoc and check later*/
length=strlen(argv[2]);
assoc=(char*)malloc(length*sizeof(char));
/*store user inputs*/
cachesize=atoi(argv[1]);
strncpy(assoc,argv[2],length);
blocksize=atoi(argv[3]);

/*make sure inputs are valid*/
	/*cachesize and blocksize must be powers of 2*/
	if(ispoweroftwo(cachesize)==false||cachesize<=0){
		printf("Cache size is not a power of two!");
		return 0;
	}
	if(ispoweroftwo(blocksize)==false||blocksize<=0){
		printf("Block size is not a power of two!");
	}
	/*if direct, 1 block per set*/
	if(strncmp(assoc,"direct",length)==0){
		numlines=1;
		numsets=cachesize/(numlines*blocksize);
		
	/*if assoc, fully associative 1 set*/
	}else if(strncmp(assoc,"assoc",length)==0){
		numlines=cachesize/blocksize;
		numsets=1;
		
	/*if other associativity n sets*/
	}else if(strncmp(assoc,"assoc:",6)==0){
		int index=6;
		numlines=argv[2][index]-'0';
		while(isdigit(argv[2][index+1])!=0){
			numlines=numlines*10+(argv[2][index+1]-'0');
			index++;
		}
		/*n must be power of two*/
		if(ispoweroftwo(numlines)==false||numlines<=0){
			printf("n is not a power of two.");
			return 0;
		}
		numsets=cachesize/(numlines*blocksize);
		
	/*if assoc is not "direct","assoc", or "assoc:n": return bad input*/
	}else{
		printf("Associativity input is not direct, assoc, or assoc:n!");
		return 0;
	}
	/*find how many bits for each tag, index, and offset*/
	indexbits=log2(numsets);
	offsetbits=log2(blocksize);
	tagbits=48-(indexbits+offsetbits);
	/*create caches A and B*/
	Queue* cacheA[numsets];
	Queue* cacheB[numsets];
	/*set the max size of lines per set*/
	max=numlines;

/*allocate space for the amount of lines per set*/
	for(i=0;i<numsets;i++){
		cacheA[i]=(Queue*)malloc(sizeof(Queue));
	}
	for(i=0;i<numsets;i++){
		cacheB[i]=(Queue*)malloc(sizeof(Queue));
	}

/*open file */
fp= fopen(filename, "r");
/*if file is not in directory: do nothing*/
	if(fp==NULL){
		return 0;
	}
/*read file*/
while(fscanf(fp,"%s %s %s", counter, command, address)!= EOF){
	if(strcmp(counter,"#eof")==0)
	{
		break;
	}
	/*convert address to binary*/
	binary=hexconvert(address);
	/*create temp char*'s to hold the tag bits and the index bits as a string before converting*/
	char* temptag=(char*)calloc(tagbits+1,sizeof(char));
	char* tempindex=(char*)calloc(indexbits+1,sizeof(char));
	/*get tag and index bits for chaches A and B*/
	/*A*/
	ptr=binary;
	strncat(temptag,ptr,tagbits);
	tagA=(long)strtol(temptag,NULL,2);
	ptr+=tagbits;
	strncat(tempindex,ptr,indexbits);
	indexA=(long)strtol(tempindex,NULL,2);
	/*B*/
	/*reset temps*/
	temptag[0]='\0';
	tempindex[0]='\0';
	ptr=binary;
	strncat(tempindex,ptr,indexbits);
	indexB=(long)strtol(tempindex,NULL,2);
	ptr+=indexbits;
	strncat(temptag,ptr,tagbits);
	tagB=(long)strtol(temptag,NULL,2);

	/*perform read or write*/
	if(command[0]=='R'){
		/*cacheA*/
		/*if empty*/
		if(cacheA[indexA]->size==0){
		 	push(cacheA[indexA],tagA);
		 	cachemissesA++;
		 	memreadsA++;
		}else{/*if full*/
			/*if there*/
			s=search(cacheA[indexA],tagA);
			if(s==1){
				cachehitsA++;
			}/*if not there*/
			else{
				cachemissesA++;
				memreadsA++;
				if(cacheA[indexA]->size==max){
				 	pop(cacheA[indexA]);
					push(cacheA[indexA], tagA);
				}else{
					push(cacheA[indexA], tagA);
				}

			}
		}
		/*cacheB*/
		/*if empty*/
		if(cacheB[indexB]->size==0){
		 	push(cacheB[indexB],tagB);
		 	cachemissesB++;
		 	memreadsB++;
		}else{/*if full*/
			/*if there*/
			s=search(cacheB[indexB],tagB);
			if(s==1){
				cachehitsB++;
			}/*if not there*/
			else{
				cachemissesB++;
				memreadsB++;
				if(cacheB[indexB]->size==max){
				 	pop(cacheB[indexB]);
					push(cacheB[indexB], tagB);
				}else{
					push(cacheB[indexB], tagB);
				}

			}
		}
	}else{
		/*cacheA*/
		if(cacheA[indexA]->size==0){
			cachemissesA++;
			memreadsA++;
			memwritesA++;
			push(cacheA[indexA], tagA);
		}else{
			s=search(cacheA[indexA],tagA);
			if(s==1){
				cachehitsA++;
				memwritesA++;
			}else{
				cachemissesA++;
				memreadsA++;
				memwritesA++;
				if(cacheA[indexA]->size == max){
					pop(cacheA[indexA]);
					push(cacheA[indexA], tagA);
				}else{
					push(cacheA[indexA], tagA);
				}

			}
		}
		/*cacheB*/
		if(cacheB[indexB]->size==0){
			cachemissesB++;
			memreadsB++;
			memwritesB++;
			push(cacheB[indexB], tagB);
		}else{
			s=search(cacheB[indexB],tagB);
			if(s==1){
				cachehitsB++;
				memwritesB++;
			}else{
				cachemissesB++;
				memreadsB++;
				memwritesB++;
				if(cacheB[indexB]->size == max){
					pop(cacheB[indexB]);
					push(cacheB[indexB], tagB);
				}else{
					push(cacheB[indexB], tagB);
				}

			}
		}
	}
}
fclose(fp);
/*output reads, writes, hits, and misses for A and B*/
printf("cache A\n");
printf("Memory reads: %d\n", memreadsA);
printf("Memory writes: %d\n", memwritesA);
printf("Cache hits: %d\n", cachehitsA);
printf("Cache misses: %d\n", cachemissesA);
printf("cache B\n");
printf("Memory reads: %d\n", memreadsB);
printf("Memory writes: %d\n", memwritesB);
printf("Cache hits: %d\n", cachehitsB);
printf("Cache misses: %d\n", cachemissesB);
return 0;

}
