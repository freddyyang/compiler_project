#ifndef __SYMBOL_HPP
#define __SYMBOL_HPP

#include "ast.hpp"
#include <map>

// Defines a compound type, which is a basetype as well as a
// string representing the class name of an object type.
typedef struct compoundtype {
  BaseType baseType;
  std::string objectClassName;
} CompoundType;

// Defines the information for a variable. This will be the
// data in the variable table (each variable will map to one
// of these). Includes the type, the offset, and the size
// (always 4 bytes or 1 word in our language).
typedef struct variableinfo {
  CompoundType type;
  int offset;
  int size;
} VariableInfo;

// Defines a variable table. Maps from a string (variable
// name) to a variable info.
typedef std::map<std::string, VariableInfo> VariableTable;

// Defines the information for a method. This will be the
// data in the method table (each method will map to one
// of these). Includes return type, the variable table for
// the method (which will have the paramters and locals),
// and the size of the local variables (used when allocating
// space in the stack frame).
typedef struct methodinfo {
  CompoundType returnType;
  VariableTable variables;
  int localsSize;
} MethodInfo;

// Defines a method table. Maps from a string (method name)
// to a method info.
typedef std::map<std::string, MethodInfo> MethodTable;

// Defines the information for a class. This will be the
// data in the class table (each class will map to one
// of these). Includes the super class name (empty string
// if no super class), the method table, the member table
// (which is a variable table), and the size of the members
// (which is used when allocating on the heap).
typedef struct classinfo {
  std::string superClassName;
  MethodTable methods;
  VariableTable members;
  int membersSize;
} ClassInfo;

// Defines a class table. Maps from a string (class name)
// to a class info.
typedef std::map<std::string, ClassInfo> ClassTable;

// This function will print the symbol table. The code is
// at the bottom of this file, and does not need modification.
void print(ClassTable classTable);

// This defines the Symbol visitor, which will visit the AST
// and construct the symbol table. You will do all your
// implementation of the symbol table construction in the
// visitor functions for this visitor.
class Symbol : public Visitor {
public:
  // This member represents the main class table. You can
  // think of this as the "root" of the symbol table.
  //
  // NOTE: You will need to construct a new ClassTable
  // and set this pointer at the beginning of the Symbol
  // visitor pass over the AST.
  ClassTable* classTable;
  
  // These members allow you to keep track of the current
  // method table and and current variable table. This allows
  // you to insert variables and methods as soon as you finish
  // visiting them in the AST.
  // For example, you might insert variables immediately in your
  // visitDeclarationNode function.
  //
  // NOTE: These are _pointers_. Set them with the address-of
  // operator. For example, if you want to set the current
  // method table to the address of newMethodTable, do:
  //   this->currentMethodTable = &(newMethodTable);
  //
  // NOTE: These are not automatically set, you will need to
  // maintain/set them as your visitor visits the AST.
  MethodTable* currentMethodTable;
  VariableTable* currentVariableTable;
  
  // These members allow you to keep track of several current
  // offsets. Important offsets are the current offset in the
  // local variable space, the current offset for parameters,
  // and the current offset for class members.
  //
  // NOTE: The current local offset starts at -4
  // and goes _down_ by 4 for each new variable;
  // the current parameter offset starts at 8 and
  // goes _up_ by 4 for each parameter;
  // and the current member offset starts a 0 and
  // goes _up_ by 4 for each member.
  //
  // NOTE: These are not automatically set, you will need to
  // maintain/set them as your visitor visits the AST.
  int currentLocalOffset;
  int currentParameterOffset;
  int currentMemberOffset;
  
  // All the visitor functions. You will need to write
  // appropriate implementation in the symbol.cpp file.
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

// The following functions are used to print the Symbol Table.
// They do not need to be modified at all.

std::string inline genIndent(int indent) {
    std::string string = std::string("");
    for (int i = 0; i < indent; i++)
        string += std::string(" ");
    return string;
}

std::string inline string(CompoundType type) {
    switch (type.baseType) {
    case bt_integer:
        return std::string("Integer");
    case bt_boolean:
        return std::string("Boolean");
    case bt_none:
        return std::string("None");
    case bt_object:
        return std::string("Object(") + type.objectClassName + std::string(")");
    }
}


void inline print(VariableTable variableTable, int indent) {
    std::cout << genIndent(indent) << "VariableTable {";
    if (variableTable.size() == 0) {
        std::cout << "}";
        return;
    }
    std::cout << std::endl;
    for (VariableTable::iterator it = variableTable.begin(); it != variableTable.end(); it++) {
        std::cout << genIndent(indent + 2) << it->first << " -> {" << string(it->second.type) << ", " << it->second.offset << ", " << it->second.size << "}";
        if (it != --variableTable.end())
            std::cout << ",";
        std::cout << std::endl;
    }
    std::cout << genIndent(indent) << "}";
}

void inline print(MethodTable methodTable, int indent) {
    std::cout << genIndent(indent) << "MethodTable {";
    if (methodTable.size() == 0) {
        std::cout << "}";
        return;
    }
    std::cout << std::endl;
    for (MethodTable::iterator it = methodTable.begin(); it != methodTable.end(); it++) {
        std::cout << genIndent(indent + 2) << it->first << " -> {" << std::endl;
        std::cout << genIndent(indent + 4) << string(it->second.returnType) << "," << std::endl;
        std::cout << genIndent(indent + 4) << it->second.localsSize << "," << std::endl;
        print(it->second.variables, indent + 4);
        std::cout <<std::endl;
        std::cout << genIndent(indent + 2) << "}";
        if (it != --methodTable.end())
            std::cout << ",";
        std::cout << std::endl;
    }
    std::cout << genIndent(indent) << "}";
}

void inline print(ClassTable classTable, int indent) {
    std::cout << genIndent(indent) << "ClassTable {" << std::endl;
    for (ClassTable::iterator it = classTable.begin(); it != classTable.end(); it++) {
        std::cout << genIndent(indent + 2) << it->first << " -> {" << std::endl;
        if (it->second.superClassName != "")
            std::cout << genIndent(indent + 4) << it->second.superClassName << "," << std::endl;
        print(it->second.members, indent + 4);
        std::cout << "," << std::endl;
        print(it->second.methods, indent + 4);
        std::cout <<std::endl;
        std::cout << genIndent(indent + 2) << "}";
        if (it != --classTable.end())
            std::cout << ",";
        std::cout << std::endl;
    }
    std::cout << genIndent(indent) << "}" << std::endl;
}

void inline print(ClassTable classTable) {
    print(classTable, 0);
}

#endif
