//**************************************
// cSymbol.cpp
//
// Defines class used to represent symbols.
// Later labs will add features to this class.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Feb. 11, 2017
//

#include "cSymbol.h"
#include "cDeclNode.h"
#include <string>

using std::string;

        // param is name of symbol
cSymbol::cSymbol(string name) : cAstNode()
        {
            m_id = ++nextId;        // get next available ID
            m_name = name;
            m_decl = nullptr;
        }

        // return name of symbol
        string cSymbol::GetName() { return m_name; }
        
        // Get/Set the decl associated with this symbol
        cDeclNode * cSymbol::GetDecl() { return m_decl; }
        void cSymbol::SetDecl(cDeclNode *decl) { m_decl = decl; }

        // return attributes for ToString()
        string cSymbol::AttributesToString()
        {
            string result(" id=\"");
            result += std::to_string(m_id) + "\"";
            result += " name=\"" + m_name + "\"";
            if (m_decl != nullptr)
            {
                result += " decl=\"" + std::to_string(m_decl->GetName()->m_id);
                result +=  "\"";
            }
            return result;
        }

        // Node type for ToString()
        string cSymbol::NodeType() { return string("sym"); }

        // standard visitor
        void cSymbol::Visit(cVisitor *visitor) { visitor->Visit(this); }

