#include "ds.h"

int main(){
    cout<<"code start"<<endl;
    if(take_input_csv("data.csv"))
        cout<<"INPUT TAKEN"<<endl;

    if(take_input_classroom("Classroom.csv"))
        cout<<"CLASSROOMS READ" <<endl;

    if(take_input_labsroom("Labsroom.csv"))
        cout<<"Labs input taken"<<endl;


    allocate_pc(Ps);


    debug_print();
    classroom_print();    
}