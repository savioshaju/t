%{
    #include<stdio.h>

    int yylex();
    int yyerror(char *s);
%}

%token VALID
%token INVALID


%%
    input:
    /* Empty */ | input line;

    line:
    VALID '\n' {
        printf(" Valid\n");
    } |
    INVALID '\n'{
        printf(" Invalid\n");
    };


%%

int yyerror(char *s){
    printf("Error");
    return 0;
}

int main(){
    yyparse();
    return 0;

}