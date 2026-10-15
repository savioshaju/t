#include <stdio.h>

#define MAX 20

int n;
int epsilon[MAX][MAX];
int closure[MAX][MAX];

void findClosure(int state, int current)
{
    int i;

    closure[state][current] = 1;

    for (i = 0; i < n; i++) {
        if (epsilon[current][i] == 1 && closure[state][i] == 0) {
            findClosure(state, i);
        }
    }
}

int main(void)
{
    int i, j;

    printf("Enter number of states: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Enter a number between 1 and %d.\n", MAX);
        return 1;
    }

    printf("\nEnter epsilon transition matrix:\n");
    printf("(Enter 1 if an epsilon transition exists, otherwise 0)\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (scanf("%d", &epsilon[i][j]) != 1) {
                printf("Invalid matrix input.\n");
                return 1;
            }
        }
    }

    // Find the epsilon closure of every state.
    for (i = 0; i < n; i++) {
        findClosure(i, i);
    }

    printf("\nEpsilon Closure of all states:\n");

    for (i = 0; i < n; i++) {
        printf("E-closure(q%d) = { ", i);

        for (j = 0; j < n; j++) {
            if (closure[i][j] == 1) {
                printf("q%d ", j);
            }
        }

        printf("}\n");
    }

    return 0;
}