#include "ds.h"

bool allocate_prac_hours(course *c, int p, practical *first_prac, string lab_dept, int tut, time_table* dept)
{
    // cout << "p   = " << p << c->course_code<<endl;
    slot *temp_slot = new slot();
    temp_slot->day = 0;
    temp_slot->time_slot = 0;

    bool flag = 0;
    while (temp_slot->day < working_days || temp_slot->time_slot < no_of_slots)
    {
        bool flag_busy = 0;
        instructor *x = map_instructor[c->course_code];
        // cout<<"checking a slot"<<endl;
        int i=0;
        while(i<p){
            bool a = checkmy_instructor_slot(x, temp_slot);                
            if (dept->table[temp_slot->day][temp_slot->time_slot].first != 0 || !a)
            {
                flag_busy = 1;
                break;
            }
            else{
                if(temp_slot->time_slot >= no_of_slots-1){
                    flag_busy = 1;
                    break;
                }
                i++;
                temp_slot->time_slot += 1;
            }
        }
        temp_slot->time_slot -= i; //reseting time slot

        //lab_check will add slots to the lab time_table if the slots are free
        if(!lab_check(c,temp_slot)){
            flag_busy = 1;
        }
        if (flag_busy == 0)
        {
            // cout << "Practical allocated" << endl;
            flag = 1;
                    
            //adding every slot to instructor and department time table
            practical* new_slot = new practical();
            new_slot->day = temp_slot->day;
            for (int j = 0; j < p; j++)
            {
                dept->table[temp_slot->day][temp_slot->time_slot] = make_pair(3,c);
                instructor *prof = map_instructor[c->course_code];
                add_instructor_slot(prof, temp_slot);

                new_slot->time_slot.push_back(temp_slot->time_slot);
                temp_slot->time_slot++;
            }
            if( first_prac == NULL){
                first_prac = new_slot;
                first_prac->dept = dept->name;
            }
            else{
                practical* temp = first_prac;
                while(temp->next != NULL){
                    temp = temp->next;
                }
                temp->next = new_slot;
                temp->next->dept = dept->name;
            }
            return true;
        }
        else{
            // cout<<"going for new slot"<<endl;
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
        }
    }
    cout<<"####### Practicals cant be allocates for course = "<<c->course_code<<endl;
    return false;
}

bool allocate_prac_same(course *c, int p, practical *first_prac, string lab_dept, int tut)
{
    // cout << "p   = " << p << c->course_code<<endl;
    slot *temp_slot = new slot();
    temp_slot->day = 0;
    temp_slot->time_slot = 0;

    
    while (temp_slot->day < working_days || temp_slot->time_slot < no_of_slots)
    {
        bool flag = 0;
        for(int cur=0; cur<dept.size(); cur++){
            bool flag_busy = 0;
            instructor *x = map_instructor[c->course_code];
            // cout<<"checking a slot"<<temp_slot->day<<" "<<temp_slot->time_slot<<endl;
            int i=0;
            while(i<p){
                bool a = checkmy_instructor_slot(x, temp_slot);                
                if (dept[cur]->table[temp_slot->day][temp_slot->time_slot].first != 0 || !a)
                {
                    flag_busy = 1;
                    break;
                }
                else{
                    if(temp_slot->time_slot >= no_of_slots-1){
                        flag_busy = 1;
                        break;
                    }
                    i++;
                    temp_slot->time_slot += 1;
                }
            }
            if(flag_busy == 1){
                flag = 1;
                break;
            }
            temp_slot->time_slot -= i; //reseting time slot
        }
        
        //lab_check will add slots to the lab time_table if the slots are free
        if(!lab_check(c,temp_slot)){
            flag = 1;
        }
        if (flag == 0)
        {
            // cout << "Practical allocated" << endl;
            flag = 1;
                    
            // cout<<temp_slot->day<<" "<<temp_slot->time_slot<<endl;
            //adding every slot to instructor and department time table
            for(int cur2=0; cur2<dept.size(); cur2++){
                practical* new_slot = new practical();
                new_slot->day = temp_slot->day;
                for (int j = 0; j < p; j++)
                {
                    dept[cur2]->table[temp_slot->day][temp_slot->time_slot] = make_pair(3,c);
                    if(cur2==0){
                        instructor *prof = map_instructor[c->course_code];
                        add_instructor_slot(prof, temp_slot);
                    }

                    new_slot->time_slot.push_back(temp_slot->time_slot);
                    temp_slot->time_slot++;
                }
                if( first_prac == NULL){
                    first_prac = new_slot;
                    first_prac->dept = dept[cur2]->name;
                }
                else{
                    practical* temp = first_prac;
                    while(temp->next != NULL){
                        temp = temp->next;
                    }
                    temp->next = new_slot;
                    temp->next->dept = dept[cur2]->name;
                }
                temp_slot->time_slot -= p;
            }
            return true;
        }
        else{
            // cout<<"going for new slot"<<endl;
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
        }
    }
    cout<<"####### Practicals cant be allocates for course = "<<c->course_code<<endl;
    return false;
}