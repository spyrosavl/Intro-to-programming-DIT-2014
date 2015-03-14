#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int c(long i, long j , char ** words, long words_no, int w){/*c is the cost to get words ito j into one line*/
	int k, wij=0, x;
	for(k=i-1; k<j;k++){
		x=0;
		while(words[k][x] != '\0'){
			wij++;
			x++;
		}
		wij++;
		if(wij-1>w)break;
	}
	if(wij-1>w)return -1;/* we cant put all these words in a single line*/
	if(j==words_no)return 0;/* its the last line*/
	return (w - wij + 1)*(w - wij +  1);
}
int f(long j, char ** words, long words_no, int w, int * min_i, int **costs, int **line_costs){/*f is the function which you find the minimum cost for a text of j words*/
	int i=0, min=-1, k, temp, cmin;
	int temp_min_i ;
	if(j==0)return 0;
	if(costs[j-1][0]!=-1){/*we already have computed that*/
		*min_i=costs[j][1];
		return costs[j][0];
	}

	for(i=1;i<=j;i++){/*epanaliptika vriskoyme to f(j)*/
		min = -1;
		for (k = i; k >=1 ; k--)/*gia kathe i koitame kathe k apo 1<=k<=i gia na vroume to minimum*/
		{	
			cmin = line_costs[k-1][i-1];/*to kostos gia na valoume se mia grammi tis lekseis apo k mexri i*/
			if(cmin==-1)break;/*den xorene alles lekseis se ayti ti grammi*/
			if(i!=words_no)cmin =(w-cmin)*(w-cmin);
			if(cmin>=min && min!=-1)continue;
			cmin = cmin + costs[k-1][0];
			if( cmin < min || min==-1){
				min=cmin;
				temp_min_i=k;
			}
		}
		costs[i][0] = min;/*minimum*/
		costs[i][1] = temp_min_i;/*H thesi toy minimum*/
	}




	*min_i = temp_min_i;
	return min;	
}
int wrap(char ** words,long  words_no,int  w, char * allages){
	int i, j , wij,x, k, cmin, temp_min_i, min;
	int cost=0, min_i;
	
	int **costs = malloc((words_no+1)*sizeof(int * ));
	/*cost  is the array with the cost to keep the cost to format the first J(costs[j][0]) words and costs[j][1] is the position of the min i */
	int **line_costs = malloc(words_no*sizeof(int * ));
	/*line costs is the array with the costs to put words from i to j in a single line (line_costs[i][j])*/
	for(i=0;i<words_no;i++)line_costs[i] = malloc(words_no*sizeof(int));
	/*fill the line_costs array below*/
	for(i=words_no-1;i>=0;i--){
			wij = 0;
			for(j=i;j>=0;j--){
				wij = wij + strlen(words[j])+1;
				if(wij-1>w){/*we cant put so many words in a line*/
					line_costs[j][i] = -1;
					break;

				}
	            		else if(i+1 == words_no)/*it is the last line*/
					line_costs[j][i] = 0;
				else
					line_costs[j][i] = wij-1;
			}

	}

	/*-------------------------------------------------------*/
	for(i=0;i<words_no+1;i++){
		costs[i] = malloc(2*sizeof(int ));
		costs[i][0]=-1;
	}
	costs[0][0] = 0; 	
	i = words_no;/*we first compute f(j) , j=words count*/
	while(i>1){
		if(i==words_no)/*we save the result*/
			cost=f(i, words, words_no, w, &min_i, costs, line_costs);
		else /*else we just call the f*/ {
			f(i, words, words_no, w, &min_i, costs, line_costs);
		}
		i = min_i - 1 ;/*we put the words i(the i which f had found the min cost) to j in a line and we go to find the previous line*/
		allages[i] = 1;/*if allages[i]==1 , a \n would be printed before the i word*/
		
	}
	for(i=0;i<words_no;i++)
		free(line_costs[i]);
	free(line_costs);
	for(i=0;i<=words_no;i++)
		free(costs[i]);
	free(costs);
	return cost;
}
