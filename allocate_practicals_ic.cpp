#include "ds.h"

bool allocate_prac_IC(vector<course*> IC){

    sort(IC.begin(), IC.end(), [](course*& lhs, course* & rhs){return lhs->p > rhs->p;});
    
    vector<course*> IC_with_prac;
    for(auto it :IC){
        if(it->p != 0){
            IC_with_prac.push_back(it);
        }
        else{
            break;
        }
    }
    for(auto it: IC_with_prac){
        if(it->p > 4){
            cout<< "###### Labs greater than 4 hours are not allocated"<<endl;
            cout<<"The course code is : "<<it->course_code<<endl;
            cout<<endl;
            continue;
        }
        for(int i=0; i<dept.size(); i++){
            allocate_prac_hours(it, it->p, it->first_p, it->lab_dept, 3, dept[i]);
        }
    }
    return true;
}
