%{
#include <stdio.h>

int yylex();
int yyerror(char *s);
%}


%token VARIABLE
%token INVALID

%%
input:
/* Empty */ | input line ;

line:
VARIABLE '\n' {
  
printf("Valid Variable \n");
} 
| INVALID '\n' {
printf("Invalid Variable \n");
};

%%

int yyerror(char *s) { printf("Error \n"); return 0;
}

int main () { yyparse(); return 0;
}
