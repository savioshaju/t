%{
    #include<stdio.h>
    #include"y.tab.h"
%}

%%
[A-Za-z][A-Za-z0-9]* {
    printf("%s : ",yytext);
    return VALID;
}

.+ {
    printf("%s : ",yytext);
    return INVALID;
}

\n {
    return '\n';
}
%%

int yywrap(){
    return 1;

}