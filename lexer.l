/* referrenced from http://geekwentfreak-raviteja.rhcloud.com/blog/2011/01/02/passing-valuesyylval-other-than-strings-from-flex-to-bison/ */

%option yylineno
%pointer

%{
    #include <stdlib.h>
    #include <errno.h>
    #include <limits.h>
    #include "ast.hpp"
    #include "parser.hpp"
    void yyerror(const char *);
%}

/* WRITEME: Copy any definitions and start conditions from Project 3 here */

%x comment
%%

"or" {return OR;}
"<" {return LESS;}
"<=" {return LESSEQL;}
"==" {return IFEQL;}
"+" {return PLUS;}
"-" {return MINUS;}
"*" {return TIMES;}
"/" {return DIVIDE;}
"." {return DOT;}

"not" {return NOT;}
bool {return BOOL;}
int  {return INT;}
none {return NONE;}
print {return PRINT;}
return {return RETURN;}
if {return IF;}
else {return ELSE;}
for {return FOR;}
new {return NEW;}
and {return AND;}
true {return TRUE;}
false {return FALSE;}

0   {yylval.integer_ptr = new IntegerNode(atoi(yytext));return INTEGER;}
[1-9][0-9]*              {yylval.integer_ptr = new IntegerNode(atoi(yytext)) ;return INTEGER;}
[A-Za-z][0-9A-Za-z]*         { yylval.identifier_ptr = new IdentifierNode(std::string(strdup(yytext))); return IDENTIFIER;}


";" { return SIMICOLON;}
":" { return COLON; }
"," { return COMMA; }
"|" { return ABSOLUTEVALUE;}
"(" { return OPENPAREN; }
")" { return CLOSEPAREN; }
"{" { return OPENBRACE;}
"}" { return CLOSEBRACE; }
"=" { return EQL; }

[ \t\n] ; /* skip whitespace */
.       { yyerror("invalid character"); }


"/*"         BEGIN(comment);
<comment>[^*\n]*        /* eat anything that's not a '*' */
<comment>"*"+[^*/\n]*   /* eat up '*'s not followed by '/'s */
<comment>\n ;
<comment>"*"+"/"        BEGIN(INITIAL);








%%

int yywrap(void) {
  return 1;
}
