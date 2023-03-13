#include "ds.h"

bool  allocate_prac_hours(course* c, int p, practical* first_prac, string lab_dept, int tut){
    slot* temp_slot = new slot();
    temp_slot->day = 0;
    temp_slot->time_slot = 0;

    first_prac->time_slot.push_back(all_slots);

}