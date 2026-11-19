
#include<stdio.h>
#include<string.h>

int top = -1;
char stack[100], input[100];
char prod[100][100];
int n;

void reduce()
{
    for(int i = 0; i < n; i++)
    {
        int plen = strlen(prod[i]) - 2;
        int flag = 1;

        if(top >= plen - 1)
        {
            for(int j = 0; j < plen; j++)
            {
                if(stack[top - plen + 1 + j] != prod[i][j + 2])
                {
                    flag = 0;
                    break;
                }
            }

            if(flag == 1)
            {
                top = top - plen + 1;
                stack[top] = prod[i][0];
                stack[top + 1] = '\0';

                printf("Reduce %c -> %s\tStack: %s\n",
                       prod[i][0], prod[i] + 2, stack);

                return;
            }
        }
    }
}

void main()
{
    printf("Enter the number of production rules : ");
    scanf("%d", &n);

    printf("Enter the production rules : \n");

    for(int i = 0; i < n; i++)
    {
        scanf("%s", prod[i]);
    }

    printf("Enter the input string : ");
    scanf("%s", input);

    for(int i = 0; input[i] != '\0'; i++)
    {
        top++;
        stack[top] = input[i];
        stack[top + 1] = '\0';

        printf("Shift %c Stack : %s\n", input[i], stack);

        reduce();
    }

    while(top > 0)
    {
        int oldtop = top;

        reduce();

        if(oldtop == top)
            break;
    }

    if(top == 0 && stack[0] == prod[0][0])
        printf("\nString Accepted\n");
    else
        printf("\nString Rejected\n");
}
