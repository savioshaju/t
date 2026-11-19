%{
    #include <stdio.h>
    int line =0;
    int word = 0;
    int cha = 0;
    int vowe =0 , const ;
%}

%%
\n {
    line++;
    cha++;
}
[ \t]+ {
    cha += yyleng;
}

[^ \t\n]+ {
    word++;
    cha += yyleng;
}

%%

int main(){
    yylex();

    printf("%d %d %d",line,word,cha);
    return 0;
}

int yywrap(){
    return 1;
}