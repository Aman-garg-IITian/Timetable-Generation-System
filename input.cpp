#include "ds.h"

bool check_lab_id(string id_to_check){
    for(auto it: labs_room){
        if(it->id == id_to_check)
            return true;
    }
    return false;
}

bool take_input_csv(string fname){
    
    vector< vector<string> > content;
    vector<string> row;
    string line, word;
    unordered_map <string,int> dept_substr;
    
    for(int i=0;i<no_of_dept;i++){
        dept_substr[dept_code[i]]=i;
        DC * temp_obj = new DC(i);
        D_core.push_back((temp_obj));
    }

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
        cout<<"dbe";
        cout<<"file opened"<<endl;
        cout<<"#########";
    }
    else{
        cout<<"File not found!";
        return 0;
    }
    
    cout<<content.size();
    for(int i=1;i<content.size();i++){
        cout<<"&&&&&&&&&&&&";
        if(content[i][1]!= ""){
            course * temp_input = new course();
            if( content[i][3] =="Institute Core" ){
                temp_input->course_code = content[i][1];
                map_instructor[content[i][i]]=NULL;
                temp_input->l= stoi(content[i][6]);
                temp_input->p= stoi(content[i][8]);
                temp_input->t= stoi(content[i][7]);
                cout<<"^^^^^^^^^^^^";
                if(temp_input->p > 0){
                    if(content[i][13].size() == 0){
                        cout<<"###### lab id not provided for a course with p>0"<<endl;
                        cout<<"Course is = "<<temp_input->course_code<<endl;
                    }
                    else{
                        stringstream s(content[i][13]);
                        string str;
                        getline(s, str, ' ');
                        while(str.size() > 0){
                            if(check_lab_id(str) == false){
                                labsroom_c * new_lab = new labsroom_c();
                                new_lab->id = str;
                                labs_room.push_back(new_lab);
                            }
                            temp_input->labs.push_back(str);
                            getline(s, str, ' ');
                        }
                    }
                }

                ICs.push_back(temp_input);
            }
            else if(content[i][3] =="Departmental Core" ){
                temp_input->course_code = content[i][1];
                temp_input->l= stoi(content[i][6]);
                temp_input->p= stoi(content[i][8]);
                temp_input->t= stoi(content[i][7]);
                D_core[dept_substr[(temp_input->course_code).substr(0,2)]]->DCs.push_back(temp_input);
            }
        }
    }
    for(int i=13; i<ICs.size(); i++){
        ICs[i]->registered_stu = 40;
    }
    

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
    
    vector<instructor*> ins_added;
    for (int i = 1; i < content.size(); i++)
    {
        bool flag=1;
        for (int j = 0; j < ins_added.size(); j++)
        {
            if(ins_added[j]->ID==content[i][9]){
                map_instructor[content[i][1]]=ins_added[j];
                flag=0;
                break;
            }
        }
        if (flag)
        {
            instructor *temp_ins=new instructor();
            temp_ins->ID=content[i][9];
            temp_ins->name=content[i][10];
            map_instructor[content[i][1]]=temp_ins;
        }
        
        
    }
    

    int break_slot, dept_no, day_no;
    cout<<"ENTER DEPT NO AND BREAK SLOT and day no.: ";
    cin>>dept_no>>break_slot>> day_no ;
    course * break_name = new course();
    break_name->course_code = "test break";
    dept[dept_no]->table[day_no][break_slot] = make_pair(1,break_name);

    //taking input for OE slots.
    cout<<"ENTER NO OF SLOTS FOR OPEN ELECTIVES:   ";
    cin>>num_oe;
    for(int i(0); i<num_oe;i++){
        cout<<"Enter L T P for  "<<i+1<<" OE   :";
        cin>>oe_l>>oe_t>>oe_p;
        course* oe = new course();
        oe->l = oe_l;
        oe->t = oe_t;
        oe->p = oe_p;
        oe->course_code = "OE"+to_string(i+1);
        OEs.push_back(oe);

    }

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

}
bool take_input_labsroom(string fname){
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
        cout<<"file opened labsroom"<<endl;
    }
    else{
        cout<<"File not found!";
        return 0;
    }
    for(int i=1;i<content.size();i++){
        labsroom_c* object = new labsroom_c();
        object->id = content[i][0];
        object->capacity = stoi(content[i][1]); 
        object->department= content[i][0].substr(0,2);
        labs_room.push_back(object);
    }
    return 0;

}