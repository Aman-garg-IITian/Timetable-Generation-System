#include "ds.h"

bool allocate_pc(vector<course*> P){
    vector<course *>::iterator itr;
   
    for(itr = P.begin(); itr != P.end(); itr++){
        
        if( (*itr)->p != 0){
           
            allocate_practicals(*itr, (*itr)->p, 3, (*itr)->first_p,(*itr)->lab_dept);
            
        }
    }

   return 0;

}