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

// Partition function for QuickSort
int partition(AR_TM &S, int low, int high) {
    int pivot_row = S.row[low];
    int pivot_col = S.col[low];
    int i = low + 1;
    int j = high;

    while (i <= j) {
        while (i <= j && (S.row[i] < pivot_row || (S.row[i] == pivot_row && S.col[i] < pivot_col))) {
            i++;
        }

        while (i <= j && (S.row[j] > pivot_row || (S.row[j] == pivot_row && S.col[j] > pivot_col))) {
            j--;
        }

        if (i < j) {
            swap(S.row[i], S.row[j]);
            swap(S.col[i], S.col[j]);
            i++;
            j--;
        }
    }

    swap(S.row[low], S.row[j]);
    swap(S.col[low], S.col[j]);

    return j;
}

// QuickSort function for sorting AR_TM
void quickSort(AR_TM &S, int low, int high) {
    if (low < high) {
        int pivot = partition(S, low, high);
        quickSort(S, low, pivot - 1);
        quickSort(S, pivot + 1, high);
    }
}

// Sort the Array Representation format Dataset with QuickSort function
AR_TM Sort_AR_TM(AR_TM S){
    int low = 0;
    int high = S.Edge_num - 1;
    quickSort(S, low, high);
    return S;
}

// Sort the Array Representation format Dataset with Bubble Sort function
AR_TM Sort_AR_TM_Bubble(AR_TM S){
    bool update = true;
    int L = 0;
    while (update && L < S.Edge_num * S.Edge_num){
        update = false;
        for(int k=0; k<(S.Edge_num-1); k++){
            if((S.row[k] > S.row[k+1]) || ((S.row[k] == S.row[k+1]) && (S.col[k] > S.col[k+1]))){
                swap(S.col[k], S.col[k+1]);
                swap(S.row[k], S.row[k+1]);
                update = true;
            }
        }
        L++;
    }
    return S;
}

// Naive Matrix Vector multiplication for the Transition matrix stored in Array Representation format.  
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
        (*v_1_j) = (*v_1_j) + (float)(*v_0_i)/(*NZ_num_i);
        j = (*col_k);
        row_k ++;
        col_k ++;
    }
    return v_1;
}

#endif