#include <stdio.h>

#define MAX_STATES 10
#define MAX_SYMBOLS 10
#define MAX_DFA_STATES (1 << MAX_STATES)

int n, symbols;
int nfa[MAX_STATES][MAX_STATES][MAX_SYMBOLS];
int dfa[MAX_DFA_STATES][MAX_SYMBOLS];
int dfaStates[MAX_DFA_STATES][MAX_STATES];
int dfaCount = 0;

int isSame(const int a[], const int b[])
{
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

int findState(const int state[])
{
    for (int i = 0; i < dfaCount; i++) {
        if (isSame(dfaStates[i], state)) {
            return i;
        }
    }
    return -1;
}

void printState(const int state[])
{
    int empty = 1;

    printf("{ ");
    for (int i = 0; i < n; i++) {
        if (state[i]) {
            printf("q%d ", i);
            empty = 0;
        }
    }

    if (empty) {
        printf("Dead ");
    }
    printf("}");
}

int main(void)
{
    printf("Enter number of states: ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_STATES) {
        printf("Number of states must be between 1 and %d.\n", MAX_STATES);
        return 1;
    }

    printf("Enter number of input symbols: ");
    if (scanf("%d", &symbols) != 1 ||
        symbols < 1 || symbols > MAX_SYMBOLS) {
        printf("Number of symbols must be between 1 and %d.\n", MAX_SYMBOLS);
        return 1;
    }

    printf("\nEnter the NFA transition matrix for each symbol.\n");
    printf("Enter 1 if a transition exists, otherwise 0.\n");

    for (int k = 0; k < symbols; k++) {
        printf("\nFor symbol %c:\n", 'a' + k);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (scanf("%d", &nfa[i][j][k]) != 1 ||
                    (nfa[i][j][k] != 0 && nfa[i][j][k] != 1)) {
                    printf("Enter only 0 or 1 in the transition matrix.\n");
                    return 1;
                }
            }
        }
    }

    /* The initial DFA state is the set {q0}. */
    for (int i = 0; i < n; i++) {
        dfaStates[0][i] = 0;
    }
    dfaStates[0][0] = 1;
    dfaCount = 1;

    /* Build each reachable DFA state and its transitions. */
    for (int state = 0; state < dfaCount; state++) {
        for (int symbol = 0; symbol < symbols; symbol++) {
            int next[MAX_STATES] = {0};

            for (int q = 0; q < n; q++) {
                if (dfaStates[state][q]) {
                    for (int destination = 0; destination < n; destination++) {
                        if (nfa[q][destination][symbol]) {
                            next[destination] = 1;
                        }
                    }
                }
            }

            int found = findState(next);

            if (found == -1) {
                if (dfaCount >= MAX_DFA_STATES) {
                    printf("Too many DFA states.\n");
                    return 1;
                }

                found = dfaCount;
                for (int i = 0; i < n; i++) {
                    dfaStates[dfaCount][i] = next[i];
                }
                dfaCount++;
            }

            dfa[state][symbol] = found;
        }
    }

    printf("\nDFA Transition Table:\n\n");
    printf("DFA State\t");

    for (int symbol = 0; symbol < symbols; symbol++) {
        printf("%c\t\t", 'a' + symbol);
    }
    printf("\n");

    for (int state = 0; state < dfaCount; state++) {
        printf("D%d = ", state);
        printState(dfaStates[state]);

        for (int symbol = 0; symbol < symbols; symbol++) {
            printf("\tD%d", dfa[state][symbol]);
        }
        printf("\n");
    }

    return 0;
}