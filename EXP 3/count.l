%{
#include <stdio.h>

int lines = 1;
int words = 0;
int characters = 0;
int vowels = 0;
int consonants = 0;
%}

%%

\n {
    lines++;
    characters++;
}

[ \t]+ {
    characters += yyleng;
}

[a-zA-Z]+ {
    words++;
    characters += yyleng;

    for(int i = 0; i < yyleng; i++) {
        if(yytext[i]=='a' || yytext[i]=='e' || yytext[i]=='i' ||
           yytext[i]=='o' || yytext[i]=='u' || yytext[i]=='A' ||
           yytext[i]=='E' || yytext[i]=='I' || yytext[i]=='O' ||
           yytext[i]=='U')
            vowels++;
        else
            consonants++;
    }
}

[0-9]+ {
    words++;
    characters += yyleng;
}

. {
    characters++;
}

%%

int main()
{
    yylex();

    printf("\nNumber of Lines      : %d\n", lines);
    printf("Number of Words      : %d\n", words);
    printf("Number of Characters : %d\n", characters);
    printf("Number of Vowels    : %d\n", vowels);
    printf("Number of Consonants: %d\n", consonants);

    return 0;
}

int yywrap()
{
    return 1;
}