#include "ds.h"
using namespace std;

bool checkmy_instructor_slot(instructor *Prof, slot* s ){
    if (s==NULL)
    {
        return true;
    }
    
    slot* temp=Prof->first_slot;
    while (temp!=NULL)
    {
        if (temp->day==s->day && temp->time_slot==s->time_slot )
        {
            return false;
        }
        temp=temp->next;
        
    }
    return true;
}

void add_instructor_slot(instructor *Prof, slot* s){
    if (s==NULL)
    {
        return;
    }
    slot * copied_s = new slot();
    *copied_s = *s;
    
    slot* temp=Prof->first_slot;
    if(temp==NULL){
        Prof->first_slot= copied_s;
        Prof->first_slot->next=NULL;
        return;
    }
    while (temp->next!=NULL)
    {
        temp=temp->next;
    }
    temp->next= copied_s;
    temp=temp->next;
    temp->next=NULL;
    return;
}