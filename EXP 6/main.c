#include <stdio.h>

#define MAX 20

int n;
int symbols;

int transition[MAX][MAX][MAX];
int epsilon[MAX][MAX];
int closure[MAX][MAX];
int newTransition[MAX][MAX][MAX];

void findClosure(int state, int current)
{
    closure[state][current] = 1;

    for (int i = 0; i < n; i++) {
        if (epsilon[current][i] == 1 && closure[state][i] == 0) {
            findClosure(state, i);
        }
    }
}

void calculateClosures(void)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            closure[i][j] = 0;
        }

        findClosure(i, i);
    }
}

void convertNFA(void)
{
    for (int state = 0; state < n; state++) {
        for (int symbol = 0; symbol < symbols; symbol++) {
            for (int p = 0; p < n; p++) {
                if (closure[state][p] == 1) {
                    for (int q = 0; q < n; q++) {
                        if (transition[symbol][p][q] == 1) {
                            for (int r = 0; r < n; r++) {
                                if (closure[q][r] == 1) {
                                    newTransition[symbol][state][r] = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void displayClosures(void)
{
    printf("\nEpsilon Closures:\n");

    for (int i = 0; i < n; i++) {
        printf("Closure(q%d) = { ", i);

        for (int j = 0; j < n; j++) {
            if (closure[i][j] == 1) {
                printf("q%d ", j);
            }
        }

        printf("}\n");
    }
}

void displayResult(void)
{
    for (int symbol = 0; symbol < symbols; symbol++) {
        printf("\nTransition matrix for symbol %c:\n", 'a' + symbol);

        printf("    ");
        for (int j = 0; j < n; j++) {
            printf("q%d ", j);
        }
        printf("\n");

        for (int i = 0; i < n; i++) {
            printf("q%d  ", i);

            for (int j = 0; j < n; j++) {
                printf("%d  ", newTransition[symbol][i][j]);
            }

            printf("\n");
        }
    }
}

int main(void)
{
    printf("Enter number of states: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX) {
        printf("Number of states must be between 1 and %d.\n", MAX);
        return 1;
    }

    printf("Enter number of input symbols: ");
    if (scanf("%d", &symbols) != 1 || symbols < 1 || symbols > MAX) {
        printf("Number of symbols must be between 1 and %d.\n", MAX);
        return 1;
    }

    for (int s = 0; s < symbols; s++) {
        printf("\nEnter transition matrix for symbol %c:\n", 'a' + s);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (scanf("%d", &transition[s][i][j]) != 1) {
                    printf("Invalid transition matrix input.\n");
                    return 1;
                }
            }
        }
    }

    printf("\nEnter epsilon transition matrix:\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &epsilon[i][j]) != 1) {
                printf("Invalid epsilon transition matrix input.\n");
                return 1;
            }
        }
    }

    calculateClosures();
    displayClosures();

    convertNFA();

    printf("\nNFA without epsilon transitions:\n");
    displayResult();

    return 0;
}