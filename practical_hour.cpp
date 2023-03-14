#include "ds.h"

bool allocate_prac_hours(course *c, int p, practical *first_prac, string lab_dept, int tut)
{
    cout << "p   = " << p << endl;
    slot *temp_slot = new slot();
    temp_slot->day = 0;
    temp_slot->time_slot = 0;
  
    while (true)
    {
        bool flag = 0;

        while (temp_slot->day < working_days || temp_slot->time_slot < no_of_slots)
        {
            bool flag_busy = 0;
            for (int i = 0; i < dept.size(); i++)
            {
                instructor *x = map_instructor[c->course_code];
                bool a = checkmy_instructor_slot(x, temp_slot);
                if ((dept[i]->table[temp_slot->day][temp_slot->time_slot]).first != 0 || !a)
                {

                    flag_busy = 1;
                    if (temp_slot->time_slot < no_of_slots - 1)
                    {
                        // cout<<"next slot"<<endl;
                        temp_slot->time_slot += 1;
                        // cout<<temp_slot->day<<" "<<temp_slot->time_slot<<endl;
                    }
                    else
                    {
                        // cout<<"next day"<<endl;
                        temp_slot->day += 1;
                        temp_slot->time_slot = 0;
                        // cout<<temp_slot->day<<" "<<temp_slot->time_slot<<endl;
                    }
                    break;
                }
            }
            if (flag_busy == 0)
            {
                bool free = 1;
                slot *checktemp = temp_slot;
                for (int j = 0; j < 2 * p; j++)
                {
                    for (int i = 0; i < dept.size(); i++)
                    {
                        instructor *x = map_instructor[c->course_code];
                        bool a = checkmy_instructor_slot(x, checktemp);
                        if ((dept[i]->table[checktemp->day][checktemp->time_slot]).first != 0 || !a)
                        {
                            free = 0;
                            break;
                        }
                        temp_slot->time_slot += 1;
                    }
                    if (free = 0)
                    {
                        break;
                    }
                }
                if (free == 1)
                {
                    cout << "Practical allocated" << endl;
                    flag = 1;
                    slot* temp=temp_slot;
                    for (int j = 0; j < 2 * p; j++)
                    {
                        for (int i = 0; i < dept.size(); i++)
                        {
                            dept[i]->table[temp->day][temp->time_slot] = make_pair(3,c);
                            instructor *prof = map_instructor[c->course_code];
                            add_instructor_slot(prof, temp);
                        }
                        if(j!=2*p-1){
                            slot* x=temp;
                            temp=new slot();
                            x->next=temp;
                            temp->day=x->day;
                            temp->time_slot=x->time_slot+1;
                        }
                    }
                }
                else
                {
                     temp_slot->day += 1;
                     temp_slot->time_slot = 0;
                }
                
            }
        }
    }
}
