#pragma once

//************************
// ciFloatExprNode.h
//
// Author: Emma Thompson
// emma.thompson@oit.edu
//
// Feb 9, 2017
//
//

#include "cAstNode.h"
#include "cExprNode.h"

class cFloatExprNode : public cExprNode
{
    public:
        cFloatExprNode(float value) : cExprNode()
        {
            m_value = value;
        }

        virtual string AttributesToString()
        {
            return " value=\"" + std::to_string(m_value) + "\"";
        }

        virtual cDeclNode * GetType()
        {
            return g_SymbolTable.Find("float")->GetDecl();
        }

        virtual string NodeType() { return string("float"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        float m_value;
};
