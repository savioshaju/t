%{
    #include<stdio.h>
    #include"y.tab.h"
%}

%%
[A-Za-z] {
    printf("%s",yytext);
    return LETTER;
}

[0-9] {
    printf("%s",yytext);
    return NUMBER;
}

_ {
    printf("%s",yytext);
    return UNDERSCORE;
}

\n {
    return '\n';
}

. {
    printf("%s",yytext);
    return INVALID;
}
%%

int yywrap(){
    return 1;

}