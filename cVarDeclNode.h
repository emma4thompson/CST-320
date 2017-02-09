#pragma once

//************************
//
//
//
//
//
//
//
//
//
//
//

#include "cAstNode.h"
#include "cExprNode.h"

class cVarDeclNode : public cDeclNode
{
    public:
        cVarDeclNode(cSymbol *type, cSymbol *name) : cDeclNode()
        {
            if (g_SymbolTable.Find(name->GetName()) != nullptr)
            {
                name = new cSymbol(name->GetName());
            }
            
            g_SymbolTable.Insert(name);

            AddChild(type);
            AddChild(name);
        }
        
        virtual string NodeType() { return string("var_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
