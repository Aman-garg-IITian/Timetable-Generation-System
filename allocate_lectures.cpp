#include "ds.h"

bool allocate_lecture(course* IC, int l, int tut, slot *& head){
    


    cout<<l<<endl;
    slot* temp_slot = new slot();
    temp_slot->day = 0;
    temp_slot->time_slot = 0;
    bool flag = 0;


    while(l > 0){
        
        while(temp_slot->day < working_days || temp_slot->time_slot < no_of_slots){
            bool flag_busy = 0;
            
            for(int i=0 ; i< dept.size(); i++){
                if( (dept[i]->table[temp_slot->day][temp_slot->time_slot]).first != 0){
                    
                    flag_busy = 1;
                    if(temp_slot->time_slot < no_of_slots - 1){
                        // cout<<"next slot"<<endl;
                        temp_slot->time_slot += 1;
                        // cout<<temp_slot->day<<" "<<temp_slot->time_slot<<endl;
                    }
                    else{
                        // cout<<"next day"<<endl;
                        temp_slot->day += 1;
                        temp_slot->time_slot = 0;
                        // cout<<temp_slot->day<<" "<<temp_slot->time_slot<<endl;
                    }
                    break;
                }
            }
            if(flag_busy == 0){
                // cout<<"lecture allocated"<<endl;
                if(classroom_check(IC, temp_slot, tut) == false){
                    if(temp_slot->time_slot < no_of_slots - 1){
                        temp_slot->time_slot += 1;
                    }
                    else{
                        temp_slot->day += 1;
                        temp_slot->time_slot = 0;
                    }
                    continue;
                }
                flag =1;
                // cout<<"enter"<<temp_slot->day<<" ";
                // cout<<temp_slot->time_slot<<endl;
                for(int i=0; i<dept.size(); i++){
                    if(tut==2){
                        dept[i]->table[temp_slot->day][temp_slot->time_slot] = make_pair(2,IC) ;
                        // cout<<"tutorial" << dept[i]->table[temp_slot->day][temp_slot->time_slot].first<<endl;
                    }
                    else if(tut==1){
                        dept[i]->table[temp_slot->day][temp_slot->time_slot] = make_pair(1,IC) ;
                        // dept[i]->table[temp->day][temp->time_slot].second = IC;
                    }
                }
                if( head == NULL){
                    head = temp_slot;
                    temp_slot = new slot();
                    temp_slot->day = head->day +1;
                }
                else{
                    slot* temp = head;
                    while(temp->next != NULL){
                        temp = temp->next;
                    }
                    temp->next = temp_slot;
                    temp_slot = new slot();
                    // cout<<temp->day<<endl;
                    temp_slot->day = temp->next->day +1;
                }
                temp_slot->time_slot = 0;
                l--;
                break;
            }
        }
        if(flag == 0){
            cout << "ERRORRRRR: THE COURSE" << IC->course_code << "COULDN'T GET ALL LECTURES ALLOTED "<< l <<"lectures left"<<endl;
            // head = NULL;
            return false;
        }
    }
   
    return true;
}