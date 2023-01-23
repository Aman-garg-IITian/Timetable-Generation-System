#include "ds.h"

bool lab_check(course* P,slot * slot_to_allot, int tut, string depts){
  
  sort(labs_room.begin(), labs_room.end(), [](labsroom_c*& lhs, labsroom_c* rhs){return lhs->capacity < rhs->capacity;});
  cout<<" labs_room.size->"<<labs_room.size()<<endl;
  int starting_index;
  int flag(0);

  // find the first lab with sufficient capacity for the course

  for(int j=0; j < labs_room.size(); j++){
    if(labs_room[j]->capacity >= P->registered_stu){
      cout<<labs_room[j]->capacity<<"--"<<P->registered_stu<<endl;
      starting_index = j;
      break;
    }
  }

  // check if a suitable lab is available

  for(int j=starting_index;j<labs_room.size();j++){
    // check if the lab is available for the given time slot
    
    if(labs_room[j]->department == depts && labs_room[j]->class_table.table[slot_to_allot->day][slot_to_allot->time_slot].first==0){
       cout<<"deptarment--"<<labs_room[j]->department<<"and"<<depts<<endl;
      // add lab id to allocated_labs list
    
      if( find(P->allocated_labs.begin(), P->allocated_labs.end(), labs_room[j]->id) == P->allocated_labs.end()){
        P->allocated_labs.push_back(labs_room[j]->id);
      }
      labs_room[j]->class_table.table[slot_to_allot->day][slot_to_allot->time_slot] = make_pair(3, P);
      return true;
    }
  }
  return false;
}
