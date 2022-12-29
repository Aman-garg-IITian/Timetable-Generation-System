#include "ds.h"
bool classroom_check(course* IC, slot * slot_to_allot, int type){

    sort(room.begin(), room.end(), [](classroom*& lhs, classroom* rhs){return lhs->capacity < rhs->capacity;});

    
    int starting_index;
    int flag(0);
    for(int j=0; j < room.size(); j++){
        if(room[j]->capacity >= IC->registered_stu){
            starting_index = j;
            break;
        }
    }
    for(int j=starting_index;j<room.size();j++){

        if(room[j]->class_table.table[slot_to_allot->day][slot_to_allot->time_slot].first==0){
            if( find(IC->allocated_classrooms.begin(), IC->allocated_classrooms.end(), room[j]->id) == IC->allocated_classrooms.end()){
                IC->allocated_classrooms.push_back(room[j]->id);
            }
            room[j]->class_table.table[slot_to_allot->day][slot_to_allot->time_slot] = make_pair(type, IC);
            return true;
        }

    }
    return false;
}