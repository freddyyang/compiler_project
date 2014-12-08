#include "symbol.hpp"

// Symbol Visitor Functions: These are the functions you will
// complete to build the symbol table. Not all functions must
// have code, many may be left empty.

void Symbol::visitProgramNode(ProgramNode* node) {
    // WRITEME: Replace with code if necessary
    classTable = new ClassTable;
    node-> visit_children(this);
}

void Symbol::visitClassNode(ClassNode* node) {

    ClassInfo class_info;
    std::string class_name = node -> identifier_1 -> name;
    if (node -> identifier_2 != NULL)
    {
        class_info.superClassName = node -> identifier_2 -> name;
    }
    else
    {
        class_info.superClassName = "";
    }
    currentVariableTable = &(class_info.members);
    currentMethodTable = &(class_info.methods);
    currentMemberOffset = 0;
    currentLocalOffset = 0; 
    node -> visit_children(this);
    class_info.membersSize = currentMemberOffset;
    classTable -> insert(std::pair<std::string,ClassInfo>(class_name,class_info));
}

void Symbol::visitMethodNode(MethodNode* node) 
{
    MethodInfo method_info;
    std::string method_name= node -> identifier -> name;

    if (method_info.returnType.baseType == bt_object)
        method_info.returnType.objectClassName = ((ObjectTypeNode*)node -> type)->identifier->name;
    else
        method_info.returnType.baseType = node->type->basetype;
    currentVariableTable = &(method_info.variables);
    currentLocalOffset = -4;     //initialize Local Offset
    currentParameterOffset = 8;  //initialize Param Offset

    node->visit_children(this);
    method_info.localsSize = -(currentLocalOffset - (-4)); //  Starts from -4, -4 each time
    currentMethodTable -> insert(std::pair<std::string,MethodInfo>(method_name, method_info));
}

void Symbol::visitMethodBodyNode(MethodBodyNode* node) {
    node -> visit_children(this);
}

void Symbol::visitParameterNode(ParameterNode* node) {
    VariableInfo variable_info;
    std::string variable_name = node->identifier->name;
    if (variable_info.type.baseType == bt_object)
        variable_info.type.objectClassName = ((ObjectTypeNode*)node -> type)->identifier->name;
    else
        variable_info.type.baseType = node->type->basetype;
    variable_info.size = 4;
    node -> visit_children(this);
    variable_info.offset = currentParameterOffset;
    currentVariableTable -> insert(std::pair<std::string,VariableInfo>(variable_name, variable_info));
    currentParameterOffset += 4;
}

void Symbol::visitDeclarationNode(DeclarationNode* node) {
    for (std::list<IdentifierNode*>::iterator iter = node -> identifier_list->begin(); iter!= node->identifier_list -> end(); iter++)
    {
        VariableInfo variable_info;
        std::string variable_name = (*iter)->name;
        if ( variable_info.type.baseType == bt_object)
            variable_info.type.objectClassName = ((ObjectTypeNode*)node->type)->identifier->name;
        else
            variable_info.type.baseType = node->type->basetype;
        variable_info.size = 4;
        node -> visit_children(this);
        variable_info.offset = currentLocalOffset;
        currentVariableTable -> insert(std::pair<std::string,VariableInfo>(variable_name, variable_info));
        currentLocalOffset -= 4;
    }
}

void Symbol::visitReturnStatementNode(ReturnStatementNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitAssignmentNode(AssignmentNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitCallNode(CallNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitIfElseNode(IfElseNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitForNode(ForNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitPrintNode(PrintNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitPlusNode(PlusNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitMinusNode(MinusNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitTimesNode(TimesNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitDivideNode(DivideNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitLessNode(LessNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitLessEqualNode(LessEqualNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitEqualNode(EqualNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitAndNode(AndNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitOrNode(OrNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitNotNode(NotNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitNegationNode(NegationNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitMethodCallNode(MethodCallNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitMemberAccessNode(MemberAccessNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitVariableNode(VariableNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitIntegerLiteralNode(IntegerLiteralNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitBooleanLiteralNode(BooleanLiteralNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitNewNode(NewNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitIntegerTypeNode(IntegerTypeNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitBooleanTypeNode(BooleanTypeNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitObjectTypeNode(ObjectTypeNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitNoneNode(NoneNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitIdentifierNode(IdentifierNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitIntegerNode(IntegerNode* node) {
    // WRITEME: Replace with code if necessary
}
