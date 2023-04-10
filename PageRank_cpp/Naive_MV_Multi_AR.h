#ifndef ARSMV_H
#define ARSMV_H
#include <vector>
#include <string>
using namespace std;

// Array Representation Format for the Transition Matrix
struct AR_TM
{
    // the column index of each non-zero element
    vector<int> col;
    // the row index of each non-zero element
    vector<int> row;
    // the number of the non-zero value of each row
    vector<int> NZ_num;
    // the number of the Nodes of the network
    int Node_num;
    // the number of the Edges of the network
    int Edge_num;
    // the name of the network
    string Network_name;
};

AR_TM Sort_AR_TM(AR_TM S){
    bool update = true;
    int L = 0;
    while (update && L < S.Edge_num * S.Edge_num){
        update = false;
        vector<int> ::iterator row_k = S.row.begin();
        vector<int> ::iterator col_k = S.col.begin();
        for(int k=0; k<(S.Edge_num-1); k++){
            if(((*row_k) > (*(row_k+1))) || (((*row_k) == (*(row_k+1))) && ((*col_k) > (*(col_k+1))))){
                int Col_vals[2] = {0, 0};
                int Row_vals[2] = {0, 0};
                Col_vals[0] = *(col_k+1);
                Col_vals[1] = *col_k;
                Row_vals[0] = *(row_k+1);
                Row_vals[1] = *row_k;
                (*col_k) = Col_vals[0];
                (*row_k) = Row_vals[0];
                (*(col_k+1)) = Col_vals[1];
                (*(row_k+1)) = Row_vals[1];
                update = true;
            }
            col_k++;
            row_k++;
        }
        L++;
    }
    return S;
}

vector<float> Naive_Matrix_Vector_Multi_AR_TM(AR_TM S, vector<float> v_0){
    vector<float> v_1(S.Node_num, 0);
    int *row_k = S.row.data();
    int *col_k = S.col.data();
    float *v_1_j = v_1.data();
    float *v_0_i = v_0.data();
    int *NZ_num_i = S.NZ_num.data();
    int i=0;
    int j=0;
    for(int k=0; k<(S.Edge_num); k++){
        if(i!=(*row_k)){
            v_1_j = v_1.data();
            j = 0;
            v_0_i += ((*row_k) - i);
            NZ_num_i += ((*row_k) - i);
            i = (*row_k);
        }
        v_1_j += (*col_k - j);
        (*v_1_j) = (*v_1_j) + (*v_0_i)/(*NZ_num_i);
        j = (*col_k);
        row_k ++;
        col_k ++;
    }
    return v_1;
}

#endif