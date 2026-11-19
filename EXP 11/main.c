
#include<stdio.h>
#include<string.h>
#include<ctype.h>

char operandStack[100][100];
char operatorStack[100];

int operandTop = -1;
int operatorTop = -1;
int temp = 0;

void generate(char operator, char operand1[], char operand2[], char result[])
{
    printf("%s = %s %c %s\n", result, operand1, operator, operand2);
}

int precedence(char operator)
{
    if(operator == '*' || operator == '/')
        return 3;
    else if(operator == '+' || operator == '-')
        return 2;
    else
        return 0;
}

void main()
{
    char expression[100];

    printf("Enter the input string : ");
    scanf("%s", expression);

    for(int i = 0; expression[i] != '\0'; i++)
    {
        if(isalnum(expression[i]))
        {
            operandTop++;
            operandStack[operandTop][0] = expression[i];
            operandStack[operandTop][1] = '\0';
        }

        else if(expression[i] == '(')
        {
            operatorTop++;
            operatorStack[operatorTop] = expression[i];
        }

        else if(expression[i] == ')')
        {
            while(operatorTop >= 0 && operatorStack[operatorTop] != '(')
            {
                char operand1[10], operand2[10], result[10];

                strcpy(operand2, operandStack[operandTop--]);
                strcpy(operand1, operandStack[operandTop--]);

                sprintf(result, "t%d", temp++);
                strcpy(operandStack[++operandTop], result);

                generate(operatorStack[operatorTop], operand1, operand2, result);

                operatorTop--;
            }

            operatorTop--;
        }

        else
        {
            while(operatorTop >= 0 &&
                  operatorStack[operatorTop] != '(' &&
                  precedence(operatorStack[operatorTop]) >= precedence(expression[i]))
            {
                char operand1[10], operand2[10], result[10];

                strcpy(operand2, operandStack[operandTop--]);
                strcpy(operand1, operandStack[operandTop--]);

                sprintf(result, "t%d", temp++);
                strcpy(operandStack[++operandTop], result);

                generate(operatorStack[operatorTop], operand1, operand2, result);

                operatorTop--;
            }

            operatorStack[++operatorTop] = expression[i];
        }
    }

    while(operatorTop >= 0)
    {
        char operand1[10], operand2[10], result[10];

        strcpy(operand2, operandStack[operandTop--]);
        strcpy(operand1, operandStack[operandTop--]);

        sprintf(result, "t%d", temp++);
        strcpy(operandStack[++operandTop], result);

        generate(operatorStack[operatorTop], operand1, operand2, result);

        operatorTop--;
    }

    printf("Result = %s\n", operandStack[operandTop]);
}
