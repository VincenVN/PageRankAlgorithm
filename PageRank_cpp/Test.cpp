#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/types.h>
#include <chrono>
#include "DataStructure_Tramsform.h"
#include "Importing_data.h"
using namespace std;
using namespace std:: chrono;

void Test_algorithms(string Network_file_name){
    ofstream mycsv_out;
    ifstream mycsv_in;
    mycsv_out.open("./Testing_Result_New.csv");
    mycsv_in.open("./Testing_Result.csv");

    string line;

    while(!mycsv_in.eof()){
        getline(mycsv_in, line);
        mycsv_out << line << "\n";
    }

    mycsv_in.close();
    cout << "Start" << endl;

    // Importing directed graph data from the text file and transform it to the Transition Matrix stored in Array Representation Format
    auto _start = high_resolution_clock:: now();
    AR_TM S = DG_to_TM_AR(Network_file_name);
    cout << "Data imported" << endl;

    S = Sort_AR_TM(S);
    cout << "Data sorted" << endl;
    auto _stop = high_resolution_clock:: now();
    auto _duration = duration_cast<microseconds>(_stop-_start);
    mycsv_out << S.Network_name << ",";
    mycsv_out << S.Node_num << ",";
    mycsv_out << S.Edge_num << ",";

    // Multiply the Transition Matrix S with the given initial distribution v_0 to calculate the distribution of the step 1 
    vector<float> v_0(S.Node_num, 1.0/S.Node_num);
    
    auto Multi_start = high_resolution_clock:: now();
    vector<float> v_1 = Naive_Matrix_Vector_Multi_AR_TM(S, v_0);
    auto Multi_stop = high_resolution_clock:: now();
    auto Multi_duration = duration_cast<microseconds>(Multi_stop-Multi_start);
    cout << "AR done" << endl;
    mycsv_out << Multi_duration.count() << ",";


    CSRF_TM S_CSRF = AR_TM_to_CSRF_TM(S);
    Multi_start = high_resolution_clock:: now();
    v_1 = Naive_Matrix_Vector_Multi_CSRF_TM(S_CSRF, v_0);
    Multi_stop = high_resolution_clock:: now();
    Multi_duration = duration_cast<microseconds>(Multi_stop-Multi_start);
    cout << "All done" << endl;
    mycsv_out << Multi_duration.count();

    mycsv_out.close();

    //removing the old data file
    remove("./Testing_Result.csv");
    
    // renaming the updated data file with the old data file name
    rename("./Testing_Result_New.csv", "Testing_Result.csv");
    return;
}

int main(){
    // Test_algorithms("p2p-Gnutella08.txt");
    DIR *dr;
    struct dirent *en;
    dr = opendir("./Directed_Graphs");
    if(dr){
        while((en=readdir(dr)) != NULL){
            string Network_file_name = en->d_name;
            if(Network_file_name[0]!='.'){
                cout << Network_file_name << endl;
                Test_algorithms(Network_file_name);
            }
        }

        closedir(dr);
    }
    return 0;
}