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

bool allocate_practical(course * IC){
    return true;  
}


bool allocate_lecture(course* IC, int l, bool tut, slot *& head){
    // cout<<"allocating lecture for "<< IC->course_code<<" " << l <<endl;
    cout<<l<<endl;
    slot* temp_slot = new slot();
    temp_slot->day = 0;
    temp_slot->time_slot = 0;
    bool flag = 0;
    while(l > 0){
        // cout<<"lecture left "<<l<<endl;
        while(temp_slot->day < working_days || temp_slot->time_slot < no_of_slots){
            bool flag_busy = 0;
            for(int i=0 ; i< dept.size(); i++){
                if( (dept[i]->table[temp_slot->day][temp_slot->time_slot]).first != 0){
                    
                    flag_busy = 1;
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
                    break;
                }
            }
            if(flag_busy == 0){
                // cout<<"lecture allocated"<<endl;
                flag =1;
                // cout<<"enter"<<temp_slot->day<<" ";
                // cout<<temp_slot->time_slot<<endl;
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
                }
                temp_slot->time_slot = 0;
                l--;

                break;
            }
        }
        if(flag == 0){
            cout << "ERRORRRRR: THE COURSE" << IC->course_code << "COULDN'T GET ALL LECTURES ALLOTED "<< l <<"lectures left"<<endl;
            head = NULL;
            return false;
        }
    }
    slot * temp = head;
    // if(temp){
    //     cout<<"its not null"<<endl;
    // }
    // else{
    //     cout<<"its nulll"<<endl;
    // }
    while(temp){
        cout<<"allocating "<<IC->course_code<<" "<<temp->day<<" "<<temp->time_slot <<endl;
        for(int i=0; i<dept.size(); i++){
            if(tut){
                dept[i]->table[temp->day][temp->time_slot] = make_pair(2,IC) ;
                cout<<"tutorial" << dept[i]->table[temp->day][temp->time_slot].first<<endl;
            }
            else{
                dept[i]->table[temp->day][temp->time_slot] = make_pair(1,IC) ;
                // dept[i]->table[temp->day][temp->time_slot].second = IC;
            }
        }
        temp = temp->next;
    }
    cout<<endl;
    return true;
}

bool allocate_ic(vector<course*> IC){
    // cout<<"ICS FUNCTION CALLED"<<endl;
    vector<course *>::iterator itr;
    sort(IC.begin(), IC.end(), [](course*& lhs, course* & rhs){return lhs->p < rhs->p;});

    //first allocate practicals of all ICs
    // for(itr = IC.begin(); itr != IC.end(); itr++){
    //     if( (*itr)->p != 0){
    //         allocate_practical(*itr);
    //     }
    //     else{
    //         break;
    //     }
    // }

    //then allocate all lectures of ICs
    for(itr = IC.begin(); itr != IC.end(); itr++){
        if( (*itr)->l != 0){
            allocate_lecture(*itr, (*itr)->l, false, (*itr)->first_l);
        }
    }
    sort(IC.begin(), IC.end(), [](course*& lhs, course* & rhs){return lhs->t > rhs->t;});
    //at end allocate the tutorial hours
    for(itr = IC.begin(); itr != IC.end(); itr++){
        if( (*itr)->t != 0){
            allocate_lecture(*itr, (*itr)->t, true, (*itr)->first_t);
        }
        else{
            break;
        }
    }
    return true;
}

void debug_print(){
    cout<<"PRINT CALLED"<<endl;
    for(int i=0; i< dept.size(); i++){
        cout<<"TABLE FOR "<<dept[i]->name<<endl;
        for(int j=0; j< 5; j++){
            for(int k=0; k< 11; k++){
                // cout<<dept[i]->table[j][k].first<<" ";
                if( dept[i]->table[j][k].first == 0 ){
                    cout << "empty           ";
                }
                else{
                    cout<< dept[i]->table[j][k].second->course_code;
                    int le = dept[i]->table[j][k].second->course_code.length();
                    if(dept[i]->table[j][k].first == 2){
                        cout<<"(TUT)";
                        le += 5;
                    }
                    if(dept[i]->table[j][k].first == 3){
                        cout<<"(PRA)";
                        le += 5;
                    }
                    for(int letters=0; letters< 16-le; letters++){
                        cout<<" ";
                    }
                }
            }
            cout<<endl;
        }
    }
    cout << "COURSES AND CLASSROOMS ALLOCATED TO THEM:"<<endl;
    for(int i=0; i<ICs.size(); i++){
        cout<<ICs[i]->course_code<<"  -  ";
        for(int j=0; j<ICs[i]->allocated_classrooms.size(); j++){
            cout<<ICs[i]->allocated_classrooms[j]<<" / ";
        }
        cout<<endl;
    }
}

bool take_input_csv(string fname){
    vector< vector<string> > content;
    vector<string> row;
    string line, word;

    fstream file (fname,ios::in);
    if(file.is_open())
    {
        while(getline(file,line)){
            row.clear();
            stringstream str(line);
            while(getline(str,word,','))
            row.push_back(word);
            content.push_back(row);
        }
        cout<<"file opened"<<endl;
    }
    else{
        cout<<"File not found!";
        return 0;
    }
    for(int i=1;i<content.size();i++){
        if(content[i][1]!= ""){
            course * temp_input = new course();
            if( content[i][3] =="Institute Core" ){
                temp_input->course_code = content[i][1];
                temp_input->l= stoi(content[i][6]);
                temp_input->p= stoi(content[i][8]);
                temp_input->t= stoi(content[i][7]);
                ICs.push_back(temp_input);
            }
        }
    }
    for(int i=13; i<ICs.size(); i++){
        ICs[i]->registered_stu = 40;
    }
    // cout<<ICs.size()<<endl;
    // for(int i=0; i< ICs.size(); i++){
    //     cout<<ICs[i]->course_code<<" "<<ICs[i]->l<<" "<<ICs[i]->t<<" "<<ICs[i]->p<<endl;
    // }
    for(int i=0; i<dept.size(); i++){
        time_table * object = new time_table();
        object->name = dept_name[i];
        dept[i] = object;
    }

    cout<<"ENTER LUNCH SLOT FOR THE BATCH: ";
    cin>>lunch;

    for(int i=0; i<dept.size(); i++){
        for(int j=0; j<working_days; j++){
            course * lunch_name = new course();
            lunch_name->course_code = "LUNCHBREAK ";
            dept[i]->table[j][lunch] = make_pair(1,lunch_name);
        }
    }
    int break_slot, dept_no, day_no;
    cout<<"ENTER DEPT NO AND BREAK SLOT and day no.: ";
    cin>>dept_no>>break_slot>> day_no ;
    course * break_name = new course();
    break_name->course_code = "test break";
    dept[dept_no]->table[day_no][break_slot] = make_pair(1,break_name);

    return 1;
}
void classroom_print(){
    cout<<"CLASSROOM INFO"<<endl;
    for(int i=0; i< room.size(); i++){
        cout<<"TABLE FOR "<<room[i]->id<<endl;
        for(int j=0; j< 5; j++){
            for(int k=0; k< 11; k++){
                if( room[i]->class_table.table[j][k].first == 0 ){
                    cout << "empty           ";
                }
                else{
                    cout<< room[i]->class_table.table[j][k].second->course_code;
                    int le = room[i]->class_table.table[j][k].second->course_code.length();
                    if(room[i]->class_table.table[j][k].first == 2){
                        cout<<"(TUT)";
                        le += 5;
                    }
                    if(room[i]->class_table.table[j][k].first == 3){
                        cout<<"(PRA)";
                        le += 5;
                    }
                    for(int letters=0; letters< 16-le; letters++){
                        cout<<" ";
                    }
                }
            }
            cout<<endl;
        }
    }
}

bool take_input_classroom(string fname){
    vector< vector<string> > content;
    vector<string> row;
    string line, word;

    fstream file (fname,ios::in);
    if(file.is_open())
    {
        while(getline(file,line)){
            row.clear();
            stringstream str(line);
            while(getline(str,word,','))
            row.push_back(word);
            content.push_back(row);
        }
        cout<<"file opened"<<endl;
    }
    else{
        cout<<"File not found!";
        return 0;
    }
    for(int i=1;i<content.size();i++){
        classroom* object = new classroom();
        object->id = content[i][0];
        object->capacity = stoi(content[i][1]); 
        room.push_back(object);
    }

}

bool allocate(classroom* room, course* c){

    slot * temp = c->first_l;
    c->allocated_classrooms.push_back(room->id);
    while(temp){
        cout<< "running"<<endl;
        room->class_table.table[temp->day][temp->time_slot] = make_pair(1, c);
        // cout<<"allocating room " <<room->id <<" to "<<c->course_code<<endl;
        temp = temp->next;
    }
    temp = c->first_t;
    while(temp){
        room->class_table.table[temp->day][temp->time_slot] = make_pair(2, c);
        // cout<<"allocating room " <<room->id <<" to "<<c->course_code<<endl;
        temp = temp->next;
    }
    return 1;

}

int allocate_classroom_same(vector<course*> ICs){
    sort(room.begin(), room.end(), [](classroom*& lhs, classroom* rhs){return lhs->capacity < rhs->capacity;});
    sort(ICs.begin(), ICs.end(), [](course*& lhs, course* & rhs){return lhs->registered_stu > rhs->registered_stu;});
    
    for(int i=0;i<ICs.size();i++){
        int starting_index;
        int flag(0);
        for(int j=0; j < room.size(); j++){
            if(room[j]->capacity >= ICs[i]->registered_stu){
                starting_index = j;
                break;
            }
        }
        int check = 0;
        for(int j=starting_index;j<room.size();j++){
            flag=0;
            slot* temp = ICs[i]->first_l;
            int twice=0;
            while(temp != NULL && twice !=1){
                if(room[j]->class_table.table[temp->day][temp->time_slot].first==0){
                    temp = temp->next;
                    continue;
                }
                else{
                    flag=1;
                    break;
                }
                if(temp == NULL){
                    twice = 1;
                    temp = ICs[i]->first_t;
                }
            }
            if(flag==0){
                check = allocate(room[j], ICs[i]);
                break;
            }
        }
        if(check){
            // cout<<"CLASROOM ALLOCATED"<<endl;
        }
        else{
            cout<<"allocation not possible for" << ICs[i]->course_code <<endl;
        // call allocate_room_different
        }
    }
    
    return 0;
}
int main(){
    cout<<"code start"<<endl;
    if(take_input_csv("data.csv"))
        cout<<"INPUT TAKEN"<<endl;

    if(take_input_classroom("Classroom.csv"))
        cout<<"CLASSROOMS READ" <<endl;

    allocate_ic(ICs);
    allocate_classroom_same(ICs);
    debug_print();
    classroom_print();    
}