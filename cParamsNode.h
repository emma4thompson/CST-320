#pragma once

//**********************
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
#include "cDeclNode.h"

class cParamsNode : public cAstNode
{
    public:
        cParamsNode(cDeclNode *multiple) : cAstNode()
        {
            AddChild(multiple);
        }
        void Insert(cDeclNode *multiple)
        {
            AddChild(multiple);
        }

    virtual string NodeType() { return string("args"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
