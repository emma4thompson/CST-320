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
            //starts langout.sl file
            InitOutput(fname.c_str());
        }

        void VisitAllNodes(cAstNode * node)
        {
            //visits each visit aha
            node->Visit(this);
        }
        
        void Vist(cProgramNode * node)
        {
            //allocates memory for prog to run
            EmitString("ADJSP");
            EmitInt(node->GetBlock()->GetSize());
            EmitString("\n");
        
            VisitAllChildren(node);      
        }
               
        void Visit(cPrintNode * node)
        {
            //calls Phil's print function on top elem of stack
            VisitAllChildren(node);
        
            EmitString("CALL @print\n");
            EmitString("POP\nPOP\n");
        }
        
        void Visit(cIntExprNode * node)
        {
            //pushes number onto stack
            EmitString("PUSH ");
            EmitInt(node->GetValue());
            EmitString("\n");
        }
        
        void Visit(cReturnNode * node)
        {
            VisitAllChildren(node);
        
            //pushes RETURNV onto stack for end of a function
            EmitString("RETURNV\n");
        }
        
        void Visit(cVarExprNode * node)
        {
            //if var is array
            if(node->GetName()->GetDecl()->GetType()->IsArray())
            {

            }
            //if var is char
            else if(node->GetName()->GetDecl()->GetType()->IsChar())
            {
                //pushed char var onto stack
                EmitString("PUSHCVAR ");
                EmitInt(node->GetName()->GetDecl()->GetOffset());
                EmitString("\n");
            }
            //if var is int
            else if(node->GetName()->GetDecl()->GetType()->IsInt())
            {
                //pushes int var onto stack
                EmitString("PUSHVAR ");
                EmitInt(node->GetName()->GetDecl()->GetOffset());
                EmitString("\n");
            }
        }
        
        void Visit(cWhileNode * node)
        {
            string labelA = GenerateLabel();
            string labelB = GenerateLabel();

            EmitString(labelA + ":\n");
            node->GetCondition()->Visit(this);
            EmitString("JUMPE @" + labelB + "\n");
            node->GetWhileStmt()->Visit(this);
            EmitString("JUMP @" + labelA + "\n");
            EmitString(labelB + ":\n");
        }

        //sets up binary expresion by visiting children of binary expr node
        void Visit(cBinaryExprNode * node)
        {
            //pushes them on in postOp order
            node->GetLeft()->Visit(this);
            node->GetRight()->Visit(this);
            node->GetOp()->Visit(this);
        }

        void Visit(cAssignNode * node)
        {
            node->GetExpr()->Visit(this);

            if(node->GetLVal()->GetName()->GetDecl()->GetType()->IsChar())
            {
                //If this is a char
                EmitString("POPCVAR ");
                EmitInt(node->GetLVal()->GetOffset());
                EmitString("\n");
            }
            else if(node->GetLVal()->GetName()->GetDecl()->GetType()->IsInt())
            {
                //If this is an int
                EmitString("POPVAR ");
                EmitInt(node->GetLVal()->GetOffset());
                EmitString("\n");
            }
            else if(node->GetLVal()->GetName()->GetDecl()->GetType()->IsArray())
            {
                //Later
            }
        }
        
        void Visit(cIfNode * node)
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
            if(node->GetElseCode() != nullptr) 
            {
                node->GetElseCode()->Visit(this);
            }
            
            //Destination labelB
            EmitString(labelB + ":\n");
        }
        
        void Visit(cParamListNode * node)
        {
            int numToVisit = node->NumChildren() -1;
            for(int i = numToVisit; i >=0 ; i--)
            {
                node->GetParam(i)->Visit(this);
            }
        }

        
        ~cCodeGen()
        {
            FinalizeOutput();
        }
};
