#pragma once
#include <iostream>
#include <string>

class cSemantics : public cVisitor
{
    public:
        cSemantics() : cVisitor()
        {}
        void SemanticError(cAstNode *node, std::string msg)
        {
            NumErrors++;
            node->SetHasError();
            std::cout << "ERROR: " << msg << " on line " << node->LineNumber() << "\n";
        }
        int GetNumErrors()
        {
            return NumErrors;
        }

        void VisitAllNodes(cAstNode * node)
        {
            node->Visit(this);
        }

        virtual void Visit(cVarExprNode * node)
        {
            if(node->ExprGetDecl() == nullptr && node->HasError() == false)
            {
                SemanticError(node, "Symbol " + node->GetName()->GetName() + " not defined");
            }
        }

        void Visit(cFuncExprNode * node)
        {
            if(node->ExprGetNode() != nullptr && node->HasError() == false)
            {
                if(node->ExprGetNode()->IsFunc())
                {
                    cFuncDeclNode* recentFunctionDecl = static_cast<cFuncDeclNode*>(node->ExprGetNode());
                    
                    
                    if(recentFunctionDecl != nullptr)
                    {
                        //A function exists with this name

                        //Check to see if func has stmts, if it doesnt, error
                        if(recentFunctionDecl->GetStmts() != nullptr)
                        {
                            if(recentFunctionDecl->GetNumParams( ) == node->GetNumParams())
                            {
                                bool isError;

                                for(int i = 0; i < node->GetNumParams(); i++)
                                {
                                    if(recentFunctionDecl->GetLocalParams()->GetParam(i)->GetType() != node->GetParamsList()->GetParam(i)->GetType())
                                        {
                                            if(node->GetParamsList()->GetParam(i)->GetType()->CanConvert(recentFunctionDecl->GetLocalParams()->GetParam(i)->GetType()) == false)
                                            isError = true;
                                        }
                                }
                                if(isError == true)
                                {
                                    SemanticError(node, node->GetName()->GetName() + " called with incompatible argument");
                                }
                            }
                            else
                            {
                                SemanticError(node, node->GetName()->GetName() + " called with wrong number of arguments");
                            }
                        }
                        else
                        {
                            SemanticError(node, "Function " + node->GetName()->GetName() + " is not fully defined");
                        }
                    }
                }
                else
                {
                    if(node->HasError() == false)
                    {
                        SemanticError(node, node->GetName()->GetName() + " is not a function");
                    }
                }
            }
            else
            {
                SemanticError(node, "Function " + node->GetName()->GetName() + " is not declared");
            }
        }

    private:
        int NumErrors = 0;
};
