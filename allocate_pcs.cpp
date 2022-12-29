#include "ds.h"

bool allocate_pc(vector<course*> P){
    vector<course *>::iterator itr;

    for(itr = P.begin(); itr != P.end(); itr++){
        if( (*itr)->l != 0){
            allocate_practicals(*itr, (*itr)->p, 5, (*itr)->first_l,(*itr)->lab_dept);
            cout<<"asdfghjkl;rdtfyguhijokplrdtfyguhijokertfyguhijokwrestdryftugyihuojizxdcfvgbhnjmkx5dcf6vgbhinjmz4xc6vbyn";
        }
    }

   return 0;

}