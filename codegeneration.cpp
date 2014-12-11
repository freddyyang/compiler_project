#include "codegeneration.hpp"
using namespace std;
// CodeGenerator Visitor Functions: These are the functions
// you will complete to generate the x86 assembly code. Not
// all functions must have code, many may be left empty.
//
// NOTE: You only need to complete code for expressions,
// assignments, returns, and local variable space allocation.
// Refer to project description for exact details.

void CodeGenerator::visitProgramNode(ProgramNode* node) {

    cout<< "  .data" << endl;
    cout<< "  printstr: .asciz \"%d\n\"" << endl;
    cout<< "  .text" << endl;

    #if __APPLE__
        cout<< "  .globl _Main_main" << endl;
    #else
        cout<< "  .globl Main_main" << endl;
    #endif

    // WRITEME: Replace with code if necessary
    // Func Prolog -> visit_children -> Func Epilog
    //
    // Function Prologue:
    // 1. Push the current frame pointer value onto the stack
    // 2. Copy the stack pointer value into the frame pointer register
    // 3. Make space on the stack for local variables (decrement stack pointer)
    // 4. Push callee-save register values onto the stack
    //
    // Function Epilogue:
    // 1. Put return value in known register
    // 2. Pop callee-save register values from the stack and restore them
    // 3. Deallocate local variables by moving frame pointer value into stack pointer register
    // 4. Pop caller’s frame pointer value from the stack and put it in the frame pointer register
    // 5. Pop call site’s return address from the stack and jump to it
    // (In x86, the return value register is %eax and point 5 is handled by the ret instruction.)
    node -> visit_children(this);
}

void CodeGenerator::visitClassNode(ClassNode* node) {
    // WRITEME: Replace with code if necessary
    currentClassName = node -> identifier_1 ->name;
    currentClassInfo = (*classTable) [currentClassName];
    
    node -> visit_children(this);
}

void CodeGenerator::visitMethodNode(MethodNode* node) {
    // WRITEME: Replace with code if necessary
    currentMethodName = node ->identifier -> name;
    currentMethodInfo = currentClassInfo.methods[currentMethodName];

    cout << "  ##### method (func pro)" << endl;


    #if __APPLE__
        cout << "  _" << currentClassName << "_" << currentMethodName <<":"<<endl;
    #else
        cout << "  " << currentClassName << "_" << currentMethodName <<":"<<endl;
    #endif

    // 1. Push the current frame pointer value onto the stack
    cout << "  push %ebp" << endl;
    
    // 2. Copy the stack pointer value(esp) into the frame pointer register(ebp)
    cout << "  mov %esp, %ebp" << endl;
    
    // 3. Deallocate local variables by moving frame pointer value into stack pointer register
    cout << "  sub $"<< currentMethodInfo.localsSize <<", %esp" <<endl;

    // 4. Push callee-save register values onto the stack

    node -> visit_children(this); 
    // Function Epilogue:
    // 1. Put return value in known register
    // 2. Pop callee-save register values from the stack and restore them
    // 3. Deallocate local variables by moving frame pointer value into stack pointer register
    // 4. Pop caller’s frame pointer value from the stack and put it in the frame pointer register
    // 5. Pop call site’s return address from the stack and jump to it  
    // 
    // cout << "  ##### return states (func epi)" << endl;
    // cout << "  pop %eax" << endl;           // 1. Put return value in known register
    // cout << "  mov %ebp, %esp" <<endl;      // 2. Deallocate local variable space
    // cout << "  pop %ebp" <<endl;            // 3. Restore previous frame pointer value
    // cout << "  ret" <<endl;                 // 4. Pop return address and jump to it
}

void CodeGenerator::visitMethodBodyNode(MethodBodyNode* node) {
    // WRITEME: Replace with code if necessary
    node -> visit_children(this); 
}

void CodeGenerator::visitParameterNode(ParameterNode* node) {
    // WRITEME: Replace with code if necessary
    node -> visit_children(this); 
}

void CodeGenerator::visitDeclarationNode(DeclarationNode* node) {
    // WRITEME: Replace with code if necessary
    node -> visit_children(this); 
}

void CodeGenerator::visitReturnStatementNode(ReturnStatementNode* node) {
    // WRITEME: Replace with code if necessary
    node -> visit_children(this); 
    cout << "  ##### return states (func epi)" << endl;
    cout << "  pop %eax" << endl;           // 1. Put return value in known register
    cout << "  mov %ebp, %esp" <<endl;      // 2. Deallocate local variable space
    cout << "  pop %ebp" <<endl;            // 3. Restore previous frame pointer value
    cout << "  ret" <<endl;                 // 4. Pop return address and jump to it
}

void CodeGenerator::visitAssignmentNode(AssignmentNode* node) {
    // WRITEME: Replace with code if necessary
    node -> visit_children(this);
    cout << "  ##### assignment " << endl;
    cout << "  pop %eax" << endl;
    cout << "  mov %eax,"<< (currentMethodInfo.variables[node->identifier->name]).offset
    << "(%ebp)" << endl;
}

void CodeGenerator::visitCallNode(CallNode* node) {
    // WRITEME: Replace with code if necessary
     node -> visit_children(this);
}

// ############################# PROJ_6
void CodeGenerator::visitIfElseNode(IfElseNode* node) {

    //node -> visit_children(this); ?

    node -> expression -> accept(this);

    int labl_ifElse = nextLabel();

    cout << "  ### ifElse" << endl;
    cout << "  pop %eax"   << endl;     // pop out the expression?
    cout << "  mov $0, %ebx" <<endl;    // set ebx to False
    cout << "  je ELSE_"<< labl_ifElse << endl; //if false jumps to lable1 (means skip if to lable1)
    
    // IF:
    //# Visit and generate code for
    //# statements in true branch
    for (std::list<StatementNode*>::iterator iter = node -> statement_list_1 ->begin(); iter!= node-> statement_list_1 -> end(); iter++)
        (*iter)  -> accept(this);

    cout << "  jmp endIfELSE_" <<labl_ifElse << endl;    
    cout << "  ELSE_" << labl_ifElse << ":" <<endl; //instruction after if
    // ELSE:
    // CODE in ELSE part of IF-ELSE
    for (std::list<StatementNode*>::iterator iter = node -> statement_list_2 ->begin(); iter!= node-> statement_list_2 -> end(); iter++)
        (*iter)  -> accept(this);

    cout << "  endIfELSE_" << labl_ifElse << ":" << endl;    

}

// ############################# PROJ_6
void CodeGenerator::visitForNode(ForNode* node) {
    // WRITEME: Replace with code if necessary
}

// ############################# PROJ_6
void CodeGenerator::visitPrintNode(PrintNode* node) {
    // WRITEME: Replace with code if necessary
    node -> visit_children(this);
    std::cout << "  ##### PRINT" << std::endl;
    std::cout << "  push $printstr" << std::endl;
    std::cout << "  call printf" << std::endl;

}

void CodeGenerator::visitPlusNode(PlusNode* node) {
    // WRITEME: Replace with code if necessary
    node -> visit_children(this);
    std::cout << "  ##### ADD" << std::endl;
    std::cout << "  pop %ebx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  add %ebx, %eax" << std::endl;
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitMinusNode(MinusNode* node) {
    // WRITEME: Replace with code if necessary x(eax) - y(ebx)
    node->visit_children(this);
    std::cout << "  ##### Minus" << std::endl;
    std::cout << "  pop %ebx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  sub %ebx, %eax" << std::endl;
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitTimesNode(TimesNode* node) {
    // x(eax) * y(ebx) -> 
    node->visit_children(this);
    std::cout << "  ##### Times" << std::endl;
    std::cout << "  pop %ebx" << std::endl;
    std::cout << "  pop %eax" << std::endl;
    std::cout << "  imul %ebx, %eax" << std::endl;
    std::cout << "  push %eax" << std::endl;
}

void CodeGenerator::visitDivideNode(DivideNode* node) {
    // WRITEME: Replace with code if necessary numerator x(eax) / y(ebx) -> 
    node->visit_children(this);
    std::cout << "  ##### Divide" << std::endl;
    std::cout << "  pop %ebx" << std::endl; //y denom
    std::cout << "  pop %eax" << std::endl; //x numerator
    std::cout << "  cdq" << std::endl;
    std::cout << "  idiv %ebx" << std::endl;
    std::cout << "  push %eax" << std::endl;
}


// ############################# PROJ_6, maybeDone
void CodeGenerator::visitLessNode(LessNode* node) {

    node->visit_children(this);
    int labl_lessThan = nextLabel();

    cout << "  ### LessThan" << endl;
    cout << "  pop %eax" << endl;
    cout << "  pop %ebx" << endl;
    cout << "  cmp %eax, %ebx" << endl;
    cout << "  jl ifLess_" << labl_lessThan << endl;

    // if not less, false -> 0
    cout << "  push $0" << endl;
    cout << "  jmp endLessThan_" << labl_lessThan << endl;
 
    // if less, ifLess_lable1
    cout << "  ifLess_" << labl_lessThan << endl;
    cout << "  push $1" << endl;
    
    cout << "  endLessThan_" << labl_lessThan << ":" << endl;
}

// ############################# PROJ_6
void CodeGenerator::visitLessEqualNode(LessEqualNode* node) {

    node->visit_children(this);
    int labl_lessEqual = nextLabel();

    cout << "  ### LessEqual" << endl;
    cout << "  pop %eax" << endl;
    cout << "  pop %ebx" << endl;
    cout << "  cmp %eax, %ebx" << endl;
    cout << "  jle ifLessEql_" << labl_lessEqual << endl;

    // if not less, false -> 0
    cout << "  push $0" << endl;
    cout << "  jmp endLessEql_" << labl_lessEqual << endl;
 
    // if less, ifLess_lable1
    cout << "  ifLessEql_" << labl_lessEqual << ":" << endl;
    cout << "  push $1" << endl;
    
    cout << "  endLessEql_" << labl_lessEqual << ":" << endl;
}

// ############################# PROJ_6
void CodeGenerator::visitEqualNode(EqualNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
    int labl_Equal = nextLabel();

    cout << "  ### Equal" << endl;
    cout << "  pop %eax" << endl;
    cout << "  pop %ebx" << endl;
    cout << "  cmp %eax, %ebx" << endl;
    cout << "  je Equal_" << labl_Equal << endl;

    // if not less, false -> 0
    cout << "  push $0" << endl;
    cout << "  jmp endEql_" << labl_Equal << endl;
 
    // if less, ifLess_lable1
    cout << "  Equal_" << labl_Equal << endl;
    cout << "  push $1" << endl;
    
    cout << "  endEql_" << labl_Equal << ":" << endl;
}

// ############################# PROJ_6
void CodeGenerator::visitAndNode(AndNode* node) {
    node->visit_children(this);
    cout << "  pop %eax" <<endl;
    cout << "  pop %ebx" <<endl;
    cout << "  and %eax, %ebx" <<endl;
    cout << "  push %ebx" <<endl;
}

// ############################# PROJ_6
void CodeGenerator::visitOrNode(OrNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
    cout << "  pop %eax" <<endl;
    cout << "  pop %ebx" <<endl;
    cout << "  or %eax, %ebx" <<endl;
    cout << "  push %ebx" <<endl;
}

// ############################# PROJ_6, QUESTION, SAME AS NEG?
void CodeGenerator::visitNotNode(NotNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
    cout << "pop %eax" <<endl;
    cout << "not %eax" <<endl;
    cout << "push %eax" <<endl;
}

void CodeGenerator::visitNegationNode(NegationNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
    cout << "pop %eax" <<endl;
    cout << "neg %eax" <<endl;
    cout << "push %eax" <<endl;
}

// ############################# PROJ_6
void CodeGenerator::visitMethodCallNode(MethodCallNode* node) {
    // WRITEME: Replace with code if necessary
}

// ############################# PROJ_6
void CodeGenerator::visitMemberAccessNode(MemberAccessNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitVariableNode(VariableNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
    std::string Variable_Name = node -> identifier -> name;
    cout << "  ##### Variable " << endl; 
    cout << "  push " << currentMethodInfo.variables[Variable_Name].offset <<"(%ebp)" <<endl; 
}

void CodeGenerator::visitIntegerLiteralNode(IntegerLiteralNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
    cout << "  ##### IntegerLiteral" << endl;
    cout << "  push $" << node->integer->value << endl;
}

// ############################# PROJ_6
void CodeGenerator::visitBooleanLiteralNode(BooleanLiteralNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
    cout << "  ##### BooleanLiteral" << endl;
    cout << "  push $" << node->integer->value << endl;
}

// ############################# PROJ_6
void CodeGenerator::visitNewNode(NewNode* node) {
    // WRITEME: Replace with code if necessary
}

// ############################# PROJ_6
void CodeGenerator::visitIntegerTypeNode(IntegerTypeNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
}

// ############################# PROJ_6
void CodeGenerator::visitBooleanTypeNode(BooleanTypeNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
}

// ############################# PROJ_6
void CodeGenerator::visitObjectTypeNode(ObjectTypeNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
}

// ############################# PROJ_6
void CodeGenerator::visitNoneNode(NoneNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
}

// ############################# PROJ_6
void CodeGenerator::visitIdentifierNode(IdentifierNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
}

// ############################# PROJ_6
void CodeGenerator::visitIntegerNode(IntegerNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
}
