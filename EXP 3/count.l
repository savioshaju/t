%{
#include <stdio.h>

int lines = 1; int words = 0;
int characters = 0;
%}
%%

\n {
lines++; characters++;
}
[ \t]+ {	
characters += yyleng;
}

[^ \t\n]+ { 
words++;
characters += yyleng;
}

%%

int main()
{
yylex();

printf("\nNumber of Lines	: %d\n", lines);
printf("Number of Words	: %d\n", words);
printf("Number of Characters : %d\n", characters);

return 0;
}

int yywrap() { return 1;
}
