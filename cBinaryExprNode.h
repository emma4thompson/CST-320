#pragma once

//************************
// cBinaryExprNode.h
//
// Author: Emma Thompson
// emma.thompson@oit.edu
//
// Feb 9, 2017
//
//

#include "cExprNode.h"

class cBinaryExprNode : public cExprNode
{
    public:
        cBinaryExprNode(cExprNode *expr1, cOpNode *op, cExprNode *expr2 )
        {
            AddChild(expr1);
            AddChild(op);
            AddChild(expr2);
        }
        virtual string NodeType() { return string("expr"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

};
