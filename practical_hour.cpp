#include "ds.h"

bool allocate_prac_hours(course *c, int p, practical *first_prac, string lab_dept, int tut, time_table* dept)
{
    cout << "p   = " << p << endl;
    slot *temp_slot = new slot();
    temp_slot->day = 0;
    temp_slot->time_slot = 0;

    bool flag = 0;
    while (temp_slot->day < working_days || temp_slot->time_slot < no_of_slots)
    {
        bool flag_busy = 0;
        instructor *x = map_instructor[c->course_code];
        for(int i=0; i<p; i++){
            bool a = checkmy_instructor_slot(x, temp_slot);                
            if ((dept->table[temp_slot->day][temp_slot->time_slot]).first != 0 || !a)
            {
                flag_busy = 1;
            }
            else{
                if(temp_slot->time_slot >= no_of_slots-1){
                    flag_busy = 1;
                }
                temp_slot->time_slot ++;
            }
        }
        temp_slot->time_slot -= p; //reseting time slot

        //lab_check will add slots to the lab time_table if the slots are free
        if(!lab_check(c,temp_slot)){
            flag_busy = 1;
        }
        if (flag_busy == 0)
        {
                    cout << "Practical allocated" << endl;
                    flag = 1;

                    //
                    
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
        else
        {
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
