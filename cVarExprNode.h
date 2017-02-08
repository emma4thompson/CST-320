#pragma once

//************************************
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
//


#include "cExprNode.h"

class cVarExprNode : public cExprNode
{
    public:
        cVarExprNode(cSymbol *sym)
        {
            AddChild(sym);
        }
        virtual string NodeType() { return string("varref"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
