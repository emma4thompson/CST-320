//**************************************
// cSymbolTable.h
//
//
// Author: Emma Thompson 
// emma.thompson@oit.edu
//
// Date: January 26, 2017
//

#include <string>
#include "cSymbol.h"
#include <unordered_map>
#include <list>

using std::list;
using std::unordered_map;
using std::string;

class cSymbolTable{
    public:
     //************************************
     //pops the top table off the stack
     //and next down down becomes default
     void DecreaseScope() 
     {
        if (!cSymbolList.empty()) 
        {
            cSymbolList.pop_front();
        }
     }
  
     //************************************
     //create a new, empty, symbol table
     // and place it on a stack of symbol 
     // tables
     void IncreaseScope()
     {
         unordered_map<string, cSymbol *> hashtable;
         cSymbolList.push_front(hashtable);
     }
  
     //************************************
     //inserts symbols into the current 
     //default table
     cSymbol * Insert(string yytxt) 
     {
         unordered_map<string, cSymbol *>::iterator iter = 
            cSymbolList.front().find(yytxt);
         cSymbol * ret_val = nullptr;


         if(iter != cSymbolList.front().end())
         {
             ret_val = iter->second;
         }
         else
         {
             ret_val = new cSymbol(yytxt);
             cSymbolList.front().insert({yytxt, ret_val});
         }

         return ret_val;
     }

     //************************************
     //search the other tables on the stack 
     //until either the symbol is found or 
     //the last table is searched 
     cSymbol * LookUpAll(string yytxt) 
     {
         cSymbol * ret_val = nullptr;

         for(auto iter = cSymbolList.begin(); iter != cSymbolList.end(); ++iter)
         {
             unordered_map<string, cSymbol *>::iterator iter_2 = 
                 iter->find(yytxt);
             if(iter_2 != iter->end())
             {
                 ret_val = iter_2->second;
             }
         }
         return ret_val;
     }

     //************************************
     //searches default table (inner-most
     //scope)
     cSymbol * LookUpRecent(string yytxt) 
     {
          unordered_map<string, cSymbol *>::iterator iter =
             cSymbolList.front().find(yytxt);
          cSymbol * ret_val = nullptr;
          
          if(iter != cSymbolList.front().end())
          {
             ret_val = iter->second;
          }
         
          return ret_val;
     }

    protected:
     list <unordered_map<string, cSymbol *>> cSymbolList;

};
