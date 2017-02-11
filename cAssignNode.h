#pragma once

//************************
// cAssignNode.h
//
// Author: Emma Thompson
// emma.thompson@oit.edu
//
// Feb 9, 2017
//
//

#include "cStmtNode.h"

class cAssignNode : public cStmtNode
{
    public:
        cAssignNode (cVarExprNode *var, cExprNode *expr)
        {
            AddChild(var);
            AddChild(expr);
        }
        virtual string NodeType() { return string("assign"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
