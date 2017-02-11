#pragma once

//************************
// cParamsNode.h
//
// Author: Emma Thompson
// emma.thompson@oit.edu
//
// Feb 9, 2017
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
