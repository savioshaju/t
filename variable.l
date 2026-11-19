%{
#include "y.tab.h"
%}

%%
[a-zA-Z_][a-zA-Z0-9_]* {
printf("%s: ", yytext); return VARIABLE;
}

.+ {
printf("%s: ", yytext); return INVALID;
}

\n {
return '\n';
}

%%

int yywrap() 
{ return 1;

}
