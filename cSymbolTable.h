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

class cSymbolTable{
    public:
     void DecreaseScope() 
     {
        
     }
     void IncreaseScope()
     {
     
     }
     cSymbol * Insert(std::string yytxt) 
     {
         return NULL;
     }   
     cSymbol * LookUpAll(std::string) 
     {
         return NULL;
     }
     cSymbol * LookUpRecent(std::string) 
     {
         return NULL;
     
     " "+                        {/* delete blanks */}
     "//".*$                     {/* deletes comments*/}
     [\n]                        {/* deletes new lines*/}
     [\t]                        {/* deletes tabs*/}
     
     " "+                        {/* delete blanks */}
     "//".*$                     {/* deletes comments*/}
     [\n]                        {/* deletes new lines*/}
     [\t]                        {/* deletes tabs*/}
     }

    private:
     std::list <std::unordered_map<std::string, cSymbol *>> cSymbolList;

};
