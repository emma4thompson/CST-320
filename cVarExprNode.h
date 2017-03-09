#pragma once
//**************************************
// cVarExprNode.h
//
// Defines AST node for a variable reference
//
// Inherits from cExprNode so variable refs can be used in expressions`
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2016
//

#include "cSymbol.h"
#include "cAstNode.h"
#include "cExprNode.h"
#include <vector>
#include <iostream>

class cVarExprNode : public cExprNode
{
    public:
        // param is the symbol for the variable
        cVarExprNode(cSymbol *name)
            : cExprNode()
        {
            AddChild(name);
        }

        // called for the fields in struct refs
        void AddElement(cSymbol *name)
        {
            AddChild(name);
        }

        void AddElement(cExprNode *index)
        {
            AddChild(index);
        }

        cSymbol* GetName() 
        {
            return static_cast<cSymbol*>(GetChild(0));
        }

        cDeclNode * GetDecl()
        {
            return GetName()->GetDecl();
        }

        int GetSize()
        {
            return m_size;
        }

        void SetSize(int size)
        {
            m_size = size;
        }

        int GetOffset()
        {
            return m_offset;
        }

        void SetOffset(int offset)
        {
            m_offset = offset;
        }

        int GetRowSize()
        {
            return m_rowSize;
        }

        void SetRowSize(int rowsize)
        {
            m_rowSize = rowsize;
        }

        virtual string AttributesToString()
        {
            if(GetName()->GetDecl()->GetType()->IsArray())
            {
                return " size=\"" + std::to_string(m_size) + "\" offset=\"" + std::to_string(m_offset) + "\" rowsizes=\"" + std::to_string(m_rowSize) + "\"";
            }
            else
            {
                return " size=\"" + std::to_string(m_size) + "\" offset=\"" + std::to_string(m_offset) + "\"";
            }
        }
        // return a string representation of the name of the var
        virtual string GetTextName()
        {
            string name("");
            cSymbol* sym;

            sym = GetName();

            name += sym->GetName();

            for (int ii=0; ii<NumItems(); ii++)
            {
                if (ItemIsIndex(ii))
                {
                    name += "[]";
                }
                else
                {
                    sym = GetElement(ii);
                    name += "." + sym->GetName();
                }
            }

            return name;
        }

        // return the type of the VarExpr. This includes dereferencing arrays
        virtual cDeclNode *GetType() 
        { 
            cDeclNode* decl = GetName()->GetDecl();
            if (decl == nullptr) return nullptr;

            cDeclNode* type = decl->GetType();

            if (type->IsArray())
            {
                return type->GetType(NumItems());
            }
            else
            {
                return type; 
            }
        }

        int NumItems() { return NumChildren() - 1; }

        bool ItemIsIndex(int index)
        {
            // if the dynamic cast fails, this item must be a cSymbol* for
            // a struct member
            return dynamic_cast<cExprNode*>(GetChild(index + 1)) != nullptr;
        }

        cSymbol* GetElement(int index)
        {
             return (cSymbol*)GetChild(index + 1);
        }

        cExprNode* GetIndex(int index)
        {
             return (cExprNode*)GetChild(index + 1);
        }

        virtual string NodeType() { return string("varref"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    
    protected:
        int m_size;
        int m_offset;
        int m_rowSize;
        //std::vector<int> m_rowSizes;
};
