#include<stdio.h>
#include<string.h>
#include<ctype.h>
int n ;
char prod[100][100];

void adds(char c,char result[]){
    int i = 0 ;
    for(i = 0 ; result[i]!='\0' ; i 
        
        ++){
        if(result[i] == c )
            return;
    }
    result[i]= c;
    result[i+1] = '\0';
}

void FIRST(char c,char result[]){
    if(!isupper(c)){
        adds(c,result);
        return;
    }

    for(int i = 0; i < n ; i ++){
        if(prod[i][0]==c){
            int j =2;
            int e =1;
            if(prod[i][j]=='#'){
                adds('#',result);
                continue;
            }
            while(prod[i][j]!='\0'){
                char temp[100] = "";
                FIRST(prod[i][j],temp);

                int epsi = 0;

                for(int k = 0 ; temp[k]!='\0';k++){
                    if(temp[k]=='#'){
                        epsi = 1;
                    }
                    else{
                        adds(temp[k],result);
                    }
                }
                if(!epsi){
                    e=0;
                    break;
                }
                j++;
            }
            if(e){
                adds('#',result);
            }
        }
    }
}


void FOLLOW(char c,char result[]){
    if(c==prod[0][0]){
        adds('$',result);
    }
    for(int i = 0; i<n ; i++){
        for(int  j = 2 ; prod[i][j] != '\0' ;j++){
            if(prod[i][j] == c){
                int k  = j+1;
                int epsi = 1;

                while(prod[i][k]!='\0' && epsi){
                    char temp[100]="";


                    FIRST(prod[i][k],temp);
                    epsi =0;
                    for(int s = 0; temp[s]!='\0';s++){
                        if(temp[s]=='#'){
                            epsi = 1;
                        }
                        else{
                            adds(temp[s],result);
                        }
                    }
                    k++;
                }
                if(epsi && prod[i][0]!=c){
                    char temp[100]="";

                    FOLLOW(prod[i][0],temp);
                
                    for(int s = 0; temp[s]!='\0';s++){
                        
                            adds(temp[s],result);
                    }
                }
            }
        }
    }
}

void main(){

    char test[100]="";
    printf("Enter the number of prduction rule : ");
    scanf("%d",&n);
    printf("Enter the perduction rules :\n");
    for(int i = 0 ; i < n ; i++){
        scanf(" %s",prod[i]);
        adds(prod[i][0],test);
    }

    char temp[100]="";
    for(int i = 0 ; test[i]!='\0'; i++){
        temp[0]='\0';
        FIRST(test[i],temp);

        printf("FIRST(%c) : {",test[i]);
        for(int j = 0 ; temp[j]!='\0' ; j++){
            printf("%c",temp[j]);
        }
        printf("}\n");
    }

    for(int i = 0 ; test[i]!='\0'; i++){

        temp[0]='\0';
        FOLLOW(test[i],temp);

        printf("FOLLOW(%c) : {",test[i]);
        for(int j = 0 ; temp[j]!='\0' ; j++){
            printf("%c",temp[j]);
        }
        printf("}\n");
    }
}