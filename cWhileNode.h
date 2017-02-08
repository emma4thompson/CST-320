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
//


#include "cStmtNode.h"

class cWhileNode : public cStmtNode
{
    public:
        cWhileNode (cExprNode *exprnode, cStmtNode *stmtnode)
        {
            AddChild(exprnode);
            AddChild(stmtnode);
        }

        virtual string NodeType() { return string("while"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
