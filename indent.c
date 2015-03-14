
#include <stdio.h>
int remove_white_space(int ch, int prevch){
	if(ch==' ' && prevch== ' '){
		return 0;
	}else if(ch==' ' && (prevch==';'||prevch==')'||prevch=='}'||prevch=='{'||prevch=='('||prevch=='\n') ){
		return 0;
	}else if(ch=='\n' || ch=='\t'){
		if(prevch != ' ' &&  prevch!=';' && prevch!='{' && prevch!='}'&& prevch!='\n' && prevch!='\t' )
			putchar(' ');
		return 0;
	}else
		return 1;
}
int main(void){
	int brackets=0, level=-1,headerline=0, ch ,preprevch = -1, prevch = -1, noSquotes = 0, noDquotes = 0, i, we_have_checked_again=0 ;
	ch = getchar();
	while(ch != EOF){
		if(ch == '#' && noSquotes%2==0 &&  noDquotes%2==0)headerline=1;
		if(!headerline){ /*den eimaste se  header line*/
			if(noSquotes%2==0 &&  noDquotes%2==0){ /*den eimaste mesa se mona H dipla eisagogika*/
				if( remove_white_space(ch, prevch)){ /*den exoyme xaraktira pou theloume na paralipsome, opos /n H /t H to keno*/
					if(prevch=='\n' && ch!='{'){ /*prosthetoume tabs stin arxi tis grammis analoga me ta posa { H }  exoyme vrei*/
						if(ch=='}')level--;
						for(i=0;i<=level;i++) putchar('\t');
					}
					if(ch=='(')
						brackets++;
					else if (ch==')')
						brackets--;
					if(ch=='{'){
						if(prevch!='\n')
							putchar('\n');
						for(i=0;i<=level;i++)
                              				 putchar('\t');
						putchar(ch);
						putchar('\n');
						prevch = ch;
						ch='\n';
						level++;/*gia na kseroume posa tabs tha valoume prin tin kathe grammi tou block*/
					}else if(ch=='}'){
						putchar(ch);
						putchar('\n');
						prevch = ch;
                        			ch='\n';
					}else if( ch==';'  && brackets==0){/*eimaste sigouroi oti den eimaste mesa se (), px se ena for*/
						putchar(ch);
						putchar('\n');
						prevch = ch;
                        			ch='\n';
					}else{
						putchar(ch);
					}
				}else{
					if(prevch=='\'' || prevch =='\"')we_have_checked_again=1;/*gia na min ksanametrisoyme ta eisagogika parakatw*/
					ch=prevch;
				}
			}else{
				if( ch!= '\n'){ /*an eimaste mesa se eisagogika metaferoume ton kathe xaraktira kai fernoume tin entoli stin idia grammi*/
					putchar(ch);
				}
			}
			if(ch == '\''  && (prevch!= '\\' || (prevch=='\\' && preprevch == '\\'))  &&  noDquotes%2==0 && !we_have_checked_again ){ /*metrame ta ' pou exoume vrei*/ 
				noSquotes++;
			}
			if(ch == '\"' && (prevch!= '\\' || (prevch=='\\' && preprevch == '\\'))  && noSquotes%2==0  && !we_have_checked_again ){/*metrame ta " pou exoume vrei */
				noDquotes++;
			}
			we_have_checked_again = 0;
		}else{
			putchar(ch);
		}
		if(headerline && ch=='\n' && noSquotes%2==0 && noDquotes%2==0){/*edo teleionei mia header line*/
			headerline=0;
		}
		preprevch = prevch;
		prevch = ch;
		ch = getchar();
	}
	return 0 ;
}
 
