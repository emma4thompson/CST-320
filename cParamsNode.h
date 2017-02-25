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
#include "cDeclsNode.h"

class cParamsNode : public cDeclsNode
{
    public:
        cParamsNode(cDeclNode *multiple) : cDeclsNode(multiple)
        {}
        void Insert(cDeclNode *multiple)
        {
            AddChild(multiple);
        }

        int GetNumParams()
        {
            return NumChildren();
        }

        cDeclNode * GetParam(int index)
        {
            return static_cast<cDeclNode *>(GetChild(index));
        }

        virtual string NodeType() { return string("args"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
