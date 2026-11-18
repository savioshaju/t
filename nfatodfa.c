#include<stdio.h>

int nfa[100][100][100];

int dfa[100][100];
int dfastates[100][100];
int dfacount[100];
int totaldfa =0;

char symbol[100];

int contains(int set[],int len,int value){
    for(int i = 0 ; i <len;i++){
        if(set[i]==value)
            return 1;
    }
    return 0;
}

int sameset(int a[],int alen,int b[],int blen){
    if(alen!=blen)
        return 0;
    for(int i = 0 ; i < alen ; i++){
        if(!contains(b,blen,a[i]))
            return 0;
    }
    return 1;
}

int findDFA(int set[],int len){
    for(int i = 0 ; i < totaldfa; i++){
        if(sameset(dfastates[i],dfacount[i],set,len))
            return i;
    }
    return -1;
}

void printset(int set[],int len){
    if(len==0){
        printf("{}");
        return;
    }

    printf("{");
    for(int i = 0 ; i < len ; i++){
        if(i>0)
        printf(",");
        printf("q%d",set[i]);
    }
    printf("}");
}

void sort(int set[],int len){
    for(int i = 0 ; i <len-1; i++){
        for(int j= 0 ; j <len-i-1 ; j++){
            if(set[j]>set[j+1]){
                int a = set[j];
                set[j]=set[j+1];
                set[j+1] = a;
            }
        }
    }
}
void main(){
    int n,m;
    printf("Enter the number of states : ");
    scanf("%d",&n);
    printf("Enter the number of input symbols : ");
    scanf("%d",&m);

    printf("Enter the input symbols : ");
    for(int i = 0; i<m;i++){
        scanf(" %c",&symbol[i]);
    }



    for(int i = 0 ; i < n ; i++){
        for(int j =0 ; j < m ; j++){
            printf("number of transition of delta(q%d,%c)",i,symbol[j]);

            int c;
            scanf("%d",&c);
            nfa[i][j][0]=c;
            printf("Enter transition of delta(q%d,%c)\n",i,symbol[j]);
            for(int k = 1 ; k <=c;k++){
                scanf("%d",&nfa[i][j][k]);
            }
        }
    }

    dfastates[0][0]=0;
    dfacount[0]=1;
    totaldfa=1;
    int current =0;
    while(current<totaldfa){
        for(int j = 0 ;j < m ; j++){
            int newset[10];
            int newcount =0;
            for(int i = 0 ; i < dfacount[current] ; i++){
                int state = dfastates[current][i];

                int transc = nfa[state][j][0];
                for(int k =1 ; k <= transc ; k++){
                    int transs = nfa[state][j][k];
                    if(!contains(newset,newcount,transs)){
                        newset[newcount++]=transs;

                    }
                }
            }

            sort(newset,newcount);
            int index =findDFA(newset,newcount);
            if(index == -1){
                index =  totaldfa;

                for(int k = 0 ;k < newcount;k++){
                    dfastates[totaldfa][k]=newset[k];
                }
                dfacount[totaldfa] = newcount;
                totaldfa++;
            }
            dfa[current][j]=index;

        }
        current++;
    }

    printf("DFA States \t");
    for(int i = 0 ; i < m ; i++){
        printf(" %c\t\t",symbol[i]);
    }
    printf("\n");
    for(int i = 0;i <totaldfa; i++){
        printset(dfastates[i],dfacount[i]);
        printf("\t\t");
        for(int j = 0 ; j< m;j++){
            int s =dfa[i][j];
            printset(dfastates[s],dfacount[s]);
            printf("\t\t");

        }
        printf("\n");
    }

}