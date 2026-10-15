%{
#include "y.tab.h"
%}

%%
[a-zA-Z][a-zA-Z0-9]* {
printf("%s: ", yytext); return VARIABLE;
}

.+ {
printf("%s: ", yytext); return INVALID;
}

\n {
return '\n';
}

%%

int yywrap() { return 1;

}
