#include "cSymbolTable.h"
#include "cBaseTypeNode.h"

void cSymbolTable::insertSym()
{
    cSymbol * char_sym = new cSymbol("char");
    char_sym->SetDecl(new cBaseTypeNode("char", 1, false));
    Insert(char_sym);

    //int and float
    cSymbol * int_sym = new cSymbol("int");
    int_sym->SetDecl(new cBaseTypeNode("int", 4, false));
    Insert(int_sym);
    
    cSymbol * float_sym = new cSymbol("float");
    float_sym->SetDecl(new cBaseTypeNode("float", 8, true));
    Insert(float_sym);
}

