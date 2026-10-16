
#include <stdio.h>

int n, symbols;
int nfa[10][10][10];
int dfaStates[100][10];
int dfaTransition[100][10];
int dfaCount = 0;

int isSame(int a[], int b[])
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (a[i] != b[i])
            return 0;
    }

    return 1;
}

int findState(int state[])
{
    int i;

    for (i = 0; i < dfaCount; i++)
    {
        if (isSame(dfaStates[i], state))
            return i;
    }

    return -1;
}

void printState(int state[])
{
    int i, empty = 1;

    printf("{");

    for (i = 0; i < n; i++)
    {
        if (state[i])
        {
            printf("q%d ", i);
            empty = 0;
        }
    }

    if (empty)
        printf("Dead");

    printf("}");
}

int main()
{
    int i, j, k, p, next[10];

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &symbols);

    if (n < 1 || n > 10 || symbols < 1 || symbols > 10)
    {
        printf("Invalid input size\n");
        return 1;
    }

    printf("\nEnter NFA transition matrix:\n");
    printf("Enter destination states as 1, separated by spaces.\n");
    printf("Enter 0 if there is no transition.\n");

    for (k = 0; k < symbols; k++)
    {
        printf("\nFor symbol %c:\n", 'a' + k);

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                scanf("%d", &nfa[k][i][j]);
            }
        }
    }

    /* Initial DFA state = {q0} */
    dfaStates[0][0] = 1;
    dfaCount = 1;

    /* Construct DFA using subset construction */
    for (i = 0; i < dfaCount; i++)
    {
        for (k = 0; k < symbols; k++)
        {
            for (j = 0; j < n; j++)
                next[j] = 0;

            for (j = 0; j < n; j++)
            {
                if (dfaStates[i][j] == 1)
                {
                    for (p = 0; p < n; p++)
                    {
                        if (nfa[k][j][p] == 1)
                            next[p] = 1;
                    }
                }
            }

            int found = findState(next);

            if (found == -1)
            {
                found = dfaCount;

                for (j = 0; j < n; j++)
                    dfaStates[dfaCount][j] = next[j];

                dfaCount++;
            }

            dfaTransition[i][k] = found;
        }
    }

    printf("\nDFA Transition Table:\n");

    printf("DFA State\t");

    for (k = 0; k < symbols; k++)
        printf("%c\t", 'a' + k);

    printf("\n");

    for (i = 0; i < dfaCount; i++)
    {
        printf("D%d = ", i);
        printState(dfaStates[i]);
        printf("\t");

        for (k = 0; k < symbols; k++)
            printf("D%d\t", dfaTransition[i][k]);

        printf("\n");
    }

    return 0;
}
