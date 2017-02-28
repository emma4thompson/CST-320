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

        cExprNode * GetLeft()
        {
            return static_cast<cExprNode *>(GetChild(0));
        }

        cExprNode * GetRight()
        {
            return static_cast<cExprNode *>(GetChild(2));
        }

        virtual cDeclNode * GetType()
        {
            if(GetLeft()->GetType() == GetRight()->GetType())
               return GetLeft()->GetType();
            if(GetLeft()->GetType()->IsFloat() && GetRight()->GetType()->IsInt())
                return GetLeft()->GetType();
            if(GetLeft()->GetType()->IsFloat() && GetRight()->GetType()->IsChar())
                return GetLeft()->GetType();
            if(GetLeft()->GetType()->IsInt() && GetRight()->GetType()->IsChar())
                return GetLeft()->GetType();
            return GetRight()->GetType();
        }

        virtual string NodeType() { return string("expr"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

};
