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

class cFuncDeclNode : public cDeclNode
{
    public:
        cFuncDeclNode(cSymbol *type, cSymbol *name) : cDeclNode()
        {
            cSymbol* localName = g_SymbolTable.FindLocal(name->GetName());
            
            //doesn't exist in current inner scope
            if (localName == nullptr)
            {
                //already declared somewhere in the program
                if (g_SymbolTable.Find(name->GetName()) != nullptr)
                {
                    name = new cSymbol(name->GetName());
                }

                g_SymbolTable.Insert(name);
                name->SetDecl(this);
        
                AddChild(type);
                AddChild(name);
                AddChild(nullptr);
                AddChild(nullptr);
                AddChild(nullptr);
        
            }
            else
            {
                if(!IsFunc())
                {
                    SemanticError(name->GetName() + string(" previously declared as other than a function"));
                    //adding children because we're creating a new function 
                    //because what we just found WASN'T a function
                    AddChild(type);
                    AddChild(name);
                    AddChild(nullptr);
                    AddChild(nullptr);
                    AddChild(nullptr);
                }

                //old_decl is a function
                cFuncDeclNode * old_decl = dynamic_cast<cFuncDeclNode*>(localName->GetDecl());

                if(old_decl->GetReturnType()->GetDecl() != type->GetDecl())
                {
                    SemanticError(name->GetName() + string(" previously declared with different return type"));
                    AddChild(type);
                    AddChild(name);
                    AddChild(nullptr);
                    AddChild(nullptr);
                    AddChild(nullptr);
                }
                else
                {
                    name->SetDecl(this);
                    m_children = old_decl->m_children;
                }
            }
//            AddChild(type);
//            AddChild(name);
//            AddChild(nullptr);
//            AddChild(nullptr);
//            AddChild(nullptr);

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

        virtual cSymbol *GetReturnType()
        {
            return static_cast<cSymbol*>(GetChild(0));
        }

        virtual bool IsFunc()  {return true;}

        virtual string NodeType() { return string("func"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};

    



