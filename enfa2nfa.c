#include <stdio.h>

int n, symbols;
int epsilon[10][10];
int transition[10][10][10];
int closure[10][10];
int newTransition[10][10][10];

int final[10];
int newFinal[10];

void findClosure(int state, int current)
{
    int i;

    closure[state][current] = 1;
    for (i = 0; i < n; i++)
    {
        if (epsilon[current][i] == 1 && closure[state][i] == 0)
        {
            findClosure(state, i);
        }
    }
}

int main()
{
    int i, j, k, s, t;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &symbols);

    printf("\nEnter epsilon transition matrix:\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &epsilon[i][j]);
        }
    }

    for (i = 0; i < n; i++)
    {
        findClosure(i, i);
    }


    printf("\nEnter final states (1 if final, 0 otherwise):\n");

    for (i = 0; i < n; i++)
    {
        printf("q%d: ", i);
        scanf("%d", &final[i]);
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (closure[i][j] == 1 && final[j] == 1)
            {
                newFinal[i] = 1;
                break;
            }
        }
    }

    printf("\nEnter transitions for each input symbol:\n");

    for (k = 0; k < symbols; k++)
    {
        printf("\nSymbol %d:\n", k);

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                scanf("%d", &transition[k][i][j]);
            }
        }
    }


for (i = 0; i < n; i++)
{
    for (k = 0; k < symbols; k++)
    {
        for (s = 0; s < n; s++)
        {
            if (closure[i][s] == 1)
            {
                for (t = 0; t < n; t++)
                {
                    if (transition[k][s][t] == 1)
                    {
                        for (j = 0; j < n; j++)
                        {
                            if (closure[t][j] == 1)
                            {
                                newTransition[k][i][j] = 1;
                            }
                        }
                    }
                }
            }
        }

        
    }
}


    printf("\nNFA without epsilon transitions:\n");

    for (k = 0; k < symbols; k++)
    {
        printf("\nSymbol %d:\n", k);

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                printf("%d ", newTransition[k][i][j]);
            }
            printf("\n");
        }
    }


    printf("\nNew final states: ");

    for (i = 0; i < n; i++)
    {
        if (newFinal[i] == 1)
            printf("q%d ", i);
    }

    printf("\n");

    return 0;
}
