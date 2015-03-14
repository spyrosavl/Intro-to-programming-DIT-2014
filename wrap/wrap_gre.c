#include <stdio.h>
#include <ctype.h>
#include <string.h>
int wrap(char** words, long words_no, int w, char * allages){
	long i ,cost = 0, line_chars=0;

	for(i=0;i<words_no;i++){
		if( (strlen(words[i]) + line_chars <= w && line_chars==0 ) || (strlen(words[i]) + line_chars + 1 <= w )  ){
		/*if next word will not exceed max line width and it is the first word in this line so we don't need to add 1 space
		  or if  next word + 1(one space char) will not exceed max line width */
			if(line_chars != 0){//add the space char
				line_chars++;
			}

			line_chars += strlen(words[i]);/*add the word width*/
		}else{
		/*else we need to change line*/	
			cost = cost + (w-line_chars)*(w-line_chars);/*cost of the previous line added to the sum */
			allages[i]=1;/*we need to put a \n here at the output(in this array i kee the points where i will put \n in the output)*/
			line_chars = strlen(words[i]);/*it is the first word , so line width = word width*/
		}
	}
	return cost;
}
