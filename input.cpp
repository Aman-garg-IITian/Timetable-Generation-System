#include "ds.h"

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


    for(int i=1;i<content.size();i++){
        if(content[i][1]!= ""){
            course * temp_input = new course();
            if( stoi(content[i][8]) > 1 ){
                temp_input->course_code = content[i][1];
                temp_input->p= stoi(content[i][8]);
                Ps.push_back(temp_input);
            }
        }
    }


    for(int i=13; i<ICs.size(); i++){
        ICs[i]->registered_stu = 40;
    }

    for(int i=13; i<Ps.size(); i++){
        Ps[i]->registered_stu = 40;
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
    return 0;

}