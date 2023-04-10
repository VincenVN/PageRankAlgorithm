#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "DataStructure_Tramsform.h"
#include "Importing_data.h"
using namespace std;
using namespace std:: chrono;

int main(){
    // Importing directed graph data from the text file and transform it to the Transition Matrix stored in Array Representation Format
    string Network_file_name="p2p-Gnutella04.txt";
    auto _start = high_resolution_clock:: now();
    AR_TM S = DG_to_TM_AR(Network_file_name=Network_file_name);
    S = Sort_AR_TM(S=S);
    auto _stop = high_resolution_clock:: now();
    auto _duration = duration_cast<microseconds>(_stop-_start);
    cout << S.Network_name << endl;
    cout << "Number of Nodes = " << S.Node_num << " ";
    cout << "Number of Edges = " << S.Edge_num << endl;
    cout << "time taken to transform the directed graph to the adjacency matrix = " << _duration.count()*1e-6 << " seconds" << endl;

    // Multiply the Transition Matrix S with the given initial distribution v_0 to calculate the distribution of the step 1 
    vector<float> v_0(S.Node_num, 1.0/S.Node_num);
    cout << "v_0 =" << endl;
    cout << "{";
    for(int i=0; i<10; i++){
        cout << v_0[i] << ", ";
    }
    cout << "...}" << endl;

    auto Multi_start = high_resolution_clock:: now();
    vector<float> v_1 = Naive_Matrix_Vector_Multi_AR_TM(S, v_0);
    auto Multi_stop = high_resolution_clock:: now();

    cout << "(v_0^T)*S =" << endl;
    cout << "{";
    for(int i=0; i<10; i++){
        cout << v_1[i] << ", ";
    }
    cout << "...}" << endl;
    auto Multi_duration = duration_cast<microseconds>(Multi_stop-Multi_start);
    cout << "time taken to multiply the initial distribution vector v_0 and the transition matrix S in AR format = " << Multi_duration.count() << " microseconds" << endl;

    cout << endl;

    CSRF_TM S_CSRF = AR_TM_to_CSRF_TM(S);
    Multi_start = high_resolution_clock:: now();
    v_1 = Naive_Matrix_Vector_Multi_CSRF_TM(S_CSRF, v_0);
    Multi_stop = high_resolution_clock:: now();

    cout << "(v_0^T)*S =" << endl;
    cout << "{";
    for(int i=0; i<10; i++){
        cout << v_1[i] << ", ";
    }
    cout << "...}" << endl;
    Multi_duration = duration_cast<microseconds>(Multi_stop-Multi_start);
    cout << "time taken to multiply the initial distribution vector v_0 and the transition matrix S in CSR format = " << Multi_duration.count() << " microseconds" << endl;

    return 0;
}