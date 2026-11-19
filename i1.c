
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int prec(char ch)
{
    if(ch == '+' || ch == '-')
        return 1;

    if(ch == '*' || ch == '/')
        return 2;

    return 0;
}

int main()
{
    char exp[100], op[50], pos[100], str[50][50];
    int p = -1, top = -1, s = -1, t = 1;
    int i;
    char a[50], b[50];

    printf("Enter the Expression\n");
    scanf("%99s", exp);

    for(i = 0; exp[i] != '\0'; i++)
    {
        if(isalnum(exp[i]))
        {
            pos[++p] = exp[i];
        }
        else if(exp[i] == '(')
        {
            op[++top] = exp[i];
        }
        else if(exp[i] == ')')
        {
            while(top >= 0 && op[top] != '(')
                pos[++p] = op[top--];

            top--;
        }
        else
        {
            while(top >= 0 && op[top] != '(' &&
                  prec(op[top]) >= prec(exp[i]))
            {
                pos[++p] = op[top--];
            }

            op[++top] = exp[i];
        }
    }

    while(top >= 0)
    {
        pos[++p] = op[top--];
    }

    pos[++p] = '\0';

    for(i = 0; pos[i] != '\0'; i++)
    {
        if(isalnum(pos[i]))
        {
            str[++s][0] = pos[i];
            str[s][1] = '\0';
        }
        else
        {
            strcpy(b, str[s--]);
            strcpy(a, str[s--]);

            printf("t%d: %s %c %s\n", t, a, pos[i], b);

            sprintf(str[++s], "t%d", t);
            t++;
        }
    }

    if(s >= 0)
        printf("Result: %s\n", str[s]);

    return 0;
}
