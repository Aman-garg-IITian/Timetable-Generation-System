#include "ds.h"

bool allocate_practicals(course* P, int p, int tut, slot *& head,string lab_dept){

  cout<<p<<endl;

  slot* temp_slot = new slot();
  temp_slot->day = 0;
  temp_slot->time_slot = 0;
  bool flag = 0;



  while(p > 0){
    

    while(temp_slot->day < working_days || temp_slot->time_slot < no_of_slots){
      bool flag_busy = 0;

      for(int i=0 ; i< dept.size(); i++){
        if((dept[i]->table[temp_slot->day][temp_slot->time_slot]).first!=0){
          
          flag_busy = 1;

          if(temp_slot->time_slot < no_of_slots - 1){
                temp_slot->time_slot += 1;
          }
          else{
               
                temp_slot->day += 1;
                temp_slot->time_slot = 0;
               
          }
          break;
        }
      }
      if(flag_busy == 0){
        if(lab_check(P, temp_slot, 5,lab_dept) == false){
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
      
        for(int i=0; i<dept.size(); i++){
          if(tut==5){
            dept[i]->table[temp_slot->day][temp_slot->time_slot] = make_pair(5,P) ;
            // cout<<"tutorial" << dept[i]->table[temp_slot->day][temp_slot->time_slot].first<<endl;
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
          temp_slot->time_slot = 0;
        }
        p--;
        break;
      }
    }
    if(flag == 0){
      cout << "ERRORRRRR: THE COURSE" << P->course_code << "COULDN'T GET ALL PRACTICALS ALLOTED "<< p <<"practicals left"<<endl;
      // head = NULL;
      return false;
    }
  }
   
  return true;
}

