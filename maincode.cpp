#include "ds.h"

int main(){
    if(take_input_classroom("Classroom.csv"))
        cout<<"CLASSROOMS READ" <<endl;

    for(int i=1;i<=4;i++){
        cout<<"code start"<<endl;
        if(take_input_csv("final.csv", i,"testing.csv"))
            cout<<"INPUT TAKEN"<<endl;

        // if(take_input_labsroom("Labsroom.csv"))
        //     cout<<"Labs input taken"<<endl;  
        allocate_ic(ICs);
        allocate_classroom_same(ICs);

        cout<<"allocatung practicals now"<<endl;
        allocate_prac_IC(ICs);
        // allocate_ic(OEs);
        // allocate_classroom_same(OEs);
        cout<<"done with practicals"<<endl;
        allocate_dc(D_core);
        vector<DC*> :: iterator itr;
        for(itr = D_core.begin(); itr != D_core.end(); itr++){
            allocate_classroom_same((*itr)->DCs);
        }
        cout<<"Dc lecture alloted"<<endl;
        allocate_prac_dc(D_core);
        debug_print();
        classroom_print();
        debug_print_csv(i);
        ICs.clear();
        D_core.clear();
    } 
    classroom_print_csv();    
}