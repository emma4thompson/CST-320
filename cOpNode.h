#pragma once
//**************************************
// cOpNode.h
//
// Class for an operator (e.g. + - etc.)
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2016
//

#include "cAstNode.h"
#include "langparse.h"

class cOpNode : public cAstNode
{
    public:
        cOpNode(int op) : cAstNode()
        {
            m_op = op;
        }
        int GetOperator(){return m_op; }
        virtual string NodeType()       { return "op"; }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
        virtual string AttributesToString()   
        { 
            string result(" value='");

            switch (m_op)
            {
                case EQUALS:
                    result += "==";
                    break;
                case OR:
                    result += "||";
                    break;
                case AND:
                    result += "&&";
                    break;
                case NOTEQUALS:
                    result += "!=";
                    break;
                default:
                    result += (char)m_op;
                    break;
            }

            result += "'";

            return result;
        }
    protected:
        int m_op;      // the operand
};

