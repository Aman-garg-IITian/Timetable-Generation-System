bool allocate_practicals(course* P, int p, slot* &head,string lab_dept, int tut=3){

 // cout<<"no of p-->"<<p<<endl;
  if(p > 4){
    cout<<"Encounter lab of >4 hourss ------- CANNOT ALLOCATE";
    return false;
  }

  // Determine the number of consecutive hours needed for the practicals
  int consecutive_hours = p;
  if (p >= 3) {
    consecutive_hours = 3;
  }

  slot* temp_slot = new slot();
  temp_slot->day = 0;
  temp_slot->time_slot = 0;
  int consecutive_allocated = 0;
  bool flag = false;
  slot* last_allocated_slot = NULL;

 while (consecutive_allocated < consecutive_hours) {
    while (temp_slot->day < working_days && temp_slot->time_slot < no_of_slots) {
      // check if slot is available for all departments
      bool flag_busy = false;
      for(int i=0; i<dept.size(); i++){
        if((dept[i]->table[temp_slot->day][temp_slot->time_slot]).first != 0) {
          flag_busy = true;
          break;
        }
      }
      if(flag_busy == false) {
        // check if lab is available for the course
        if(lab_check(P, temp_slot, tut, lab_dept) == false) {
          if(temp_slot->time_slot < no_of_slots - 1){
            temp_slot->time_slot += 1;
          } else {
            temp_slot->day += 1;
            temp_slot->time_slot = 0;
          }
          continue;
        }
        // mark slot as allocated
        flag = true;
        for (int i = 0; i < dept.size(); i++) {
          if (tut == 3 && temp_slot->time_slot >3) {
            // check if the last allocated slot for the same course on the same day is the previous time slot
            if (last_allocated_slot != NULL && last_allocated_slot->day == temp_slot->day && last_allocated_slot->time_slot == temp_slot->time_slot - 1 ) {
              dept[i]->table[temp_slot->day][temp_slot->time_slot] = make_pair(2, P); // mark as continuation
            } else {
              dept[i]->table[temp_slot->day][temp_slot->time_slot] = make_pair(3, P); // mark as new allocation
            }
          }
        }
        last_allocated_slot = temp_slot;
        consecutive_allocated++;
        // add slot to linked list if first practical
        if(consecutive_allocated == 1) {
          if(head == NULL) {
            head = temp_slot;
          } else {
            slot* temp = head;
            while(temp->next != NULL){
              temp = temp->next;
            }
            temp->next = temp_slot;
          }
        }
        // check for end of consecutive allocation
        if(consecutive_allocated == consecutive_hours) {
          break;
        }
      }
      // move to next slot
      if(temp_slot->time_slot < no_of_slots - 1) {
        temp_slot->time_slot += 1;
      } else {
        temp_slot->day += 1;
        temp_slot->time_slot = 0;
      }
    }
    // if no slot available for consecutive allocation, return false
    if(flag == false) {
      cout << "ERROR: THE COURSE " << P->course_code << " COULDN'T GET ALL PRACTICALS ALLOTED " << p - consecutive_allocated << " practicals left" << endl;
      return false;
    }
  }
  return true;

}
