#pragma once

class cSemantics : public cVisitor
{
    public:
        cSemantics() : cVisitor()
        {}

        int NumErrors()
        {
            return numErrors;
        }

        void VisitAllNodes(cAstNode * node)
        {
            node->Visit(this);
        }

    private:
        int numErrors = 0;
};
