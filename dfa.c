#include <stdio.h>

int nfa[20][20][20];
char symbol[10];
int dfa[20][20];
int dfastates[20][20];
int dfacount[10];
int totaldfa =0;
int n, m ;


int contains(int set[],int count,int state){
    for(int i = 0 ; i < count;i++){
        if(set[i]==state)
            return 1;
    }
    return 0 ;

}

void sortset(int set[],int n){
    for(int i = 0; i < n-1 ; i++){
        for(int j = 0 ; j < n-i-1; j++){
            if(set[j]>set[j+1]){
                int temp = set[j];
                set[j]=set[j+1];
                set[j+1]= temp;
            }
        }
    }
}

int sameset(int a[],int ac,int b[],int bc){
    if (ac != bc)
        return 0;

    for(int i = 0; i <ac ; i++){
        if(!contains(b,bc,a[i]))
            return 0;
    }

    return 1;
}

int findDFA(int set[],int count){
    for(int i =0;i <totaldfa;i++ ){
        if(sameset(dfastates[i],dfacount[i],set,count))
            return i;
    }
    return -1;
}

void printSet(int set[], int count){
    if (count == 0){
        printf("{}");
        return;
    }

    printf("{");

    for (int i = 0; i < count; i++){
        if (i > 0)
            printf(",");

        printf("q%d", set[i]);
    }

    printf("}");
}

void main(){

    printf("Enter the number of symbols : ");
    scanf("%d",&m);
    printf("Enter the number of states : ");
    scanf("%d",&n);

    printf("Enter the input symbols :");
    for (int i =0 ; i < m ; i++)
        scanf(" %c",&symbol[i]);

    printf("Enter the NFA transitions : \n");
    for(int i = 0; i < n ; i++){
        for (int j =0 ; j < m ; j++){
            printf("Enter the number of trasition for delta(q%d,%c)",i, symbol[j]);
            
            int c;
            scanf("%d",&c);


            nfa[i][j][0] = c;
            for(int k  =1; k <= c ; k ++){
                scanf("%d", &nfa[i][j][k]);
            }
        }
    }
    dfastates[0][0] =0;
    dfacount[0]=1;
    totaldfa =1;

    int current = 0;

    while ( current < totaldfa){
        for(int j = 0 ; j < m ;j++){
            int newset[20];
            int newcount =0;
            for(int i = 0 ; i < dfacount[current] ; i++){
                int state = dfastates[current][i];

                int transitioncount = nfa[state][j][0];

                for(int k = 1 ; k <= transitioncount ; k++){
                    if(!contains(newset,newcount,nfa[state][j][k]))
                        newset[newcount++] = nfa[state][j][k];
                }
            }

            sortset(newset,newcount);
            int index = findDFA(newset,newcount);

            if(index == -1){
                index = totaldfa;
                for(int k = 0 ; k < newcount ; k++){
                    dfastates[totaldfa][k] = newset[k];
                }
                dfacount[totaldfa]=newcount;
                totaldfa++;
            }
            dfa[current][j]=index;
        }
        current++;
    }

    printf("\nEquivalent DFA Transition Table:\n\n");

    printf("DFA State\t");
    for (int i = 0; i < m; i++)
        printf("%c\t\t", symbol[i]);

    printf("\n");

    for (int i = 0; i < totaldfa; i++){
        printSet(dfastates[i], dfacount[i]);
        printf("\t\t");

        for (int j = 0; j < m; j++){
            int next = dfa[i][j];

            printSet(dfastates[next], dfacount[next]);
            printf("\t\t");
        }
        printf("\n");
    }

}