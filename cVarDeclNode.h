#pragma once

//************************
// cVarDeclNode.h
//
// Author: Emma Thompson
// emma.thompson@oit.edu
//
// Feb 9, 2017
//
//

#include "cAstNode.h"
#include "cExprNode.h"
#include "cSymbolTable.h"

extern g_SymbolTable cSymbolTable;

class cVarDeclNode : public cDeclNode
{
    public:
        cVarDeclNode(cSymbol *type, cSymbol *name) : cDeclNode()
        { 
            if(g_SymbolTable.FindInTable(name->GetName()) != nullptr)
            {
                SemanticError(string("Symbol ") + name->GetName() + string( "already in current scope"));
            }
            //if it's already defined outside the current scope
            else if (g_SymbolTable.Find(name->GetName()) != nullptr)
            {
                name = new cSymbol(name->GetName());
                g_SymbolTable.Insert(name);
                name->SetDecl(this);
            }
            //insert a new one, lang.y just made it
            else
            {
                g_SymbolTable.Insert(name);
                name->SetDecl(this);
            }
            
            AddChild(type);
            AddChild(name);
        }

        virtual cSymbol *GetName()
        {
            return static_cast<cSymbol *>(GetChild(1));
        }

        virtual cDeclNode *GetType()
        {
            return (static_cast<cSymbol *>(GetChild(0)))->GetDecl();
        }

        virtual bool IsVar()  {return true;}

        virtual string NodeType() { return string("var_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
