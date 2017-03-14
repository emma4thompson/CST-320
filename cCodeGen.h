#pragma once

#include "cVisitor.h"
#include "emit.h"
#include <string>

using std::string;

class cCodeGen : public cVisitor
{
    public:
        cCodeGen(string fname) : cVisitor()
        {
            InitOutput(fname.c_str());
        }

        void VisitAllNodes(cAstNode * node)
        {
            node->Visit(this);
        }
        void Vist(cProgramNode* node)
        {
            EmitString("ADJSP");
            EmitInt(node->GetBlock()->GetSize());
            EmitString("\n");
            VisitAllChildren(node);
        }
               
        void Visit(cPrintNode* node)
        {
            VisitAllChildren(node);
            EmitString("CALL @print\n");
            EmitString("POP\nPOP\n");
        }
        void Visit(cIntExprNode * node)
        {
            EmitString("PUSH ");
            EmitInt(node->GetValue());
            EmitString("\n");
        }
        void Visit(cReturnNode * node)
        {
            VisitAllChildren(node);
            EmitString("RETURNV\n");
        }
        void Visit(cVarExprNode* node)
        {
            if(node->GetName()->GetDecl()->GetType()->IsArray())
            {

            }
            else if(node->GetName()->GetDecl()->GetType()->IsChar())
            {
                EmitString("PUSHCVAR ");
                EmitInt(node->GetName()->GetDecl()->GetOffset());
                EmitString("\n");
            }
            else if(node->GetName()->GetDecl()->GetType()->IsInt())
            {
                EmitString("PUSHVAR ");
                EmitInt(node->GetName()->GetDecl()->GetOffset());
                EmitString("\n");
            }
        }
        void Visit(cBinaryExprNode* node)
        {
            node->GetLeft()->Visit(this);
            node->GetRight()->Visit(this);
            node->GetOp()->Visit(this);
        }
        void Visit(cIfNode* node)
        {
            //Labels for skipping stmts
            string labelA = GenerateLabel();
            string labelB = GenerateLabel();
            
            node->GetCondition()->Visit(this);
            //If condition fails, jump to else/ end
            EmitString("JUMPE @" + labelA + "\n");
            node->GetIfCode()->Visit(this);
            //Jump to end
            EmitString("JUMP @" + labelB + "\n");
            //Destination labelA
            EmitString(labelA + ":\n");
            if(node->GetElseCode() != nullptr) {node->GetElseCode()->Visit(this);}
            //Destination labelB
            EmitString(labelB + ":\n");
        }
        ~cCodeGen()
        {
            FinalizeOutput();
        }
};
