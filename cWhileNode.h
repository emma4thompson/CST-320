#pragma once

//************************
// cWhileNode.h
//
// Author: Emma Thompson
// emma.thompson@oit.edu
//
// Feb 9, 2017
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
