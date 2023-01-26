#include "ds.h"

bool allocate_pc(vector<course*> P){
    vector<course *>::iterator itr;
  cout<<"in allocatepc function"<<endl;
    for(itr = P.begin(); itr != P.end(); itr++){
         
        if( (*itr)->p != 0 && (*itr)->p < 5){
           
            allocate_practicals(*itr, (*itr)->p, 3, (*itr)->first_p,(*itr)->lab_dept);
            
        }
    }

   return 0;

}