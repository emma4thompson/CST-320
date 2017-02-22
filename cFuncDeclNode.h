#pragma once

//************************
// cFuncDeclNode.h
//
// Author: Emma Thompson
// emma.thompson@oit.edu
//
// Feb 9, 2017
//
//

#include "cDeclNode.h"
#include "cParamsNode.h"
#include "cStmtsNode.h"
#include "cSymbol.h"
#include "cAstNode.h"

class cFuncDeclNode : public cDeclNode
{
    public:
        cFuncDeclNode(cSymbol *type, cSymbol *name) : cDeclNode()
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

            AddChild(type);
            AddChild(name);
            AddChild(nullptr);
            AddChild(nullptr);
            AddChild(nullptr);
        }

        void AddType(cSymbol *type)
        {
            SetChild(0, type);
        }

        void AddID(cSymbol *id)
        {
            SetChild(1, id);
        }

        void AddParams(cParamsNode *params)
        {
            SetChild(2, params);
        }

        void AddDecls(cDeclsNode *locals)
        {
            SetChild(3, locals);
        }

        void AddStmts(cStmtsNode *stmts)
        {
            SetChild(4, stmts);
        }

        virtual cSymbol *GetName()
        {
            return static_cast<cSymbol *>(GetChild(1));
        }

        virtual cDeclNode *GetType()
        {
            return this;
        }

        virtual bool IsFunc()  {return true;}

        virtual string NodeType() { return string("func"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};

    



