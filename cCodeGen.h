#pragma once
#include "emit.h"
#include "cVisitor.h"
#include <string>

class cCodeGen : public cVisitor
{
    public:
        cCodeGen(string fname) : cVisitor()
        {
            //starts output to langout
            InitOutput(fname.c_str());
        }
        
        void VisitAllNodes(cAstNode * node){ node->Visit(this); }
        
        ~cCodeGen()
        {
            //finishes langout output 
            FinalizeOutput();
        }
        
        void Visit(cProgramNode * node)
        {
            //sets up space for prog
            EmitString("ADJSP");
            EmitInt(node->GetBlock()->GetSize());
            EmitString("\n");

            VisitAllChildren(node);
        }
        
        void Visit(cPrintNode * node)
        {
            //calls Phil's print function
            VisitAllChildren(node);

            //pops first thing off stack
            EmitString("CALL @print\nPOP\nPOP\n");
        }
        
        void Visit(cIntExprNode * node)
        {
            //pushes an int to the stack
            EmitString("PUSH ");
            EmitInt(node->GetValue());
            EmitString("\n");
        }

        void Visit(cBinaryExprNode * node)
        {
            //visits kiddos of an expr
            node->GetLeft()->Visit(this);
            node->GetRight()->Visit(this);
            node->GetOp()->Visit(this);
        }

        void Visit(cVarExprNode * node)
        {
            //if it's an int
            if(node->GetName()->GetDecl()->GetType()->IsInt())
            {
                //pushes int onto stack
                EmitString("PUSHVAR ");
                EmitInt(node->GetName()->GetDecl()->GetOffset());
                EmitString("\n");
            }
            //if it's a char
            else if(node->GetName()->GetDecl()->GetType()->IsChar())
            {
                //pushes char onto stack
                EmitString("PUSHCVAR ");
                EmitInt(node->GetName()->GetDecl()->GetOffset());
                EmitString("\n");
            }
            //if it's an array
            else if(node->GetName()->GetDecl()->GetType()->IsArray())
            {
                //pushes array onto stack
                EmitString("PUSHFP\n");

                for(int c = 0; c < node->GetAmtRows(); c++)
                {
                    //calculating array size
                    EmitString("PUSH ");
                    EmitInt(node->GetOffset());
                    EmitString("\nPLUS\n");
                
                    node->GetIndex(c)->Visit(this);
                
                    EmitString("PUSH ");
                    EmitInt(node->GetRowSizeAtIndex(c));
                    EmitString("\nTIMES\nPLUS\n");
                }
                
                //if it's an int
                if(node->GetType()->GetBaseType()->IsInt())
                    EmitString("PUSHVARIND\n");
                //if it's a char
                else
                    EmitString("PUSHCVARIND\n");
            }
        }
        
        void Visit(cAssignNode * node)
        {
            node->GetExpr()->Visit(this);

            //if it's an int
            if(node->GetLVal()->GetName()->GetDecl()->GetType()->IsInt())
            {
                EmitString("POPVAR ");
                EmitInt(node->GetLVal()->GetOffset());
                EmitString("\n");
            }
            //if it's a char
            else if(node->GetLVal()->GetName()->GetDecl()->GetType()->IsChar())
            {
                EmitString("POPCVAR ");
                EmitInt(node->GetLVal()->GetOffset());
                EmitString("\n");
            }
            //if it's an array
            else if(node->GetLVal()->GetName()->GetDecl()->GetType()->IsArray())
            {
                EmitString("PUSHFP\n");
            
                for(int c = 0; c < node->GetLVal()->GetAmtRows(); c++)
                {
                    EmitString("PUSH ");
                    EmitInt(node->GetLVal()->GetOffset());
                    EmitString("\nPLUS\n");
            
                    node->GetLVal()->GetIndex(c)->Visit(this);
            
                    EmitString("PUSH ");
                    EmitInt(node->GetLVal()->GetRowSizeAtIndex(c));
                    EmitString("\nTIMES\nPLUS\n");
                }
            
                //int
                if(node->GetLVal()->GetType()->GetBaseType()->IsInt())
                    EmitString("POPVARIND\n");
                //char
                else
                    EmitString("POPCVARIND\n");
            }
        }

        void Visit(cOpNode * node)
        {
            switch(node->GetOperator())
            {
                case    '+':
                    EmitString("PLUS");
                    break;
                case    '-':
                    EmitString("MINUS");
                    break;
                case    '/':
                    EmitString("DIVIDE");
                    break;
                case    '*':
                    EmitString("TIMES");
                    break;
                case    EQUALS:
                    EmitString("EQ");
                    break;
                case    OR:
                    EmitString("OR");
                    break;
                case    AND:
                    EmitString("AND");
                    break;
                case    NOTEQUALS:
                    EmitString("NE");
                    break;
                case    '%':
                    EmitString("MOD");
                    break;
                default:
                    break;
            }
        
            EmitString("\n");
        }

        void Visit(cIfNode * node)
        {
            string L1 = GenerateLabel();
            string L2 = GenerateLabel();

            //if condition's false
            node->GetCondition()->Visit(this);
            EmitString("JUMPE @" + L1 + "\n");
            //if it's true do the thing
            node->GetIfStmt()->Visit(this);
            EmitString("JUMP @" + L2 + "\n");
            
            EmitString(L1 + ":\n");
            
            //is there an else?
            if(node->GetElseStmt())
            {
                node->GetElseStmt()->Visit(this);
            }
            
            EmitString(L2 + ":\n");
        }
        
        void Visit(cWhileNode * node)
        {
            string L1 = GenerateLabel();
            string L2 = GenerateLabel();
        
            //if while condition is false
            EmitString(L1 + ":\n");
            node->GetCondition()->Visit(this);
            EmitString("JUMPE @" + L2 + "\n");
            //execute while thingy
            node->GetWhileStmt()->Visit(this);
            EmitString("JUMP @" + L1 + "\n");
        
            EmitString(L2 + ":\n");
        }
        
        void Visit(cFuncExprNode * node)
        {
            //if there aren't any params
            if(node->GetParams() != nullptr)
                node->GetParams()->Visit(this);

            //call the function
            EmitString("CALL @" + node->GetName()->GetName() + "\n");
            
            //if there are params
            if(node->GetParams() != nullptr)
            {
                //pop arguments off stack
                EmitString("POPARGS ");
                EmitInt(node->GetParams()->GetSize());
                EmitString("\n");
            }
        }

        void Visit(cParamListNode * node)
        {
            //visit params of function call
            for(int c = node->NumChildren()-1; c >= 0; c--)
            {
                node->GetParam(c)->Visit(this);
            }
        }

        void Visit(cReturnNode * node)
        {
            //return
            VisitAllChildren(node);
            EmitString("RETURNV\n");
        }

        void Visit(cFuncDeclNode * node)
        {
            //if no stmts
            if(node->GetStmts() != nullptr)
            {
                //output function
                StartFunctionOutput(node->GetName()->GetName());
                    
                //makes space for function
                EmitString(node->GetName()->GetName() + ":\n");
                EmitString("ADJSP ");
                EmitInt(node->GetSize());
                EmitString("\n");
                node->GetStmts()->Visit(this);

                EndFunctionOutput();
            }
        }
};
