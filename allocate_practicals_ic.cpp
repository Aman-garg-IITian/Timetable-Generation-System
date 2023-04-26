#include "ds.h"

bool allocate_prac_IC(vector<course*> IC){

    //sorting the ics with respect to practical hours
    sort(IC.begin(), IC.end(), [](course*& lhs, course* & rhs){return lhs->p > rhs->p;});
    
    //crreating a new vector of course which have practicals
    vector<course*> IC_with_prac;
    for(auto it :IC){
        if(it->p != 0){
            IC_with_prac.push_back(it);
        }
        else{
            break;
        }
    }

    //allocating each practical one by one
    for(auto it: IC_with_prac){
        if(it->p > 4){
            cout<< "###### Labs greater than 4 hours are not allocated"<<endl;
            cout<<"The course code is : "<<it->course_code<<endl;
            cout<<endl;
            continue;
        }

        //as it is an ic practical to allocating it for every branch
        if(it->batch_pract == dept.size()){
            for(int i=0; i<dept.size(); i++){
                allocate_prac_hours(it, it->p, it->first_p, it->lab_dept, 3, dept[i]);
            }
        }
        else if(it->batch_pract == 1){
            allocate_prac_same(it, it->p, it->first_p, it->lab_dept, 3);
        }
    }
    return true;
}

bool allocate_prac_dc(vector<DC*> dc){
    for( auto i: dc){
        vector<course*> IC = i->DCs;

        sort(IC.begin(), IC.end(), [](course*& lhs, course* & rhs){return lhs->p > rhs->p;});
    
        //crreating a new vector of course which have practicals
        vector<course*> IC_with_prac;
        for(auto it :IC){
            if(it->p != 0){
                IC_with_prac.push_back(it);
            }
            else{
                break;
            }
        }

        //allocating each practical one by one
        for(auto it: IC_with_prac){
            if(it->p > 4){
                cout<< "###### Labs greater than 4 hours are not allocated"<<endl;
                cout<<"The course code is : "<<it->course_code<<endl;
                cout<<endl;
                continue;
            }

            //as it is an ic practical to allocating it for every branch
            allocate_prac_hours(it, it->p, it->first_p, it->lab_dept, 3, dept[i->dept_no]);
        }
    }
    return true;

}
