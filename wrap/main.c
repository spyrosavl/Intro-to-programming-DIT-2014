#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "wrap.h"
int no_more_memory(void){
	fprintf(stderr, "No more memory");
        return 2;
}
int main(int argc, char *argv[]){
	int ch, w, cost=0, buffer_size;
	char **words;
	char *buffer;
	char * allages;
	long i,n=0, words_no=0;
	if(argc == 2)w=atoi(argv[1]);
	else w=80;
	ch = getchar();
	int  words_size = 5 ;
	if((words = malloc(words_size*sizeof(char * )))==NULL )no_more_memory();
	buffer_size=5;
	if((buffer  = malloc((buffer_size+1)*sizeof(char)))==NULL)no_more_memory();//+1 is for \0
	while(ch!=EOF){
		if(words_no==words_size ){/*increase words array size*/
			words_size = words_size + 5 ;
			if((words = realloc(words, words_size*sizeof(char *))) == NULL)no_more_memory();
		}
		n = 0 ;
		while(ch!=EOF && !isspace(ch) ){
			if(n==w){
				fprintf(stderr, "\nToo big word! \n");
				return 3;
			}
			if(n==buffer_size){
				buffer_size = buffer_size * 2 ;
				if((buffer = realloc(buffer, buffer_size+1))==NULL)no_more_memory();
			}
			*(buffer  + n) = ch;
			n++;
			ch = getchar();
		}
		if(!isspace(ch) || n>0){/*copy from buffer to main array*/
			*(buffer + n)='\0';
			if((*(words + words_no) = malloc((n+1)*sizeof(char ))) == NULL )no_more_memory();
			strcpy( *(words + words_no), buffer );
			words_no++;
		}
		ch = getchar();
	}
	if((allages = malloc(words_no*sizeof(char)))==NULL)no_more_memory();/*here we would save line changes*/
	for(i=0;i<words_no;i++)allages[i]=0;
	
	cost = wrap( words,words_no, w, allages);/*wrap would return wrap cost and ALSO fill allages array*/
	for(i=0;i<words_no;i++){/*here we print the text formated*/
		if(allages[i]==0){
			printf("%s ", words[i]);
		}else{
			printf("\n%s ", words[i]);
		}
	}
	printf("\n");
	fprintf(stderr, "words=%lu\nwidth=%d\ncost=%d\n",words_no,w,cost);
	
	for(i=0;i<words_no;i++)
		free(words[i]);
	free(words);
	free(allages);
	free(buffer);
	return 0;
}

