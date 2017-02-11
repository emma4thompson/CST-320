#pragma once

//************************
// cArrayDeclNode.h
//
// Author: Emma Thompson
// emma.thompson@oit.edu
//
// Feb 9, 2017
//

#include "cSymbol.h"
#include "cDeclNode.h"

class cArrayDeclNode : public cDeclNode
{
    public:
        cArrayDeclNode(cSymbol *type, int count, cSymbol *name) : cDeclNode()
        {   
            m_count = count;

            if (g_SymbolTable.Find(name->GetName()) != nullptr)
            {
                name = new cSymbol(name->GetName());
            }

            name->setType();

            g_SymbolTable.Insert(name);

            AddChild(type);
            AddChild(name);
    
        }
        
        virtual string AttributesToString()
        {
            string result(" count='");
            result += std::to_string(m_count);
            result += "'";
            return result;
        }
        
        virtual string NodeType() { return string("array_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    
    protected:
        int m_count;

};
