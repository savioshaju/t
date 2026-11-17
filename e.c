#include <stdio.h>

int n,epsilon[20][20],closure[20][20];

void findClosure(int state, int current){
    closure[state][current] = 1;
    for(int i = 0 ; i < n ; i++){
        if(epsilon[current][i]==1 &&  closure[state][i]==0){
            findClosure(state, i);
        }
    }
}

void main(){

    printf("Enter the number of states : ");
    scanf("%d",&n);


    printf("\nEnter the Transition Matrix \n");
    
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            scanf("%d", &epsilon[i][j]);
        }
    }

    for(int i = 0 ; i < n ; i++){
        findClosure(i,i);
    }

    for(int i  = 0 ; i < n ; i ++){
        printf("\nE Closure of q%d : { ",i);
        for(int j = 0 ; j  < n ; j ++){
            if(closure[i][j] ==1){
                printf("q%d, ",j);
            }
        }
        printf("}");
    }
}