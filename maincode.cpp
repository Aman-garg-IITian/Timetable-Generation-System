#include "ds.h"

int main(){
    cout<<"code start"<<endl;
    if(take_input_csv("clean_data.csv"))
        cout<<"INPUT TAKEN"<<endl;

    if(take_input_classroom("Classroom.csv"))
        cout<<"CLASSROOMS READ" <<endl;

    if(take_input_labsroom("Labsroom.csv"))
        cout<<"Labs input taken"<<endl;
        
    allocate_ic(ICs);
    allocate_classroom_same(ICs);

    allocate_prac_IC(ICs);
    // allocate_ic(OEs);
    // allocate_classroom_same(OEs);
    allocate_dc(D_core);
    vector<DC*> :: iterator itr;
    for(itr = D_core.begin(); itr != D_core.end(); itr++){
        allocate_classroom_same((*itr)->DCs);
    }
    debug_print();
    classroom_print();    
}