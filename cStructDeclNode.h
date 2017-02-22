#pragma once

//************************
// cStructDeclNode.h
//
// Author: Emma Thompson
// emma.thompson@oit.edu
//
// Feb 9, 2017
//
//

#include "cDeclNode.h"

class cStructDeclNode : public cDeclNode
{
    public:
        cStructDeclNode(cDeclsNode *decls, cSymbol *name) : cDeclNode()
        {
            if (g_SymbolTable.Find(name->GetName()) != nullptr)
            {
                name = new cSymbol(name->GetName());
                g_SymbolTable.Insert(name);
                name->SetDecl(this);
            }
            else
            {
                g_SymbolTable.Insert(name);
                name->SetDecl(this);
            }

            AddChild(decls);
            AddChild(name);
        }

        virtual cSymbol *GetName()
        {
            return static_cast<cSymbol *>(GetChild(1));
        }

        virtual cDeclNode *GetType()
        {
            return this;
        }

        virtual bool IsType()   {return true;}
        virtual bool IsStruct()  {return true;}
        
        virtual string NodeType() { return string("struct_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
