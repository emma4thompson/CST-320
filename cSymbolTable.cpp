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

cSymbolTable::cSymbolTable()
{
    IncreaseScope();
}

cSymbolTable::symbolTable_t * cSymbolTable::IncreaseScope()
{
    symbolTable_t *table = new symbolTable_t();
    m_SymbolTable.push_front(table);

    return table;
}

cSymbolTable::symbolTable_t * cSymbolTable::DecreaseScope()
{
    m_SymbolTable.pop_front();
    
    return m_SymbolTable.front();
}

void cSymbolTable::Insert(cSymbol *sym)
{
    pair<string, cSymbol*> new_val(sym->GetName(), sym);
    m_SymbolTable.front()->insert(new_val);
}

cSymbol * cSymbolTable::Find(string name)
{
    cSymbol *sym = nullptr;

    list<symbolTable_t *>::iterator it = m_SymbolTable.begin();

    while (it != m_SymbolTable.end())
    {
        sym = FindInTable(*it, name);
        if (sym != nullptr) return sym;
            it++;
                                                                                       }
    return nullptr;
}

cSymbol * cSymbolTable::FindLocal(string name)
{
    return FindInTable(m_SymbolTable.front(), name);
}

cSymbol * cSymbolTable::FindInTable(symbolTable_t *table, string& name)
{
    symbolTable_t::const_iterator got = table->find(name);

    if (got == table->end())
        return nullptr;
    else
        return got->second;
}



