#pragma once

//**********************************
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
//


#include "cAstNode.h"
#include "cStmtNode.h"

class cReturnNode : public cStmtNode
{
    public:
        cReturnNode(cExprNode *exprnode) : cStmtNode()
        {
            AddChild(exprnode);
        }
        virtual string NodeType() { return string("return"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
