#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int c(long i, long j , char ** words, long words_no, int w){/*c is the cost to get words ito j into one line*/
	int k, wij=0;
	for(k=i-1; k<j;k++){
                wij = wij + strlen(words[k]) + 1;
		if(wij-1>w)break;
	}
	if(wij-1>w)return -1;/* we cant put all these words in a single line*/
	if(j==words_no)return 0;/* its the last line*/
	return (w - wij + 1)*(w - wij +  1);
}
int f(long j, char ** words, long words_no, int w, int * min_i){/*f is the function which you find the minimum cost for a text of j words*/
	int i=0, min=-1, temp;
	int temp_min_i ;
	if(j==0)return 0;
	for(i=1;i<=j;i++){
		temp = c(i, j, words, words_no, w);/*we split f(i-1)+cij in two, first temp=cij*/
		if(temp == -1 ) continue;/*if we can't put words from i to j  in a single line continue*/
		if(temp >= min && min!=-1)continue;/*if already temp=cij >= min then cij+f(i-1) would also be*/
		temp = temp + f(i-1, words, words_no, w, &temp_min_i);/*here we add to temp f(i-1) and we finaly have f(j)=f(i-1)+cij*/
		if( temp  < min || min  == -1 ){/*check for the minimum*/
			min = temp;
			*min_i = i;/*the i of the minimum cost*/
		}
		
		
	}
	return min;	
}
int wrap(char ** words,long  words_no,int  w, char * allages){
	int i ;
	int cost=0, min_i;
	i = words_no;/*we first compute f(j) , j=words count*/
	while(i>1){
		if(i==words_no)/*we save the result*/
			cost=f(i, words, words_no, w, &min_i);
		else /*else we just call the f*/
			f(i, words, words_no, w, &min_i);
		i = min_i - 1 ;/*we put the words i(the i which f had found the min cost) to j in a line and we go to find the previous line*/
		allages[i] = 1;/*if allages[i]==1 , a \n would be printed before the i word*/
		
	}
	return cost;
}
