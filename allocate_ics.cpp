#include "ds.h"

bool allocate_ic(vector<course*> IC){
    // cout<<"ICS FUNCTION CALLED"<<endl;
    vector<course *>::iterator itr;
    //sort(IC.begin(), IC.end(), [](course*& lhs, course* & rhs){return lhs->p < rhs->p;});

    //first allocate practicals of all ICs
    // for(itr = IC.begin(); itr != IC.end(); itr++){
    //     if( (*itr)->p != 0){
    //         allocate_practical(*itr);
    //     }
    //     else{
    //         break;
    //     }
    // }

    //then allocate all lectures of ICs
    for(itr = IC.begin(); itr != IC.end(); itr++){
        if( (*itr)->l != 0){
            allocate_lecture(*itr, (*itr)->l, 1, (*itr)->first_l);
        }
    }
    sort(IC.begin(), IC.end(), [](course*& lhs, course* & rhs){return lhs->t > rhs->t;});
    //at end allocate the tutorial hours
    for(itr = IC.begin(); itr != IC.end(); itr++){
        if( (*itr)->t != 0){
            allocate_lecture(*itr, (*itr)->t, 2, (*itr)->first_t);
        }
        else{
            break;
        }
    }
    return true;
}