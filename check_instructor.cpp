#include <bits/stdc++.h>
#include <ds.h>
using namespace std;

bool check_instructor_slot(instructor *Prof, slot* s ){
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
        
    }
    return true;
}