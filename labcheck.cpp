#include "ds.h"
bool lab_check(course* c,slot * slot_to_allot){

  // find the hours to allocate
  int hours = c->p;

  //iterate over all the possible labs for that course
  if(c->labs.size() == 0) return true;
  for(auto lab_to_check: c->labs){

    //check the inex of lab in labs_room vector by lab id
    int j;
    for(int ind = 0; ind<labs_room.size(); ind++){
      if(labs_room[ind]->id == lab_to_check){
        j = ind;
        break;
      }
    }

    //check if that lab is free or not 
    bool consecutive_hours_available = true;

    for(int i=0; i<hours; i++){
      int hour = slot_to_allot->time_slot + i;
      if(hour >= no_of_slots || labs_room[j]->class_table.table[slot_to_allot->day][hour].first != 0){
        consecutive_hours_available = false;
        break;
      }
    }

    //if free allocate the lab and return true
    if(consecutive_hours_available){
      for(int k=0; k<hours; k++){
        int hour = slot_to_allot->time_slot+k;
        (labs_room[j]->class_table).table[slot_to_allot->day][hour] = {3,c};
      }
      return true;
    }
  }
  //if none of the labs are free for that slot return false;
  return false;
}
