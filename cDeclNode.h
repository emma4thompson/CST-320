#pragma once
//**************************************
// cDeclNode
//
// Defines base class for all declarations.
// Future labs will add features to this class.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2015
//

#include "cAstNode.h"

class cDeclNode : public cAstNode
{
    public:
        cDeclNode() : cAstNode() {}

        virtual bool IsArray()  { return false; }
        virtual bool IsStruct() { return false; }
        virtual bool IsType()   { return false; }
        virtual bool IsFunc()   { return false; }
        virtual bool IsVar()    { return false; }
        virtual bool IsFloat()  { return false; }
        virtual bool IsInt()    { return false; }
        virtual bool IsChar()   { return false; }

        virtual cSymbol* GetName() = 0;
        virtual cDeclNode *GetType() = 0;

        bool CanConvert(cDeclNode * right)
        {
            if(this->GetType() == right->GetType())
                return true;
            if(this->GetType()->IsFloat() && right->GetType()->IsInt())
                return true;
            if(this->GetType()->IsFloat() && right->GetType()->IsChar())
                return true;
            if(this->GetType()->IsInt() && right->GetType()->IsChar())
                return true;

            return false;
        }

};
