
/*file protoi.c*/
#include <stdio.h>
#include <time.h>
#define MIN_NUM 1990000001
#define MAX_NUM 2000000000
#define MAXTRIES 10
int main(void){
    long long i, j,min_num, a;
    int found_divisor  ;
    long tries, counter = 0, exponent ;
    double  stime, ftime;
    long long  result, base  ;
    printf("Searching for primes between %i and %i \n", MIN_NUM, MAX_NUM );
    printf("Trying deterministic alorithm \n");
    stime   = ((double) clock())/CLOCKS_PER_SEC;       /* Get CPU time */
    

    if(MIN_NUM <= 2 ){ /* counter=1 gia na symplerilavoume to 2 san proto */
        counter++;
    }
    if(MIN_NUM<=3){
    counter++;
    min_num = 5 ;
    }
    else if (MIN_NUM%2==0){  /* ksekiname apo artio */
        min_num = MIN_NUM + 1;
    }else{min_num = MIN_NUM;}
    
    for(i=min_num;i<=MAX_NUM; i=i+2){ //pame ana 2 oste na elenxoume peritous
    
        found_divisor = 0 ;
        j = 11; //kseksiname apo 11 giati elenxoyme prin mpoyme stin epanalipsi ta pollaplasia tou 3,5,7.
        if( ( i%3!=0 && i%5!=0 &&  i%7!=0) || ( i==5 ||  i==7)  ){ 
            do{
                if(i%j==0 && i!=j || i%(j+2)==0 && i!=(j+2)  ){  //elenxoyme an to j H to j+2 diairoyn ton arithmo giati ksekinontas apo to 11 oloi oi pithanoi protoi einai ana 6 to n H to n+2
                    found_divisor =1;
                    break;
                }else{
                    j =  j + 6;  //allios pame + 6
                }        
            }while( j*j <= i  );   
            if(!found_divisor){  //an den vroume diaireti exoyme vrei proto arithmo
                counter ++;
            }           
            
        }
        
    }
    
    ftime =  ((double) clock())/CLOCKS_PER_SEC;       /* Get CPU time */
    printf("Deterministic algorithm: found %ld primes \n", counter);
    printf("in %fl secs \n", ftime-stime);
    
    /***********FERMAT ALGORITHM********************************* */
    printf("Trying Fermat test \n");
    srand(time(NULL));
    for(tries=1;tries <= MAXTRIES; tries++){ //tries
        stime =  ((double) clock())/CLOCKS_PER_SEC;
        
        counter = 0;
        if(MIN_NUM <= 2 ){
            counter = 1;
        }
        for(i=min_num;i<=MAX_NUM; i++){  //current number
            
            found_divisor = 0 ;
            j=0;
            do{
                j++;
                a = rand()%(i-1)+1;
                
                base = a; //basi
                base = base % i;  
                exponent = i-1; //ekthetis
                result = 1;  
                while(exponent >0){   /*modular exponentiation*/
                    if(exponent % 2 == 1){ //an artios ekthetis  diladi  2n+1
                        result = (result* base)% (i); // tote  to teliko result tha einai  result = (result * base) mod i
                    }
                    exponent = exponent >> 1; //kanoume  div  2 ton ektheti 
                    base = (base*base) % (i);//kanoyme  x = x^2 mod m
                }
                if(result != 1){ 
                    found_divisor = 1;
                }
                
                
            }while(j<tries && !found_divisor);
            if(!found_divisor){
                counter++;
            }
            
        }
        
        ftime =  ((double) clock())/CLOCKS_PER_SEC;
        printf("Probabilistic algorithm: Found %ld  primes in %fl  secs , (tries = %ld) \n", counter,  ftime-stime, tries);
    }
        return 0;
}
 
