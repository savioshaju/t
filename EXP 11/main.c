#include<stdio.h>
#include<string.h>
#include<ctype.h>
char opera[100][100];
char oprand[100];

int top = -1;
int optop = -1;
int temp = 0;

void gen(char op, char a[], char b[], char res[])
{
    printf("%s = %s %c %s\n", res, a, op, b);
}

int pre(char op)
{
    if(op == '*' || op == '/')
        return 3;
    else if(op == '+' || op == '-')
        return 2;
    else
        return 0;
}

void main()
{
    char stg[100];

    printf("Enter the input string : ");
    scanf("%s", stg);

    for(int i = 0; stg[i] != '\0'; i++)
    {
        if(isalnum(stg[i]))
        {
            top++;
            opera[top][0] = stg[i];
            opera[top][1] = '\0';
        }

        else if(stg[i] == '(')
        {
            oprand[++optop] = stg[i];
        }

        else if(stg[i] == ')')
        {
            while(optop >= 0 && oprand[optop] != '(')
            {
                char a[10], b[10], res[10];

                strcpy(b, opera[top--]);
                strcpy(a, opera[top--]);

                sprintf(res, "t%d", temp++);
                strcpy(opera[++top], res);

                gen(oprand[optop--], a, b, res);
            }

            optop--;
        }

        else
        {
            while(optop >= 0 &&
                  oprand[optop] != '(' &&
                  pre(oprand[optop]) >= pre(stg[i]))
            {
                char a[10], b[10], res[10];

                strcpy(b, opera[top--]);
                strcpy(a, opera[top--]);

                sprintf(res, "t%d", temp++);
                strcpy(opera[++top], res);

                gen(oprand[optop--], a, b, res);
            }

            oprand[++optop] = stg[i];
        }
    }

    while(optop >= 0)
    {
        char a[10], b[10], res[10];

        strcpy(b, opera[top--]);
        strcpy(a, opera[top--]);

        sprintf(res, "t%d", temp++);
        strcpy(opera[++top], res);

        gen(oprand[optop--], a, b, res);
    }

    printf("Result = %s\n", opera[top]);
}
