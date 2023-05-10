#include "ds.h"

bool allocate(classroom* room, course* c){

    slot * temp = c->first_l;
    c->allocated_classrooms.push_back(room->id);
    while(temp){
        // cout<< "running"<<endl;
        room->class_table.table[temp->day][temp->time_slot] = make_pair(1, c);
        // cout<<"allocating room " <<room->id <<" to "<<c->course_code<<endl;
        temp = temp->next;
    }
    temp = c->first_t;
    while(temp){
        room->class_table.table[temp->day][temp->time_slot] = make_pair(2, c);
        // cout<<"allocating room " <<room->id <<" to "<<c->course_code<<endl;
        temp = temp->next;
    }
    return 1;

}

bool allocate_ic(vector<course*> IC){
    // cout<<"ICS FUNCTION CALLED"<<endl;
    vector<course *>::iterator itr;
    sort(IC.begin(), IC.end(), [](course*& lhs, course* & rhs){return lhs->p < rhs->p;});

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
            // cout<<"calling allocate lecture"<<endl;
            allocate_lecture(*itr, (*itr)->l, false, (*itr)->first_l);
        }
    }
    sort(IC.begin(), IC.end(), [](course*& lhs, course* & rhs){return lhs->t > rhs->t;});
    //at end allocate the tutorial hours
    for(itr = IC.begin(); itr != IC.end(); itr++){
        if( (*itr)->t != 0){
            allocate_lecture(*itr, (*itr)->t, true, (*itr)->first_t);
        }
        else{
            break;
        }
    }
    sort(room.begin(), room.end(), [](classroom*& lhs, classroom* rhs){return lhs->capacity < rhs->capacity;});
    sort(ICs.begin(), ICs.end(), [](course*& lhs, course* & rhs){return lhs->registered_stu > rhs->registered_stu;});

    for(int i=0;i<IC.size();i++){
        int starting_index, end_index;
        int flag(0);
        for(int j=0; j < room.size(); j++){
            if(room[j]->capacity >= IC[i]->registered_stu){
                starting_index = j;
            }
            else{
                end_index=j;
                break;
            }
        }
        int check = 0;
        for(int j=starting_index;j<end_index;j++){
            flag=0;
            slot* temp = IC[i]->first_l;
            int twice=0;
            while(temp != NULL && twice !=1){
                if(room[j]->class_table.table[temp->day][temp->time_slot].first==0){
                    temp = temp->next;
                    continue;
                }
                else{
                    flag=1;
                    break;
                }
                if(temp == NULL){
                    twice = 1;
                    temp = IC[i]->first_t;
                }
            }
            if(flag==0){
                check = allocate(room[j], ICs[i]);
                break;
            }
        }
        if(check){
            // cout<<"CLASROOM ALLOCATED"<<endl;
        }
        else{
            cout<<"allocation not possible for" << IC[i]->course_code <<endl;
        // call allocate_room_different
        }
    }    
    return true;
}