#include<stdio.h>
#include<string.h>

int top = -1;
char stack[100], input[100];
char prod[100][100];
int n;

int reduce()
{
    for(int i = 0; i < n; i++)
    {
        int len = strlen(prod[i]) - 2;
        int flag = 1;

        if(top >= len - 1)
        {
            for(int j = 0; j < len; j++)
            {
                if(stack[top - len + 1 + j] != prod[i][j + 2])
                {
                    flag = 0;
                    break;
                }
            }

            if(flag)
            {
                top = top - len + 1;
                stack[top] = prod[i][0];
                stack[top + 1] = '\0';

                printf("Reduce %s\tStack: %s\n",
                       prod[i], stack);

                return 1;
            }
        }
    }

    return 0;
}

int main()
{
    printf("Enter the number of production rules: ");
    scanf("%d", &n);

    printf("Enter the production rules:\n");

    for(int i = 0; i < n; i++)
        scanf("%s", prod[i]);

    printf("Enter the input string: ");
    scanf("%s", input);

    for(int i = 0; input[i] != '\0'; i++)
    {
        stack[++top] = input[i];
        stack[top + 1] = '\0';

        printf("Shift %c\tStack: %s\n", input[i], stack);

        while(reduce());
    }

    while(reduce());

    if(top == 0 && stack[0] == prod[0][0])
        printf("\nString Accepted\n");
    else
        printf("\nString Rejected\n");

    return 0;
}
