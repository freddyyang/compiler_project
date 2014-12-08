#ifndef __AST_HPP
#define __AST_HPP

#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <string>
#include <sstream>

// Enumaration of all base types in the language
typedef enum {bt_integer, bt_boolean, bt_none, bt_object} BaseType;

// Forward declarations of AST Node classes
class ProgramNode;
class ClassNode;
class MethodNode;
class MethodBodyNode;
class ParameterNode;
class DeclarationNode;
class ReturnStatementNode;
class AssignmentNode;
class CallNode;
class IfElseNode;
class ForNode;
class PrintNode;
class PlusNode;
class MinusNode;
class TimesNode;
class DivideNode;
class LessNode;
class LessEqualNode;
class EqualNode;
class AndNode;
class OrNode;
class NotNode;
class NegationNode;
class MethodCallNode;
class MemberAccessNode;
class VariableNode;
class IntegerLiteralNode;
class BooleanLiteralNode;
class NewNode;
class IntegerTypeNode;
class BooleanTypeNode;
class ObjectTypeNode;
class NoneNode;


class StatementNode;

class ExpressionNode;

class TypeNode;

class IdentifierNode;
class IntegerNode;

// Check order of inclusion
#ifdef YYSTYPE_IS_TRIVIAL
#error Make sure to include this file BEFORE parser.hpp
#endif

// Define YYSTYPE (type of all $$, $N variables) as a union
//   of all necessary pointers (including lists). This will
//   be used in %type specifiers and in lexer.
typedef union {
  ProgramNode* program_ptr;
  std::list<ClassNode*>* class_list_ptr;
  ClassNode* class_ptr;
  IdentifierNode* identifier_ptr;
  std::list<DeclarationNode*>* declaration_list_ptr;
  std::list<MethodNode*>* method_list_ptr;
  MethodNode* method_ptr;
  std::list<ParameterNode*>* parameter_list_ptr;
  TypeNode* type_ptr;
  MethodBodyNode* methodbody_ptr;
  std::list<StatementNode*>* statement_list_ptr;
  ReturnStatementNode* returnstatement_ptr;
  ParameterNode* parameter_ptr;
  DeclarationNode* declaration_ptr;
  std::list<IdentifierNode*>* identifier_list_ptr;
  ExpressionNode* expression_ptr;
  AssignmentNode* assignment_ptr;
  CallNode* call_ptr;
  MethodCallNode* methodcall_ptr;
  IfElseNode* ifelse_ptr;
  ForNode* for_ptr;
  PrintNode* print_ptr;
  PlusNode* plus_ptr;
  MinusNode* minus_ptr;
  TimesNode* times_ptr;
  DivideNode* divide_ptr;
  LessNode* less_ptr;
  LessEqualNode* lessequal_ptr;
  EqualNode* equal_ptr;
  AndNode* and_ptr;
  OrNode* or_ptr;
  NotNode* not_ptr;
  NegationNode* negation_ptr;
  std::list<ExpressionNode*>* expression_list_ptr;
  MemberAccessNode* memberaccess_ptr;
  VariableNode* variable_ptr;
  IntegerLiteralNode* integerliteral_ptr;
  IntegerNode* integer_ptr;
  BooleanLiteralNode* booleanliteral_ptr;
  NewNode* new_ptr;
  IntegerTypeNode* integertype_ptr;
  BooleanTypeNode* booleantype_ptr;
  ObjectTypeNode* objecttype_ptr;
  NoneNode* none_ptr;
  StatementNode* statement_ptr;
  char* base_char_ptr;
  int base_int;
} astnode_union;
#define YYSTYPE astnode_union

// Define abstract base class for all Visitors
class Visitor {
public:
  // Declare all virtual visitor functions (all must be implemented in visitors)
  virtual void visitProgramNode(ProgramNode* node) = 0;
  virtual void visitClassNode(ClassNode* node) = 0;
  virtual void visitMethodNode(MethodNode* node) = 0;
  virtual void visitMethodBodyNode(MethodBodyNode* node) = 0;
  virtual void visitParameterNode(ParameterNode* node) = 0;
  virtual void visitDeclarationNode(DeclarationNode* node) = 0;
  virtual void visitReturnStatementNode(ReturnStatementNode* node) = 0;
  virtual void visitAssignmentNode(AssignmentNode* node) = 0;
  virtual void visitCallNode(CallNode* node) = 0;
  virtual void visitIfElseNode(IfElseNode* node) = 0;
  virtual void visitForNode(ForNode* node) = 0;
  virtual void visitPrintNode(PrintNode* node) = 0;
  virtual void visitPlusNode(PlusNode* node) = 0;
  virtual void visitMinusNode(MinusNode* node) = 0;
  virtual void visitTimesNode(TimesNode* node) = 0;
  virtual void visitDivideNode(DivideNode* node) = 0;
  virtual void visitLessNode(LessNode* node) = 0;
  virtual void visitLessEqualNode(LessEqualNode* node) = 0;
  virtual void visitEqualNode(EqualNode* node) = 0;
  virtual void visitAndNode(AndNode* node) = 0;
  virtual void visitOrNode(OrNode* node) = 0;
  virtual void visitNotNode(NotNode* node) = 0;
  virtual void visitNegationNode(NegationNode* node) = 0;
  virtual void visitMethodCallNode(MethodCallNode* node) = 0;
  virtual void visitMemberAccessNode(MemberAccessNode* node) = 0;
  virtual void visitVariableNode(VariableNode* node) = 0;
  virtual void visitIntegerLiteralNode(IntegerLiteralNode* node) = 0;
  virtual void visitBooleanLiteralNode(BooleanLiteralNode* node) = 0;
  virtual void visitNewNode(NewNode* node) = 0;
  virtual void visitIntegerTypeNode(IntegerTypeNode* node) = 0;
  virtual void visitBooleanTypeNode(BooleanTypeNode* node) = 0;
  virtual void visitObjectTypeNode(ObjectTypeNode* node) = 0;
  virtual void visitNoneNode(NoneNode* node) = 0;
  virtual void visitIdentifierNode(IdentifierNode* node) = 0;
  virtual void visitIntegerNode(IntegerNode* node) = 0;
};

// Define abstract base class for all AST Nodes
//   (this also serves to define the visitable objects)
class ASTNode {
public:
  // All AST nodes have a member which stores their basetype (int, bool, none, object)
  //   Further type information will come from the symbol table.
  BaseType basetype;

  // All AST nodes provide visit children and accept methods
  virtual void visit_children(Visitor* v) = 0;
  virtual void accept(Visitor* v) = 0;
};

// Define all abstract AST node classes
class StatementNode : public ASTNode {};
class ExpressionNode : public ASTNode {};
class TypeNode : public ASTNode {};

// Define leaf AST nodes for ids and ints (also used for bools)
// Identifiers have a member name, which is a string
class IdentifierNode : public ASTNode {
public:
  std::string name;
  virtual void visit_children(Visitor* v) { /* No Children */ }
  virtual void accept(Visitor* v) { v->visitIdentifierNode(this); }
  IdentifierNode(std::string name) { this->name = name; }

};

// Integers have a member value, which is a C int
class IntegerNode : public ASTNode {
public:
  int value;

  virtual void visit_children(Visitor* v) {/* No Children */ }
  virtual void accept(Visitor* v) { v->visitIntegerNode(this); }

  IntegerNode(int value) { this->value = value; }
};

// Define all other AST nodes

// AST Node for Program
class ProgramNode : public ASTNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitProgramNode(this); }

  std::list<ClassNode*>* class_list;

  ProgramNode(std::list<ClassNode*>* class_list);
};

// AST Node for Class
class ClassNode : public ASTNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitClassNode(this); }

  IdentifierNode* identifier_1;
  IdentifierNode* identifier_2;
  std::list<DeclarationNode*>* declaration_list;
  std::list<MethodNode*>* method_list;

  ClassNode(IdentifierNode* identifier_1, IdentifierNode* identifier_2, std::list<DeclarationNode*>* declaration_list, std::list<MethodNode*>* method_list);
};

// AST Node for Method
class MethodNode : public ASTNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitMethodNode(this); }

  IdentifierNode* identifier;
  std::list<ParameterNode*>* parameter_list;
  TypeNode* type;
  MethodBodyNode* methodbody;

  MethodNode(IdentifierNode* identifier, std::list<ParameterNode*>* parameter_list, TypeNode* type, MethodBodyNode* methodbody);
};

// AST Node for MethodBody
class MethodBodyNode : public ASTNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitMethodBodyNode(this); }

  std::list<DeclarationNode*>* declaration_list;
  std::list<StatementNode*>* statement_list;
  ReturnStatementNode* returnstatement;

  MethodBodyNode(std::list<DeclarationNode*>* declaration_list, std::list<StatementNode*>* statement_list, ReturnStatementNode* returnstatement);
};

// AST Node for Parameter
class ParameterNode : public ASTNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitParameterNode(this); }

  TypeNode* type;
  IdentifierNode* identifier;

  ParameterNode(TypeNode* type, IdentifierNode* identifier);
};

// AST Node for Declaration
class DeclarationNode : public ASTNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitDeclarationNode(this); }

  TypeNode* type;
  std::list<IdentifierNode*>* identifier_list;

  DeclarationNode(TypeNode* type, std::list<IdentifierNode*>* identifier_list);
};

// AST Node for ReturnStatement
class ReturnStatementNode : public ASTNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitReturnStatementNode(this); }

  ExpressionNode* expression;

  ReturnStatementNode(ExpressionNode* expression);
};

// AST Node for Assignment
class AssignmentNode : public StatementNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitAssignmentNode(this); }

  IdentifierNode* identifier;
  ExpressionNode* expression;

  AssignmentNode(IdentifierNode* identifier, ExpressionNode* expression);
};

// AST Node for Call
class CallNode : public StatementNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitCallNode(this); }

  MethodCallNode* methodcall;

  CallNode(MethodCallNode* methodcall);
};

// AST Node for IfElse
class IfElseNode : public StatementNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitIfElseNode(this); }

  ExpressionNode* expression;
  std::list<StatementNode*>* statement_list_1;
  std::list<StatementNode*>* statement_list_2;

  IfElseNode(ExpressionNode* expression, std::list<StatementNode*>* statement_list_1, std::list<StatementNode*>* statement_list_2);
};

// AST Node for For
class ForNode : public StatementNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitForNode(this); }

  AssignmentNode* assignment_1;
  ExpressionNode* expression;
  AssignmentNode* assignment_2;
  std::list<StatementNode*>* statement_list;

  ForNode(AssignmentNode* assignment_1, ExpressionNode* expression, AssignmentNode* assignment_2, std::list<StatementNode*>* statement_list);
};

// AST Node for Print
class PrintNode : public StatementNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitPrintNode(this); }

  ExpressionNode* expression;

  PrintNode(ExpressionNode* expression);
};

// AST Node for Plus
class PlusNode : public ExpressionNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitPlusNode(this); }

  ExpressionNode* expression_1;
  ExpressionNode* expression_2;

  PlusNode(ExpressionNode* expression_1, ExpressionNode* expression_2);
};

// AST Node for Minus
class MinusNode : public ExpressionNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitMinusNode(this); }

  ExpressionNode* expression_1;
  ExpressionNode* expression_2;

  MinusNode(ExpressionNode* expression_1, ExpressionNode* expression_2);
};

// AST Node for Times
class TimesNode : public ExpressionNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitTimesNode(this); }

  ExpressionNode* expression_1;
  ExpressionNode* expression_2;

  TimesNode(ExpressionNode* expression_1, ExpressionNode* expression_2);
};

// AST Node for Divide
class DivideNode : public ExpressionNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitDivideNode(this); }

  ExpressionNode* expression_1;
  ExpressionNode* expression_2;

  DivideNode(ExpressionNode* expression_1, ExpressionNode* expression_2);
};

// AST Node for Less
class LessNode : public ExpressionNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitLessNode(this); }

  ExpressionNode* expression_1;
  ExpressionNode* expression_2;

  LessNode(ExpressionNode* expression_1, ExpressionNode* expression_2);
};

// AST Node for LessEqual
class LessEqualNode : public ExpressionNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitLessEqualNode(this); }

  ExpressionNode* expression_1;
  ExpressionNode* expression_2;

  LessEqualNode(ExpressionNode* expression_1, ExpressionNode* expression_2);
};

// AST Node for Equal
class EqualNode : public ExpressionNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitEqualNode(this); }

  ExpressionNode* expression_1;
  ExpressionNode* expression_2;

  EqualNode(ExpressionNode* expression_1, ExpressionNode* expression_2);
};

// AST Node for And
class AndNode : public ExpressionNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitAndNode(this); }

  ExpressionNode* expression_1;
  ExpressionNode* expression_2;

  AndNode(ExpressionNode* expression_1, ExpressionNode* expression_2);
};

// AST Node for Or
class OrNode : public ExpressionNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitOrNode(this); }

  ExpressionNode* expression_1;
  ExpressionNode* expression_2;

  OrNode(ExpressionNode* expression_1, ExpressionNode* expression_2);
};

// AST Node for Not
class NotNode : public ExpressionNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitNotNode(this); }

  ExpressionNode* expression;

  NotNode(ExpressionNode* expression);
};

// AST Node for Negation
class NegationNode : public ExpressionNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitNegationNode(this); }

  ExpressionNode* expression;

  NegationNode(ExpressionNode* expression);
};

// AST Node for MethodCall
class MethodCallNode : public ExpressionNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitMethodCallNode(this); }

  IdentifierNode* identifier_1;
  IdentifierNode* identifier_2;
  std::list<ExpressionNode*>* expression_list;

  MethodCallNode(IdentifierNode* identifier_1, IdentifierNode* identifier_2, std::list<ExpressionNode*>* expression_list);
};

// AST Node for MemberAccess
class MemberAccessNode : public ExpressionNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitMemberAccessNode(this); }

  IdentifierNode* identifier_1;
  IdentifierNode* identifier_2;

  MemberAccessNode(IdentifierNode* identifier_1, IdentifierNode* identifier_2);
};

// AST Node for Variable
class VariableNode : public ExpressionNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitVariableNode(this); }

  IdentifierNode* identifier;

  VariableNode(IdentifierNode* identifier);
};

// AST Node for IntegerLiteral
class IntegerLiteralNode : public ExpressionNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitIntegerLiteralNode(this); }

  IntegerNode* integer;

  IntegerLiteralNode(IntegerNode* integer);
};

// AST Node for BooleanLiteral
class BooleanLiteralNode : public ExpressionNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitBooleanLiteralNode(this); }

  IntegerNode* integer;

  BooleanLiteralNode(IntegerNode* integer);
};

// AST Node for New
class NewNode : public ExpressionNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitNewNode(this); }

  IdentifierNode* identifier;
  std::list<ExpressionNode*>* expression_list;

  NewNode(IdentifierNode* identifier, std::list<ExpressionNode*>* expression_list);
};

// AST Node for IntegerType
class IntegerTypeNode : public TypeNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitIntegerTypeNode(this); }
};

// AST Node for BooleanType
class BooleanTypeNode : public TypeNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitBooleanTypeNode(this); }
};

// AST Node for ObjectType
class ObjectTypeNode : public TypeNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitObjectTypeNode(this); }

  IdentifierNode* identifier;

  ObjectTypeNode(IdentifierNode* identifier);
};

// AST Node for None
class NoneNode : public TypeNode {
public:
  virtual void visit_children(Visitor* v);
  virtual void accept(Visitor* v) { v->visitNoneNode(this); }
};

// Define the provided Print visitor, which will print the AST,
//   this is an example of a concrete visitor which visit the tree
class Print : public Visitor {
private:
  std::vector<std::string>* elements;
  std::stack<std::vector<std::string>*> stack;

  void pushLevel(std::string);
  void addElement(std::string);
  void popLevel();

public:
  virtual void visitProgramNode(ProgramNode* node);
  virtual void visitClassNode(ClassNode* node);
  virtual void visitMethodNode(MethodNode* node);
  virtual void visitMethodBodyNode(MethodBodyNode* node);
  virtual void visitParameterNode(ParameterNode* node);
  virtual void visitDeclarationNode(DeclarationNode* node);
  virtual void visitReturnStatementNode(ReturnStatementNode* node);
  virtual void visitAssignmentNode(AssignmentNode* node);
  virtual void visitCallNode(CallNode* node);
  virtual void visitIfElseNode(IfElseNode* node);
  virtual void visitForNode(ForNode* node);
  virtual void visitPrintNode(PrintNode* node);
  virtual void visitPlusNode(PlusNode* node);
  virtual void visitMinusNode(MinusNode* node);
  virtual void visitTimesNode(TimesNode* node);
  virtual void visitDivideNode(DivideNode* node);
  virtual void visitLessNode(LessNode* node);
  virtual void visitLessEqualNode(LessEqualNode* node);
  virtual void visitEqualNode(EqualNode* node);
  virtual void visitAndNode(AndNode* node);
  virtual void visitOrNode(OrNode* node);
  virtual void visitNotNode(NotNode* node);
  virtual void visitNegationNode(NegationNode* node);
  virtual void visitMethodCallNode(MethodCallNode* node);
  virtual void visitMemberAccessNode(MemberAccessNode* node);
  virtual void visitVariableNode(VariableNode* node);
  virtual void visitIntegerLiteralNode(IntegerLiteralNode* node);
  virtual void visitBooleanLiteralNode(BooleanLiteralNode* node);
  virtual void visitNewNode(NewNode* node);
  virtual void visitIntegerTypeNode(IntegerTypeNode* node);
  virtual void visitBooleanTypeNode(BooleanTypeNode* node);
  virtual void visitObjectTypeNode(ObjectTypeNode* node);
  virtual void visitNoneNode(NoneNode* node);
  virtual void visitIdentifierNode(IdentifierNode* node);
  virtual void visitIntegerNode(IntegerNode* node);
};

#endif

