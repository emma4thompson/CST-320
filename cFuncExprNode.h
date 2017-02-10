#pragma once
//*****************************
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
#include "cParamListNode.h"

class cFuncExprNode : public cExprNode
{
    public:
        cFuncExprNode(cSymbol *name, cParamListNode *paramlist) : cExprNode()
        {
            AddChild(name);
            AddChild(paramlist);
        }
        virtual string NodeType() { return string("funcCall"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
