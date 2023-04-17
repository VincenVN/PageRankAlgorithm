#ifndef CSRFSMV_H
#define CSRFSMV_H
#include <vector>
#include <string>
using namespace std;

// Compressed Sparse Row Format for the Transition Matrix
struct CSRF_TM
{
    // the index of the first non-zero element of each row
    vector<int> NZI_first;
    // the column index of each non-zero element
    vector<int> col;
    // the number of the Nodes of the Network
    int Node_num;
    // the number of the Edges of the Network
    int Edge_num;
    // the name of the network
    string Network_name;
};

vector<float> Naive_Matrix_Vector_Multi_CSRF_TM(CSRF_TM S, vector<float> v_0){
    vector<float> v_1(S.Node_num, 0.0);
    int j = 0;

    int *NZI_first_i = S.NZI_first.data();
    int *col_k = S.col.data();
    float *v_0_i = v_0.data();
    float *v_1_j = v_1.data();

    for(int i=0; i<(S.Node_num-1); i++){
        j = 0;
        v_1_j = v_1.data();

        int r = (*(NZI_first_i+1)-*(NZI_first_i));

        for(int l=0; l<r; l++){
            v_1_j += (*col_k - j);
            j = (*col_k);
            *v_1_j += (float)(*v_0_i)/r;
            col_k++;
        }

        NZI_first_i++;
        v_0_i++;
    }

    j = 0;
    v_1_j = v_1.data();

    int r = (S.Edge_num - *NZI_first_i);

    for(int l=0; l<r; l++){
        v_1_j += (*col_k - j);
        j = (*col_k);
        *v_1_j += (*v_0_i)/r;
        col_k++;
    }

    return v_1;
}

#endif