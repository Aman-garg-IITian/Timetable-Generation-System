#include "ds.h"

string getCurrentTimestamp()
{
    std::time_t now = std::time(nullptr);
    char timestamp[100];
    std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return timestamp;
}

void logMessage(const std::string &message)
{
    std::ofstream logfile("log.txt", std::ios::app);
    if (logfile.is_open())
    {
        std::string timestamp = getCurrentTimestamp();
        logfile << timestamp << ": " << message << std::endl;
        logfile.close();
    }
    else
    {
        std::cout << "Failed to open log file." << std::endl;
    }
}

int main(){
    if(take_input_classroom("Classroom.csv")){
        cout<<"CLASSROOMS READ" <<endl;
        logMessage("Classrooms Data Read Successfull");
    }

    for(int i=1;i<=4;i++){
        cout<<"code start"<<endl;
        string s="Code Started for year "+ to_string(i);
        logMessage(s);
        if(take_input_csv("final.csv", i,"testing.csv"))
            cout<<"INPUT TAKEN"<<endl;
        s="Read Input Successful for year "+ to_string(i);
        logMessage(s);
        // if(take_input_labsroom("Labsroom.csv"))
        //     cout<<"Labs input taken"<<endl;  
        allocate_ic(ICs);
        s="ICs Allocated for year "+ to_string(i);
        logMessage(s);
        allocate_classroom_same(ICs);
        s="Classrooms Allocated for ICs for year "+ to_string(i);
        logMessage(s);

        cout<<"allocatung practicals now"<<endl;
        allocate_prac_IC(ICs);
        s="Practicals Allocated for year "+ to_string(i);
        logMessage(s);
        // allocate_ic(OEs);
        // allocate_classroom_same(OEs);
        cout<<"done with practicals"<<endl;
        allocate_dc(D_core);
        s="DC Courses Allocated for year "+ to_string(i);
        logMessage(s);
        vector<DC*> :: iterator itr;
        for(itr = D_core.begin(); itr != D_core.end(); itr++){
            allocate_classroom_same((*itr)->DCs);
        }
        cout<<"Dc lecture alloted"<<endl;
        allocate_prac_dc(D_core);
        s="DC Practicals Allocated for year "+ to_string(i);
        logMessage(s);
        debug_print();
        classroom_print();
        debug_print_csv(i);
        s="Printed Output in CSV for year "+ to_string(i);
        logMessage(s);
        ICs.clear();
        D_core.clear();
    } 
    classroom_print_csv();    
}