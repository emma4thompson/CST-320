#pragma once

//************************
// cIfNode.h
//
// Author: Emma Thompson
// emma.thompson@oit.edu
//
// Feb 9, 2017
//
//

#include "cAstNode.h"
#include "cStmtNode.h"

class cIfNode : public cStmtNode
{
    public:
        cIfNode(cExprNode *exprnode, cStmtsNode *if1, cStmtsNode * else1) : cStmtNode()
        {
            AddChild(exprnode);
            AddChild(if1);
            AddChild(else1);
        }

        cIfNode(cExprNode *exprnode, cStmtsNode *if1) : cStmtNode()
        {
            AddChild(exprnode);
            AddChild(if1);
        }

        virtual string NodeType() { return string("if"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
