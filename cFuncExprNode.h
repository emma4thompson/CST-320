#pragma once

//************************
// cFuncExprNode.h
//
// Author: Emma Thompson
// emma.thompson@oit.edu
//
// Feb 9, 2017
//
//

#include "cExprNode.h"
#include "cParamListNode.h"

class cFuncExprNode : public cExprNode
{
    public:
        cFuncExprNode(cSymbol *name, cParamListNode *paramlist) : cExprNode()
        {
            AddChild(name);
            AddChild(paramlist);
        }

        virtual cDeclNode * GetType()
        {
            return static_cast<cSymbol*>(GetChild(0))->GetDecl()->GetType();
        }

        int GetNumParams()
        {
            if(GetChild(1) != nullptr)
            {
                return static_cast<cParamListNode*>(GetChild(1))->NumParamsInList();
            }
            else
                return 0;
        }
        cSymbol* GetName()
        {
            return static_cast<cSymbol*>(GetChild(0));
        }
        cDeclNode * ExprGetNode()
        {
            return GetName()->GetDecl();
        }
        cParamListNode * GetParamsList()
        {
            return static_cast<cParamListNode*>(GetChild(1));
        }

        virtual string NodeType() { return string("funcCall"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
