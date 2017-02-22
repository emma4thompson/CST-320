       
#include "cBaseTypeNode.h"
#include "cSymbolTable.h"

extern cSymbolTable g_SymbolTable;

cBaseTypeNode::cBaseTypeNode(string name, int size, bool isFloat) : cDeclNode()
{
    m_name = name;  
    m_size = size;
    m_isFloat = isFloat;
}

cDeclNode * cBaseTypeNode::GetType()
{
    return g_SymbolTable.Find(m_name)->GetDecl();
}

cSymbol * cBaseTypeNode::GetName()
{
    return g_SymbolTable.Find(m_name);
}

bool cBaseTypeNode::IsType() {return true;}
string cBaseTypeNode::NodeType() { return string("base_type"); }
void cBaseTypeNode::Visit(cVisitor *visitor) { visitor->Visit(this); }

