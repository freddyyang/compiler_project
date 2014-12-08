#include "ast.hpp"
// For node constructors, all children are taken as
//   parameters, and must be passed in. Optional children
//   may be NULL pointers. List children are pointers to
//    std::lists of the appropriate type (pointer to some node type).

// Visit Children method for Program AST node
void ProgramNode::visit_children(Visitor* v) {
  if (this->class_list) {
    for(std::list<ClassNode*>::iterator iter = this->class_list->begin();
        iter != this->class_list->end(); iter++) {
      (*iter)->accept(v);
    }
  }
}

// Constructor for Program AST node
ProgramNode::ProgramNode(std::list<ClassNode*>* class_list) {
  this->class_list = class_list;
}

// Visit Children method for Class AST node
void ClassNode::visit_children(Visitor* v) {
  identifier_1->accept(v);
  if (this->identifier_2) {
    this->identifier_2->accept(v);
  }
  if (this->declaration_list) {
    for(std::list<DeclarationNode*>::iterator iter = this->declaration_list->begin();
        iter != this->declaration_list->end(); iter++) {
      (*iter)->accept(v);
    }
  }
  if (this->method_list) {
    for(std::list<MethodNode*>::iterator iter = this->method_list->begin();
        iter != this->method_list->end(); iter++) {
      (*iter)->accept(v);
    }
  }
}

// Constructor for Class AST node
ClassNode::ClassNode(IdentifierNode*  identifier_1, IdentifierNode*  identifier_2, std::list<DeclarationNode*>* declaration_list, std::list<MethodNode*>* method_list) {
  this->identifier_1 = identifier_1;
  this->identifier_2 = identifier_2;
  this->declaration_list = declaration_list;
  this->method_list = method_list;
}

// Visit Children method for Method AST node
void MethodNode::visit_children(Visitor* v) {
  identifier->accept(v);
  if (this->parameter_list) {
    for(std::list<ParameterNode*>::iterator iter = this->parameter_list->begin();
        iter != this->parameter_list->end(); iter++) {
      (*iter)->accept(v);
    }
  }
  type->accept(v);
  methodbody->accept(v);
}

// Constructor for Method AST node
MethodNode::MethodNode(IdentifierNode*  identifier, std::list<ParameterNode*>* parameter_list, TypeNode*  type, MethodBodyNode*  methodbody) {
  this->identifier = identifier;
  this->parameter_list = parameter_list;
  this->type = type;
  this->methodbody = methodbody;
}

// Visit Children method for MethodBody AST node
void MethodBodyNode::visit_children(Visitor* v) {
  if (this->declaration_list) {
    for(std::list<DeclarationNode*>::iterator iter = this->declaration_list->begin();
        iter != this->declaration_list->end(); iter++) {
      (*iter)->accept(v);
    }
  }
  if (this->statement_list) {
    for(std::list<StatementNode*>::iterator iter = this->statement_list->begin();
        iter != this->statement_list->end(); iter++) {
      (*iter)->accept(v);
    }
  }
  if (this->returnstatement) {
    this->returnstatement->accept(v);
  }
}

// Constructor for MethodBody AST node
MethodBodyNode::MethodBodyNode(std::list<DeclarationNode*>* declaration_list, std::list<StatementNode*>* statement_list, ReturnStatementNode*  returnstatement) {
  this->declaration_list = declaration_list;
  this->statement_list = statement_list;
  this->returnstatement = returnstatement;
}

// Visit Children method for Parameter AST node
void ParameterNode::visit_children(Visitor* v) {
  type->accept(v);
  identifier->accept(v);
}

// Constructor for Parameter AST node
ParameterNode::ParameterNode(TypeNode*  type, IdentifierNode*  identifier) {
  this->type = type;
  this->identifier = identifier;
}

// Visit Children method for Declaration AST node
void DeclarationNode::visit_children(Visitor* v) {
  type->accept(v);
  if (this->identifier_list) {
    for(std::list<IdentifierNode*>::iterator iter = this->identifier_list->begin();
        iter != this->identifier_list->end(); iter++) {
      (*iter)->accept(v);
    }
  }
}

// Constructor for Declaration AST node
DeclarationNode::DeclarationNode(TypeNode*  type, std::list<IdentifierNode*>* identifier_list) {
  this->type = type;
  this->identifier_list = identifier_list;
}

// Visit Children method for ReturnStatement AST node
void ReturnStatementNode::visit_children(Visitor* v) {
  expression->accept(v);
}

// Constructor for ReturnStatement AST node
ReturnStatementNode::ReturnStatementNode(ExpressionNode*  expression) {
  this->expression = expression;
}

// Visit Children method for Assignment AST node
void AssignmentNode::visit_children(Visitor* v) {
  identifier->accept(v);
  expression->accept(v);
}

// Constructor for Assignment AST node
AssignmentNode::AssignmentNode(IdentifierNode*  identifier, ExpressionNode*  expression) {
  this->identifier = identifier;
  this->expression = expression;
}

// Visit Children method for Call AST node
void CallNode::visit_children(Visitor* v) {
  methodcall->accept(v);
}

// Constructor for Call AST node
CallNode::CallNode(MethodCallNode*  methodcall) {
  this->methodcall = methodcall;
}

// Visit Children method for IfElse AST node
void IfElseNode::visit_children(Visitor* v) {
  expression->accept(v);
  if (this->statement_list_1) {
    for(std::list<StatementNode*>::iterator iter = this->statement_list_1->begin();
        iter != this->statement_list_1->end(); iter++) {
      (*iter)->accept(v);
    }
  }
  if (this->statement_list_2) {
    for(std::list<StatementNode*>::iterator iter = this->statement_list_2->begin();
        iter != this->statement_list_2->end(); iter++) {
      (*iter)->accept(v);
    }
  }
}

// Constructor for IfElse AST node
IfElseNode::IfElseNode(ExpressionNode*  expression, std::list<StatementNode*>* statement_list_1, std::list<StatementNode*>* statement_list_2) {
  this->expression = expression;
  this->statement_list_1 = statement_list_1;
  this->statement_list_2 = statement_list_2;
}

// Visit Children method for For AST node
void ForNode::visit_children(Visitor* v) {
  assignment_1->accept(v);
  expression->accept(v);
  assignment_2->accept(v);
  if (this->statement_list) {
    for(std::list<StatementNode*>::iterator iter = this->statement_list->begin();
        iter != this->statement_list->end(); iter++) {
      (*iter)->accept(v);
    }
  }
}

// Constructor for For AST node
ForNode::ForNode(AssignmentNode*  assignment_1, ExpressionNode*  expression, AssignmentNode*  assignment_2, std::list<StatementNode*>* statement_list) {
  this->assignment_1 = assignment_1;
  this->expression = expression;
  this->assignment_2 = assignment_2;
  this->statement_list = statement_list;
}

// Visit Children method for Print AST node
void PrintNode::visit_children(Visitor* v) {
  expression->accept(v);
}

// Constructor for Print AST node
PrintNode::PrintNode(ExpressionNode*  expression) {
  this->expression = expression;
}

// Visit Children method for Plus AST node
void PlusNode::visit_children(Visitor* v) {
  expression_1->accept(v);
  expression_2->accept(v);
}

// Constructor for Plus AST node
PlusNode::PlusNode(ExpressionNode*  expression_1, ExpressionNode*  expression_2) {
  this->expression_1 = expression_1;
  this->expression_2 = expression_2;
}

// Visit Children method for Minus AST node
void MinusNode::visit_children(Visitor* v) {
  expression_1->accept(v);
  expression_2->accept(v);
}

// Constructor for Minus AST node
MinusNode::MinusNode(ExpressionNode*  expression_1, ExpressionNode*  expression_2) {
  this->expression_1 = expression_1;
  this->expression_2 = expression_2;
}

// Visit Children method for Times AST node
void TimesNode::visit_children(Visitor* v) {
  expression_1->accept(v);
  expression_2->accept(v);
}

// Constructor for Times AST node
TimesNode::TimesNode(ExpressionNode*  expression_1, ExpressionNode*  expression_2) {
  this->expression_1 = expression_1;
  this->expression_2 = expression_2;
}

// Visit Children method for Divide AST node
void DivideNode::visit_children(Visitor* v) {
  expression_1->accept(v);
  expression_2->accept(v);
}

// Constructor for Divide AST node
DivideNode::DivideNode(ExpressionNode*  expression_1, ExpressionNode*  expression_2) {
  this->expression_1 = expression_1;
  this->expression_2 = expression_2;
}

// Visit Children method for Less AST node
void LessNode::visit_children(Visitor* v) {
  expression_1->accept(v);
  expression_2->accept(v);
}

// Constructor for Less AST node
LessNode::LessNode(ExpressionNode*  expression_1, ExpressionNode*  expression_2) {
  this->expression_1 = expression_1;
  this->expression_2 = expression_2;
}

// Visit Children method for LessEqual AST node
void LessEqualNode::visit_children(Visitor* v) {
  expression_1->accept(v);
  expression_2->accept(v);
}

// Constructor for LessEqual AST node
LessEqualNode::LessEqualNode(ExpressionNode*  expression_1, ExpressionNode*  expression_2) {
  this->expression_1 = expression_1;
  this->expression_2 = expression_2;
}

// Visit Children method for Equal AST node
void EqualNode::visit_children(Visitor* v) {
  expression_1->accept(v);
  expression_2->accept(v);
}

// Constructor for Equal AST node
EqualNode::EqualNode(ExpressionNode*  expression_1, ExpressionNode*  expression_2) {
  this->expression_1 = expression_1;
  this->expression_2 = expression_2;
}

// Visit Children method for And AST node
void AndNode::visit_children(Visitor* v) {
  expression_1->accept(v);
  expression_2->accept(v);
}

// Constructor for And AST node
AndNode::AndNode(ExpressionNode*  expression_1, ExpressionNode*  expression_2) {
  this->expression_1 = expression_1;
  this->expression_2 = expression_2;
}

// Visit Children method for Or AST node
void OrNode::visit_children(Visitor* v) {
  expression_1->accept(v);
  expression_2->accept(v);
}

// Constructor for Or AST node
OrNode::OrNode(ExpressionNode*  expression_1, ExpressionNode*  expression_2) {
  this->expression_1 = expression_1;
  this->expression_2 = expression_2;
}

// Visit Children method for Not AST node
void NotNode::visit_children(Visitor* v) {
  expression->accept(v);
}

// Constructor for Not AST node
NotNode::NotNode(ExpressionNode*  expression) {
  this->expression = expression;
}

// Visit Children method for Negation AST node
void NegationNode::visit_children(Visitor* v) {
  expression->accept(v);
}

// Constructor for Negation AST node
NegationNode::NegationNode(ExpressionNode*  expression) {
  this->expression = expression;
}

// Visit Children method for MethodCall AST node
void MethodCallNode::visit_children(Visitor* v) {
  identifier_1->accept(v);
  if (this->identifier_2) {
    this->identifier_2->accept(v);
  }
  if (this->expression_list) {
    for(std::list<ExpressionNode*>::iterator iter = this->expression_list->begin();
        iter != this->expression_list->end(); iter++) {
      (*iter)->accept(v);
    }
  }
}

// Constructor for MethodCall AST node
MethodCallNode::MethodCallNode(IdentifierNode*  identifier_1, IdentifierNode*  identifier_2, std::list<ExpressionNode*>* expression_list) {
  this->identifier_1 = identifier_1;
  this->identifier_2 = identifier_2;
  this->expression_list = expression_list;
}

// Visit Children method for MemberAccess AST node
void MemberAccessNode::visit_children(Visitor* v) {
  identifier_1->accept(v);
  identifier_2->accept(v);
}

// Constructor for MemberAccess AST node
MemberAccessNode::MemberAccessNode(IdentifierNode*  identifier_1, IdentifierNode*  identifier_2) {
  this->identifier_1 = identifier_1;
  this->identifier_2 = identifier_2;
}

// Visit Children method for Variable AST node
void VariableNode::visit_children(Visitor* v) {
  identifier->accept(v);
}

// Constructor for Variable AST node
VariableNode::VariableNode(IdentifierNode*  identifier) {
  this->identifier = identifier;
}

// Visit Children method for IntegerLiteral AST node
void IntegerLiteralNode::visit_children(Visitor* v) {
  integer->accept(v);
}

// Constructor for IntegerLiteral AST node
IntegerLiteralNode::IntegerLiteralNode(IntegerNode*  integer) {
  this->integer = integer;
}

// Visit Children method for BooleanLiteral AST node
void BooleanLiteralNode::visit_children(Visitor* v) {
  integer->accept(v);
}

// Constructor for BooleanLiteral AST node
BooleanLiteralNode::BooleanLiteralNode(IntegerNode*  integer) {
  this->integer = integer;
}

// Visit Children method for New AST node
void NewNode::visit_children(Visitor* v) {
  identifier->accept(v);
  if (this->expression_list) {
    for(std::list<ExpressionNode*>::iterator iter = this->expression_list->begin();
        iter != this->expression_list->end(); iter++) {
      (*iter)->accept(v);
    }
  }
}

// Constructor for New AST node
NewNode::NewNode(IdentifierNode*  identifier, std::list<ExpressionNode*>* expression_list) {
  this->identifier = identifier;
  this->expression_list = expression_list;
}

// Visit Children method for IntegerType AST node
void IntegerTypeNode::visit_children(Visitor* v) {
}

// Visit Children method for BooleanType AST node
void BooleanTypeNode::visit_children(Visitor* v) {
}

// Visit Children method for ObjectType AST node
void ObjectTypeNode::visit_children(Visitor* v) {
  identifier->accept(v);
}

// Constructor for ObjectType AST node
ObjectTypeNode::ObjectTypeNode(IdentifierNode*  identifier) {
  this->identifier = identifier;
}

// Visit Children method for None AST node
void NoneNode::visit_children(Visitor* v) {
}

// Definitions for print functions
// Push Level adds a new level to the printed tree (for a node with children)
void Print::pushLevel(std::string name) {
  if (this->elements)
    this->stack.push(this->elements);
  this->elements = new std::vector<std::string>();
  std::stringstream ss;
  ss << name << "(";
  this->elements->push_back(ss.str());
}

// Add Element adds a new leaf to the printed tree (for a node with no children)
void Print::addElement(std::string name) {
  this->elements->push_back(name);
}

// Pop Level finishes the printing of a node with children, and matches with
//   calls to push level.
void Print::popLevel() {
  std::stringstream ss;
  ss << this->elements->at(0);
  for (std::vector<std::string>::iterator iter = this->elements->begin()+1; iter != this->elements->end(); iter++) {
    ss << (*iter);
    if (iter != this->elements->end() - 1)
      ss << ", ";
  }
  delete this->elements;
  ss << ")";
  if (!stack.empty()) {
    this->elements = stack.top();
    this->elements->push_back(ss.str());
    stack.pop();
  } else
    std::cout << ss.str() << std::endl;
}

// Define concrete implementations of all abstract visitor functions
// Concrete visit function for Program nodes
void Print::visitProgramNode(ProgramNode* node) {
  this->pushLevel("Program");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for Class nodes
void Print::visitClassNode(ClassNode* node) {
  this->pushLevel("Class");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for Method nodes
void Print::visitMethodNode(MethodNode* node) {
  this->pushLevel("Method");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for MethodBody nodes
void Print::visitMethodBodyNode(MethodBodyNode* node) {
  this->pushLevel("MethodBody");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for Parameter nodes
void Print::visitParameterNode(ParameterNode* node) {
  this->pushLevel("Parameter");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for Declaration nodes
void Print::visitDeclarationNode(DeclarationNode* node) {
  this->pushLevel("Declaration");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for ReturnStatement nodes
void Print::visitReturnStatementNode(ReturnStatementNode* node) {
  this->pushLevel("ReturnStatement");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for Assignment nodes
void Print::visitAssignmentNode(AssignmentNode* node) {
  this->pushLevel("Assignment");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for Call nodes
void Print::visitCallNode(CallNode* node) {
  this->pushLevel("Call");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for IfElse nodes
void Print::visitIfElseNode(IfElseNode* node) {
  this->pushLevel("IfElse");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for For nodes
void Print::visitForNode(ForNode* node) {
  this->pushLevel("For");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for Print nodes
void Print::visitPrintNode(PrintNode* node) {
  this->pushLevel("Print");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for Plus nodes
void Print::visitPlusNode(PlusNode* node) {
  this->pushLevel("Plus");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for Minus nodes
void Print::visitMinusNode(MinusNode* node) {
  this->pushLevel("Minus");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for Times nodes
void Print::visitTimesNode(TimesNode* node) {
  this->pushLevel("Times");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for Divide nodes
void Print::visitDivideNode(DivideNode* node) {
  this->pushLevel("Divide");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for Less nodes
void Print::visitLessNode(LessNode* node) {
  this->pushLevel("Less");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for LessEqual nodes
void Print::visitLessEqualNode(LessEqualNode* node) {
  this->pushLevel("LessEqual");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for Equal nodes
void Print::visitEqualNode(EqualNode* node) {
  this->pushLevel("Equal");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for And nodes
void Print::visitAndNode(AndNode* node) {
  this->pushLevel("And");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for Or nodes
void Print::visitOrNode(OrNode* node) {
  this->pushLevel("Or");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for Not nodes
void Print::visitNotNode(NotNode* node) {
  this->pushLevel("Not");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for Negation nodes
void Print::visitNegationNode(NegationNode* node) {
  this->pushLevel("Negation");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for MethodCall nodes
void Print::visitMethodCallNode(MethodCallNode* node) {
  this->pushLevel("MethodCall");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for MemberAccess nodes
void Print::visitMemberAccessNode(MemberAccessNode* node) {
  this->pushLevel("MemberAccess");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for Variable nodes
void Print::visitVariableNode(VariableNode* node) {
  this->pushLevel("Variable");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for IntegerLiteral nodes
void Print::visitIntegerLiteralNode(IntegerLiteralNode* node) {
  this->pushLevel("IntegerLiteral");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for BooleanLiteral nodes
void Print::visitBooleanLiteralNode(BooleanLiteralNode* node) {
  this->pushLevel("BooleanLiteral");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for New nodes
void Print::visitNewNode(NewNode* node) {
  this->pushLevel("New");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for IntegerType nodes
void Print::visitIntegerTypeNode(IntegerTypeNode* node) {
this->addElement("IntegerType");
}

// Concrete visit function for BooleanType nodes
void Print::visitBooleanTypeNode(BooleanTypeNode* node) {
this->addElement("BooleanType");
}

// Concrete visit function for ObjectType nodes
void Print::visitObjectTypeNode(ObjectTypeNode* node) {
  this->pushLevel("ObjectType");
  node->visit_children(this);
  this->popLevel();
}

// Concrete visit function for None nodes
void Print::visitNoneNode(NoneNode* node) {
this->addElement("None");
}

// Concrete visit function for Identifiers (leaf nodes)
void Print::visitIdentifierNode(IdentifierNode* node) {
  std::stringstream ss;
  // Print the name of the indentifier surrounded by quotes
  ss << "\"" << node->name << "\"";
  this->addElement(ss.str());
  node->visit_children(this);
}

void Print::visitIntegerNode(IntegerNode* node) {
  std::stringstream ss;
  // Print the value of the integer
  ss << node->value;
  this->addElement(ss.str());
  node->visit_children(this);
}

