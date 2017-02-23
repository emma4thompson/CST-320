#pragma once
//**************************************
// cSymbol.h
//
// Defines class used to represent symbols.
// Later labs will add features to this class.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Feb. 11, 2017
//

#include <string>

using std::string;

#include "cAstNode.h"
//#include "cDeclNode.h"

class cSymbol : public cAstNode
{
    public:
        // param is name of symbol
        cSymbol(string name);

        // return name of symbol
        string GetName();
        
        // Get/Set the decl associated with this symbol
        cDeclNode *GetDecl();
        void SetDecl(cDeclNode *decl);

        // return attributes for ToString()
        virtual string AttributesToString();

        // Node type for ToString()
        virtual string NodeType();

        // standard visitor
        virtual void Visit(cVisitor *visitor);

    protected:
        static long long nextId;        // Next avail symbol ID
        long long m_id;                 // Unique ID for this symbol
        string m_name;                  // name of symbol
        cDeclNode *m_decl;              // declaration of this symbol
};
