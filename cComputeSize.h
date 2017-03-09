#pragma once

#include <iostream>
#include "cVisitor.h"
#include "cSymbolTable.h"

class cComputeSize : public cVisitor
{
    public:
        cComputeSize() : cVisitor()
        {
            m_highWaterMark = 0;
            m_offset = 0;
            m_tempSize = 0;
        }

        void SetHighWater(int highWaterMark)
        {
            if(highWaterMark > m_highWaterMark)
                m_highWaterMark = highWaterMark;
        }

        void Visit(cProgramNode * node)
        {
            VisitAllChildren(node);
            cBlockNode * block = node->GetBlock();
            block->SetSize(RoundUp(block->GetSize()));
        }

        void VisitAllNodes(cAstNode *node) { node->Visit(this); }
        
        void Visit(cArrayDeclNode *node)     
        { 
            VisitAllChildren(node); 
            node->SetSize(node->GetBaseType()->GetSize() * node->GetCount());
        }

        //void Visit(cAstNode *node)          { VisitAllChildren(node); }
        //void Visit(cAssignNode *node)       {                         } 
        //void Visit(cBinaryExprNode *node)   {                         }
        void Visit(cBlockNode *node)        
        { 
            int offset = m_offset;
            int highWaterMark = m_highWaterMark;

            m_highWaterMark = m_offset;
            VisitAllChildren(node);
            node->SetSize(m_highWaterMark - offset);
            SetHighWater(highWaterMark);
            m_offset = offset;
        }

        void Visit(cDeclsNode *node)         
        { 
            int offset = m_offset;

            VisitAllChildren(node); 
            node->SetSize(m_offset - offset);
        }

        //void Visit(cDeclNode *node)        { VisitAllChildren(node); }
        //void Visit(cExprNode *node)         { VisitAllChildren(node); }
        //void Visit(cFloatExprNode *node)    { VisitAllChildren(node); }
        void Visit(cFuncDeclNode *node)     
        { 
            int offset = m_offset;
            int highWaterMark = m_highWaterMark;

            m_offset = 0;
            m_highWaterMark = 0;

            node->SetOffset(0);

            VisitAllChildren(node); 
            node->SetSize(RoundUp(m_highWaterMark));
            m_highWaterMark = highWaterMark;
            //SetHighWater(highWaterMark);
            
            m_offset = offset;
        }
        
        //void Visit(cIfNode *node)           { VisitAllChildren(node); }
        //void Visit(cIntExprNode *node)      { VisitAllChildren(node); }
        //void Visit(cOpNode *node)           { VisitAllChildren(node); }
        
        void Visit(cParamListNode *node)    
        { 
            int size = m_tempSize;

            VisitAllChildren(node); 

            node->SetSize(m_tempSize - size);

            m_tempSize = 0;
        }
        
        void Visit(cParamsNode *node)       
        { 
            //int size = 0;
            m_offset = -8;

            VisitAllChildren(node); 
        
            //for(int i = 0; i <node->NumChildren(); i++)
            //{
            //    size += node->GetDecl(i)->GetSize();
            //}

            node->SetSize(abs(RoundUp(m_offset))-8);

            m_offset = 0;
        }
        
        //void Visit(cPrintNode *node)        { VisitAllChildren(node); }
        //void Visit(cReturnNode *node)       { VisitAllChildren(node); }
        //void Visit(cStmtNode *node)         { VisitAllChildren(node); }
        //void Visit(cStmtsNode *node)        { VisitAllChildren(node); }
        //void Visit(cStructDeclNode *node)   { VisitAllChildren(node); }
        //void Visit(cSymbol *node)           { VisitAllChildren(node); }
        
        void Visit(cVarDeclNode *node)      
        { 
            if (m_offset < 0)
            {
                //VisitAllChildren(node);
                node->SetSize(node->GetType()->GetSize());

            
                if(node->GetSize() != 1)
                {
                    m_offset = ((-1) * RoundUp(m_offset * (-1)));
                }

                m_offset -= RoundUp(node->GetSize());
                node->SetOffset(m_offset);
                //m_offset -= node->GetSize();
            }
            else
            {
                //VisitAllChildren(node);
                node->SetSize(node->GetType()->GetSize());

                if(node->GetType()->IsArray())
                {
                   node->SetSize(node->GetType()->GetBaseType()->GetSize() * node->GetType()->GetCount());
                }
                
                if(node->GetSize() != 1)
                {
                   m_offset = RoundUp(m_offset);
                }

                node->SetOffset(m_offset);
                m_offset += node->GetSize();
                SetHighWater(m_offset);
            }
        }

        int RoundUp(int value)
        {
            if(value % 4 != 0)
                value += 4 - value % 4;

            return value;
        }
        
        void Visit(cVarExprNode *node)      
        {
            VisitAllChildren(node);

            node->SetSize(node->GetDecl()->GetSize());
            node->SetOffset(node->GetDecl()->GetOffset());

            m_tempSize += node->GetSize();

            if(node->GetDecl()->GetType()->IsArray())
            {
                for (int i = 0; i < node->NumItems(); i++){
                    node->SetRowSize(node->GetName()->GetDecl()->GetType(i)->GetBaseType()->GetSize());}
        
            }
        }
        //void Visit(cWhileNode *node)        { VisitAllChildren(node); }

    protected:
        int m_highWaterMark;
        int m_offset;
        int m_tempSize;
};
