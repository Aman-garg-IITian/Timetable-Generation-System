#include "ds.h"

int main()
{
    cout << "code start" << endl;
    if (take_input_csv("clean_data.csv"))
        cout << "INPUT TAKEN" << endl;

    if (take_input_classroom("Classroom.csv"))
        cout << "CLASSROOMS READ" << endl;

    allocate_ic(ICs);
    allocate_classroom_same(ICs);
    allocate_dc(D_core);
    // Made changes here
    allocate_dc(D_Elec);
    debug_print();
    classroom_print();
}