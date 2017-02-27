#pragma once

//************************
// cVarExprNode.h
//
// Author: Emma Thompson
// emma.thompson@oit.edu
//
// Feb 9, 2017
//
//

#include "cExprNode.h"

class cVarExprNode : public cExprNode
{
    public:
        cVarExprNode(cSymbol *sym) : cExprNode()
        {
            AddChild(sym);
        }

        virtual cDeclNode * GetType()
        {
            return (static_cast<cSymbol *>(GetChild(0)))->GetDecl(); 
        }

        cDeclNode * ExprGetDecl()
        {
            return GetName()->GetDecl();
        }
       
        virtual cSymbol *GetName()
        {
            return static_cast<cSymbol *>(GetChild(0));
        }
            
         string NodeType() { return string("varref"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }



};
