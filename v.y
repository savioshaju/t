%{
    #include<stdio.h>

    int yylex();
    int yyerror(char *s);
%}

%token LETTER NUMBER UNDERSCORE INVALID


%%
input :
    identifier '\n' {
        printf(" : Valid Identifier\n");
    };

identifier :
    LETTER
    | UNDERSCORE
    | identifier LETTER
    | identifier UNDERSCORE
    | identifier NUMBER
    ;


%%


int main(){
    yyparse();
    return 0;

}
int yyerror(char *s){
    printf("Invalid Identifier\n");
    main();
}