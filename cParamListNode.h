#pragma once

//************************
// cParamListNode.h
//
// Author: Emma Thompson
// emma.thompson@oit.edu
//
// Feb 9, 2017
//
//

#include "cExprNode.h"
#include "cAstNode.h"

class cParamListNode : public cAstNode
{
    public:
        cParamListNode(cExprNode *multiple) : cAstNode()
        {
            AddChild(multiple);
        }
        void Insert(cExprNode *multiple)
        {
            AddChild(multiple);
        }
        int NumParamsInList()
        {
            return this->NumChildren();
        }
        cExprNode * GetParam(int index)
        {
            return static_cast<cExprNode*>(GetChild(index));
        }
    virtual string NodeType() { return string("params"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
