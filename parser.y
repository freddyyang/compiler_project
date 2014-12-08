%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <iostream>
    #include "ast.hpp"
    
    #define YYDEBUG 1
    int yylex(void);
    void yyerror(const char *);
    
    extern ASTNode* astRoot;
%}

%error-verbose

/* WRITEME: Copy your token and precedence specifiers from Project 3 here */

/* WRITEME: List all your tokens here */
%token OR;
%token AND;
%token LESS;
%token LESSEQL;
%token IFEQL;
%token BOOL;
%token INT;
%token NONE;
%token PRINT;
%token RETURN;
%token IF;
%token ELSE;
%token FOR;
%token NEW;
%token TRUE;
%token FALSE;
%token INTEGER;
%token SIMICOLON;
%token COLON;
%token COMMA;
%token ABSOLUTEVALUE;
%token OPENPAREN;
%token CLOSEPAREN;
%token OPENBRACE;
%token CLOSEBRACE;
%token EQL;
%token DOT;
%token IDENTIFIER;
%token PLUS;
%token MINUS;
%token TIMES;
%token DIVIDE;
%token NOT;

/* WRITEME: Specify precedence here */
%left OR;
%left AND;
%left LESS LESSEQL IFEQL;
%left PLUS MINUS;
%left TIMES DIVIDE;
%right NOT;
%left DOT;


/* WRITEME: Specify types for all nonterminals and necessary terminals here 
  Push back when left recursive, Push front when right recursive
*/


%type <expression_list_ptr> Parameters ParametersPrime;
%type <expression_ptr> Expression;
%type <methodcall_ptr> MethodCall;
%type <identifier_ptr> IDENTIFIER;
%type <base_int> TRUE FALSE;
%type <returnstatement_ptr> returnStatement;
%type <type_ptr> Type;
%type <print_ptr> Print;
%type <for_ptr> forLoop;
%type <assignment_ptr> Assignment;
%type <ifelse_ptr> ifElse;
%type <statement_list_ptr> Statements;
%type <declaration_list_ptr> Declarations Members;
%type <declaration_ptr> Declaration;
%type <identifier_list_ptr> IDList;
%type <methodbody_ptr> Body;
%type <parameter_list_ptr>  Arguments ArgumentsPrime;
%type <method_list_ptr> Methods;
%type <class_ptr> Class;
%type <class_list_ptr> Classes;
%type <program_ptr> Start;
%type <integer_ptr> INTEGER;


%%

/* WRITEME: This rule is a placeholder. Replace it with your grammar
            rules from Project 3 */

Start : Classes {$$ = new ProgramNode($1); astRoot = $$;}
      ;

Classes : Classes Class {$$ = $1; $$->push_back($2);}
    | Class {$$ = new std::list<ClassNode*>(); $$ -> push_back($1);}
    ;

Class : IDENTIFIER OPENBRACE Members Methods CLOSEBRACE 
    {$$ = new ClassNode($1, NULL,$3, $4);}
    | IDENTIFIER COLON IDENTIFIER OPENBRACE Members Methods CLOSEBRACE 
    {$$ = new ClassNode($1, $3, $5, $6); }
    ;

Members : Members Type IDList {$$ = $1; $$->push_back(new DeclarationNode($2,$3));}
    | {$$ = new std::list<DeclarationNode*>(); }
    ;

Methods : IDENTIFIER OPENPAREN Arguments CLOSEPAREN COLON Type OPENBRACE Body CLOSEBRACE Methods
    {$$ = $10; $$->push_front(new MethodNode($1, $3, $6, $8));}
    | {$$ = new std::list<MethodNode*>();}
    ;

Arguments : ArgumentsPrime { $$ = $1;}
      | {$$ = new std::list<ParameterNode*>();}
      ;

ArgumentsPrime : ArgumentsPrime COMMA Type IDENTIFIER {$$ = $1; $$->push_back(new ParameterNode($3, $4));}
     | Type IDENTIFIER {$$ = new std::list<ParameterNode*>(); $$->push_back (new ParameterNode($1, $2));}
     ;

Body : Declarations Statements returnStatement {$$ = new MethodBodyNode($1,$2,$3); }
   ;

Declarations : Declarations Declaration { $$ = $1; $$->push_back($2);}
       | {$$ = new std::list<DeclarationNode*>();}
       ;

Declaration : Type IDList { $$ = new DeclarationNode($1,$2);}
      ; 

IDList : IDENTIFIER COMMA IDList { $$ = $3; $$->push_front($1);}
    | IDENTIFIER {$$ = new std::list<IdentifierNode*>(); $$->push_back($1);}
    ;

Statements : Assignment Statements {$$ = $2; $$->push_front($1);}
       | MethodCall Statements {$$ = $2; $$->push_front(new CallNode($1));}
       | ifElse Statements {$$ = $2; $$->push_front($1);}
       | forLoop Statements {$$ = $2; $$->push_front($1);}
       | Print Statements {$$ = $2; $$->push_front($1);}
       | { $$ = new std::list<StatementNode*> ();}
       ;

Assignment : IDENTIFIER EQL Expression
    {$$ = new AssignmentNode($1,$3);}
    ;

ifElse : IF Expression OPENBRACE Statements CLOSEBRACE {$$ = new IfElseNode($2,$4,NULL);}
     | IF Expression OPENBRACE Statements CLOSEBRACE ELSE OPENBRACE Statements CLOSEBRACE
     {$$ = new IfElseNode($2,$4,$8);}
     ;

forLoop : FOR Assignment SIMICOLON Expression SIMICOLON Assignment OPENBRACE Statements CLOSEBRACE
    {$$ = new ForNode($2, $4, $6, $8);}
    ;

Print : PRINT Expression { $$ = new PrintNode($2); }
    ;

Type : INT {$$ = new IntegerTypeNode();}
   | BOOL {$$ = new BooleanTypeNode();}
   | NONE {$$ = new NoneNode();}
   | IDENTIFIER {$$ = new ObjectTypeNode($1);}
   ;

returnStatement : RETURN Expression {$$ = new ReturnStatementNode($2);}
        | {$$ = NULL;}
        ;

Expression:   Expression PLUS Expression { $$ = new PlusNode($1,$3);}
    | Expression MINUS Expression {$$ = new MinusNode($1,$3);}
    | Expression TIMES Expression {$$ = new TimesNode($1,$3);}
    | Expression DIVIDE Expression {$$ = new DivideNode($1,$3);}
    | Expression LESS Expression {$$ = new LessNode($1,$3);}
    | Expression LESSEQL Expression {$$ = new LessEqualNode($1,$3);}
    | Expression IFEQL Expression {$$ = new EqualNode($1,$3);}
    | Expression AND Expression {$$ = new AndNode($1,$3);}
    | Expression OR Expression {$$ = new OrNode($1,$3);}
    | NOT Expression          %prec NOT {$$ = new NotNode($2);}
    | MINUS Expression        %prec NOT {$$ = new NegationNode($2);}
    | IDENTIFIER {$$ = new VariableNode($1);}
    | IDENTIFIER DOT IDENTIFIER {$$ = new MemberAccessNode($1,$3);}
    | MethodCall {$$ = $1;}
    | OPENPAREN Expression CLOSEPAREN { $$ = $2;}
    | INTEGER {$$ = new IntegerLiteralNode ($1);}
    | TRUE  {$$ = new BooleanLiteralNode (new IntegerNode(1));}
    | FALSE {$$ = new BooleanLiteralNode (new IntegerNode(0));}
    | NEW IDENTIFIER {$$ = new NewNode($2,new std::list<ExpressionNode*>());}
    | NEW IDENTIFIER OPENPAREN Parameters CLOSEPAREN {$$ = new NewNode($2,$4);}
    ;

MethodCall:   IDENTIFIER OPENPAREN Parameters CLOSEPAREN {$$ = new MethodCallNode($1,NULL,$3); }
    | IDENTIFIER DOT IDENTIFIER OPENPAREN Parameters CLOSEPAREN {$$ = new MethodCallNode($1,$3,$5); }
    ;

Parameters: ParametersPrime  {$$ = $1;}
    |   {$$ = new std::list<ExpressionNode*>();}
    ;

ParametersPrime:  ParametersPrime COMMA Expression {$$ = $1; $$->push_back($3);}
    | Expression {$$ = new std::list<ExpressionNode*>();$$->push_back($1);}
    ;

%%

extern int yylineno;

void yyerror(const char *s) {
  fprintf(stderr, "%s at line %d\n", s, yylineno);
  exit(0);
}
