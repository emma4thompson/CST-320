#pragma once
//**************************************
// cDeclsNode.h
//
// Defines a class to represent a list of declarations.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2016
//

#include "cAstNode.h"
#include "cDeclNode.h"

class cDeclsNode : public cAstNode
{
    public:
        // param is the first decl in this decls
        cDeclsNode(cDeclNode *decl) : cAstNode()
        {
            AddChild(decl); 
            m_size = 0;
        }

        // Add a decl to the list
        void Insert(cDeclNode *decl)
        {
            AddChild(decl);
        }

        // return a particular decl from the list
        cDeclNode* GetDecl(int index)
        {
            return static_cast<cDeclNode*>(GetChild(index));
        }

        int GetSize()
        {
            return m_size;
        }

        void SetSize(int size)
        {
            m_size = size;
        }

        virtual string AttributesToString()
        {
            if(m_size == 0)
                return "";
            return " size=\"" + std::to_string(GetSize()) + "\"";
        }

        virtual string NodeType() { return string("decls"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

    protected:
        int m_size;
};
