#pragma once
#ifndef ds
#define ds

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

#define no_of_slots 11
#define working_days 5
#define no_of_dept 6 


//linked list structure of slot
class slot{
    public:
    int day;
    int time_slot;
    slot* next = NULL;
};

class practical{
    public:
    int day;
    vector<int> time_slot;   //stores all the allocate time_slots of a particular department of a given practical
    string dept;
    practical * next;
};

class instructor{
    public:
    string name;
    slot* first_slot;
};
//structure for course
class course{
    public:
    string course_code;
    int l;
    slot* first_l;
    int t;
    slot* first_t;
    int p;
    practical* first_p;
    int registered_stu = 80;
    vector<string> parallel;  /*to store courses like in HSS slot 3 courses run all at same time diff classroom;
                     no use in timtable algo used in classroom allocation   */
    vector<string> ins_name;
    instructor* Prof;
    vector<string> coordinator;
    vector<string> allocated_classrooms;
};



//2D table structure of time table
class time_table{
    public:
    string name;
    vector<vector< pair<int, course*> > > table; // stores 0 for empty 1 for lecture 2 for tutorial 3 for practical, course/classrrom id in case of filled
    time_table(){
        for(int i=0; i<5; i++){
            vector< pair <int, course*> > test;
            for(int j=0; j<11; j++){
                course * temp = NULL;
                test.push_back(make_pair(0, temp));
            }
            table.push_back(test);
        }
    }
};

//structure for classrooms
class classroom{
    public:
    string id;
    int capacity;
    time_table class_table;   //stores 2D table of class slots 
};


class DC{
    public:
    string dept_name;
    course* DCs[];
};

unordered_map <string, instructor *> map_instructor;  //this map will map a particular course to instructors using his/her name

vector<course *> ICs, OEs;
vector<DC> D_core, D_Elec;
vector<classroom*> room;
vector<time_table*> dept(no_of_dept);
int lunch;

string dept_name[no_of_dept] = {"CHEMICAL", "CIVIL", "CSE", "EE", "MECH", "MAT"};

#include "input.cpp"
bool take_input_csv(string fname);
bool take_input_classroom(string fname);

#include "allocate_lectures.cpp"
bool allocate_lecture(course* IC, int l, bool tut, slot *& head);

#include "allocate_prac.cpp"
bool allocate_practical(course * IC);

#include "allocate_ics.cpp"
bool allocate_ic(vector<course*> IC);

#include "allocate_classroom.cpp"
bool allocate(classroom* room, course* c);
int allocate_classroom_same(vector<course*> ICs);

#include "final_print.cpp"
void debug_print();
void classroom_print();

#include "check_instructor.cpp"
bool check_instructor_slot(instructor *Prof, slot* s );

#endif