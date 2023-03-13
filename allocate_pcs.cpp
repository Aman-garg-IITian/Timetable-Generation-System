#include "ds.h"

bool allocate_pc(vector<course*> P){
    vector<course *>::iterator itr;
  cout<<"in allocate pc function"<<endl;
  int count = 0;
    for(itr = P.begin(); itr != P.end(); itr++){
         
        if( (*itr)->p != 0 && (*itr)->p < 5){
           
            allocate_practicals(*itr, (*itr)->p, (*itr)->first_p,(*itr)->lab_dept, 3);
            count++;
            if(count == 5) break;
            
        }
    }

   return 0;

}