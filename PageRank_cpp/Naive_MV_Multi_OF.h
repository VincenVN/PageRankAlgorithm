#include <vector>
#include <string>
using namespace std;

struct OF_TM{
    // the adjacency Matrix A
    vector< vector<bool> > A;
    // the number of the non zero elements of each row
    vector<int> NZ_num;
    // the number of the Nodes of the network
    int Node_num; 
    // the number of the Edges of the network
    int Edge_num;
    // the name of the network
    string Network_name;
};

// the Naive Matrix Vector Multiplication for the Ordinary Transition matrix
vector<float> Naive_Matrix_Vector_Multi_OF_TM(OF_TM S, vector<float> v_0){
    vector<float> v_1(S.Node_num, 0);
    vector<bool> *A_i = S.A.data();
    float *v_0_i = v_0.data();
    int *S_NZ_num_i = S.NZ_num.data();
    for(int i=0; i<(S.Node_num); i++){
        float *v_1_j = v_1.data();
        for(vector<bool> ::iterator A_ij = (*A_i).begin(); A_ij!=(*A_i).end(); A_ij++){
            if(*A_ij){
                (*v_1_j) += (float)((*v_0_i)/(*S_NZ_num_i));
            }
            v_1_j++;
        }
        v_0_i++;
        A_i++;
        S_NZ_num_i++;
    }
    return v_1;
}