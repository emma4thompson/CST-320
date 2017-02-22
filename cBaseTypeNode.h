#pragma once

//*********************
//
//  cBaseTypeNode.h
//
//  Emma Thompson
//
//  Feb 16, 17
//

#include "cDeclNode.h"

using std::string;

class cBaseTypeNode : public cDeclNode
{
    public:
       cBaseTypeNode(string name, int size, bool isFloat);
       virtual cDeclNode *GetType();
       virtual cSymbol *GetName();
       virtual bool IsType();
       virtual string NodeType();
       virtual void Visit(cVisitor *visitor);

    
    private:
       string m_name;
       int m_size;
       bool m_isFloat;
};
